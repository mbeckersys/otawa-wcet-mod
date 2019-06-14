"""Contains basic classes for build system."""
import imp
import os
import platform
import shutil
import subprocess
import sys

VERSION = "1.3"
OS_LINUX_32 = "linux-x86"
OS_LINUX_64 = "linux-x86_64"
OS_WINDOWS_32 = "win32"
OS_WINDOWS_64 = "win64"
OS_DARWIN_64 = "darwin-x86_64"
IMPORT_ROOT = "http://www.irit.fr/recherches/ARCHI/MARCH/OTAWA"

BUILD_DEV = 1
BUILD_BIN = 2
BUILD_TYPES = [
	"all",
	"dev",
	"bin",
	"all"
]

# (host, target)
KNOWN_CROSSES = [
	(OS_LINUX_64, OS_LINUX_32),
	(OS_LINUX_64, OS_WINDOWS_32),
	(OS_LINUX_64, OS_WINDOWS_64)
]

KNOWN_CONFIGS = [
	("Linux", "i686", 32, OS_LINUX_32),
	("Linux", "i686", 64, OS_LINUX_64),
	("Linux", "x86_64", 32, OS_LINUX_32),	# chrooted
	("Linux", "x86_64", 64, OS_LINUX_64),
	("Windows", None, 32, OS_WINDOWS_32),
	("Windows", None, 64, OS_WINDOWS_64),
	("Darwin", "x86_64", 64, OS_DARWIN_64)
]

DISTANT_SCHEMES = [
	"http:",
	"https:",
	"ftp:",
	"ftps:"
]

class BuildException(Exception):
	"""Exception thrown when a build error arise."""

	def __init__(self, msg):
		Exception.__init__(self, msg)


