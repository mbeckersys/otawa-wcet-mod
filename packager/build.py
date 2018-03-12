#!/usr/bin/python

import base
import buildlib
import datetime
import imp
import optparse
import os
import os.path
import pack
import shutil
import sys

# action definition
ACTION_DOWNLOAD	= 0
ACTION_SETUP	= 1
ACTION_MAKE		= 2
ACTION_INSTALL	= 3
ACTION_PACKAGE	= 4
ACTION_SOURCES	= 5
ACTION_INIT = 6
ACTION_DEFAULT	= ACTION_MAKE

class Site:
	"""A compilation site."""
	path = None
	env = None
	packages = None
	changed = False
	
	def __init__(self, path, env):
		self.path = os.path.abspath(path)
		self.env = env
	
	def init(self):
		self.packages = []
	
	def getPackages(self):
		"""Get the packages of the site."""
		if self.packages == None:
			self.packages = []
			ppath = os.path.join(self.path, ".packages")
			if os.path.exists(ppath):
				for p in self.env.loadList(ppath):
					pack = buildlib.Package(p, self.env, self.path)
					if pack.exists():
						self.packages.append(pack)
					else:
						env.warn("package %s has possibly been removed: module base cleaned" % p)
		return self.packages
	
	def get(self, name):
		"""Get a pakcage by its name or return None."""
		for p in self.getPackages():
			if p.name == name:
				return p
		return None
	
	def remove(self, pack):
		"""Remove a package from the site."""
		self.getPackages()
		self.packages.remove(pack)
		self.changed = True

	def add(self, pack):
		"""Add a package."""
		self.getPackages()
		self.packages.append(pack)
		self.changed = True
	
	def look(self, name):
		"""Look for a module in the given packages.
		Return the found module or None."""
		for p in self.getPackages():
			m = p.look(name)
			if m:
				return m
		return None

	def save(self):
		"""Save the package configuration."""
		if self.changed:
			list = []
			for p in self.packages:
				p.save()
				list.append(p.name)
			self.env.saveList(os.path.join(self.path, ".packages"), list)


# scan arguments
parser = optparse.OptionParser()
parser.add_option("-D", "--dist", dest="dist", action="store_true", help="build distribution package")
parser.add_option("-S", "--sdist", dest="sdist", action="store_true", help="build distribution sources")
parser.add_option("-B", "--bdist", dest="bdist", action="store_true", help="build a binary distribution")
parser.add_option("-P", "--pdist", dest="pdist", action="store_true", help="build a development distribution")
parser.add_option("-d", "--download", dest="download", action="store_true", help="only download the modules")
parser.add_option("-s", "--setup", dest="setup", action="store_true", help="stop after setup")
parser.add_option("-m", "--make", dest="make", action="store_true", help="make the requested packages")
parser.add_option("-i", "--install", dest="install", action="store_true", help="perform installation")
parser.add_option("--dev", dest="dev", action="store_true", help="download as a developper")
parser.add_option("-p", "--package", dest="package", help="name of the built package")
parser.add_option("-v", "--verbose", dest="verbose", action="store_true", help="activate verbose mode")
parser.add_option("-b", "--builddir", dest="builddir", help="directory to build in")
parser.add_option("-t", "--tag", dest="tag", help="tag for version ('today' for current date)")
parser.add_option("-l", "--log", dest="log", help="use the given file for loggin ('none' for no log)")
parser.add_option("-c", "--cross", dest="cross", help="cross-compile to the given architecture")
parser.add_option("-u", "--user", dest="user", help="user name to perform connection on donwloading")
(options, args) = parser.parse_args()

# initialization
env = base.Env()
env.set("user", options.user)	
if options.verbose:
	env.verbose = True
if options.builddir:
	builddir = options.builddir
else:
	builddir = os.getcwd()

# set the log
log = options.log
if log == "none":
	log = "/dev/null"
else:
	log = "build.log"
try:
	env.setLog(open(log, "w"))
except IOError, e:
	env.warn("can not log to %s, default logging to stderr" % log)

# process the cross-compilation
if options.cross:
	env.target_arch = options.cross
	if (env.get_host_arch(), env.get_target_arch()) not in buildlib.KNOWN_CROSSES:
		print "Supported cross-compilation are:"
		for h, t in buildlib.KNOWN_CROSSES:
			print "\t%s => %s" % (h, t)
		env.error("unsupported cross from %s to %s" % (env.get_host_arch(), env.get_target_arch()))

# compute the tag
tag = options.tag
if tag == "today" or not tag:
	tag = datetime.datetime.today().strftime("%y%m%d")
if tag:
	tag = tag + "-"

# look for a package
package = options.package
if not package:
	package = "core1"
if args:
	pack = buildlib.Package(package, env, tag = tag, names = args)
else:
	path = os.path.join(os.getcwd(), "packages", "%s.py" % package)
	try:
		pmod = imp.load_source(package, path)
		pack = pmod.get(env, tag)
		pack.tag = tag
	except IOError,e:
		env.error("can not find package %s (%s)" % (package, e))


# source distribution action
try:
	if options.sdist:
		if options.builddir:
			builddir = options.builddir
		else:
			builddir = os.getcwd()
		site = Site(builddir, env)
		pack.setBuildDir(os.path.join(builddir, "sources"))
		pack.buildSourceDist(site)
		sys.exit(0)

	else:
		build_type = 0
		if options.dist:
			build_type = base.BUILD_DEV | base.BUILD_BIN
		elif options.bdist:
			build_type = base.BUILD_BIN
		elif options.pdist:
			build_type = base.BUILD_DEV
		else:
			build_type = base.BUILD_DEV | base.BUILD_BIN

		if build_type:
			builddir = os.path.join(builddir, env.get_target_arch())
			site = Site(builddir, env)
			old_pack = site.get(pack.name)
			if old_pack:
				env.info("removing old %s\n" % old_pack.name)
				site.remove(old_pack)
			site.save()			# in case it fails
			pack.setBuildDir(builddir)
			pack.buildDist(site, build_type)
			site.add(pack)
			site.save()
			sys.exit(0)

except base.BuildException as e:
	print("ERROR: %s" % e)
	sys.exit(1)

