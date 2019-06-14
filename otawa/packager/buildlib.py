import base
from base import *
import datetime
import imp
import os
import os.path
import pack
from pack import *
import platform
import re
import shutil
import subprocess
import sys
import tempfile

OS_DEFS = base.Definitions("OS_DEFS",
"""
# identify the OS
UNAME := $(shell uname -o)
OS = unix
ifeq ($(UNAME), GNU/Linux)
OS = linux
endif
ifeq ($(UNAME), Msys)
OS = mingw
export CC = gcc
endif

ifndef TARGET_OS
TARGET_OS=$(OS)
endif
"""
)

PATH_DEFS = base.Definitions("PATH_DEFS",
"""
ifeq ($(OS),mingw)
path_win2ux=$(subst c:,/c,$(subst \,/,$(1)))
else
path_win2ux=$(1)
endif
""", [OS_DEFS])


CORE_DEFS = base.Definitions("CORE_DEFS",
"""
# compute max number of jobs
ifdef NO_JOBS
P_JOBS=
else
ifeq ($(OS),linux)
P_CORES=$(shell cat /proc/cpuinfo | grep processor | wc -l)
else
P_CORES=1
endif
ifeq ($(P_CORES),1)
P_JOBS=
else
P_JOBS=-j $(P_CORES)
endif
endif
""",
[ OS_DEFS ]
)

CMAKE_DEFS = base.Definitions("CMAKE_DEFS",
"""
# CMake flags
ifeq ($(OS),mingw)
CMAKE_FLAGS=-G "MSYS Makefiles"
else
CMAKE_FLAGS=
endif
""",
[OS_DEFS]
)


ID_RE = re.compile("@@(\w+)@@")
def replace(text, dict):
	""" Perform replacement of variable from the dictionnary in the
	given text. Variable must be put between double "@@ID@@"."""
	res = ""
	last = 0
	for match in ID_RE.finditer(text):
		id = match.group(1)
		if dict.has_key(id):
			rep = dict[id]
		else:
			rep = ""
		res = res + text[last:match.start()] + rep
		last = match.end()
	res = res + text[last:]
	return res

class CVSDownloader(pack.Downloader):
	"""Downloader using CVS checkout."""
	root = None
	version = None

	def __init__(self, root):
		self.root = root

	def proceed(self, mod, env):
		if os.path.exists(mod.name):
			success = env.execute("cd %s; cvs update -d" % mod.name)

		else:
			root = self.root
			opts = ""
			if self.version:
				opts = "%s -r %s" % (opts, self.version)
			if env.user:
				root = root.replace("anonymous", env.user)
			env.execute("cvs -d %s co %s %s" % (root, opts, mod.name))


class BootstrapSetup(pack.Setup):
	"""Setup for autotools.
	Call the bootstrap script and then perform the configure."""
	flags = None

	def __init__(self, flags = ""):
		self.flags = flags

	def gen(self, mod, env):
		return [
			"./bootstrap",
			"./configure %s --prefix=$(PREFIX)" % self.flags
		]

CMAKE_MATRIX = {
	(base.OS_LINUX_64, base.OS_LINUX_32): 	"linux-32",
	(base.OS_LINUX_64, base.OS_WINDOWS_32): "win32",
	(base.OS_LINUX_64, base.OS_WINDOWS_64): "win64"
}
class CMakeSetup(pack.Maker):
	"""Setup for CMake."""
	prefix = None
	opts = None

	def __init__(self, prefix = None, opts = ""):
		self.prefix = prefix
		self.opts = opts

	def get_defs(self, mod, pack):
		return [CMAKE_DEFS]

	def gen(self, mod, env):
		opts = self.opts
		if env.is_cross():
			opts = "%s -DCMAKE_TOOLCHAIN_FILE=%s/cross/%s.cmake" % (opts, env.get_base_dir(), CMAKE_MATRIX[(env.get_host_arch(), env.get_target_arch())])
		if self.prefix:
			opts = "%s -DCMAKE_INSTALL_PREFIX:PATH=%s" % (opts, self.prefix)
		if env.is_win():
			opts = "%s -G \"MSYS Makefiles\"" % opts
		return [ "cmake . %s" % opts ]


CC_MATRIX = {
	(base.OS_LINUX_64, base.OS_LINUX_32): 	("cc -m32", "linux-32"),
	(base.OS_LINUX_64, base.OS_WINDOWS_32):	("i686-w64-mingw32-gcc", "win32"),
	(base.OS_LINUX_64, base.OS_WINDOWS_64): ("x86_64-w64-mingw32-gcc", "win64")
}

