<?php

/*
 * @brief legacy functions layer
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
 * SVN: $Id: legacy.php 5023 2011-06-01 12:16:12Z vladislavm $
 *
 */

define("INITDRAWCOMMAND",0);
define("DRAWLINECOMMAND",1);
define("DRAWCIRCLECOMMAND",2);
define("DRAWPOLYGONCOMMAND",3);
define("DRAWTEXTCOMMAND",4);
define("DRAWRECTANGLECOMMAND",5);
define("DRAWARCCOMMAND",6);
define("DRAWARROWCOMMAND",7);
define("DRAWBEZIERCOMMAND",8);
define("DRAWPIXELCOMMAND",9);

function _CreateIDFromCell()
{
	return activesheet()->uuid()  . "!" . activerange()->address() ;
}

function CURRENTENTITY($fullpath=0)
{
    return "not yet implemented";
}

function FIRSTENTITY()
{
    return "/";
}

function NEXTENTITY($key)
{
    return "not yet implemented";
}

function ENTITYNAME($key,$indent=false)
{
    return "not yet implemented";
}

function ENTITYDATA($Entity,$Sheet,$Cell,$Application="")
{
    return "not yet implemented";
}

function CURRENTENTITYLEVEL($bottomup=false)
{
    return "not yet implemented";
}

function CURRENTENTITYISBASE()
{
    return 0;
}

function _DRAWHelper($ID, $command, $args)
{
       $temp = explode(":",$ID);
       $tmpID = $temp[0];
       $ID_Counter = $tmpID. "_CanvasCounter";

	   $entry = array($command, $args, activesheet()->name(), activerange()->address());

       if ($command == INITDRAWCOMMAND)
       {
               $_SESSION[$tmpID] = array($entry);
               $_SESSION[$ID_Counter] = 0;
       }
       else
       {
               $_SESSION[$tmpID][] = $entry;
               $_SESSION[$ID_Counter]++;
       }
	
       return $tmpID . ":" . $_SESSION[$ID_Counter];
}

function fixArray($Array)
{
	$data = array();
	foreach($Array as $value) {
		foreach($value as $v) {
			$data[] = $v;
		}
	}
	return $data;
}

function _INITDRAW(&$canvas, &$scale, &$shape, $Height, $Width, $Xmin, $Xmax, $Ymin, $Ymax)
{
	include_once("jpgraph.php");
	include_once("jpgraph_canvas.php");
	include_once("jpgraph_canvtools.php");

	// Create a new Canvas
	$canvas = new CanvasGraph($Width, $Height);
	$canvas->img->SetAntiAliasing();
	$canvas->SetMargin(0,0,0,0);
	$canvas->InitFrame();

	// Create a new scale
	$scale  = new CanvasScale($canvas);
	$scale->Set($Xmin, $Xmax, $Ymax, $Ymin);

	// The shape class is wrapper around the Imgae class which translates
	// the coordinates for us
	$shape  = new Shape($canvas, $scale);
}

//Drawing Functions
function INITDRAW()
{
	$ArrayValues = func_get_Args();

	$ID = _CreateIDFromCell(); // Unique Chart ID

	// Min/Max-Values of data area

	$Xmin = (isset($ArrayValues[0])) ? $ArrayValues[0] : 0;
	$Xmax = (isset($ArrayValues[1])) ? $ArrayValues[1] : null;
	$Ymin = (isset($ArrayValues[2])) ? $ArrayValues[2] : 0;
	$Ymax = (isset($ArrayValues[3])) ? $ArrayValues[3] : null;

	$args = array($Xmin, $Xmax, $Ymin,  $Ymax);

	return _DRAWHelper($ID, INITDRAWCOMMAND, $args);
}

function _DRAWLINE(&$canvas, &$scale, &$shape, $FromX, $FromY, $ToX, $ToY, $Color, $Style)
{
	$shape->SetColor($Color);

	// if Linestyle
	if (isset($Style) && (chop($Style)!="") && ($Style >= 1) && ($Style <=4) )
	{
		$shape->SetLineStyle($Style);
		$shape->StyleLine($FromX, $FromY, $ToX ,$ToY);
	}
	else
	{
		$shape->Line($FromX, $FromY, $ToX , $ToY);
	}
}


