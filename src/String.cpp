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
# include <string>
# include <stdexcept>


namespace QtUtilities
{
# ifndef QT_UTILITIES_FALSE_STRING
# define QT_UTILITIES_FALSE_STRING "0"
# endif
# ifndef QT_UTILITIES_TRUE_STRING
# define QT_UTILITIES_TRUE_STRING "1"
# endif

const QString & falseString()
{
    static const QString s = QT_UTILITIES_FALSE_STRING;
    return s;
}
const QString & trueString()
{
    static const QString s = QT_UTILITIES_TRUE_STRING;
    return s;
}


StringError::~StringError() noexcept = default;

namespace ConvertQString
{
template <>
std::string to<std::string>(const QString & qStr)
{
    const QByteArray byteArray = qStr.toUtf8();
    const std::size_t bytes = std::size_t(byteArray.size());
    return std::string(byteArray.constData(), bytes);
}


namespace
{
QString invalidStringMessage()
{
    return QObject::tr("invalid %1 string");
}

StringError makeError(const QString & type)
{
    return StringError(invalidStringMessage().arg(type) + '.');
}

template <typename Number, typename QStringToNumber>
Number qStringToNumber(const QString & numberTypeName,
                       QStringToNumber converter)
{
    bool ok;
    const Number result = converter(& ok);
    if (! ok)
        throw makeError(numberTypeName);
    return result;
}

}


template <>
bool to<bool>(const QString & str)
{
    if (str == falseString())
        return false;
    if (str == trueString())
        return true;
    throw StringError(
        invalidStringMessage().arg("bool") +
        QObject::tr(". \"%1\" or \"%2\" expected but \"%3\" found.").
        arg(falseString(), trueString(), str));
}


template <>
signed char to<signed char>(const QString & str)
{
    bool ok;
    const short result = str.toShort(& ok);
    if (! ok || result < std::numeric_limits<signed char>::min() ||
            result > std::numeric_limits<signed char>::max()) {
        throw makeError("signed char");
    }
    return (signed char)result;
}

template <>
short to<short>(const QString & str)
{
    return qStringToNumber<short>("short",
    [& str](bool * ok) {
        return str.toShort(ok);
    });
}

template <>
int to<int>(const QString & str)
{
    return qStringToNumber<int>("int",
    [& str](bool * ok) {
        return str.toInt(ok);
    });
}

template <>
long to<long>(const QString & str)
{
    return qStringToNumber<long>("long",
    [& str](bool * ok) {
        return str.toLong(ok);
    });
}

template <>
long long to<long long>(const QString & str)
{
    return qStringToNumber<long long>("long long",
    [& str](bool * ok) {
        return str.toLongLong(ok);
    });
}


template <>
unsigned char to<unsigned char>(const QString & str)
{
    bool ok;
    const unsigned short result = str.toUShort(& ok);
    if (! ok || result > std::numeric_limits<unsigned char>::max())
        throw makeError("unsigned char");
    return (unsigned char)result;
}

template <>
unsigned short to<unsigned short>(const QString & str)
{
    return qStringToNumber<unsigned short>("unsigned short",
    [& str](bool * ok) {
        return str.toUShort(ok);
    });
}

template <>
unsigned int to<unsigned int>(const QString & str)
{
    return qStringToNumber<unsigned int>("unsigned int",
    [& str](bool * ok) {
        return str.toUInt(ok);
    });
}

template <>
unsigned long to<unsigned long>(const QString & str)
{
    return qStringToNumber<unsigned long>("unsigned long",
    [& str](bool * ok) {
        return str.toULong(ok);
    });
}

template <>
unsigned long long to<unsigned long long>(const QString & str)
{
    return qStringToNumber<unsigned long long>("unsigned long long",
    [& str](bool * ok) {
        return str.toULongLong(ok);
    });
}


template <>
float to<float>(const QString & str)
{
    return qStringToNumber<float>("float",
    [& str](bool * ok) {
        return str.toFloat(ok);
    });
}

template <>
double to<double>(const QString & str)
{
    return qStringToNumber<double>("double",
    [& str](bool * ok) {
        return str.toDouble(ok);
    });
}

template <>
long double to<long double>(const QString & str)
{
    try {
        const std::string s = to<std::string>(str);
        std::size_t index;
        const long double result = std::stold(s, & index);
        if (index != s.size())
            throw std::invalid_argument("extra symbols at the end of string");
        return result;
    }
    catch (const std::logic_error & error) {
        throw StringError(invalidStringMessage().arg("long double") +
                          " (" + error.what() + ").");
    }
}

}

}