def config_linux_64_to_32(env):
	env.ensure_tmp_link()
	env.ensure_install("cross/linux-32/ocaml", "%s/private/ocaml-linux-64-32.tar.bz2" % IMPORT_ROOT)
	env.ensure_install("cross/linux-32/xml", "%s/private/xml-linux-x86.tar.bz2" % IMPORT_ROOT)
	os.environ['PATH'] = "/tmp/otawa-dist/cross/linux-32/ocaml/bin/:%s" % os.environ['PATH']
	if not os.environ.has_key('LD_LIBRARY_PATH'):
		os.environ['LD_LIBRARY_PATH'] = ''
	os.environ['LD_LIBRARY_PATH'] = "/tmp/otawa-dist/cross/linux-32/xml/lib/:%s" % os.environ['LD_LIBRARY_PATH']
	os.environ['CFLAGS'] = '-m32'

def config_no(env):
	pass

CONFIG_MATRIX = {
	(base.OS_LINUX_64, base.OS_LINUX_32): 	config_linux_64_to_32,
	(base.OS_LINUX_64, base.OS_WINDOWS_32):	config_no,
	(base.OS_LINUX_64, base.OS_WINDOWS_64): config_no
}

class MakeMaker(pack.Maker):
	"""Simple maker: make"""

	def __init__(self, flags = "", makefile = None, nojob = False, chroot = False, goal = "all"):
		self.flags = flags
		self.makefile = makefile
		self.nojob = nojob
		self.chroot = chroot
		self.goal = goal

	def get_defs(self, mod, pack):
		return [CORE_DEFS]

	def make(self, mod, env):
		cc = ""
		prefix = ""
		flags = self.flags
		if env.is_cross():
			c, dir = CC_MATRIX[(env.get_host_arch(), env.get_target_arch())]
			if self.chroot:
				prefix = "export PATH=%s/cross/%s/chroot/usr/bin:$$PATH; export LD_LIBRARY_PATH=%s/cross/%s/chroot/usr/lib:$$LD_LIBRARY_PATH; " % (
					env.get_base_dir(), dir, env.get_base_dir(), dir)
			else:
				cc = "CC='%s'" % c
			f = CONFIG_MATRIX[(env.get_host_arch(), env.get_target_arch())]
			f(env);
		if self.makefile:
			flags = "-f %s %s" % (self.makefile, flags)
		if not self.nojob:
			flags = "$(P_JOBS) %s" % flags
		return "%smake %s %s %s" % (prefix, flags, cc, self.goal)

	def gen(self, mod, env):
		return [ self.make(mod, env) ]


class MakeInstaller(pack.Installer):
	"""Simple installer with make."""
	flags = None
	goal = None

	def __init__(self, flags = "", goal = "install"):
		self.flags = flags
		self.goal = goal

	def get_defs(self, mod, pack):
		return [CORE_DEFS]

	def gen(self, mod, env):
		return [ "make %s %s" % (self.flags, self.goal) ]

class CopyInstaller(pack.Installer):
	"""Installer that copies files.
	Files are relative to the current module while target is relative
	to the installation directory."""
	files = None
	target = None

	def __init__(self, target = "", files = ""):
		self.target = target
		self.files = files

	def gen(self, mod, env):
		return [
			"mkdir -p $(PREFIX)/%s" % self.target,
			"cp %s $(PREFIX)/%s" % (self.files, self.target)
		]


class MercurialDownloader(pack.Downloader):
	"""Downloader using the Mercurial version controler.

	Arguments:
	* target: archive to download from,
	* dev_target: development archive to download from
	* interactive: to run hg in interactive mode (usually to enter user/password).

	Parameters:
	* <mod_name>-REPO: 		repository to use,
	* <mod_name>-BRANCH:	branch to use (replaced final trunk in repository),
	* <mod_name>-REV:		revision to check out.
	"""
	target = None
	dev_target = None

	def __init__(self, target, dev_target = None, interactive = False):
		self.target = target
		if dev_target:
			self.dev_target = dev_target
		else:
			self.dev_target = target
		self.interactive = interactive

	def proceed(self, mod, env):
		rev = env.get("%s-REV" % mod.name)
		if rev:
			flagrev = "--rev {}".format(rev)
			env.info("Cloning specific revision: {}".format(rev))
		else:
			flagrev = ""
		if os.path.exists(mod.name):
			env.info("module %s already downloaded" % mod.name)
		elif env.user and not self.public:
			env.execute("hg clone %s %s %s" % (flagrev, self.dev_target, mod.name))
		else:
			repo = env.get("%s-REPO" % mod.name, self.target)
			branch = env.get("%s-BRANCH" % mod.name)
			if branch:
				if repo.endswith("/trunk"):
					repo = "%s/%s" % (repo[0:-6], branch)
				else:
					raise base.BuildException("branch %s used with repo without trunk: %s" % (repo, branch))

			env.execute("hg clone %s %s %s" % (flagrev, repo, mod.name), interactive = self.interactive)