function DRAWLINE($ID, $FromX, $FromY, $ToX, $ToY, $Color, $Style)
{
	$args = func_get_Args();
	$dummy = array_shift($args);
	return _DRAWHelper($ID, DRAWLINECOMMAND, $args);
}

function _DRAWRECTANGLEHelper(&$from, &$to)
{
	if ($from < $to)
	{
		$temp = $from;
		$from = $to;
		$to = $temp;
	}
}

function _DRAWRECTANGLE(&$canvas, &$scale, &$shape, $FromX, $FromY, $ToX, $ToY, $Color, $FillColor, $Radius)
{
	_DRAWRECTANGLEHelper($FromY , $ToY);
	_DRAWRECTANGLEHelper($FromX , $ToX);

	if (isset($FillColor) && (chop($FillColor) != ""))
	{
		$shape->SetColor($FillColor);
		if (isset($Radius) && (chop($Radius) != "") && ($FromY != $ToY) && ($FromX != $ToX) )
		{
			$shape->FilledRoundedRectangle($FromX, $FromY, $ToX, $ToY, $Radius);
		}
		else
		{
			$shape->FilledRectangle($FromX, $FromY, $ToX, $ToY);
		}
	}

	if (isset($Color) && (chop($Color)!= "") || !isset($FillColor) || (chop($FillColor) == ""))
	{
		$shape->SetColor($Color);
		if (isset($Radius) && (chop($Radius) != "") && ($FromY != $ToY) && ($FromX != $ToX ))
		{
			$shape->RoundedRectangle($FromX, $FromY, $ToX, $ToY, $Radius);
		}
		else
		{
			$shape->Rectangle($FromX, $FromY, $ToX, $ToY);
		}
	}
}

function DRAWRECTANGLE($ID, $FromX, $FromY, $ToX, $ToY, $Color, $FillColor, $Radius)
{
	$args = func_get_Args();
	$dummy = array_shift($args);
	return _DRAWHelper($ID, DRAWRECTANGLECOMMAND, $args);
}

function _DRAWCIRCLE(&$canvas, &$scale, &$shape, $FromX, $FromY, $Radius, $Color, $FillColor)
{
	if (isset($FillColor) && (chop($FillColor)!=""))
	{
		$shape->SetColor($FillColor);
		$shape->FilledCircle($FromX, $FromY, $Radius);
	}

	if ((isset($Color) && (chop($Color)!="")) || !isset($FillColor) || (chop($FillColor)==""))
	{
		$shape->SetColor($Color);
		$shape->Circle($FromX, $FromY, $Radius);
	}
}

function DRAWCIRCLE($ID, $FromX, $FromY, $Radius, $Color, $FillColor)
{
	$args = func_get_Args();
	$dummy = array_shift($args);
	return _DRAWHelper($ID, DRAWCIRCLECOMMAND, $args);
}

function _DRAWARC(&$canvas, &$scale, &$shape, $CenterX, $CenterY, $Width, $Height, $Color, $FillColor, $Begin, $End)
{

	if(!isset($Begin) || (chop($Begin) == "") || ($Begin < 0) || ($Begin > 360))
	{
		$Begin = 0;
	}

	if(!isset($End) || (chop($End) == "") || ($End < 0) || ($End > 360))
	{
		$End = 360;
	}

	if(isset($FillColor) && (chop($FillColor) != ""))
	{
		$shape->SetColor($FillColor);
		$shape->FilledArc($CenterX, $CenterY, $Width, $Height, $Begin, $End);
	}

	if(isset($Color) && (chop($Color)!= "") || !isset($FillColor) || (chop($FillColor) == ""))
	{
		$shape->SetColor($Color);
		$shape->Arc($CenterX, $CenterY, $Width, $Height, $Begin, $End);
	}
}

function DRAWARC($ID, $CenterX, $CenterY, $Width, $Height, $Color, $FillColor, $Begin=0, $End=360)
{
	$args = array($CenterX, $CenterY, $Width, $Height, $Color, $FillColor, $Begin, $End);
	return _DRAWHelper($ID, DRAWARCCOMMAND, $args);
}

