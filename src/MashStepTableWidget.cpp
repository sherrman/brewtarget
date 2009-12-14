/*
 * MashStepTableWidget.cpp is part of Brewtarget, and is Copyright Philip G. Lee
 * (rocketman768@gmail.com), 2009.
 *
 * Brewtarget is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Brewtarget is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QTableView>
#include <QWidget>
#include "MashStepTableModel.h"
#include "MashStepTableWidget.h"

MashStepTableWidget::MashStepTableWidget(QWidget* parent)
        : QTableView(parent)
{
   model = new MashStepTableModel(this);
   setModel(model);
   setItemDelegate(new MashStepItemDelegate(this));
}

MashStepTableModel* MashStepTableWidget::getModel()
{
   return model;
}
