<?php

/*
 * @brief ajax
 *
 * @file Group.js
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
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: ChartInit.php 2444 2009-11-24 12:13:06Z predragm $
 *
 */

class ChartInit
{
	const MODE_NOFILTER = 1;
	const MODE_INSPECTOR = 2;
	const MODE_DYNEXMPL = 4;

	const INIT_BASE = 1;
	const INIT_CHARTGROUP = 2;
	const INIT_DATALABEL = 3;
	const INIT_HILOLINES = 4;
	const INIT_LEGENDENTRY = 5;
	const INIT_POINT = 6;
	const INIT_SERIES = 7;
	const INIT_TRENDLINE = 8;

	const INITSRC_FILE = 1;
	const INITSRC_DIR = 2;

	private $chart;
	private $charttype;
	private $layoutid;
	private $styleid;

	private $mode;

	private $initsrc_mode;

	private $dump_files;

	function __construct($chart_charttype, $mode = 0, $layoutid = 1, $styleid = 2)
	{
		if(is_object($chart_charttype) && $chart_charttype instanceof Chart)
		{
			$this->chart = $chart_charttype;
			$this->charttype = NULL;
		}
		else
		{
			$this->chart = NULL;
			$this->charttype = strval($chart_charttype);
			$this->layoutid = intval($layoutid);
			$this->styleid = intval($styleid);
		}

		$this->setMode($mode);
	}

	public function setMode ($mode)
	{
		$this->mode = intval($mode);

		$this->initsrc_path = array();

		if (defined('DUMPS_FILE') && !($this->mode & self::MODE_NOFILTER) && !($this->mode & self::MODE_DYNEXMPL))
			$this->initsrc_mode = self::INITSRC_FILE;
		else if (defined('DUMPS_DIR'))
			$this->initsrc_mode = self::INITSRC_DIR;
		else
			throw new Exception('Unknown initialization source.');
	}

	public function getMode()
	{
		return $this->mode;
	}

	public function setChartType($charttype)
	{
		$this->charttype = strval($charttype);
	}

	public function getChartType()
	{
		return $this->charttype;
	}

	public function setLayout($layoutid)
	{
		$this->layoutid = intval($layoutid);
	}

	public function getLayout()
	{
		return $this->layoutid;
	}

	public function setStyle($styleid)
	{
		$this->styleid = intval($styleid);
	}

	public function getStyle()
	{
		return $this->styleid;
	}

	public static function longval($val)
	{
		return '0x' . rtrim(ltrim($val, '&H'), '&');
	}

	public static function boolval($val)
	{
		return $val == 'True' ? TRUE : FALSE;
	}

	public static function type_convert($type)
	{
		switch($type)
		{
			case 'Long':
				$func = 'ChartInit::longval';
				break;

			case 'Single':
			case 'Double':
				$func = 'floatval';
				break;

			case 'Boolean':
				$func = 'ChartInit::boolval';
				break;

			default:
				$func = NULL;
				break;
		}

		return $func;
	}

	private function gen_path_fxs (&$path_pfx, &$path_sfx)
	{
		if ($this->initsrc_mode == self::INITSRC_FILE)
		{
			if (is_file(DUMPS_FILE) && is_readable(DUMPS_FILE))
			{
				$path_pfx = 'zip://' . realpath(DUMPS_FILE) . '#';
				$path_sfx = '';
			}
			else
				throw new Exception('Unreadable file "' . DUMPS_FILE . '".');
		}
		else if (is_dir(DUMPS_DIR) && is_readable(DUMPS_DIR))
		{
			$path_pfx = DUMPS_DIR;
			$path_sfx = '.csv';

			if (substr(DUMPS_DIR, -1) != '/')
				$path_pfx .= '/';
		}
		else
			throw new Exception('Unreadable directory "' . DUMPS_DIR . '".');
	}