function _DRAWPOLYGON(&$canvas, &$scale, &$shape, $Array, $BorderColor, $FillColor)
{
	$data = fixArray($Array);

	if (isset($FillColor) && (rtrim($FillColor) != "") && !empty($FillColor))
	{
		if($FillColor{0} != '#') {
			$FillColor =  '#'.$FillColor;
		}
		$shape->SetColor($FillColor);
		$shape->FilledPolygon($data);
	}

	if (isset($BorderColor) && (rtrim($BorderColor)!= "") && !empty($BorderColor))
	{	
		if($BorderColor{0} != '#') {
			$BorderColor =  '#'.$BorderColor;
		}

		$shape->SetColor($BorderColor);
		$shape->Polygon($data);				
	}
}

function DRAWPOLYGON($ID, $Array, $BorderColor, $FillColor, $url="", $source="", $target="")
{
	$args = array($Array, $BorderColor, $FillColor);
	return _DRAWHelper($ID, DRAWPOLYGONCOMMAND, $args);
}

function _DRAWBEZIER(&$canvas, &$scale, &$shape, $Array, $Color)
{
	$shape->SetColor($Color);
	$shape->Bezier($Array);
}

function DRAWBEZIER($ID, $Array, $Color)
{
	$args = func_get_Args();
	$dummy = array_shift($args);
	return _DRAWHelper($ID, DRAWBEZIERCOMMAND, $args);
}

function _DRAWTEXT(&$canvas, &$scale, &$shape, $Xpos, $Ypos, $Text, $Size, $Dir, $Color, $Para_Align, $CoordAlign, $Boxcolor)
{
	list($Xpos,$Ypos) = $scale->Translate($Xpos,$Ypos);

	$oldText = $Text;
	$Text = str_replace("\\r\\n","\n",$Text);

	// Text und Textposition
	if (isset($Boxcolor) && (chop($Boxcolor) != "") && ($oldText == $Text))
	{
		$t  = new Text(" ".$Text,$Xpos,$Ypos);
	}
	else
	{
		$t  = new Text($Text,$Xpos,$Ypos);
	}


	$timesfile = TTF_DIR . "times.ttf";

	if ( (file_exists($timesfile) === false) || (is_readable($timesfile) === false) )
	{
		$use_font = FF_DV_SANSSERIFCOND;
	}
	else
	{
		$use_font = FF_TIMES;
	}

	$t->SetFont($use_font, FS_NORMAL);

	// How should the text box interpret the coordinates?
	if ($CoordAlign==3)
	{
		$t->Align( 'left','top');
	}
	elseif ($CoordAlign==2)
	{
		$t->Align( 'center','center');
	}
	else
	{
		$t->Align( 'left','bottom');
	}

	// How should the paragraph be aligned?
	if ($Para_Align == 3)
	{
		$t->ParagraphAlign( 'right');
	}
	elseif ($Para_Align == 2)
	{
		$t->ParagraphAlign( 'center');
	}
	else
	{
		$t->ParagraphAlign( 'left');
	}

	// Set Color of Font
	$t->SetColor($Color);

	// Rotate 90 Degrees
	if ($Dir != 0)
	{
		$t->SetAngle(90);
	}

	// Add a box around the text, custom fill, black border
	if (isset($Boxcolor) && (chop($Boxcolor) != ""))
	{
		$t->SetBox($Boxcolor,"black");
	}

	// Stroke the text
	$t->Stroke( $canvas->img);

}

function DRAWTEXT($ID, $Xpos, $Ypos, $Text, $Size=1, $Dir=0, $Color="#000000", $Para_Align=1, $CoordAlign=1, $Boxcolor=null)
{
	$args = array($Xpos, $Ypos, $Text, $Size, $Dir, $Color, $Para_Align, $CoordAlign, $Boxcolor);
	return _DRAWHelper($ID, DRAWTEXTCOMMAND, $args);
}

function _DRAWPIXEL(&$canvas, &$scale, &$shape, $Xpos, $Ypos, $Color)
{
	$shape->SetColor($Color);

	list($Xpos,$Ypos) = $scale->Translate($Xpos, $Ypos);
	$canvas->img->Point($Xpos, $Ypos);
}

