# gel module builder
import buildlib

def get(path, env, pack):
	return buildlib.Module(
		name = "gel",
		path = path,
		env = env,
		package = pack,
		downloader = buildlib.MercurialDownloader("https://anon:anon@www.irit.fr/hg/TRACES/gel/trunk"),
		setup = buildlib.CMakeSetup(prefix = "$(PREFIX)", opts = "-DINSTALL_TYPE=$(INSTALL_TYPE)"),
		maker = buildlib.MakeMaker(),
		installer = buildlib.MakeInstaller()
	)

