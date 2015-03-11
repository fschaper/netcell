@echo off
REM ---------------------------------------------------------------
REM create debug environment
REM Florian Schaper <florian.schaper@jedox.com>
REM ---------------------------------------------------------------
set project_root=%1%

IF NOT "%2%"=="" goto set_p
IF "%2%"=="" goto default
:set_p
set ext=%2%
goto run
:default
set ext=extlibs
goto run

:run
echo deploying required files to '%project_root%\vs\debug'.
echo deploying required files to %ext%.
xcopy /D /Y /E %project_root%\server\etc\config.xml %project_root%\vs\debug
xcopy /D /Y /E %project_root%\server\xml\locale\*.* %project_root%\vs\debug\locale
xcopy /D /Y /E %project_root%\%ext%\icu\bin\Windows\i386\*.dll %project_root%\vs\debug
xcopy /D /Y /E %project_root%\%ext%\xerces\bin\Windows\i386\*D.dll %project_root%\vs\debug
xcopy /D /Y /E %project_root%\%ext%\libconnectionpool\bin\Windows\i386\*_d.dll %project_root%\vs\debug
xcopy /D /Y /E %project_root%\%ext%\libpalo_ng\bin\Windows\i386\*_d.dll %project_root%\vs\debug
xcopy /D /Y /E %project_root%\%ext%\zlib\bin\Windows\i386\zlib1_d.dll %project_root%\vs\debug
xcopy /D /Y /E %project_root%\%ext%\perftools\bin\Windows\i386\libtcmalloc_minimal-debug.dll %project_root%\vs\debug
xcopy /D /Y /E %project_root%\%ext%\php5.2.13\bin\Windows\i386\php5ts_debug.dll %project_root%\vs\debug
xcopy /D /Y /E %project_root%\%ext%\php5.2.13\lib\Windows\i386\*.dll %project_root%\vs\debug
xcopy /D /Y /E %project_root%\%ext%\openssl\bin\Windows\i386\*.dll %project_root%\vs\debug
