<?php

/*
 * \brief autoloading script
 *
 * \file autoload.php
 *
 * Copyright (C) 2006-2010 Jedox AG
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
 * Drazen Kljajic <drazen.kljajic@develabs.com>
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: autoload.php 4580 2011-02-08 15:11:21Z predragm $
 *
 */

define ('DUMPS_FILE', '../../../base/charts/chartinit/chartinit.dat');

set_include_path(
'../../../base' . PATH_SEPARATOR . '../../../base/util' . PATH_SEPARATOR . '../../../base/w3s' . PATH_SEPARATOR . '../../../base/rtn' . PATH_SEPARATOR . '../../../base/dynarange' . PATH_SEPARATOR
. '../../../base/charts' . PATH_SEPARATOR . '../../../base/charts/phpxls' . PATH_SEPARATOR . '../../../base/charts/phpxls/enum' . PATH_SEPARATOR . '../../../base/charts/chartinit' . PATH_SEPARATOR
. '../../../base/charts/chartmapper' . PATH_SEPARATOR . '../../../base/charts/chartmapper/adapters' . PATH_SEPARATOR . '../../../base/palo_import' . PATH_SEPARATOR
. '../../../lib'
);

function __autoload ($class_name)
{
	require $class_name . '.php';
}

?>