class BazaarDownloader(pack.Downloader):
		"""Downloader using the bazaar version controler.
		target: archive to download from
		dev_target: development archive to donwload from
		public: public read-only archive
		"""
		target = None
		dev_target = None
		public = None

		def __init__(self, target, dev_target = None, public = False):
			self.public = public
			self.target = target
			if dev_target:
				self.dev_target = dev_target
			else:
				self.dev_target = target

		def proceed(self, mod, env):
			if os.path.exists(mod.name):
				env.info("module %s already downloaded" % mod.name)
			elif env.user and not self.public:
				env.execute("bzr branch %s %s" % (self.dev_target, mod.name))
			else:
				env.execute("bzr export %s %s" % (mod.name, self.target))


class GitDownloader(pack.Downloader):
		"""Downloader using the git version controler.
		target: archive to download from
		dev_target: development archive to donwload from
		public: public read-only archive
		"""
		target = None
		dev_target = None
		public = None

		def __init__(self, target, dev_target = None, public = False):
			self.public = public
			self.target = target
			if dev_target:
				self.dev_target = dev_target
			else:
				self.dev_target = target

		def proceed(self, mod, env):
			if os.path.exists(mod.name):
				env.info("module %s already downloaded" % mod.name)
			elif env.user and not self.public:
				env.execute("git clone %s %s" % (self.dev_target, mod.name))
			else:
				env.execute("git clone %s %s" % (self.target, mod.name))

class ArchiveDownloader(pack.Downloader):
	"""Downloader for an archive, possibly in a distant location.
	Supported archive includes .tar, .tar.gz, .tar.bz2, .zip
	target: package to download
	dir: rename the directory"""
	target = None
	dir = None

	def __init__(self, target, dir = None):
		self.target = target
		self.dir = dir

	def proceed(self, mod, env):
		path = self.target

		# check for existence
		if os.path.exists(mod.name):
			env.info("module %s already downloaded" % mod.name)
			return

		# get distant archive
		if env.is_distant(self.target):
			env.execute("wget %s" % self.target)
			path = self.target[self.target.rfind("/") + 1 : ]
			arc = path
		else:
			arc = None

		# process the archive
		if path.endswith(".zip"):
			env.execute("unzip %s" % env.to_unix_path(path))
			path = path[:-4]
		elif path.endswith(".tar.gz") or path.endswith(".tgz"):
			env.execute("tar xvfz %s" % env.to_unix_path(path))
			if path.endswith(".tgz"):
				path = path[:-4]
			else:
				path = path[:-7]
		elif path.endswith(".tar.bz2"):
			env.execute("tar xvfj %s" % env.to_unix_path(path))
			path = path[:-8]
		else:
			env.error("unknown archive type")

		# rename if required
		if self.dir:
			path = self.dir
		else:
			idx = path.rfind("/")
			if idx >= 0:
				path = path[idx + 1 :]
		if path <> mod.name:
			os.rename(path, mod.name)

		# cleanup the archive
		if arc:
			env.remove(arc)

class PatchDownloader(pack.Downloader):
	"""Downloader including a patch application and, possibly, a sub-setup.
	patch: patch to apply
	download: downloader to get the sources"""
	patch = None
	download = None

	def __init__(self, patch, download):
		self.patch = patch
		self.download = download

	def proceed(self, mod, env):

		# perform sub-download
		self.download.proceed(mod, env)

		# apply patch
		file = tempfile.NamedTemporaryFile()
		path = os.path.abspath(file.name)
		file.write(self.patch)
		file.flush()
		env.execute("cd %s; patch -p1 < %s" % (mod.name, path))
		file.close()


