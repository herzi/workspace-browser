#!/bin/bash

aclocal
automake --add-missing
libtoolize --automake
autoconf

./configure $@
