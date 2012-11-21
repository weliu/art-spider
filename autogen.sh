#!/usr/local/bin/bash

aclocal
libtoolize
autoheader
autoconf
automake --add-missing
./configure
