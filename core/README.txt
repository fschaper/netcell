A) Tools needed for build Palo Web

	MS Visual Studio 2010 SP1

B) Third party libraries needed for building Palo Web 
Libraries headers and binaries need to be checked out from libs repository, no additional download/build is necessary.


1. astyle
Artistic Style 1.24
A Free, Fast and Small Automatic Formatter
for C, C++, C#, and Java Source Code
Home Page:	http://astyle.sourceforge.net/
Project Page:	http://sourceforge.net/projects/astyle/

2. atomic
boost atomic
Distributed under the Boost Software License, Version 1.0.
http://www.boost.org/LICENSE_1_0.txt

3. boost
boost 1.46

4. freetype
FreeType 2.3.12

http://download.savannah.gnu.org/releases/freetype/

5. gd
gd 2.0.35
GD Graphics Library
http://www.boutell.com/gd/
http://www.libgd.org/

6. icu
ICU 4.6
International Components for Unicode
http://site.icu-project.org/
http://site.icu-project.org/download

7. jlib
JEdox lib
Jedox GmbH, Freiburg, Germany
http://www.jedox.com

8. libconnectionpool
Jedox GmbH, Freiburg, Germany
http://www.jedox.com

9. libpalo_ng
Jedox GmbH, Freiburg, Germany
http://www.jedox.com

10. odbcpp
obdcpp 1.5
The odbcpp library is a C++ wrapper around the ODBC API.
http://www.m2osw.com/odbcpp_docs

11. openssl
openssl-1.0.0c
http://www.openssl.org/

12. PaloSpreadsheetFuncs
Jedox GmbH, Freiburg, Germany
http://www.jedox.com

13. perftools
version 1.6
http://code.google.com/p/google-perftools/

14. php5.3.5
PHP 5.3.5

15. sockets
Sockets - 2.3.5
http://www.alhem.net/Sockets/index.html

16. tinyjson
TinyJson 1.3.0-J2

17. xerces
xerces-c-3.0.1

18. xsd2cpp
relevant headers are located in tools/xio/

20. zlib
zlib-1.2.5






C)How to build

1. Checkout core source code 
2. checkout libraries binaries and headers
3. Create a symbolic link - extlibs - in the core folder for the external libraries.
4. Build

Example:

-Checkout core source core to c:\core

-Checkout libraries to c:\libs

-create symbolic link for libs:

	cd c:\core
	mklink /D extlibs c:\libs

- open wss_vs2010.sln located in c:\core\vs with Visual Studio 2010 SP1

- choose the needed build configuration (i.e Release )and target platform (Win32)

- build solution 



































