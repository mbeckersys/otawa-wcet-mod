# elm module builder
import buildlib
import os

CC = "cd lpsolve55; sh ccc.$(TARGET_OS)"

CROSS_OPTS = {
	(buildlib.OS_LINUX_64, buildlib.OS_LINUX_32):
		"export CFLAGS=\"-m32\"; %s" % CC,
	(buildlib.OS_LINUX_64, buildlib.OS_WINDOWS_32):
		"sed -e s/c=cc/c=i686-w64-mingw32-gcc/ -e s/^ranlib\ /i686-w64-mingw32-ranlib\ / -e s/^ar\ /i686-w64-mingw32-ar\ / lpsolve55/ccc.linux -e s/^opts=\\\"/opts=\\\"-DINLINE=static\ / > lpsolve55/ccc.win32; %s" % CC,
#		-DINLINE=static is just a wrap-around bug in i686-w64-mingw32-gcc that does not seem to support the inlining of functions.
	(buildlib.OS_LINUX_64, buildlib.OS_WINDOWS_64):
		"sed -e s/c=cc/c=x86_64-w64-mingw32-gcc/ -e s/^ranlib\ /x86_64-w64-mingw32-ranlib\ / -e s/^ar\ /x86_64-w64-mingw32-ar\ / lpsolve55/ccc.linux -e s/^opts=\\\"/opts=\\\"-DINLINE=static\ / > lpsolve55/ccc.win64; %s" % CC
#		-DINLINE=static is just a wrap-around bug in x86_64-w64-mingw32-gcc that does not seem to support the inlining of functions.
}

def get(path, env, pack):
	
	# select compilation option
	if not env.is_cross():
		cc = CC
	else:
		cc = CROSS_OPTS[(env.get_host_arch(), env.get_target_arch())]
	
	# make the module
	return buildlib.Module(
		"lp_solve5",
		path = path,
		env = env,
		package = pack,
		downloader = buildlib.ArchiveDownloader(target = os.path.join(env.get_base_dir(), "extern/lp_solve5.tar.gz")),
		maker = buildlib.CustomMaker(["(%s)" % cc]),
		defs = [buildlib.OS_DEFS]
	)
