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

# include "String.hpp"

# include <QByteArray>
# include <QString>
# include <QObject>

# include <cstddef>
# include <limits>


namespace QtUtilities
{
const QString falseString = "0", trueString = "1";


namespace ConvertQString
{
template <>
std::string to<std::string>(const QString & qStr)
{
    QByteArray byteArray = qStr.toUtf8();
    const std::size_t bytes = byteArray.size();
    return std::string(byteArray.constData(), bytes);
}

namespace
{
StringError makeError(const QString & type)
{
    return StringError(QObject::tr("invalid %1 string.").arg(type));
}

}

template <>
bool to<bool>(const QString & str)
{
    if (str == falseString)
        return false;
    if (str == trueString)
        return true;
    throw makeError("bool");
}

template <>
int to<int>(const QString & str)
{
    bool ok;
    const int result = str.toInt(& ok);
    if (! ok)
        throw makeError("int");
    return result;
}

template <>
long to<long>(const QString & str)
{
    bool ok;
    const long result = str.toLong(& ok);
    if (! ok)
        throw makeError("long");
    return result;
}

template <>
long long to<long long>(const QString & str)
{
    bool ok;
    const long long result = str.toLongLong(& ok);
    if (! ok)
        throw makeError("long long");
    return result;
}

template <>
unsigned char to<unsigned char>(const QString & str)
{
    bool ok;
    const unsigned short result = str.toUShort(& ok);
    if (! ok || result > std::numeric_limits<unsigned char>::max())
        throw makeError("unsigned char");
    return result;
}

template <>
unsigned short to<unsigned short>(const QString & str)
{
    bool ok;
    const unsigned short result = str.toUShort(& ok);
    if (! ok)
        throw makeError("unsigned short");
    return result;
}

template <>
unsigned int to<unsigned int>(const QString & str)
{
    bool ok;
    const unsigned int result = str.toUInt(& ok);
    if (! ok)
        throw makeError("unsigned int");
    return result;
}

template <>
unsigned long to<unsigned long>(const QString & str)
{
    bool ok;
    const unsigned long result = str.toULong(& ok);
    if (! ok)
        throw makeError("unsigned long");
    return result;
}

template <>
unsigned long long to<unsigned long long>(const QString & str)
{
    bool ok;
    const unsigned long long result = str.toULongLong(& ok);
    if (! ok)
        throw makeError("unsigned long long");
    return result;
}

}

}
