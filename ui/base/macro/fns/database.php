<?php

/* 
 * @brief legacy ODBC/MySQL layer
 *
 * @file database.php
 *
 * Copyright (C) 2006-2009 Jedox AG
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (Version 2) as published
 * by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * You may obtain a copy of the License at
 *
 * <a href="http://www.jedox.com/license_palo_bi_suite.txt">
 *   http://www.jedox.com/license_palo_bi_suite.txt
 * </a>
 *
 * If you are developing and distributing open source applications under the
 * GPL License, then you are free to use Palo under the GPL License.  For OEMs,
 * ISVs, and VARs who distribute Palo with their products, and do not license
 * and distribute their source code under the GPL, Jedox provides a flexible
 * OEM Commercial License.
 *
 * \author
 * Hendrik Schmieder <hendrik.schmieder@jedox.com>
 *
 * \version
 * SVN: $Id: database.php 3845 2010-09-22 13:33:22Z vladislavm $
 *
 */
 
define("NAxl", new variant_error(variant_error::NA));
define("WSSDBERROR",'dberror');
define("WSSGENERALERROR",'generalerror');

function _process_error($type, $text, $formatted_text = "")
{
}

function _getCurrentCellName()
{
	return activesheet()->uuid() . "!".  activerange()->address();
}

function _CONCATENATExl()
{
	$ArrayValues = func_get_args();
	$ArraySum = "";
	foreach($ArrayValues as $Range)
	{
		if(is_array($Range))
		{
			foreach($Range as $SingKey=>$SingValue)
			{
				if($SingKey > 1)
				{
					// since the first two elements of the array
					// contains the row/column number,
					// we begin adding with the third element
					$ArraySum = $ArraySum . $SingValue;
				}
			}
		}
		else
		{
			$ArraySum = $ArraySum . $Range;
		}
	}
	return (string) $ArraySum;
}

function _ODBCNAME1xl($name)
{
	return $name . "_odbccache";
}

function _ODBCNAME2xl($name)
{
	return $name . "_odbccacheC";
}

function _ODBCNAME3xl($name)
{
	return $name . "_odbcerrorno";
}

function _ODBCNAME4xl($name)
{
	return $name . "_odbcerrortxt";
}

function _ODBCNAME5xl($name)
{
	return $name . "_odbhost";
}

function _ODBCNAME6xl($name)
{
	return $name . "_odbcdb";
}

function _ODBCNAME7xl($name)
{
	return $name . "_odbcuser";
}

function _ODBCNAME8xl($name)
{
	return $name . "_odbcpass";
}

function _ODBCNAME9xl($name)
{
	return $name . "_token";
}

function ODBCINITxl($DSN, $Username, $Password)
{
	$ID = _getCurrentCellName(); // unique ODBC id

	$ID_Name5 = _ODBCNAME5xl($ID);
	$ID_Name7 = _ODBCNAME7xl($ID);
	$ID_Name8 = _ODBCNAME8xl($ID);

	$_SESSION[$ID_Name5] = trim($DSN);
	$_SESSION[$ID_Name7] = trim($Username);
	$_SESSION[$ID_Name8] = trim($Password);

	return $ID;
}

