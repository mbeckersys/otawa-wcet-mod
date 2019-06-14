# otawa-core v1 package
from buildlib import *

def get(env, tag):
	adds = []
	if env.is_cross() and env.get_target_arch() in [OS_WINDOWS_32, OS_WINDOWS_64]:
		adds = ['win']
	return Package(
		"otawa-core",
		env, tag = tag,
		names = [ "gel", "elm1", "otawa1", "orange" ] + adds,
		includes = [ "thot", "gliss2", "armv7t", "ppc2", "lp_solve5", "frontc" ], 
		addons = [
			Copy("otawa-core.README", "README"),
			Copy("LGPL", "COPYING"),
			OnlySource(Copy("core-build.INSTALL", "INSTALL")),
			OnlyDist(Copy("core-install.INSTALL", "INSTALL"))
		])
