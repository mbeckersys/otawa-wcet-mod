#!/bin/sh

PREFIX=$(otawa-config --prefix)
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
	install ogensim $INSTALL_PATH/ogensim
	echo "Copied 'ogensim' to '$INSTALL_PATH'"
)