function ODBCEXECxl($ID, $Query)
{
	$token = calculation_token();

	$Cache = _getCurrentCellName(); // unique datacache id

	$Cachename = _ODBCNAME1xl($Cache);
	$Cachename2 = _ODBCNAME2xl($Cache);
	$Cachename3 = _ODBCNAME3xl($Cache);
	$Cachename4 = _ODBCNAME4xl($Cache);

	$ID_Name3 = _ODBCNAME3xl($ID);
	$ID_Name4 = _ODBCNAME4xl($ID);

	$ID_Name5 = _ODBCNAME5xl($ID);
	$ID_Name7 = _ODBCNAME7xl($ID);
	$ID_Name8 = _ODBCNAME8xl($ID);

	$tokenname = _ODBCNAME9xl($ID);

	if (!isset($_SESSION[$tokenname]) || ($_SESSION[$tokenname] != $token))
	{
		$_SESSION[$tokenname] = $token;

		$_SESSION[$ID_Name3] = 0;
		$_SESSION[$ID_Name4] = "";
		$_SESSION[$Cachename] = array();
		$_SESSION[$Cachename2] = 0;
		$_SESSION[$Cachename3] = 0;
		$_SESSION[$Cachename4] = "";

		if(function_exists("odbc_pconnect"))
		{

			$handle = odbc_pconnect($_SESSION[$ID_Name5], $_SESSION[$ID_Name7] ,$_SESSION[$ID_Name8]);
			if(!$handle)
			{
				$_SESSION[$ID_Name3] = odbc_error();
				$_SESSION[$ID_Name4] = odbc_errormsg();
				_process_error(WSSDBERROR, $_SESSION[$ID_Name4], "<b>&nbsp;&nbsp;Error:</b>" . $_SESSION[$ID_Name4]);
				return NAxl;
			}
		}

		if(is_array($Query))
		{
			$Query = _CONCATENATExl($Query);
		}

		if(function_exists("odbc_do"))
		{
			$rowset = odbc_do($handle, $Query);
			if(!$rowset)
			{
				$_SESSION[$Cachename3] = odbc_error($handle);
				$_SESSION[$Cachename4] = odbc_errormsg($handle);
				_process_error(WSSDBERROR, $_SESSION[$Cachename4], "<b>&nbsp;&nbsp;Error:</b>" . "<b>&nbsp;&nbsp;Error:</b> " . str_replace('"',"",$_SESSION[$Cachename4] . "(Cell " . $Cache . ")"));
			}
			$cols= odbc_num_fields($rowset);
			$row = 0;

			if($cols != 0)
			{
				// if there's a result
				while(odbc_fetch_row($rowset))
				{
					// all data sets
					for($col=1;$col<=$cols;$col++)
					{
						if($row == 0)
						{
							// column name
							$_SESSION[$Cachename][$row][$col-1] = odbc_field_name($rowset,$col);
						}

						// all columns
						$_SESSION[$Cachename][$row+1][$col-1] = odbc_result($rowset, $col);
					}
					$row = $row + 1;
				}
			}
		}

		$_SESSION[$Cachename2] = count($_SESSION[$Cachename]) -1 ;
	}

	return $Cache;
}

function ODBCCOUNTxl($Cache)
{
	return $_SESSION[_ODBCNAME2xl($Cache)];
}

function ODBCERRORNOxl($Cache)
{
	if ($Cache == NAxl)
	{
		return NAxl;
	}

	return $_SESSION[_ODBCNAME3xl($Cache)];
}

function ODBCERRORxl($Cache)
{

	if ($Cache == NAxl)
	{
		return NAxl;
	}

	return $_SESSION[_ODBCNAME4xl($Cache)];
}

function ODBCDATAxl($Cache, $row, $col)
{
	$Cachename = _ODBCNAME1xl($Cache);
	$Cachename2 = _ODBCNAME2xl($Cache);

	if(!isset($_SESSION[$Cachename]) || $_SESSION[$Cachename] == "")
	{
		return "";
	}

	$data = $_SESSION[$Cachename];

	if(!is_numeric($row))
	{
		// if non numeric row number,
		// than search in first column and set row accordingly
		foreach($data as $key=>$value)
		{
			if(strtolower($value[0]) == strtolower($row))
			{
				// if 1.field of the row coorespond to the desired row text
				$row = $key;
				break;
			}
		}
	}

	if(!is_numeric($row) || (double)$row > $_SESSION[$Cachename2])
	{
		//  return empty string if we are after the last row
		//  or a non numeric rowindex is found
		return "";
	}

	if((is_numeric($col) && (double)$col == 0) || $col == "")
	{
		if($row == 0)
		{
			// 0,0 position always empty string
			return "";
		}
		else
		{
			// return rownumber beginning with 1. row
			return $row;
		}
	}

	if(!is_numeric($col) || $col > 1900)
	{
		// if field name or date
		$colno= array_search($col, $data[0]);
		if($colno === false)
		{
			// invalid field name
			return NAxl;
		}
		else
		{
			return $data[$row][$colno];
		}
	}
	else
	{
		if($col > count($data[0]))
		{
			// return always empty string after the last column
			return "";
		}
		else
		{
			return $data[$row][$col-1];
		}
	}

}

