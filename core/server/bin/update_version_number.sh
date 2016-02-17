#!/bin/bash

rm -f ../include/wss/version.hpp.tpl~
REV=`svn info | awk '/^Revision:/ {print $2}'`
NOW=`date +%Y%m%d%H%M%S00200`
REPODATE=`svn info | awk '/^Last Changed Date:/ {print $4 $5 $6}'`
REPODATE=${REPODATE//-/}
REPODATE=${REPODATE//:/}
REPODATE=${REPODATE// /}
REPODATE=${REPODATE//+/0}
sed s/'\$WCREV\$'/"$REV"/g ../include/wss/version.hpp.tpl | sed s/'\$WCNOW\$'/"$NOW"/g | sed s/'\$WCDATE\$'/"$REPODATE"/g > ../include/wss/version.hpp.tpl~
mv -f ../include/wss/version.hpp.tpl~ ../include/wss/version.hpp