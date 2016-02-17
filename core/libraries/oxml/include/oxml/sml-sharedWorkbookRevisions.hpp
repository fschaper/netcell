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


// This file has been auto-generated. Don't change it by hand!

#ifndef SML_SHAREDWORKBOOKREVISIONS_HPP
#define SML_SHAREDWORKBOOKREVISIONS_HPP


#include "sml-baseTypes.hpp"
#include "shared-relationshipReference.hpp"
#include "sml-sheet.hpp"
#include "sml-styles.hpp"

namespace spreadsheetml
{
	using namespace ::xio;
	using namespace ::xio::xml::schema;

	class CT_SheetId;
	class CT_SheetIdMap;
	class CT_Reviewed;
	class CT_ReviewedRevisions;
	class CT_RevisionHeader;
	class CT_RevisionHeaders;
	class CT_UndoInfo;
	class CT_RevisionCellChange;
	class CT_RevisionFormatting;
	class CT_RevisionRowColumn;
	class CT_RevisionMove;
	class CT_RevisionCustomView;
	class CT_RevisionSheetRename;
	class CT_RevisionInsertSheet;
	class CT_RevisionAutoFormatting;
	class CT_RevisionDefinedName;
	class CT_RevisionComment;
	class CT_RevisionQueryTableField;
	class CT_RevisionConflict;
	class CT_Revisions;
	class sml_sharedWorkbookRevisions;

	class CT_SheetId
	{
	public:
		UnsignedInt val;
	};

	class CT_SheetIdMap
	{
	public:
		std::vector< CT_SheetId > sheetId;
		optional< UnsignedInt > count;
	};

	class CT_Reviewed
	{
	public:
		UnsignedInt rId;
	};

	class CT_ReviewedRevisions
	{
	public:
		std::vector< CT_Reviewed > reviewed;
		optional< UnsignedInt > count;
	};

	class CT_RevisionHeader
	{
	public:
		CT_SheetIdMap sheetIdMap;
		poptional< CT_ReviewedRevisions > reviewedList;
		poptional< CT_ExtensionList > extLst;
		ST_Guid guid;
		DateTime dateTime;
		UnsignedInt maxSheetId;
		ST_Xstring userName;
		::relationships::ST_RelationshipId id;
		optional< UnsignedInt > minRId;
		optional< UnsignedInt > maxRId;
	};

	class CT_RevisionHeaders
	{
	public:
		CT_RevisionHeaders() : shared(true), diskRevisions(false), history(true), trackRevisions(true), exclusive(false), revisionId(0U), version(1), keepChangeHistory(true), _protected_(false), preserveHistory(30U) {}
		std::vector< CT_RevisionHeader > header;
		ST_Guid guid;
		poptional< ST_Guid > lastGuid;
		Boolean shared;
		Boolean diskRevisions;
		Boolean history;
		Boolean trackRevisions;
		Boolean exclusive;
		UnsignedInt revisionId;
		Int version;
		Boolean keepChangeHistory;
		Boolean _protected_;
		UnsignedInt preserveHistory;
	};

	class ST_FormulaExpression
	{
		static String _literals[];
		String _value;
	public:
		enum value { area, areaError, computedArea, ref, refError };

		static const String area_literal;
		static const String areaError_literal;
		static const String computedArea_literal;
		static const String ref_literal;
		static const String refError_literal;

