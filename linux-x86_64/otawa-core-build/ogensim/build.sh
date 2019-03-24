#!/bin/sh

PREFIX=$(otawa-config --prefix)
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
