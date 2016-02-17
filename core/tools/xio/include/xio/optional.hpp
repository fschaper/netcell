/**
 *  \file
 *  Copyright (C) 2006-2009 Jedox AG
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

#ifndef XIO_OPTIONAL_H
#define XIO_OPTIONAL_H

#include <memory>

namespace xio 
{
	template<typename T> class optional
	{
		T _v;
		bool _present;

	public:
		optional() : _v(), _present(false) {}
		optional(const T& v) : _v(v), _present(true) {};
		~optional() {};

		bool present() const { return _present; }

		T& get() { return _v;}
		T& getset() { _present = true; return _v; }
		const T& get() const { return _v;}
		void clear() { _present = false; }

		bool operator == (const T& v) {
			return present() && _v == v;
		}

		T& operator = (const T& v) { _v = v; _present = true; return _v; }
	};

	template<typename T> class poptional
	{
		std::auto_ptr<T> _p;
	public:
		poptional() {}
		poptional(const T& v) : _p(new T(v)) {};
		poptional(const poptional& v) : _p(0) { if (v.present()) _p.reset(new T(v.get())); };
		~poptional() {};

		bool present() const { return _p.get()!=0; }

		T& get() { return *_p;}
		T& getset() { if (!present()) _p.reset(new T()); return *_p; }
		const T& get() const { return *_p;}
		void clear() { _p.clear(); }

		bool operator == (const T& v) {
			return present() && *_p == v;
		}

		const T& operator = (const T& v) { _p.reset(new T(v)); return v; }
		const poptional& operator = (const poptional& v) { _p.reset(v.present() ? new T(v.get()) : 0); return *this; }
	};
}

#endif //XIO_OPTIONAL_H
