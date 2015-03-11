<?xml version="1.0" encoding="utf-8"?>
<stylesheet version="2.0"
            xmlns="http://www.w3.org/1999/XSL/Transform"
            xmlns:doc="http://tempuri.org/Palo/SpreadsheetFuncs/Documentation.xsd">

  <!-- 
	Florian Schaper <florian.schaper@jedox.com>
	Copyright (c) Jedox AG, 2007-2009
  -->
  
  <output method="text" indent="no"/>
  <strip-space elements="*"/>

<template match="/"><text disable-output-escaping="yes"><![CDATA[/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License (Version 2) as published
 *  by the Free Software Foundation at http://www.gnu.org/copyleft/gpl.html.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along with
 *  this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 *  Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *  You may obtain a copy of the License at
 *
 *  <a href="http://www.jedox.com/license_palo_bi_suite.txt">
 *    http://www.jedox.com/license_palo_bi_suite.txt
 *  </a>
 *
 *  If you are developing and distributing open source applications under the
 *  GPL License, then you are free to use Worksheetserver under the GPL License.
 *  For OEMs, ISVs, and VARs who distribute Worksheetserver with their products,
 *  and do not license and distribute their source code under the GPL, Jedox provides
 *  a flexible OEM Commercial License.
 */

// This file has been auto-generated. Don't change it by hand!

]]></text>

<apply-templates select="*"/>

</template>

<template match="doc:Function">
<if test="./doc:ExcelSpecific and not(./doc:ExcelSpecific[@xl_helper='true'] or ./doc:ExcelSpecific[@xl_helper='1'])">
<text disable-output-escaping="yes">PALO_FUNCTION_WRAPPER(</text>
<value-of disable-output-escaping="yes" select="@c_name"/>
<text disable-output-escaping="yes">,</text>
<value-of disable-output-escaping="yes" select="@internal_name"/>
<text disable-output-escaping="yes">);</text>
</if>
</template>
  <template match="doc:eof">
    <text disable-output-escaping="yes">
  </text>
  </template>
</stylesheet>