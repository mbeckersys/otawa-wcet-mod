# frontc module builder
import buildlib

DEFAULT=""
MATRIX = {
	(buildlib.OS_LINUX_64, buildlib.OS_WINDOWS_32):
		"OCAMLOPT=i686-w64-mingw32-ocamlopt OCAMLC=i686-w64-mingw32-ocamlc NATIVE=1",
	(buildlib.OS_LINUX_64, buildlib.OS_WINDOWS_64):
		"OCAMLOPT=i686-w64-mingw32-ocamlopt OCAMLC=i686-w64-mingw32-ocamlc NATIVE=1"
}

def get(path, env, pack):
	if env.is_cross():
		f = MATRIX[env.get_cross_pair()]
	else:
		f = DEFAULT
	return buildlib.Module(
		name = "frontc",
		path = path,
		env = env,
		package = pack,
		downloader = buildlib.MercurialDownloader("https://anon:anon@www.irit.fr/hg/TRACES/frontc/trunk"),
		maker = buildlib.MakeMaker(nojob = True, chroot = True, flags = f),
		local = True
	)

