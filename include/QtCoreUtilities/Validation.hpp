/*
 This file is part of vedgTools/QtCoreUtilities.
 Copyright (C) 2014 Igor Kushnir <igorkuo AT Google mail>

 vedgTools/QtCoreUtilities is free software: you can redistribute it and/or
 modify it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 vedgTools/QtCoreUtilities is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with
 vedgTools/QtCoreUtilities.  If not, see <http://www.gnu.org/licenses/>.
*/

# ifndef QT_CORE_UTILITIES_VALIDATION_HPP
# define QT_CORE_UTILITIES_VALIDATION_HPP

# include "Error.hpp"

# include <QString>
# include <QObject>


namespace QtUtilities
{
template <typename Number>
void checkMinValue(const QString & name, Number value, Number minValue)
{
    if (value < minValue) {
        throw Error(
            name +
            QObject::tr(" is less than minimum allowed value (%1 < %2).").
            arg(value).arg(minValue));
    }
}

template <typename Number>
void checkMaxValue(const QString & name, Number value, Number maxValue)
{
    if (value > maxValue) {
        throw Error(
            name +
            QObject::tr(" is greater than maximum allowed value (%1 > %2).").
            arg(value).arg(maxValue));
    }
}

template <typename Number>
void checkRange(const QString & name, Number value,
                Number minValue, Number maxValue)
{
    checkMinValue<Number>(name, value, minValue);
    checkMaxValue<Number>(name, value, maxValue);
}

}

# endif // QT_CORE_UTILITIES_VALIDATION_HPP
