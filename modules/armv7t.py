# armv7t module builder
import base
from buildlib import *

DEFAULT="WITH_DYNLIB=1"
CROSS_MATRIX = {
	(base.OS_LINUX_64, base.OS_WINDOWS_32): "RANLIB=i686-w64-mingw32-ranlib", 
	(base.OS_LINUX_64, base.OS_WINDOWS_64): "RANLIB=x86_64-w64-mingw32-ranlib" 
}

def get(path, env, pack):
	if not env.is_cross():
		opts = DEFAULT
	else:
		opts = CROSS_MATRIX[env.get_cross_pair()]
	return Module(
		name = "armv7t",
		path = path,
		env = env,
		package = pack,
		downloader = MercurialDownloader("https://anon:anon@www.irit.fr/hg/TRACES/armv7t/trunk"),
		maker = MakeMaker(nojob = True, flags = opts + " WITH_FAST_STATE=1"),
		local = True,
		requires = [ "gliss2" ]
	)