function DRAWPIXEL($ID, $Xpos, $Ypos, $Color="#000000")
{
	$args = array($Xpos, $Ypos, $Color);
	return _DRAWHelper($ID, DRAWPIXELCOMMAND, $args);
}

function _DRAWARROW(&$canvas, &$scale, &$shape, $FromX, $FromY, $ToX, $ToY, $Width, $Ratio, $Color, $FillColor)
{
	$alpha = atan2($ToY-$FromY,$ToX-$FromX);

	$Array = array();
	$Array[] = $FromX+sin($alpha)*$Width-cos($alpha)*$Width;
	$Array[] = $FromY-cos($alpha)*$Width-sin($alpha)*$Width;
	$Array[] = $FromX-sin($alpha)*$Width-cos($alpha)*$Width;
	$Array[] = $FromY+cos($alpha)*$Width-sin($alpha)*$Width;
	$Array[] = $ToX-sin($alpha)*$Width;
	$Array[] = $ToY+cos($alpha)*$Width;
	$Array[] = $ToX-sin($alpha)*$Width*$Ratio;
	$Array[] = $ToY+cos($alpha)*$Width*$Ratio;
	$Array[] = $ToX+cos($alpha)*$Width*$Ratio;
	$Array[] = $ToY+sin($alpha)*$Width*$Ratio;
	$Array[] = $ToX+sin($alpha)*$Width*$Ratio;
	$Array[] = $ToY-cos($alpha)*$Width*$Ratio;
	$Array[] = $ToX+sin($alpha)*$Width;
	$Array[] = $ToY-cos($alpha)*$Width;
	$Array[] = $Array[0];
	$Array[] = $Array[1];


	if ($Width > 0)
	{
		if (isset($FillColor) && (chop($FillColor) != ""))
		{
			$shape->SetColor($FillColor);
			$shape->FilledPolygon($Array);
		}

		if (isset($Color) && (chop($Color)!= "") || !isset($FillColor) || (chop($FillColor) == ""))
		{
			$shape->SetColor($Color);
			$shape->Polygon($Array);
		}
	}
}

function DRAWARROW($ID, $FromX, $FromY, $ToX, $ToY, $Width, $Ratio=1, $Color="#000000", $FillColor="#000000")
{
	$args = array($FromX,$FromY,$ToX,$ToY,$Width,$Ratio=1,$Color,$FillColor);
	return _DRAWHelper($ID, DRAWARROWCOMMAND, $args);
}

function DRAWPOLYGONAPPLINK($ID,$Array,$Color,$FillColor,$url="",$valueRange=array(),$tooltip="test",$newWindow=0,$defuser="",$defpass= "",$width = "800",$height = "600",$top = "0",$left = "1")
{
    return "not yet implemented";
}


