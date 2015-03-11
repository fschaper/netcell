@echo off
REM ---------------------------------------------------------------
REM create test environment
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
echo deploying required files to '%project_root%\vs\test_suite_server'.
echo deploying required files to %ext%.
xcopy /D /Y /E %project_root%\server\etc\config.xml %project_root%\vs\test_suite_server
xcopy /D /Y /E /I %project_root%\server\xml\locale\*.* %project_root%\vs\test_suite_server\locale
xcopy /D /Y /E %project_root%\%ext%\icu\bin\Windows\i386\*.dll %project_root%\vs\test_suite_server
xcopy /D /Y /E %project_root%\%ext%\xerces\bin\Windows\i386\*.dll %project_root%\vs\test_suite_server
xcopy /D /Y /E %project_root%\%ext%\libconnectionpool\bin\Windows\i386\*.dll %project_root%\vs\test_suite_server
rem xcopy /D /Y /E %project_root%\extlibs\PaloSpreadsheetFuncs\bin\Windows\i386\*.dll %project_root%\vs\test_suite_server
xcopy /D /Y /E %project_root%\%ext%\libpalo_ng\bin\Windows\i386\*.dll %project_root%\vs\test_suite_server
