<?php

/*
 * \brief script that revitalizes PHP sessions to prevent them from being garbage-collected
 *
 * \file ping.php
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: ping.php 3422 2010-06-22 14:17:19Z predragm $
 *
 */

// studio sess
session_name('STUDIO_SESSID');
session_start();
$wssu_sessid = $_SESSION['WSSU_SESSID'];
$wssd_sessid = $_SESSION['WSSD_SESSID'];
session_write_close();

// wss user sess
session_id($wssu_sessid);
session_name('WSSU_SESSID');
session_start();
session_write_close();

// wss designer sess
session_id($wssd_sessid);
session_name('WSSD_SESSID');
session_start();
session_write_close();

?>