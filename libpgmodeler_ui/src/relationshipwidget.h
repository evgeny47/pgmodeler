/*
# PostgreSQL Database Modeler (pgModeler)
#
# Copyright 2006-2018 - Raphael Araújo e Silva <raphael@pgmodeler.io>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation version 3.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# The complete text of GPLv3 is at LICENSE file on source code root directory.
# Also, you can get the complete GNU General Public License at <http://www.gnu.org/licenses/>
*/

/**
\ingroup libpgmodeler_ui
\class RelationshipWidget
\brief Implements the operations to create/edit relationships via form.
*/

#ifndef RELATIONSHIP_WIDGET_H
#define RELATIONSHIP_WIDGET_H

#include "baseobjectwidget.h"
#include "ui_relationshipwidget.h"
#include "objectstablewidget.h"
#include "colorpickerwidget.h"
#include "hinttextwidget.h"

class RelationshipWidget: public BaseObjectWidget, public Ui::RelationshipWidget {
	private:
		Q_OBJECT

		static const unsigned GENERAL_TAB=0,
		ATTRIBUTES_TAB=1,
		CONSTRAINTS_TAB=2,
		SPECIAL_PK_TAB=3,
		ADVANCED_TAB=4;

		HintTextWidget *gen_tab_name_ht, *ref_table_ht, *recv_table_ht, *identifier_ht, *single_pk_ht;

		ColorPickerWidget *color_picker;

		//! \brief Stores the tab objects to change the configuration of the form depending on the type of the relationship
		QWidgetList tabs;

		//! \brief Stores the original labels of the tabs
		QStringList tab_labels;

		SyntaxHighlighter *table1_hl,
		*table2_hl,
		*patterns_hl[7];

		//! \brief Table widgets that stores the attributes, constraint and advanced objects of relationship
		ObjectsTableWidget *attributes_tab,
		*constraints_tab,
		*advanced_objs_tab;

		//! \brief Lists the objects of relationship (attributes/constraints) on the respective table widget
		void listObjects(ObjectType obj_type);

		//! \brief Lists the advanced objects in the repective table widget
		void listAdvancedObjects(void);

		/*! \brief Shows the object data in the specified table row. The table widget is idenfied by
		 the current object type */
		void showObjectData(TableObject *object, int row);

		/*! \brief Template method that opens the editing form for the specified object.
				Class and ClassWidget should be compatible, e.g., "Column" can only be edited using ColumnWidget */
		template<class Class, class ClassWidget>
		int openEditingForm(TableObject *object, BaseObject *parent = nullptr);

	protected:
		void setAttributes(DatabaseModel *model, OperationList *op_list, Table *src_tab, Table *dst_tab, unsigned rel_type);

	public:
		RelationshipWidget(QWidget * parent = 0);
		void setAttributes(DatabaseModel *model, OperationList *op_list, BaseRelationship *base_rel);

		QSize getIdealSize(void);

	private slots:
		void addObject(void);
		void editObject(int row);
		void removeObject(int row);
		void removeObjects(void);
		void showAdvancedObject(int row);
		void selectCopyOptions(void);
		void listSpecialPkColumns(void);
		void duplicateObject(int curr_row, int new_row);

		void useFKGlobalSettings(bool value);
		void usePatternGlobalSettings(bool value);

	public slots:
		void applyConfiguration(void);
		void cancelConfiguration(void);

		friend class ModelWidget;
};

#endif