class CommandPatch(pack.Downloader):
	"""Perform a download and then some commands to do a patch"""
	cmds = None
	donwloader = None

	def __init__(self, cmds, downloader = pack.NULL_DOWNLOADER):
		self.cmds = cmds
		self.downloader = downloader

	def proceed(self, mod, env):

		# perform sub-download
		self.downloader.proceed(mod, env)

		# apply patch
		pwd = os.getcwd()
		os.chdir(mod.name)
		for cmd in self.cmds:
			env.execute("cd %s; %s" % (mod.name, cmd))
		os.chdir(pwd)


class CopyDownloader(pack.Downloader):
	"""Build a module by copying files."""
	files = None

	def __init__(self, files = []):
		self.files = files

	def proceed(self, mod, env):
		if os.path.exists(mod.name):
			try:
				shutil.rmtree(mod.name)
			except OSError,e:
				raise base.BuildException("cannot cleanup %s: %s" % (mod.name, e))
		try:
			os.mkdir(mod.name)
		except OSError,e:
			raise base.BuildException("cannot create directory %s: %s" % (mod.name, e))
		for file in self.files:
			try:
				spath = env.to_host_path(file)
				tpath = os.path.join(mod.name, os.path.basename(file))
				if os.path.isdir(spath):
					shutil.copytree(spath, tpath)
				else:
					shutil.copy(spath, tpath)
			except shutil.Error, e:
				raise base.BuildException("cannot copy %s to %s: %s" % (file, mod.name, e))
			except OSError, e:
				raise base.BuildException("cannot copy %s to %s: %s" % (file, mod.name, e))


class CommandSetup(pack.Setup):
	"""A setup one or several Unix commands.
	cmds: list of commands"""
	cmds = None

	def __init__(self, cmds):
		self.cmds = cmds

	def gen(self, mod, env):
		return self.cmds


class CustomMaker(pack.Maker):
	"""Maker with custom command.
	cmds: commands to execute"""
	cmds = None

	def __init__(self, cmds):
		self.cmds = cmds

	def gen(self, mod, env):
		return self.cmds


class Copy(pack.Addon):
	"""File copying add-on."""
	path = None
	rename = None

	def __init__(self, path, rename = None):
		"""Build the copy add-on of a file.
		path: path of file or directory to copy
			(relative path is relative to CWD/packages)
		rename: possible renaming of the file."""
		self.path = path
		self.rename = rename

	def makeCommand(self, pack):
		s = self.path
		if not os.path.isabs(s):
			s = os.path.join(os.getcwd(), "packages", s)
		t = pack.path
		if self.rename != None:
			t = os.path.join(t, self.rename)
		return "cp -R %s %s" % (s, t)

	def onSourceDist(self, pack):
		pack.env.execute(self.makeCommand(pack))

	def onBinDist(self, pack):
		pack.env.execute(self.makeCommand(pack))


class Rebase(pack.Addon):
	"""Move libraries from normal installation directory to another."""
	files = None
	dir = None

	def __init__(self, files, dir):
		"""Build the rebase add-on of a file.
		files: files or directories to move.
		dir: directory to copy to."""
		self.files = files
		self.dir = dir

	def makeCommand(self, pack):

		# get destination directory
		if not os.path.isabs(self.dir):
			adir = os.path.join(pack.path, self.dir)
		else:
			adir = self.dir

		# make the commands
		afiles = " ".join([os.path.join(pack.path, f) for f in self.files])
		return [
			"cp -R %s %s" % (afiles, adir),
			"rm -rf %s" % afiles
		]

	def execute(self, pack):
		for cmd in self.makeCommand(pack):
			pack.env.execute(cmd)

	def onSourceDist(self, pack):
		self.execute(pack)

	def onBinDist(self, pack):
		self.execute(pack)


class OnlySource(pack.Addon):
	"""Add-on working only for source distribution."""
	addon = None

	def __init__(self, addon):
		self.addon = addon

	def onSourceDist(self, pack):
		self.addon.onSourceDist(pack)

	def onBinDist(self, pack):
		pass


class OnlyDist(pack.Addon):
	"""Add-on working only for binary distribution."""
	addon = None

	def __init__(self, addon):
		self.addon = addon

	def onBinDist(self, pack):
		self.addon.onSourceDist(pack)

	def onSourceDist(self, pack):
		pass

# to maintain ascendent compatibility
#Package = pack.Package
#Module = pack.Module