class Env:
	"""An execution environment.
	Provides basic services like communication with user."""
	verbose = False
	user = None
	log = sys.stderr
	base_dir = None
	cores = None
	params = None
	last_action = None
	rewrite_action = False
	host_arch = None
	target_arch = None
	cwd = None

	def __init__(self):
		self.base_dir = os.getcwd()
		self.params = { }
		self.host_arch = self.compute_host_arch()
		self.target_arch = self.host_arch
		self.cwd = os.getcwd()

	def set(self, id, val):
		"""Set a parameter value."""
		self.params[id] = val

	def get(self, id, default = None):
		"""Get a parameter value."""
		try:
			return self.params[id]
		except KeyError, e:
			return default

	def get_base_dir(self):
		"""Get the directory containing the installation as an absolute path."""
		return self.base_dir
	
	def get_host_arch(self):
		"""Return host architecture, one of OS_XXX constants."""
		return self.host_arch
	
	def get_target_arch(self):
		"""Return the target architecture, one of OS_XXX constants."""
		return self.target_arch

	def get_cross_pair(self):
		return (self.host_arch, self.target_arch)

	def is_cross(self):
		"""Test if cros-compilation is used."""
		return self.host_arch <> self.target_arch

	def setParam(self, id, val):
		"""Set a parameter."""
		self.params[id] = val
	
	def getParam(self, id):
		"""Return the value of a parameter. None if the parameter is not
		undefined."""
		if self.params.has_key(id):
			return self.params[id]
		else:
			return None

	def error(self, msg):
		""" Display an error message."""
		sys.stderr.write("ERROR: %s\n" % msg)
		sys.exit(1)

	def getCores(self):
		"""Return the number of cores."""
		if self.cores == None:
			if platform.system() != "Linux":
				self.cores = 1
			else:
				self.cores = 0
				f = open("/proc/cpuinfo")
				for l in f.xreadlines():
					if l.find("processor") >= 0:
						self.cores = self.cores + 1
		return self.cores

	def info(self, msg):
		"""Display information to the user."""
		sys.stderr.write("INFO: " + msg + "\n")
		sys.stderr.flush()

	def warn(self, msg):
		"""Display warning to the user."""
		sys.stderr.write("WARNING: %s\n" % msg)


	def compute_host_arch(self):
		"""Build the architecture string of the current system."""
		
		# prepare information
		system = platform.system()
		is_64bits = sys.maxint > 2**32
		mach = platform.machine()
		if is_64bits:
			size = 64 
		else:
			size = 32
		
		# select the configuration
		for s, m, sz, a in KNOWN_CONFIGS:
			if s and system != s:
				continue
			if m and mach != m:
				continue
			if sz and size != sz:
				continue
			return a
		
		# not found
		self.error("unknown platform: %s %s %s" % (system, mach, size))

	def saveFile(self, path, content):
		"""Save the given content in the file matching the path.
		If there is an error, a message is displayed
		and the application stopped."""
		try:
			f = open(path, "w")
			f.write(content)
			f.close()
		except IOError, e:
			self.error("can not save %s: %s" % (path, e))

	def loadFile(self, path):
		"""Load and return a content from the file matching the path.
		If there is an error, a message is displayed
		and the application stopped."""

		try:
			f = open(path)
			content = f.read()
			f.close()
			return content
		except IOError, e:
			self.error("can not load file %s: %s" % (path, e))

	def saveList(self, path, list):
		"""Save a list in the file at the given path.
		If there is an error, a message is displayed
		and the application stopped."""
		self.saveFile(path, "\n".join(list))

	def loadList(self, path):
		"""Load a list from the file at the given path.
		If there is an error, a message is displayed
		and the application stopped."""
		content = self.loadFile(path)
		return content.split()

	def loadModuleDescriptor(self, name, path, env, pack = None):
		"""Load the descriptor of a module.
		If an error is caught, display it and stop the program."""
		path = os.path.join(self.cwd, "modules", "%s.py" % name)
		try:
			pmod = imp.load_source(name, path)
			return pmod.get(path, env, pack)
		except BaseException, e:
			env.error("can not find descriptor for %s (%s)" % (name, e))

	def makedir(self, path):
		"""Build a hierarchy of directories matching the given path.
		If an error is caught, display it and stop the program."""
		try:
			os.makedirs(path)
		except OSError, e:
			self.error("can not create directory %s (%s)" % (path, e))

	def remove(self, path):
		"""Remove the object pointed by the path whatever its type:
		directory, file or symbolic link.
		If an error is caught, display it and stop the program."""
		
		try:
			if os.path.isdir(path):
				shutil.rmtree(path)
			else:
				os.unlink(path)
		except OSError, e:
			self.error("can not remove %s (%s)" % (path, e))

	def setLog(self, log):
		self.log = log

	def write(self, msg):
		"""Write a message for user on the current display
		and in the log."""
		self.log.write(msg)
		self.log.flush()
		if self.log != sys.stderr:
			sys.stdout.write(msg)
			sys.stdout.flush()

	def do(self, msg):
		"""Display message for starting an action."""
		self.write(msg + " ... ")
		self.last_action = msg
		self.rewrite_action = False

	def fail(self):
		"""Message for a failed action."""
		if self.rewrite_action:
			self.write(self.last_action + " ... ")
		self.write("[FAILED]\n")

	def succeed(self):
		"""Message for a successful action."""
		if self.rewrite_action:
			self.write(self.last_action + " ... ")
		self.write("[OK]\n")
	
	def message(self, msg):
		"""Display a building message."""
		if not self.rewrite_action:
			self.write("\n")
			self.rewrite_action = True
		self.write(msg)

	def is_win(self):
		return self.host_arch == OS_WINDOWS_32 or self.host_arch == OS_WINDOWS_64;

	def execute(self, cmd, interactive = False):
		"""Execute a command performing an action (displayed to
		the user)."""
		self.do(cmd);
		cfds = not self.is_win()
		if not interactive:
			proc = subprocess.Popen(cmd, shell=True, close_fds=cfds, stdout=self.log, stderr=self.log)
			proc.communicate()
		else:
			proc = subprocess.Popen(cmd, shell=True, close_fds=cfds)
			proc.wait()
			
		if proc.returncode == 0:
			self.succeed()
		else:
			self.fail()
			self.error("command failed")
	
	def execute_with_trace(self, cmd):
		"""Execute a command performing an action (displayed to
		the user)."""
		cfds = not self.is_win()
		self.do(cmd);
		(inp, out) = os.pipe()
		inp = os.fdopen(inp, "r")
		out = os.fdopen(out, "w")
		proc = subprocess.Popen(
			cmd,
			shell = True,
			close_fds = cfds,
			stdout = out,
			stderr = out)
		out.close()
		while True:
			line = inp.readline()
			if not line:
				break
			self.log.write(line)
			if line.startswith("*** "):
				self.message(line)
		proc.wait()
		if proc.returncode == 0:
			self.succeed()
		else:
			self.fail()
			self.error("command failed: %s" % proc.returncode)	

	def writeRule(self, out, mod, target, source, actions):
		"""Write a rule to the given output.
		actions is a list of actions to perform."""
		out.write("%s: %s\n" % (target, source))
		for action in actions:
			pref = ""
			changed = True
			while changed:
				changed = False
				if action.startswith("@") or action.startswith("-"):
					pref = pref + action[0]
					action = action[1:]
					changed = True
			out.write("\t%scd %s; %s\n" % (pref, mod.name, action))
		out.write("\n")

	def is_distant(self, path):
		"""Test if a path represents a distant address."""
		for scheme in DISTANT_SCHEMES:
			if path.startswith(scheme):
				return True
		return False

	def to_unix_path(self, path):
		"""Convert a Python to Unix path."""
		if self.is_win():
			path = path.replace("\\", "/")
			if path[1] == ":" and path[0].isalpha():
				path = "/%s/%s" % (path[0], path[2:])
		return path
	
	def to_host_path(self, path):
		"""Convert an independent path (with "/")
		to an host path."""
		if not self.is_win():
			return path
		else:
			return path.replace("/", "\\")
	
	def to_make_path(self, path):
		"""Convert a path to Makefile-aware path."""
		if not self.is_win():
			return path
		else:
			return path.replace("\\", "/")
	
	def ensure_tmp_link(self):
		"""Ensure the link /tmp/otawa-dist" to the base directory exists.
		This link makes portable specific  tools that needs to be compiled with fixed prefix."""
		if not os.path.exists("/tmp/otawa-dist"):
			os.symlink(self.get_base_dir(), "/tmp/otawa-dist")

	def ensure_install(self, target, package):
		"""Ensure that the package whose target is given (relative to the base directory)
		is installed. If not, get the package from the given address and unpack it."""
		dir = os.path.join(self.get_base_dir(), target)
		if os.path.exists(dir):
			return
		self.execute("cd %s; wget %s" % (os.path.dirname(dir), package))
		self.execute("cd %s; tar xf %s" % (os.path.dirname(dir), os.path.basename(package)))


class Definitions:
	"""Represents a set of definition to include at the head of the Makefile."""
	defs = None
	deps = None
	
	def __init__(self, name, defs, deps = []):
		self.name = name
		self.defs = defs
		self.deps = deps

	def definitions(self):
		return self.defs
	
	def dependencies(self):
		return self.deps

	def __repr__(self):
		return self.name