	private function init_dumps ($init_part, $rootobj_parent = NULL)
	{
		$dump_rootobj = NULL;
		$layout_style = sprintf('_L%02dS%02d', $this->layoutid, $this->styleid);

		$this->gen_path_fxs(&$path_pfx, &$path_sfx);

		switch (intval($init_part))
		{
			case self::INIT_BASE:
				$dump_file_names[] = $path_pfx . $this->charttype . $layout_style . '_base' . $path_sfx;

				if($this->mode & self::MODE_DYNEXMPL)
					$dump_file_names[] = $path_pfx . $this->charttype . $layout_style . '_dynexmpl' . $path_sfx;

				$dump_rootobj = $this->chart;
				break;

			case self::INIT_CHARTGROUP:
				$dump_file_names[] = $path_pfx . $this->charttype . $layout_style . '_proto_ChartGroup' . $path_sfx;
				$dump_rootobj = new ChartGroup($rootobj_parent);
				break;

			case self::INIT_DATALABEL:
				$dump_file_names[] = $path_pfx . $this->charttype . $layout_style . '_proto_DataLabel' . $path_sfx;
				$dump_rootobj = new DataLabel($rootobj_parent);
				break;

			case self::INIT_HILOLINES:
				$dump_file_names[] = $path_pfx . $this->charttype . $layout_style . '_proto_HiLoLines' . $path_sfx;
				$dump_rootobj = new HiLoLines($rootobj_parent);
				break;

			case self::INIT_LEGENDENTRY:
				$dump_file_names[] = $path_pfx . $this->charttype . $layout_style . '_proto_LegendEntry' . $path_sfx;
				$dump_rootobj = new LegendEntry($rootobj_parent);
				break;

			case self::INIT_POINT:
				$dump_file_names[] = $path_pfx . $this->charttype . $layout_style . '_proto_Point' . $path_sfx;
				$dump_rootobj = new Point($rootobj_parent);
				break;

			case self::INIT_SERIES:
				$dump_file_names[] = $path_pfx . $this->charttype . $layout_style . '_proto_Series' . $path_sfx;
				$dump_rootobj = new Series($rootobj_parent);
				break;

			case self::INIT_TRENDLINE:
				$dump_file_names[] = $path_pfx . $this->charttype . $layout_style . '_proto_Trendline' . $path_sfx;
				$dump_rootobj = new Trendline($rootobj_parent);
				break;
		}

		$this->dump_files = array();

		if ($this->initsrc_mode == self::INITSRC_FILE)
		{
			$datf = new ZipArchive();

			if (($res = $datf->open(DUMPS_FILE)) === TRUE)
			{
				foreach ($dump_file_names as $dump_file_name)
				{
					$segment = substr($dump_file_name, strrpos($dump_file_name, '#') + 1);

					if ($datf->statName($segment) !== FALSE)
						$this->dump_files[] = fopen($dump_file_name, 'rt');
					else
						throw new Exception('Unable to access segment "'. $segment . '" in file "' . $dump_file_name . '".');
				}

				$datf->close();
			}
			else
				throw new Exception('Invalid file "' . DUMPS_FILE . '".');
		}
		else
		{
			foreach ($dump_file_names as $dump_file_name)
				if (is_file($dump_file_name) && is_readable($dump_file_name))
					$this->dump_files[] = fopen($dump_file_name, 'rt');
				else
					throw new Exception('Unable to open file "' . $dump_file_name . '".');
		}

		return $dump_rootobj;
	}

	private function close_dump_files()
	{
		foreach($this->dump_files as $dump_file)
			fclose($dump_file);
	}

	private function get_dump_line()
	{
		$i = 0;

		while(isset($this->dump_files[$i]))
		{
			$dump_line = fgetcsv($this->dump_files[$i], 1024, ',');

			if($dump_line !== FALSE)
				break;

			$i++;
		}

		return $dump_line;
	}

