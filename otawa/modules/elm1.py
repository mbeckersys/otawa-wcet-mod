# elm module builder
import buildlib

LIBXML2_DEFS = buildlib.Definitions("LIBXML2_DEFS",
"""
# ELM dependency on libxml2, libxslt
ifeq ($(TARGET_OS),mingw)
ELM_FLAGS = \\
	-DLIBXML2_INCLUDE_DIR:PATH=$(CURDIR)/win/include \\
	-DLIBXML2_LIBRARIES:FILEPATH=$(CURDIR)/win/bin/libxml2-2.dll \\
	-DLIBXSLT_INCLUDE_DIR:PATH=$(CURDIR)/win/include \\
	-DLIBXSLT_LIBRARIES:FILEPATH=$(CURDIR)/win/bin/libxslt-1.dll
endif
ifeq ($(TARGET_OS),win32)
ELM_FLAGS = \\
	-DLIBXML2_INCLUDE_DIR:PATH=$(CURDIR)/win/include \\
	-DLIBXML2_LIBRARIES:FILEPATH=$(CURDIR)/win/bin/libxml2-2.dll \\
	-DLIBXSLT_INCLUDE_DIR:PATH=$(CURDIR)/win/include \\
	-DLIBXSLT_LIBRARIES:FILEPATH=$(CURDIR)/win/bin/libxslt-1.dll
endif
ifeq ($(TARGET_OS),win64)
ELM_FLAGS = \\
	-DLIBXML2_INCLUDE_DIR:PATH=$(CURDIR)/win/include \\
	-DLIBXML2_LIBRARIES:FILEPATH=$(CURDIR)/win/bin/libxml2-2.dll \\
	-DLIBXSLT_INCLUDE_DIR:PATH=$(CURDIR)/win/include \\
	-DLIBXSLT_LIBRARIES:FILEPATH=$(CURDIR)/win/bin/libxslt-1.dll
endif

""",
[buildlib.OS_DEFS])

def get(path, env, pack):
	reqs = []
	if env.get_target_arch() in [buildlib.OS_WINDOWS_32, buildlib.OS_WINDOWS_64]:
		reqs = ["win"]
	return buildlib.Module(
		name = "elm",
		path = path,
		env = env,
		package = pack,
		downloader = buildlib.MercurialDownloader("https://anon:anon@www.irit.fr/hg//TRACES/elm/trunk"),
		setup = buildlib.CMakeSetup(prefix = "$(PREFIX)", opts="$(ELM_FLAGS)"),
		maker = buildlib.MakeMaker(),
		installer = buildlib.MakeInstaller(),
		requires = reqs,
		defs = [LIBXML2_DEFS]
	)
