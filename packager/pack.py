"""Package representation inside build utility."""
import base
import gen
import os


# Base classes
class Pass:
	"""Common base of each generation path."""

	def get_defs(self, mod, pack):
		"""Get the definitions associated with the path."""
		return []


class Downloader(Pass):
	"""Base class of all downloaders."""

	def proceed(self, mod, env):
		"""Unarchive the module to the given name
		and output log in the given environment."""
		pass
NULL_DOWNLOADER = Downloader()


class Setup(Pass):
	"""Base class for performing setup."""

	def gen(self, mod, env):
		"""Return a list of commands that are used to set up
		the module in the Makefile.
		Setup is only performed the first time the sources
		are compiled on a host."""
		return []
NULL_SETUP = Setup()


class Maker(Pass):
	"""Make base class."""

	def gen(self, mod, env):
		"""Generate the commands used for making the module."""
		return []
NULL_MAKER = Maker()


class Installer(Pass):
	"""Base class for installation."""

	def gen(self, mod, env):
		"""Generate the commands used to install the module.
		The commands may used the $(PREFIX) variable to known
		the installation directory."""
		return []
NULL_INSTALLER = Installer()


class Module:
	"""A module."""
	name = None
	path = None
	package = None
	requirements = None
	uses = None
	env = None
	local = None
	downloader = None
	setup = None
	maker = None
	installer = None
	defs = None
	
	def __init__(self, name, path, env,
		package = None,
		local = False,
		downloader = NULL_DOWNLOADER,
		setup = NULL_SETUP,
		maker = NULL_MAKER,
		installer = NULL_INSTALLER,
		requirements = [],
		uses = [],
		requires = [],
		defs = []):
			
		"""Build a module with the following arguments:
		name: name of the module
		path: installation path of the module
		env: current environment
		package: owner package
		local: the module is not installable
		requires: list of requirements
		downloader: downloader for the module
		setup: setup for the module
		maker: maker for the module
		installer: installer for the module"""
		
		self.name = name
		self.path = path
		self.package = package
		self.env = env
		self.local = local
		self.uses = uses
		self.requirements = requirements
		if requires:
			self.requirements = self.requirements + requires
		self.downloader = downloader
		self.setup = setup
		self.maker = maker
		self.installer = installer
		self.defs = defs
	
	def save(self):
		pass
	
	def get_defs(self):
		"""Called to prepare the module for generation."""
		return	self.defs + \
				self.downloader.get_defs(self, self.package) + \
				self.setup.get_defs(self, self.package) + \
				self.maker.get_defs(self, self.package) + \
				self.installer.get_defs(self, self.package)
	
	def download(self):
		self.downloader.proceed(self, self.env)
	
	def doSetup(self):
		return self.setup.gen(self, self.env)
	
	def make(self):
		return self.maker.gen(self, self.env)
	
	def install(self):
		return self.installer.gen(self, self.env)

	def __repr__(self):
		return "module(%s)" % self.name

class Addon:
	"""Action to perform after the package building."""
	
	def onSourceDist(self, pack):
		"""Called for a source distribution."""
		pass
	
	def onBinDist(self, pack):
		"""Called for a binary distribution."""
		pass


class Package:
	"""Representation of a package."""
	name = None
	path = None
	spath = None
	mods = None
	requirements = None
	names = None
	env = None
	tag = None
	addons = None
	install_util = None
	arc_list = None
	includes = None

	def __init__(self, name, env, path = None, tag = None, names = None, addons = [], install_util = True, arc_list = None, includes = []):
		"""Build a new package.
		name: package name,
		path: path to install package in,
		env: current environment,
		tag: tag to build the archive,
		names: list of modules in the package,
		addons: addons file (prefixed by i: for installation only, by s: for source only);
		relative path are relative to the .py package file directory,
		install_util: add or not the installer utility,
		arc_list: list of files/directories to put in archive.
		includes: module to include for buidling."""
		self.name = name
		self.path = path
		if self.path == None:
			self.path = os.path.join(os.getcwd(), env.get_target_arch(), name)
		self.path = os.path.abspath(self.path)
		self.setBuildDir(self.path)
		self.env = env
		self.names = names
		self.addons = addons
		self.install_util = install_util
		if tag:
			self.tag = tag + "-"
		else:
			self.tag = ""
		self.arc_list = arc_list
		self.includes = includes

	def setPath(self, path):
		"""Set the current path."""
		self.path = os.path.join(os.path.abspath(path), self.name)

	def exists(self):
		"""Test if the module is currently existing."""
		return os.path.exists(os.path.join(self.path, ".modules"))
	
	def setBuildDir(self, path):
		"""Set the building directory."""
		self.path = os.path.join(os.path.abspath(path), self.name)
		self.spath = self.path + "-build"
	
	def getModules(self):
		if self.mods == None:
			self.mods = []
			for n in self.env.loadList(os.path.join(self.path, ".modules")):
				self.mods.append(Module(n, os.path.join(self.path, n), self.env, package = self))
		return self.mods
	
	def getRequirements(self):
		if self.requirements == None:
			path = os.path.join(self.path, ".requirements")
			if os.path.exists(path):
				self.requirements = self.env.loadList()
			else:
				self.requirements = []
		return self.requirements

	def save(self):
		"""Save the current module: mainly write the module list
		and architecture information."""
		
		# save the modules
		if self.mods:
			path = os.path.join(self.path, ".modules")
			self.env.saveList(path, [m.name for m in self.mods])
	
		# save  requirements
		if self.requirements != None:
			path = os.path.join(self.path, ".requirements")
			self.env.saveList(path, self.requirements)
	
		# save the architecture
		self.env.saveFile(os.path.join(self.path, ".arch"), self.env.get_target_arch())

	def look(self, name):
		"""Look for a module in this package.
		Return the found module."""
		for m in self.getModules():
			if name == m.name:
				return m
		return None

	def buildSourceDist(self, site):
		"""Build a source distribution."""
		g = gen.Source(self, site)
		g.build(0)
	
	def buildDist(self, site, btype = base.BUILD_BIN | base.BUILD_DEV):
		"""Build the distribution of the package."""
		g = gen.Binary(self, site)
		g.build(btype)

