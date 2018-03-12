# orange module builder
# parameters:
# * orange-FLAGS= (default to NATIVE=1)
import buildlib

DEFAULT=""
MATRIX = {
	(buildlib.OS_LINUX_64, buildlib.OS_WINDOWS_32):
		"OCAMLOPT=i686-w64-mingw32-ocamlopt OCAMLC=i686-w64-mingw32-ocamlc OS=mingw",
	(buildlib.OS_LINUX_64, buildlib.OS_WINDOWS_64):
		"OCAMLOPT=i686-w64-mingw32-ocamlopt OCAMLC=i686-w64-mingw32-ocamlc OS=mingw"
}

def get(path, env, pack):
	if env.is_cross():
		f = MATRIX[env.get_cross_pair()]
	else:
		f = DEFAULT
	_flags = env.get("orange-FLAGS", "NATIVE=1")
	return buildlib.Module(
		name = "orange",
		path = path,
		env = env,
		package = pack,
		downloader = buildlib.MercurialDownloader("https://anon:anon@www.irit.fr/hg//TRACES/orange/trunk"),
		maker = buildlib.MakeMaker(nojob = True, flags = _flags + " " + f, chroot = True),
		installer = buildlib.MakeInstaller(flags = "PREFIX=$(call path_win2ux,$(PREFIX)) " + f),
		requires = [ "frontc" ],
		defs = [ buildlib.PATH_DEFS ]
	)
