#!/bin/sh

PREFIX=$(otawa-config --prefix)
if [ -z "$PREFIX" ]; then
	PREFIX="/home/becker/async/WCET_gitlab/otawa/linux-x86_64/otawa-core"
fi

PLUGIN_PATH=$PREFIX/lib/otawa/sim
INSTALL_PATH=$PREFIX/bin
BUILDDIR=objdir

if [ ! -d "$BUILDDIR" ]; then
	(
		mkdir $BUILDDIR
		cd $BUILDDIR
		cmake ..
	)
fi
(
	cd $BUILDDIR
	make -j2
	install ogensim $INSTALL_PATH/
	echo "Copied 'ogensim' to '$INSTALL_PATH'"
	install libgensim.* $PLUGIN_PATH/
	echo "Copied 'libgensim' to '$PLUGIN_PATH'"
)
