/*
 * BeerXMLElement.cpp is part of Brewtarget, and is Copyright Philip G. Lee
 * (rocketman768@gmail.com), 2009-2011.
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

#include "BeerXMLElement.h"
#include <QDomElement>
#include <QDomNode>
#include <QMetaProperty>
#include "brewtarget.h"

BeerXMLElement::BeerXMLElement() : _key(-1), _table(Database::NOTABLE)
{
}

BeerXMLElement::BeerXMLElement(BeerXMLElement const& other) : _key(other._key), _table(other._table)
{
}

double BeerXMLElement::getDouble(const QDomText& textNode)
{
   bool ok;
   double ret;

   QString text = textNode.nodeValue();

   ret = text.toDouble(&ok);
   if( !ok )
      Brewtarget::log(Brewtarget::ERROR, QString("%1 is not a number. Line %2").arg(text).arg(textNode.lineNumber()) );

   return ret;
}

bool BeerXMLElement::getBool(const QDomText& textNode)
{
   QString text = textNode.nodeValue();

   if( text == "TRUE" )
      return true;
   else if( text == "FALSE" )
      return false;
   else
      Brewtarget::log(Brewtarget::ERROR, QString("%1 is not a boolean value. Line %2").arg(text).arg(textNode.lineNumber()) );

   return false;
}

int BeerXMLElement::getInt(const QDomText& textNode)
{
   bool ok;
   int ret;
   QString text = textNode.nodeValue();

   ret = text.toInt(&ok);
   if( !ok )
      Brewtarget::log(Brewtarget::ERROR, QString("%1 is not an integer. Line %2").arg(text).arg(textNode.lineNumber()) );

   return ret;
}

QString BeerXMLElement::text(bool val)
{
   if( val )
      return QString("TRUE");
   else
      return QString("FALSE");
}

QString BeerXMLElement::text(double val)
{
   return QString("%1").arg(val, 0, 'e', 5);
}

QString BeerXMLElement::text(int val)
{
   return QString("%1").arg(val);
}

void BeerXMLElement::set( const char* prop_name, const char* col_name, QVariant const& value, bool notify )
{
   // Get the meta property.
   int ndx = metaObject()->indexOfProperty(prop_name);
   
   // Should schedule an update of the appropriate entry in table,
   // then use prop to emit its notification signal.
   Database::instance().updateEntry( _table, _key, col_name, value, metaObject()->property(ndx), this, notify );
}

QVariant BeerXMLElement::get( const char* col_name )
{
   return Database::instance().get( _table, _key, col_name );
}