		ST_FormulaExpression() : _value(ref_literal) {}
		ST_FormulaExpression(value val) : _value(convert(val)) {}
		ST_FormulaExpression(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 5, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_UndoInfo
	{
	public:
		CT_UndoInfo() : ref3D(false), array(false), v(false), nf(false), cs(false) {}
		UnsignedInt index;
		ST_FormulaExpression exp;
		Boolean ref3D;
		Boolean array;
		Boolean v;
		Boolean nf;
		Boolean cs;
		ST_RefA dr;
		poptional< ST_Xstring > dn;
		poptional< ST_CellRef > r;
		optional< UnsignedInt > sId;
	};

	class CT_RevisionCellChange
	{
	public:
		CT_RevisionCellChange() : ua(false), ra(false), odxf_attr(false), xfDxf(false), s(false), dxf(false), quotePrefix(false), oldQuotePrefix(false), ph(false), oldPh(false), endOfListFormulaUpdate(false) {}
		poptional< CT_Cell > oc;
		CT_Cell nc;
		poptional< CT_Dxf > odxf;
		poptional< CT_Dxf > ndxf;
		poptional< CT_ExtensionList > extLst;
		UnsignedInt rId;
		Boolean ua;
		Boolean ra;
		UnsignedInt sId;
		Boolean odxf_attr;
		Boolean xfDxf;
		Boolean s;
		Boolean dxf;
		poptional< ST_NumFmtId > numFmtId;
		Boolean quotePrefix;
		Boolean oldQuotePrefix;
		Boolean ph;
		Boolean oldPh;
		Boolean endOfListFormulaUpdate;
	};

	class CT_RevisionFormatting
	{
	public:
		CT_RevisionFormatting() : xfDxf(false), s(false) {}
		poptional< CT_Dxf > dxf;
		poptional< CT_ExtensionList > extLst;
		UnsignedInt sheetId;
		Boolean xfDxf;
		Boolean s;
		ST_Sqref sqref;
		optional< UnsignedInt > start;
		optional< UnsignedInt > length;
	};

	class ST_rwColActionType
	{
		static String _literals[];
		String _value;
	public:
		enum value { deleteCol, deleteRow, insertCol, insertRow };

		static const String deleteCol_literal;
		static const String deleteRow_literal;
		static const String insertCol_literal;
		static const String insertRow_literal;

		ST_rwColActionType() : _value(insertRow_literal) {}
		ST_rwColActionType(value val) : _value(convert(val)) {}
		ST_rwColActionType(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 4, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_RevisionRowColumn
	{
	public:
		CT_RevisionRowColumn() : ua(false), ra(false), eol(false), edge(false) {}
		optional< std::vector< CT_UndoInfo > > undo;
		optional< std::vector< CT_RevisionCellChange > > rcc;
		optional< std::vector< CT_RevisionFormatting > > rfmt;
		UnsignedInt rId;
		Boolean ua;
		Boolean ra;
		UnsignedInt sId;
		Boolean eol;
		ST_Ref ref;
		ST_rwColActionType action;
		Boolean edge;
	};

	class CT_RevisionMove
	{
	public:
		CT_RevisionMove() : ua(false), ra(false), sourceSheetId(0U) {}
		optional< std::vector< CT_UndoInfo > > undo;
		optional< std::vector< CT_RevisionCellChange > > rcc;
		optional< std::vector< CT_RevisionFormatting > > rfmt;
		UnsignedInt rId;
		Boolean ua;
		Boolean ra;
		UnsignedInt sheetId;
		ST_Ref source;
		ST_Ref destination;
		UnsignedInt sourceSheetId;
	};

	class ST_RevisionAction
	{
		static String _literals[];
		String _value;
	public:
		enum value { add, _delete_ };

		static const String add_literal;
		static const String _delete__literal;

		ST_RevisionAction() : _value(add_literal) {}
		ST_RevisionAction(value val) : _value(convert(val)) {}
		ST_RevisionAction(const String& str) : _value(str) {}

		static value convert(const String& str) { return (value)::xio::util::binary_search(str, _literals, 2, 0); }
		static String convert(value v) { return _literals[(int)v]; }

		bool operator == (const String& str) const { return str == _value; }
		bool operator == (value val) const {return convert(val) == _value; }
		bool operator != (const String& str) const { return str != _value; }
		bool operator != (value val) const {return convert(val) != _value; }

		const String& operator = (const String& str) { _value = str; return str; }
		const value& operator = (const value& val) { _value = convert(val); return val; }

		operator const String& () const { return _value; }
		operator String& () { return _value; }
		operator value () const { return convert(_value); }
		String serialize() const { return _value; }
	};

	class CT_RevisionCustomView
	{
	public:
		ST_Guid guid;
		ST_RevisionAction action;
	};

	class CT_RevisionSheetRename
	{
	public:
		CT_RevisionSheetRename() : ua(false), ra(false) {}
		poptional< CT_ExtensionList > extLst;
		UnsignedInt rId;
		Boolean ua;
		Boolean ra;
		UnsignedInt sheetId;
		ST_Xstring oldName;
		ST_Xstring newName;
	};

	class CT_RevisionInsertSheet
	{
	public:
		CT_RevisionInsertSheet() : ua(false), ra(false) {}
		UnsignedInt rId;
		Boolean ua;
		Boolean ra;
		UnsignedInt sheetId;
		ST_Xstring name;
		UnsignedInt sheetPosition;
	};

	class CT_RevisionAutoFormatting
	{
	public:
		UnsignedInt sheetId;
		optional< UnsignedInt > autoFormatId;
		optional< Boolean > applyNumberFormats;
		optional< Boolean > applyBorderFormats;
		optional< Boolean > applyFontFormats;
		optional< Boolean > applyPatternFormats;
		optional< Boolean > applyAlignmentFormats;
		optional< Boolean > applyWidthHeightFormats;
		ST_Ref ref;
	};

	class CT_RevisionDefinedName
	{
	public:
		CT_RevisionDefinedName() : ua(false), ra(false), customView(false), function(false), oldFunction(false), hidden(false), oldHidden(false) {}
		poptional< ST_Formula > formula;
		poptional< ST_Formula > oldFormula;
		poptional< CT_ExtensionList > extLst;
		UnsignedInt rId;
		Boolean ua;
		Boolean ra;
		optional< UnsignedInt > localSheetId;
		Boolean customView;
		ST_Xstring name;
		Boolean function;
		Boolean oldFunction;
		optional< UnsignedByte > functionGroupId;
		optional< UnsignedByte > oldFunctionGroupId;
		optional< UnsignedByte > shortcutKey;
		optional< UnsignedByte > oldShortcutKey;
		Boolean hidden;
		Boolean oldHidden;
		poptional< ST_Xstring > customMenu;
		poptional< ST_Xstring > oldCustomMenu;
		poptional< ST_Xstring > description;
		poptional< ST_Xstring > oldDescription;
		poptional< ST_Xstring > help;
		poptional< ST_Xstring > oldHelp;
		poptional< ST_Xstring > statusBar;
		poptional< ST_Xstring > oldStatusBar;
		poptional< ST_Xstring > comment;
		poptional< ST_Xstring > oldComment;
	};

	class CT_RevisionComment
	{
	public:
		CT_RevisionComment() : action(ST_RevisionAction::add_literal), alwaysShow(false), old(false), hiddenRow(false), hiddenColumn(false), oldLength(0U), newLength(0U) {}
		UnsignedInt sheetId;
		ST_CellRef cell;
		ST_Guid guid;
		ST_RevisionAction action;
		Boolean alwaysShow;
		Boolean old;
		Boolean hiddenRow;
		Boolean hiddenColumn;
		ST_Xstring author;
		UnsignedInt oldLength;
		UnsignedInt newLength;
	};

	class CT_RevisionQueryTableField
	{
	public:
		UnsignedInt sheetId;
		ST_Ref ref;
		UnsignedInt fieldId;
	};

	class CT_RevisionConflict
	{
	public:
		CT_RevisionConflict() : ua(false), ra(false) {}
		UnsignedInt rId;
		Boolean ua;
		Boolean ra;
		optional< UnsignedInt > sheetId;
	};

	class CT_Revisions
	{
	public:
		optional< std::vector< CT_RevisionRowColumn > > rrc;
		optional< std::vector< CT_RevisionMove > > rm;
		optional< std::vector< CT_RevisionCustomView > > rcv;
		optional< std::vector< CT_RevisionSheetRename > > rsnm;
		optional< std::vector< CT_RevisionInsertSheet > > ris;
		optional< std::vector< CT_RevisionCellChange > > rcc;
		optional< std::vector< CT_RevisionFormatting > > rfmt;
		optional< std::vector< CT_RevisionAutoFormatting > > raf;
		optional< std::vector< CT_RevisionDefinedName > > rdn;
		optional< std::vector< CT_RevisionComment > > rcmt;
		optional< std::vector< CT_RevisionQueryTableField > > rqt;
		optional< std::vector< CT_RevisionConflict > > rcft;
	};

	class sml_sharedWorkbookRevisions
	{
	public:
		poptional< CT_RevisionHeaders > headers;
		poptional< CT_Revisions > revisions;
	};

}
#endif

