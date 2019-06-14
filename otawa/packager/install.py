#!/usr/bin/python

import platform
import optparse
import os
import os.path
import shutil
import sys

def error(msg):
	""" Display an error message."""
	sys.stderr.write("ERROR: %s\n" % msg)
	sys.exit(1)

class Progress:
	"""Manage the progress bar."""
	cur = 0
	tot = 0
	step = 0
	lstep = 0
	
	def __init__(self, tot):
		self.tot = tot
		self.step = tot / 10.0
	
	def start(self):
		self.cur = 0
		self.lstep = 0
		sys.stdout.write("__________\n")
	
	def add(self, amt = 1):
		self.cur = self.cur + amt
		nstep = int(self.cur / self.step)
		while self.lstep < nstep:
			self.lstep = self.lstep + 1
			sys.stdout.write("#")
			sys.stdout.flush()

	def stop(self):
		sys.stdout.write("\n")

KNOWN_CONFIGS = [
	("Linux", "i686", 32, "linux-x86"),
	("Linux", "i686", 64, "linux-x86_64"),
	("Linux", "x86_64", 32, "linux-x86"),		# chrooted
	("Linux", "x86_64", 64, "linux-x86_64"),
	("Windows", None, 32, "win"),
	("Windows", None, 64, "win64"),
	("Darwin", "x86_64", 64, "darwin-x86_64")
]

def getHostArch():
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
	error("unknown platform: %s %s %s" % (system, mach, size))


def getPackageArch():
	"""Get the architecture of the current package."""
	
	try:
		f = open(".arch")
		return f.readline().strip()
	except IOError, e:
		error("can not open .arch: %s" % str(e))

def loadModules(path):
	"""Load the modules from the given files."""
	res = []	
	try:
		f = open(path)
		for m in f.xreadlines():
			m = m.strip()
			if m:
				res.append(m)
	except IOError, e:
		pass
	return res

def saveModules(path, modules):
	"""Save the modules in the given path."""
	
	try:
		f = open(path, "w")
		for m in modules:
			f.write("%s\n" % m)
		f.close()
	except OSError, e:
		error("very bad thing: %s" % str(e))


# initial configuration
install_dir = os.path.dirname(os.getcwd())
verbose = False

# scan the arguments
parser = optparse.OptionParser()
parser.add_option("-v", "--verbose", dest="verbose", action="store_true", help="activate verbose mode")
parser.add_option("-i", "--installdir", dest="install_dir", help="set the install directory")
(options, args) = parser.parse_args()
if args:
	parser.print_usage()
	error("garbage arguments")
if options.install_dir:
	install_dir = options.install_dir
if options.verbose:
	verbose = True


# read the modules
modules = loadModules(".modules")
if not modules:
	error("no module to install ?")
		
# test architecture
if verbose:
	print "INFO: checking architecture"
host_arch = getHostArch()
pack_arch = getPackageArch()
if host_arch != pack_arch:
	error("host architecture (" + host_arch + ") different of package architecture (" + pack_arch + ")")

# load modules
if verbose:
	print "INFO: checking dependencies"
pack_reqs = loadModules(".requirements")
host_mod_path = os.path.join(install_dir, ".modules")
host_mods = loadModules(host_mod_path)

# unexisting context
if not host_mods:
	if pack_reqs:
		error("no installation context: no way to get %s" % ", ".join(pack_reqs))
	print "INFO: no installation context: create one"
	try:
		f = open(host_mod_path, "w")
		f.close()
	except IOError, e:
		error("can not create installation context: " + e)

# existing context
else:
	errors = []
	for m in pack_reqs:
		if m not in host_mods:
			errors.append(m)
	if errors:
		error("requirements %s not provided !" % ", ".join(errors))

# perform the copies
to_remove = [".modules", ".requirements", "install.py", ".arch"]
if verbose:
	print "INFO: counting files"
file_tot = 0
for root, dirs, files in os.walk("."):
	file_tot = file_tot + len(dirs)
	for f in files:
		if f not in to_remove:
			file_tot = file_tot + 1
progress = Progress(file_tot)

# perform the copy
print "INFO: copying files"
progress.start()
for root, dirs, files in os.walk("."):
	
	# make the directories
	for d in dirs:
		dpath = os.path.join(install_dir, root, d)
		if not os.path.exists(dpath):
			try:
				os.mkdir(dpath)
			except OSError, e:
				progress.stop()
				error(str(e))
		progress.add()
	
	# copy the files
	for f in files:
		if f not in to_remove:
			spath = os.path.join(root, f)
			tpath = os.path.join(install_dir, root, f)
			try:
				if os.path.islink(spath):
					if os.path.exists(tpath):
						os.unlink(tpath)
					spath = os.readlink(spath)
					os.symlink(spath, tpath)
				else:
					shutil.copy2(spath, tpath)
			except shutil.Error, e:
				progress.stop()
				error(str(e))
			except OSError, e:
				progress.stop()
				error(str(e))
			progress.add()
	
progress.stop()
if verbose:
	print "INFO: copy ended successfully."

# update the .modules of install site
mpath = os.path.join(install_dir, ".modules")
imodules = loadModules(mpath)
changed = False
for m in modules:
	if m not in imodules:
		imodules.append(m)
		changed = True
if changed:
	saveModules(mpath, imodules)
print "INFO: successful installation."