function DRAWNOW($ID)
{
	$old = error_reporting();
	error_reporting( E_ALL);

	$Height = activerange()->height();
	$Width  = activerange()->width();

	$temp = explode(":",$ID);
	$ID = $temp[0];

	$steps = $_SESSION[$ID];

	$count = count($steps);

	if ($count > 0)
	{
		$args = $steps[0][1];

		$Height = $Height - 2;
		$Width = $Width - 2;
		_INITDRAW($canvas, $scale, $shape, $Height , $Width , $args[0], (is_null($args[1])) ? $Width : $args[1], $args[2], (is_null($args[3])) ? $Height : $args[3]);

		for ($i = 1; $i < $count; $i++)
		{
			$entry = $steps[$i];
			$args = $entry[1];

			switch($entry[0])
			{
				
				case DRAWLINECOMMAND:
					_DRAWLINE($canvas, $scale, $shape, $args[0], $args[1], $args[2], $args[3], $args[4], $args[5]);
					break;
				case DRAWCIRCLECOMMAND:
					_DRAWCIRCLE($canvas, $scale, $shape, $args[0], $args[1], $args[2], $args[3], $args[4]);
					break;
				case DRAWPOLYGONCOMMAND:
					_DRAWPOLYGON($canvas, $scale, $shape, $args[0], $args[1], $args[2]);
					break;
				case DRAWTEXTCOMMAND:
					_DRAWTEXT($canvas, $scale, $shape, $args[0], $args[1], $args[2], $args[3], $args[4], $args[5], $args[6], $args[7], $args[8]);
					break;
				case DRAWRECTANGLECOMMAND:
					_DRAWRECTANGLE($canvas, $scale, $shape, $args[0], $args[1], $args[2], $args[3], $args[4], $args[5], $args[6]);
					break;
				case DRAWARCCOMMAND:
					_DRAWARC($canvas, $scale, $shape, $args[0], $args[1], $args[2], $args[3], $args[4], $args[5], $args[6], $args[7]);
					break;
				case DRAWARROWCOMMAND:
					_DRAWARROW($canvas, $scale, $shape, $args[0], $args[1], $args[2], $args[3], $args[4], $args[5], $args[6], $args[7]);
					break;
				case DRAWBEZIERCOMMAND:
					_DRAWBEZIER($canvas, $scale, $shape, $args[0], $args[1]);
					break;
				case DRAWPIXELCOMMAND:
					_DRAWPIXEL($canvas, $scale, $shape, $args[0], $args[1], $args[2]);
					break;
			}			
		}

		// choose PNG file format
		$canvas->img->SetImgFormat( "png");

		ob_start();
		print $canvas->img->Stream();
		$data = ob_get_contents();
		ob_end_flush();

		$output = '<img src="data:image/png;base64,' . base64_encode($data) . '" />';
	}
	else
	{
		$output = "no drawing steps found";
	}

	error_reporting($old);
	return $output;
}

function ODOCHART()
{
    return "use built-in support for odocharts instead";
}

// ODBC functions
function SOAPINIT($cellname, $WSDL)
{
	return "not yet implemented";
}

function SOAPEXEC()
{
	return "not yet implemented";
}

function SOAPDATA()
{
	return "not yet implemented";
}

function DIRINIT($cellname, $path, $filter, $order)
{
	return "not yet implemented";
}

function DIRDATA($cellname, $row, $type)
{
	return "not yet implemented";
}

//OLAP functions
function ALEALISTBOX($TargetCell,$server,$dimension,$indent=true,$order=0, $childof="",$includeparent=true,$levelfilter=0,$atfield="",$atcompare="",$autoupdate=true,$atalias="")
{
	return "not yet implemented";
}

function TM1LISTBOX($TargetCell,$dimension,$indent=true,$order=0, $childof="",$includeparent=true,$levelfilter=0,$atfield="",$atcompare="",$autoupdate=true,$atalias="")
{
	return "not yet implemented";
}

function PALOLISTBOX($TargetCell,$server,$dimension,$indent=true,$order=0, $childof="",$includeparent=true,$levelfilter=0,$atfield="",$atcompare="",$autoupdate=true,$atalias="")
{
	return "not yet implemented";
}

function ALEADIMENSION($cellname,$server,$dimension,$indent=false, $order=0,$childof="",$includeparent=true,$levelfilter=0,$atfield="",$atcompare="",$atalias="")
{
	return "not yet implemented";
}

function ALEAELEMENT($Cache,$row,$showindent=false)
{
	return "not yet implemented";
}

function TM1DIMENSION($cellname,$dimension,$indent=false, $order=0,$childof="",$includeparent=true,$levelfilter=0,$atfield="",$atcompare="",$atalias="")
{
	return "not yet implemented";
}

function TM1ELEMENT($Cache,$row,$showindent=false)
{
	return "not yet implemented";
}

function PALODIMENSION($cellname,$server,$dimension,$indent=false, $order=0,$childof="",$includeparent=true,$levelfilter=0,$atfield="",$atcompare="",$atalias="")
{
	return "not yet implemented";
}

function PALOELEMENT($Cache,$row,$showindent=false)
{
	return "not yet implemented";
}

function XMLAINIT($cellname,$url, $username="",$password="")
{
	return "not yet implemented";
}

function XMLAEXEC($cellname,$ID,$Query,$datasource,$database)
{
	return "not yet implemented";
}

function XMLADATA()
{
	return "not yet implemented";
}

