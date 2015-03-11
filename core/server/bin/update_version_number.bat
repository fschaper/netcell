@echo off
..\bin\SubWCRev.exe ..\..\ ..\include\wss\version.hpp.tpl ..\include\wss\version.hpp~
..\bin\diff ..\include\wss\version.hpp~ ..\include\wss\version.hpp || move /Y ..\include\wss\version.hpp~ ..\include\wss\version.hpp 
..\bin\SubWCRev.exe ..\..\ wss.rc.tpl wss.rc
exit 0
