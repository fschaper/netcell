Debugging helper for Core3 Development in Visual Studio
=======================================================

Changelog:
-------------------------------------------------------
04.03.2009  initial version - Florian Schaper <florian.schaper@jedox.com>

Usage:
-------------------------------------------------------
- Compile the project

- Place the generated "core_visualizer.dll" in the same directory devenv.exe resides.
  "...\Microsoft Visual Studio 8\Common7\IDE"

- Locate the file "autoexp.dat" in your Visual Studio Installation in the
  directory "...\Microsoft Visual Studio 8\Common7\Packages\Debugger"

- Add the following definitions under the [AutoExpand] section of autoexp.dat
  ---&<------&<---
  sheet_point=$ADDIN(core_visualizer.dll,display_sheet_point)
  geometry::generic_rectangle<sheet_point>=$ADDIN(core_visualizer.dll,display_sheet_range)
  ---&<---

- Add the following definition under the [Visualizer] section of autoexp.dat
  ---&<---
  variant{
	preview
	(
		#(
			#switch( (unsigned)$e.m_value_type )
			#case 0	( #("EMPTY") )
			#case 1 ( #("STRING=", $e.m_string._Myptr) )
			#case 2 ( #("DOUBLE=", $e.m_double) )
			#case 3 ( #("BOOL=", (bool)$e.m_double) )
			#case 4 
			( 
				#(
					"ARRAY(WIDTH:", $c.m_column_width, ")=",
					#array
					(
						expr :	($c.m_array._Myptr->_Myfirst)[$i],  
						size :	$c.m_array._Myptr->_Mylast-$c.m_array._Myptr->_Myfirst
					)
				)
			)
			#case 5 
			( 
				#switch( (unsigned)$e.m_double )
				#case 0 ( #("ERROR=#NUM!") )
				#case 1 ( #("ERROR=#DIV/0!") )
				#case 2 ( #("ERROR=#VALUE!") )
				#case 3 ( #("ERROR=#REF!") )
				#case 4 ( #("ERROR=#NAME!") )
				#case 5 ( #("ERROR=#NULL!") )
				#case 6 ( #("ERROR=#N/A!") )
				#default ( #("ERROR=UNKNOWN") )
			)
			#default ( #("UNKNOWN") )
		)
	)
  }  
  ---&<---
