<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
                xmlns:wss="http://www.jedox.com/jedox/wss" 
				xmlns:fn="http://www.w3.org/2005/xpath-functions"
				xmlns="http://www.jedox.com/jedox/wss"
				version="2.0">

<!-- 
	Florian Schaper <florian.schaper@jedox.com>
	Copyright (c) Jedox AG, 2009
-->

	<xsl:output method="text" version="1.0" indent="yes"/>
	
	<xsl:template match="/" >
		<xsl:if test="count(//Error)">
			<xsl:text>list of errors in the run test cases&#10;</xsl:text>
			<xsl:text>------------------------------------&#10;</xsl:text>
			<xsl:apply-templates select="//Error"/>
		</xsl:if>
		
		<xsl:if test="count(//Exception)">
			<xsl:text>list of unexpected exceptions&#10;</xsl:text>
			<xsl:text>------------------------------------&#10;</xsl:text>
			<xsl:apply-templates select="//Exception"/>
		</xsl:if>
	</xsl:template>
				
	<xsl:template match="Error" >
		<xsl:text>testcase </xsl:text><xsl:value-of select="current()/../@name"/><xsl:text>&#10;</xsl:text>
		<xsl:text>&#9;error in file </xsl:text><xsl:value-of select="@file"/><xsl:text> line </xsl:text><xsl:value-of select="@line"/><xsl:text>&#10;</xsl:text>
		<xsl:text>&#9;</xsl:text><xsl:value-of select="replace(current(),'&#10;','&#10;&#9;')"/>
		<xsl:text>&#10;</xsl:text>
		<xsl:text>&#10;</xsl:text>
	</xsl:template>

	<xsl:template match="Exception" >
		<xsl:text>testcase </xsl:text><xsl:value-of select="current()/../@name"/><xsl:text>&#10;</xsl:text>
		<xsl:text>&#9;exception in file </xsl:text><xsl:value-of select="LastCheckpoint/@file"/><xsl:text> line </xsl:text><xsl:value-of select="LastCheckpoint/@line"/><xsl:text>&#10;</xsl:text>
		<xsl:text>&#9;</xsl:text><xsl:value-of select="."/>
		<xsl:text>&#10;</xsl:text>
		<xsl:text>&#10;</xsl:text>
	</xsl:template>
	
</xsl:stylesheet>