// ODBC functions
function LINKINIT($cellname,$URL,$entity="@current",$sheet="",$user="",$password="")
{
	return "not yet implemented";
}

function LINKDATA($cellname,$sheet,$cell)
{
	return "not yet implemented";
}

function APPLINK($URL,$caption="Start",$title="",$width=995,$height=685,$top=5,$left=5)
{
	return "not yet implemented";
}

function APPLINK2($URL, $valueRange, $newWindow=0, $caption="Start",$title="",$width=995,$height=685,$top=5,$left=5)
{
	return "not yet implemented";
}

function APPLINK3($URL, $user, $password, $valueRange, $newWindow=0, $caption="Start",$title="",$width=995,$height=685,$top=5,$left=5)
{
	return "not yet implemented";
}

// Listfunctions
function ADDTOLIST($range,$indexcol,$index,$newentry,$value,$name,$title="")
{
	return "not yet implemented";
}

function DELETEFROMLIST($range,$indexcol,$index,$newentry,$value,$name,$title="")
{
	return "not yet implemented";
}

function MOVEINLIST($range,$indexcol,$index,$up,$value,$name,$title="")
{
	return "not yet implemented";
}

function EDITINLIST($range,$indexcol,$index,$targetrange,$value,$name,$title="")
{
	return "not yet implemented";
}

// html
function SHOWPICT($url,$name="",$title="")
{
	return '<img src="' . $url . '" alt="' . $name . '" />';
}

function SHOWBUTTON($value,$name,$title="",$HyperlinkCell = false)
{
	return "not yet implemented";
}

function SHOWPOPUP($cell,$label,$type,$content,$click=0)
{
	return "not yet implemented";
}

function SHOWCALCULATOR($cell)
{
	return "not yet implemented";
}

function SHOWDATEPICKER($cell, $doRefresh = false)
{
	return "not yet implemented";
}

function SHOWTOOL($name,$ActIcon="",$InactIcon="",$title="")
{
	return "not yet implemented";
}

function LISTBOX($OrgDisplayRange,$size=1,$update=true,$TargetCell,$orgformat="General",$initval="")
{
	return "not yet implemented";
}

function DIRECTHTML($string)
{
	return $string;
}

function TREECONTROL($SourceStartCell, $SourceEndCell,$TargetCell, $fontColor="#FFFFFF", $bgColor="#000000", $width =250, $height =300, $left =-1, $top =-1, $update =false, $fontSize =10, $useTreePath =false)
{
	return "not yet implemented";
}

// system
function CURRENTFOLDER($id=false)
{
	return "not yet implemented";
}

function CHECKUSERGROUP($checkusergroup)
{
	return "not yet implemented";
}

function SHEETNAME($cell="")
{
	return activesheet()->name;//"not yet implemented";
}

function LDAPDATA()
{
	return "not yet implemented";
}

function COPYCELLS($range)
{
	return "not yet implemented";
}

function PASTECELLS($range)
{
	return "not yet implemented";
}

function MENUXL($main_menu_name, $array)
{
	return "not yet implemented";
}

function WEEKNUMxl($exceltimestamp, $Typ = 1)
{
	if (is_string($exceltimestamp))
	{
		$tunix = strtotime($exceltimestamp);
	}
	else
	{
		$tunix = ($exceltimestamp - 25569) * 3600;
	}

	$week = date("W", $tunix );
	return $week;
}

function DAYxl($exceltimestamp)
{
	if (is_string($exceltimestamp))
	{
		$tunix = strtotime($exceltimestamp);
	}
	else
	{
		$tunix = ($exceltimestamp - 25569) * 86400;
	}

	return date("j", $tunix );
}

function MONTHxl($exceltimestamp)
{
    if (is_string($exceltimestamp))
	{
		$tunix = strtotime($exceltimestamp);
	}
	else
	{
		$tunix = ($exceltimestamp - 25569) * 86400;
	}

	return date("n", $tunix );
}

function YEARxl($exceltimestamp)
{
	if (is_string($exceltimestamp))
	{
		$tunix = strtotime($exceltimestamp);
	}
	else
	{
		$tunix = ($exceltimestamp - 25569) * 86400;
	}

	return date("Y", $tunix );
}