	public function has_part ($init_part)
	{
		$layout_style = sprintf('_L%02dS%02d', $this->layoutid, $this->styleid);

		$this->gen_path_fxs(&$path_pfx, &$path_sfx);

		switch (intval($init_part))
		{
			case self::INIT_CHARTGROUP:
				$dump_file_names[] = $path_pfx . $this->charttype . $layout_style . '_proto_ChartGroup' . $path_sfx;
				break;

			case self::INIT_DATALABEL:
				$dump_file_names[] = $path_pfx . $this->charttype . $layout_style . '_proto_DataLabel' . $path_sfx;
				break;

			case self::INIT_HILOLINES:
				$dump_file_names[] = $path_pfx . $this->charttype . $layout_style . '_proto_HiLoLines' . $path_sfx;
				break;

			case self::INIT_LEGENDENTRY:
				$dump_file_names[] = $path_pfx . $this->charttype . $layout_style . '_proto_LegendEntry' . $path_sfx;
				break;

			case self::INIT_POINT:
				$dump_file_names[] = $path_pfx . $this->charttype . $layout_style . '_proto_Point' . $path_sfx;
				break;

			case self::INIT_SERIES:
				$dump_file_names[] = $path_pfx . $this->charttype . $layout_style . '_proto_Series' . $path_sfx;
				break;

			case self::INIT_TRENDLINE:
				$dump_file_names[] = $path_pfx . $this->charttype . $layout_style . '_proto_Trendline' . $path_sfx;
				break;
		}

		$files_aok = TRUE;

		if ($this->initsrc_mode == self::INITSRC_FILE)
		{
			$datf = new ZipArchive();

			if (($res = $datf->open(DUMPS_FILE)) === TRUE)
			{
				foreach ($dump_file_names as $dump_file_name)
					if (($stat = $datf->statName(substr($dump_file_name, strrpos($dump_file_name, '#') + 1))) === FALSE || $stat['size'] <= 0)
					{
						$files_aok = FALSE;
						break;
					}

				$datf->close();
			}
			else
				throw new Exception('Invalid file "' . DUMPS_FILE . '".');
		}
		else
			foreach ($dump_file_names as $dump_file_name)
				if (!is_file($dump_file_name) || !is_readable($dump_file_name) || filesize($dump_file_name) <= 0)
				{
					$files_aok = FALSE;
					break;
				}

		return $files_aok;
	}

