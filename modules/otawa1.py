# elm module builder
from buildlib import *

DEFAULT=""
CROSS_MATRIX = {
	(OS_LINUX_64, OS_WINDOWS_32): "-DMINGW_LINUX=yes",
	(OS_LINUX_64, OS_WINDOWS_64): "-DMINGW_LINUX=yes"
}

def get(path, env, pack):
	if not env.is_cross():
		copts = DEFAULT
	else:
		copts = CROSS_MATRIX[env.get_cross_pair()]
	env.set("otawa-REV", "fddfe090441c")
	return Module(
		name = "otawa",
		path = path,
		env = env,
		package = pack,
		downloader = MercurialDownloader("https://anon:anon@www.irit.fr/hg//TRACES/otawa/trunk"),
		setup = CMakeSetup(prefix = "$(PREFIX)", opts = copts),
		maker = MakeMaker(),
		installer = MakeInstaller(),
		requires = [ "elm1", "gel" ],
		uses = [ "ppc", "ppc2", "arm", "lp_solve5", "thot", "arm2", "armv7t", "ogensim"]
	)