function Core2WSS2array($core)
{
	$wss2 = array(0,0);
	if (!is_array($core))
	{
		$tmpcore = array($core);
	}
	else
	{
		$tmpcore = $core;
	}
	$rows = count($tmpcore);
	$cols = 0;
	for ($i = 0; $i < $rows; $i++)
	{
		$tmprow = $tmpcore[$i];
		if (!is_array($tmprow))
		{
			$tmprow = array($tmprow);
		}
		$cols = count($tmprow);
		for ($j = 0; $j < $cols; $j++)
		{
			$wss2[] = $tmprow[$j];
		}
	}
	$wss2[0] = $rows;
	$wss2[1] = $cols;
	
	return $wss2;

}

function wildmatch($pattern, $string, $flag=true)
{
	if($flag && is_string($pattern) && (substr($pattern,0,1) == "<"))
	{
		$pattern = substr($pattern,1);
		return strtolower($string) < strtolower($pattern);
	}
	elseif($flag && is_string($pattern) && (substr($pattern,0,1) == ">"))
	{
		$pattern = substr($pattern,1);
		return strtolower($string) > strtolower($pattern);
	}
	else
	{
		// alles in Strings umwandeln
		$pattern = (string)$pattern;
		$string = (string)$string;
		//Macht die klasssiche wildcard vergleiche mit * und ?
		if(substr($pattern,0,1) == "=")
		{
			// "=" am Anfang eines Patterns ignorieren
			$pattern = substr($pattern,1);
		} // if
		
		$patternlen = strlen($pattern);
		$stringlen = strlen($string);
		$maxlen = max($patternlen, $stringlen);

		for ($i = 0; $i < $patternlen; $i++)
		{
			if ($pattern[$i] == "*")
			{
				for ($c=$i; $c < $maxlen; $c++)
				{
					if (wildmatch(substr($pattern, $i+1), substr($string, $c),false) )
					{
						return true;
					} // if
				} // for
				return false;
			} // if

			if ( ($patternlen < $stringlen) && ! ereg("\*",$pattern) )
			{
				return false;
			} // if

			if (($pattern[$i] == "?") && ($stringlen>0) && ($patternlen<=$stringlen) )
			{
				continue;
			} // if

			if (strtoupper($pattern[$i]) != strtoupper($string[$i]) )
			{
				return false;
			} // if

		} // for
		return true;
	}
} // function wildmatch


function DSUMxl($db, $spalte, $kb)
{
	// Teilweise implementierung. Formeln im Kriterienbereich, die sich
	// auf Zellen in der Datenbank beziehen, werden nicht unterstuetzt!

	$tmpdb = Core2WSS2array($db);
	$tmpkb = Core2WSS2array($kb);

	$rows_db=array_shift($tmpdb);
	$cols_db=array_shift($tmpdb);
	$rows_kb=array_shift($tmpkb);
	$cols_kb=array_shift($tmpkb);

	for($i = 0 ; $i <= ($cols_kb-1) ; $i++)
	{
		for($j=0 ; $j <= ($cols_db-1) ; $j++)
		{
			if(strtolower($tmpkb[$i])==strtolower($tmpdb[$j]))
			{
				$result[] = array($i,$j);
			}
		}
	}

	if(!is_numeric($spalte))
	{
		for ($x = 0; $x <= ($cols_db-1); $x++)
		{
			if(strtolower($tmpdb[$x])==strtolower($spalte))
			{
				$spalte=$x;
			}
		}
	}
	else
	{
		$spalte=$spalte-1;
	}
	$total=0;
	for( $m=$cols_db; $m<= (($cols_db*$rows_db)-1); $m=$m+$cols_db)
	{
		$andCond=true;
		for($n = 0; $n <= (count($result)-1); $n++)
		{
			if(!wildmatch($tmpkb[$cols_kb+$result[$n][0]],$tmpdb[$m+$result[$n][1]]))
			{
				$andCond=false;
				break;
			}
		}
		if($andCond==true)
		{
			$total=$total+$tmpdb[$m+$spalte];
		}
	}
	return $total;
}

?>