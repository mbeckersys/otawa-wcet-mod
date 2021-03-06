# ogensim module builder
from buildlib import *

DEFAULT="WITH_DYNLIB=1"
CROSS_MATRIX = {
	(OS_LINUX_64, OS_WINDOWS_32): "RANLIB=i686-w64-mingw32-ranlib",
	(OS_LINUX_64, OS_WINDOWS_64): "RANLIB=x86_64-w64-mingw32-ranlib"
}

def get(path, env, pack):
	if not env.is_cross():
		opts = DEFAULT
	else:
		opts = CROSS_MATRIX[env.get_cross_pair()]
	#env.set("ogensim-REV", "22be16f734ba")
	return Module(
		name = "ogensim",
		path = path,
		env = env,
		package = pack,
		downloader = MercurialDownloader("https://anon:anon@www.irit.fr/hg/TRACES/ogensim"),
		maker = MakeMaker(nojob = True, flags = "WITH_VLE=1 %s" % opts),
		local = True,
		requires = [ "gliss2" ]
	)
