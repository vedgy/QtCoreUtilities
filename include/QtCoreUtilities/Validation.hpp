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
# include "String.hpp"

# include <QString>
# include <QObject>


namespace QtUtilities
{
inline QString addArgs(const QString & str,
                       const QString & arg1, const QString & arg2)
{
    return str.arg(arg1, arg2);
}

template <typename T, typename U>
QString addArgs(const QString & str, const T & arg1, const U & arg2)
{
    return addArgs(str, toQString(arg1), toQString(arg2));
}


template <typename T>
void checkMinValue(const T & value, const T & minValue)
{
    if (value < minValue) {
        throw Error(
            addArgs(QObject::tr("less than minimum allowed value (%1 < %2)."),
                    value, minValue));
    }
}

template <typename T>
void checkMaxValue(const T & value, const T & maxValue)
{
    if (value > maxValue) {
        throw Error(
            addArgs(QObject::tr(
                        "greater than maximum allowed value (%1 > %2)."),
                    value, maxValue));
    }
}

template <typename T>
void checkRange(const T & value, const T & minValue, const T & maxValue)
{
    checkMinValue(value, minValue);
    checkMaxValue(value, maxValue);
}

}

# endif // QT_CORE_UTILITIES_VALIDATION_HPP
