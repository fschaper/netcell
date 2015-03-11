/**
 *  \file
 *  Copyright (C) 2006-2010 Jedox AG, Freiburg i.Br., Germany
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
 *
 *  \Author
 *  Florian Schaper <florian.schaper@jedox.com>
 */

#pragma once

/*!
 * this family of classes is used to handle the singleton order-of-destruction
 * problem. in C++, static objects are destroyed in the reverse order of their
 * creation so if you have a singleton A and a singleton B whereas B relies on
 * functionality of A upon destruction you would have to make sure that A is
 * created before B.
 *
 * with the help of the 'singleton_dependency' class you can specify interclass
 * dependencies.
 * We can now programatically enforce the dependency relationship between our
 * A and B from the initial example by defining B as
 *
 * class B : public singleton<B>
 * {
 *   friend singleton<B>;
 * public:
 * private:
 *   B() {
 *   }
 * };
 *
 * class A : public singleton<A, singleton_dependency<B> >
 * {
 *   friend singleton<A, singleton_dependency<B> >;
 * public:
 * private:
 *   A() {
 *   }
 * };
 *
 * the singleton base class will detect the 'singleton_dependency_type' and will,
 * with the help of the singleton_dependency_* set of classes instatiate the
 * required objects before the initial intantiation of the latter object.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */


/*!
 * \brief
 * no singleton dependencies.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
class no_dependency
{
public:
    no_dependency() {
    }

    void dummy() {}
};

/*!
 * \brief
 * dependency to one other object.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class s1_T>
class singleton_dependency
{
public:
    singleton_dependency() {
        volatile s1_T& s1 = s1_T::instance();
    }

    void dummy() volatile {}
};

/*!
 * \brief
 * dependency to two other objects.
 *

 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class s1_T, class s2_T>
class singleton_dependency_2
{
public:
    singleton_dependency_2() {
        volatile s1_T& s1 = s1_T::instance();
        volatile s2_T& s2 = s2_T::instance();
    }

    void dummy() volatile {}
};

/*!
 * \brief
 * dependency to three other objects.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class s1_T, class s2_T, class s3_T>
struct singleton_dependency_3 {
public:
    singleton_dependency_3() {
        volatile s1_T& s1 = s1_T::instance();
        volatile s2_T& s2 = s2_T::instance();
        volatile s3_T& s3 = s3_T::instance();
    }

    void dummy() volatile {}
};

/*!
 * \brief
 * dependency to four other objects.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class s1_T, class s2_T, class s3_T, class s4_T>
class singleton_dependency_4
{
public:
    singleton_dependency_4() {
        volatile s1_T& s1 = s1_T::instance();
        volatile s2_T& s2 = s2_T::instance();
        volatile s3_T& s3 = s3_T::instance();
        volatile s4_T& s4 = s4_T::instance();
    }

    void dummy() volatile {}
};

/*!
 * \brief
 * dependency to five other objects.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class s1_T, class s2_T, class s3_T, class s4_T, class s5_T>
class singleton_dependency_5
{
public:
    singleton_dependency_5() {
        volatile s1_T& s1 = s1_T::instance();
        volatile s2_T& s2 = s2_T::instance();
        volatile s3_T& s3 = s3_T::instance();
        volatile s4_T& s4 = s4_T::instance();
        volatile s5_T& s5 = s5_T::instance();
    }

    void dummy() volatile {}
};

/*!
 * \brief
 * dependency to six other objects.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class s1_T, class s2_T, class s3_T, class s4_T, class s5_T, class s6_T>
class singleton_dependency_6
{
public:
    singleton_dependency_6() {
        volatile s1_T& s1 = s1_T::instance();
        volatile s2_T& s2 = s2_T::instance();
        volatile s3_T& s3 = s3_T::instance();
        volatile s4_T& s4 = s4_T::instance();
        volatile s5_T& s5 = s5_T::instance();
        volatile s6_T& s6 = s6_T::instance();
    }

    void dummy() volatile {}
};

/*!
 * \brief
 * dependency to seven other objects.
 *
 * \author
 * Florian Schaper <florian.schaper@jedox.com>
 */
template<class s1_T, class s2_T, class s3_T, class s4_T, class s5_T, class s6_T, class s7_T>
class singleton_dependency_7
{
public:
    singleton_dependency_7() {
        volatile s1_T& s1 = s1_T::instance();
        volatile s2_T& s2 = s2_T::instance();
        volatile s3_T& s3 = s3_T::instance();
        volatile s4_T& s4 = s4_T::instance();
        volatile s5_T& s5 = s5_T::instance();
        volatile s6_T& s6 = s6_T::instance();
        volatile s7_T& s7 = s7_T::instance();
    }

    void dummy() volatile {}
};

