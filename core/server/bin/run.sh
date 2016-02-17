#!/bin/bash

#
# Wrapper for the daemon binary
#
# Author:
# Dragan Simic <dragan.simic@develabs.com>
# Jedox AG, Freiburg, Germany
#

PROGNAME=./core.bin
DIRNAME=`dirname $PROGNAME`

CONFDIR=`readlink -f $DIRNAME/etc`
CONFFILE="config.xml"
LIBDIR=`readlink -f $DIRNAME/lib`
EXTDIR=`readlink -f $DIRNAME/extension`
PHP_EXTDIR=`readlink -f $DIRNAME/php_extensions`
LOCALEDIR=`readlink -f $DIRNAME/etc/locale`
AUTHDIR=`readlink -f $DIRNAME/etc/auth`
STORAGEDIR=`readlink -f $DIRNAME/var/storage`
FONTDIR=`readlink -f $DIRNAME/var/fonts`
USER="httpd"

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$LIBDIR:$EXTDIR:$PHP_EXTDIR
export LD_LIBRARY_PATH
export MALLOC_CHECK_=0

$PROGNAME -u "$USER" -d "$CONFDIR" -c "$CONFFILE" -l "$LOCALEDIR" -e "$EXTDIR"

# EOF