	public function init($init_part = self::INIT_BASE, $obj_parent = NULL, $obj_num = NULL)
	{
		if (!is_int($obj_num))
		{
			$obj_num = 1;
			$only_one = true;
		}
		else if ($obj_num == 0)
			return array();

		if($init_part == self::INIT_BASE && $obj_num > 1)
			return NULL;

		if(isset($this->chart))
		{
			$enum_refl = new ReflectionClass('XlChartType');
			$enum_names = array_flip($enum_refl->getConstants());

			$this->charttype = $enum_names[$this->chart->ChartType];
			$this->layoutid = $this->chart->GetLayout();
			$this->styleid = $this->chart->ChartStyle;
		}
		else if($init_part == self::INIT_BASE)
			$this->chart = new Chart();

		$dump_rootobjs[0] = $this->init_dumps($init_part, $obj_parent);
		for($i = 1; $i < $obj_num; $i++)
			$dump_rootobjs[$i] = clone $dump_rootobjs[0];

		$enum_refl_const = new ReflectionClass('Constants');
		$enum_names_const = array_flip($enum_refl_const->getConstants());

		while(($data = $this->get_dump_line()) !== FALSE)
		{
			//if(($data[2] == 'Object' || $data[2] == 'Collection') && __autoload($data[3]) === FALSE)
			//	print 'Missing ' . $data[3] . '<br>';
			//if($data[2] == 'Collection')
			//	print 'Collection ' . $data[3] . '<br>';

			$property = array();
			for($i = 0; $i < $obj_num; $i++)
				$property[$i] = $dump_rootobjs[$i];

			$proppath = split('\.', $data[1]);
			$ppnum = count($proppath);

			if($ppnum < 2)
				continue;

			$err = FALSE;

			//print $data[1] . '::' . $data[2] . '::' . $data[3] . '<br>';
			for($i = 1; $i < $ppnum - 1; $i++)
				if(is_object($property[0]))
				{
					if(strpos($proppath[$i], '(') === FALSE)
					{
						if(isset($property[0]->{$proppath[$i]}))
						{
							//print $proppath[$i - 1] . '(' . get_class($property[0]) . ')->' . $proppath[$i] . '<br>';
							for($j = 0; $j < $obj_num; $j++)
								$property[$j] = $property[$j]->{$proppath[$i]};
						}
						else
						{
							$err = TRUE;
							break;
						}
					}
					else
					{
						list($collection, $index) = sscanf(str_replace('(', ' ', $proppath[$i]), '%s %d)');
						if(isset($property[0]->$collection) && is_subclass_of($property[0]->$collection, 'Collection'))
							for($j = 0; $j < $obj_num; $j++)
								$property[$j] = $property[$j]->$collection->Item($index);
						else
						{
							$err = TRUE;
							break;
						}
					}
				}
				else
				{
					$err = TRUE;
					break;
				}

			if($err == TRUE)
				continue;

			if(isset($data[2]) && is_object($property[0]))
			{
				$type_is_array = strpos($data[2], '(');

				if($type_is_array === FALSE)
					$vartype = $data[2];
				else
					list($vartype, $arrcnt) = sscanf(str_replace('(', ' ', $data[2]), '%s %d)');

				switch($vartype)
				{
					case 'Object':
					case 'Collection':
						if(!class_exists($data[3]))
							break;

						if($vartype == 'Collection' && intval($data[4]) < 1)
							break;

						if(strpos($proppath[$ppnum - 1], '(') === FALSE)
							for($i = 0; $i < $obj_num; $i++)
							{
								eval('$obj = new ' . $data[3] . '($property[' . $i . ']);');
								$property[$i]->__add($proppath[$ppnum - 1], $obj, 'Object');
							}
						else
						{
							list($collection, $index) = sscanf(str_replace('(', ' ', $proppath[$ppnum - 1]), '%s %d)');
							//print $collection  . '<br>';
							if(isset($property[0]->$collection) && is_subclass_of($property[0]->$collection, 'Collection'))
								for($i = 0; $i < $obj_num; $i++)
								{
									eval('$obj = new ' . $data[3] . '($property[' . $i . ']->$collection);');
									$property[$i]->$collection->_add($obj, $index);
								}
						}
						//else print 'Missing ' . $data[3] . '<br>';
						break;

					case 'Enum':
						if($data[4] == '')
						{
							if(!($this->mode & self::MODE_INSPECTOR))
								for($i = 0; $i < $obj_num; $i++)
									$property[$i]->__add($proppath[$ppnum - 1], NULL, $data[3]);
							else
								for($i = 0; $i < $obj_num; $i++)
									$property[$i]->__add($proppath[$ppnum - 1], '&lt;empty&gt;', '_' . $data[3]);
						}
						else if($type_is_array === FALSE)
						{
							if(!($this->mode & self::MODE_INSPECTOR))
								for($i = 0; $i < $obj_num; $i++)
									$property[$i]->__add($proppath[$ppnum - 1], $data[4], $data[3]);
							else if(class_exists($data[3]) && is_object($enum_refl = new ReflectionClass($data[3])))
							{
								$enum_intval = intval($data[4]);
								$enum_names = array_flip($enum_refl->getConstants());

								if(isset($enum_names[$enum_intval]))
									for($i = 0; $i < $obj_num; $i++)
										$property[$i]->__add($proppath[$ppnum - 1], $data[3] . '::' . $enum_names[$enum_intval] . ' (' . $enum_intval . ')', '_' . $data[3]);
								else if(isset($enum_names_const[$enum_intval]))
									for($i = 0; $i < $obj_num; $i++)
										$property[$i]->__add($proppath[$ppnum - 1], 'Constants::' . $enum_names_const[$enum_intval] . ' (' . $enum_intval . ')', '_' . $data[3]);
								else
									for($i = 0; $i < $obj_num; $i++)
										$property[$i]->__add($proppath[$ppnum - 1], '&lt;unknown_enum&gt; (' . $enum_intval . ')', '_' . $data[3]);
							}
							else
								for($i = 0; $i < $obj_num; $i++)
									$property[$i]->__add($proppath[$ppnum - 1], '&lt;unknown_enum&gt; (' . intval($data[4]) . ')', '_' . $data[3]);
						}
						else
						{
							if(!($this->mode & self::MODE_INSPECTOR))
								for($i = 0; $i < $obj_num; $i++)
								{
									$propname = $proppath[$ppnum - 1];
									$property[$j]->__add($propname, array($arrcnt), $data[3] . '()');

									for($j = 0; $j < $arrcnt; $j++)
										$property[$i]->{$propname}[$j] = intval($data[4 + $j]);
								}
							else if(class_exists($data[3]) && is_object($enum_refl = new ReflectionClass($data[3])))
							{
								$enum_names = array_flip($enum_refl->getConstants());

								for($i = 0; $i < $obj_num; $i++)
								{
									$propname = $proppath[$ppnum - 1];
									$property[$i]->__add($propname, array($arrcnt), '_' .  $data[3] . '()');

									for($j = 0; $j < $arrcnt; $j++)
									{
										$enum_intval = intval($data[4 + $j]);

										if(isset($enum_names[$enum_intval]))
											$property[$i]->{$propname}[$j] = $data[3] . '::' . $enum_names[$enum_intval] . ' (' . $enum_intval . ')';
										else if(isset($enum_names_const[$enum_intval]))
											$property[$i]->{$propname}[$j] = 'Constants::' . $enum_names_const[$enum_intval] . ' (' . $enum_intval . ')';
										else
											$property[$i]->{$propname}[$j] = '&lt;unknown_enum&gt; (' . $enum_intval . ')';
									}
								}
							}
							else
								for($i = 0; $i < $obj_num; $i++)
								{
									$propname = $proppath[$ppnum - 1];
									$property[$i]->__add($propname, array($arrcnt), '_' . $data[3] . '()');

									for($j = 0; $j < $arrcnt; $j++)
										$property[$i]->{$propname}[$j] = '&lt;unknown_enum&gt; (' . intval($data[4 + $j]) . ')';
								}
						}
						break;

					case 'Empty':
						break;

					default:
						if($data[3] == '')
						{
							if(!($this->mode & self::MODE_INSPECTOR))
								for($i = 0; $i < $obj_num; $i++)
									$property[$i]->__add($proppath[$ppnum - 1], NULL, $vartype);
							else
								for($i = 0; $i < $obj_num; $i++)
									$property[$i]->__add($proppath[$ppnum - 1], '&lt;empty&gt;', '_' . $vartype);
						}
						else if(!$type_is_array)
						{
							if($this->mode & self::MODE_INSPECTOR && $vartype == 'Boolean')
								$vartype = '_Boolean';

							for($i = 0; $i < $obj_num; $i++)
								$property[$i]->__add($proppath[$ppnum - 1], $data[3], $vartype);
						}
						else
						{
							$propname = $proppath[$ppnum - 1];
							$convert_func = $this->type_convert($vartype);

							for($i = 0; $i < $obj_num; $i++)
							{
								$property[$i]->__add($propname, array($arrcnt), $vartype . '()');

								for($j = 0; $j < $arrcnt; $j++)
									$property[$i]->{$propname}[$j] = $convert_func == NULL ? $data[3 + $j] : call_user_func($convert_func, $data[3 + $j]);
							}
						}
						break;
				}
			}
		}

		$this->close_dump_files();

		return isset($only_one) ? $dump_rootobjs[0] : $dump_rootobjs;
	}

}

?>