<?php

/*
 * Copyright (C) 2006-2009 Jedox AG, Freiburg, Germany
 * http://www.jedox.com/
 *
 * \author
 * Predrag Malicevic <predrag.malicevic@develabs.com>
 *
 * \version
 * SVN: $Id: XLSProfiler.php 2212 2009-09-30 13:16:31Z predragm $
 *
 * \see
 * LICENSE.txt
 *
 */

class XLSProfiler extends XLSObject
{
	private $ms;
	private $logfile;

	function __construct($logfile = NULL)
	{
		$this->ms = array();

		if($logfile != NULL)
			$this->setLogFile($logfile);
		else
			$this->logfile = NULL;
	}

	public function log($n, $o)
	{
		$m = array($n, $o);

		if(!in_array($m, $this->ms, TRUE))
			$this->ms[] = $m;
	}

	public function setLogFile($fname)
	{
		if(!file_exists($fname))
		{
			if(($fh = fopen($fname, 'wb')) !== FALSE)
			{
				$this->logfile = $fname;
				fclose($fh);
			}
			else
				$this->logfile = NULL;
		}
		else if(is_file($fname) && is_writable($fname))
			$this->logfile = $fname;
		else
			$this->logfile = NULL;
	}

	public function show($hideObjs = TRUE, $hideColMems = TRUE)
	{
		if(count($this->ms) < 1)
			return;

		$paths = array();

		for($msnum = count($this->ms), list($mname, $mobj) = $this->ms[$i = 0]; $i < $msnum; list($mname, $mobj) = $this->ms[++$i])
		{
			if($hideObjs && $mobj->__m[$mname][XLSObject::M_TYPE] == 'Object')
				continue;

			if($mobj->__m[$mname][XLSObject::M_VAL] instanceOf Collection)
				$mname .= '()';

			$currpath = array($mname);

			$o = $mobj;

			do
			{
				$p = $o->__m['Parent'][XLSObject::M_VAL];

				if($p == NULL)
				{
					array_unshift($currpath, 'Chart');
					break;
				}

				if($p instanceof Collection && !$hideColMems)
				{
					for($i = 1; $i <= $p->Count(); $i++)
						if($p->Item($i) === $o)
						{
							array_unshift($currpath, get_class($p->Item($i)));
							break;
						}
				}
				else
				{
					foreach($p->__m as $mn => $ma)
						if($ma[XLSObject::M_VAL] === $o)
						{
							if($o instanceOf Collection)
								$mn .= '()';

							array_unshift($currpath, $mn);
							break;
						}
				}

				$o = $p;
			}
			while($o != NULL);

			$paths[] = implode('.', $currpath);
		}

		$paths = array_unique($paths);
		sort($paths);

		if($this->logfile != NULL)
		{
			$logpaths = file($this->logfile, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);
			$log_fh = fopen($this->logfile, 'ab');
		}

		foreach($paths as $idx => $path)
		{
			print sprintf('% 4u: ', $idx + 1) . $path . "\n";

			if($this->logfile != NULL && !in_array($path, $logpaths))
				fwrite($log_fh, $path . "\n");
		}

		if($this->logfile != NULL)
			fclose($log_fh);
	}
}

?>