function MYSQLINITxl($Server, $Database, $Username="", $Password="")
{
	$ID = _getCurrentCellName(); // unique datacache id

	// define the handle to the  MYSQL resource as global
	$ID_Name3 = _ODBCNAME3xl($ID);
	$ID_Name4 = _ODBCNAME4xl($ID);

	$ID_Name5 = _ODBCNAME5xl($ID);
	$ID_Name6 = _ODBCNAME6xl($ID);
	$ID_Name7 = _ODBCNAME7xl($ID);
	$ID_Name8 = _ODBCNAME8xl($ID);
	
	$_SESSION[$ID_Name3] = 0;
	$_SESSION[$ID_Name4] = "";
	$_SESSION[$ID_Name5] = $Server;
	$_SESSION[$ID_Name6] = $Database;
	$_SESSION[$ID_Name7] = $Username;
	$_SESSION[$ID_Name8] = $Password;

	return $ID;
}

function MYSQLEXECxl($ID, $Query)
{
	$token = calculation_token();

	// define the handle to the  cache array as global
	$Cache = _getCurrentCellName(); // unique datacache id
	$Cachename = _ODBCNAME1xl($Cache);
	$Cachename2 = _ODBCNAME2xl($Cache);
	$Cachename3 = _ODBCNAME3xl($Cache);
	$Cachename4 = _ODBCNAME4xl($Cache);;

	$ID_Name3 = _ODBCNAME3xl($ID);
	$ID_Name4 = _ODBCNAME4xl($ID);
	$ID_Name5 = _ODBCNAME5xl($ID);
	$ID_Name6 = _ODBCNAME6xl($ID);
	$ID_Name7 = _ODBCNAME7xl($ID);
	$ID_Name8 = _ODBCNAME8xl($ID);

	$tokenname = _ODBCNAME9xl($ID);

	if (!isset($_SESSION[$tokenname]) || ($_SESSION[$tokenname] != $token))
	{
		$_SESSION[$tokenname] = $token;

		$_SESSION[$Cachename] = array();
		$_SESSION[$Cachename2] = 0;
		$_SESSION[$Cachename3] = 0;
		$_SESSION[$Cachename4] = "";

		if(function_exists("mysql_connect"))
		{

			$handle = mysql_connect($_SESSION[$ID_Name5], $_SESSION[$ID_Name7], $_SESSION[$ID_Name8], true);

			if ($handle === false)
			{
				$_SESSION[$ID_Name3] = mysql_errno();
				$_SESSION[$ID_Name4] = mysql_error();
			}
			else
			{
				if (!mysql_select_db($_SESSION[$ID_Name6], $handle))
				{
					$_SESSION[$ID_Name3] = mysql_errno($handle);
					$_SESSION[$ID_Name4] = mysql_error($handle);
				}
			}
		}

		if (!empty($_SESSION[$ID_Name4]))
		{
			_process_error(WSSDBERROR, $_SESSION[$ID_Name4]);
			return NAxl;
		}

		if(is_array($Query))
		{
			$Query = _CONCATENATExl($Query);
		}

		if(function_exists("mysql_query"))
		{
			mysql_query("Set names 'utf8'", $handle);

			$rowset = mysql_query($Query, $handle);

			if(!$rowset)
			{
				$_SESSION[$Cachename3] = mysql_errno($handle);
				$_SESSION[$Cachename4] = mysql_error($handle);
			}

			$cols= mysql_num_fields($rowset);
			$row = 0;

			while($datarow = mysql_fetch_row($rowset))
			{
				// all data sets
				for($col=1;$col<=$cols;$col++)
				{
					if($row == 0)
					{
						// column name
						$_SESSION[$Cachename][$row][$col-1] = mysql_field_name($rowset,$col-1);
					}

					// all columns
					$_SESSION[$Cachename][$row+1] = $datarow;
				}
				$row = $row + 1;
			}
		}

		$_SESSION[$Cachename2] = count($_SESSION[$Cachename])-1;

		if (!empty($_SESSION[$Cachename4])) _process_error(WSSDBERROR, $_SESSION[$Cachename4]);
	}

	return $Cache;
}

function MYSQLCOUNTxl($Cache)
{
	return $_SESSION[_ODBCNAME2xl($Cache)];
}

function MYSQLERRORNOxl($Cache)
{
	return ODBCERRORNOxl($Cache);
}

function MYSQLERRORxl($Cache)
{
	return ODBCERRORxl($Cache);
}

function MYSQLDATAxl($Cache,$row,$col)
{
	return ODBCDATAxl($Cache,$row,$col);
}

?>
	