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

# ifndef QT_CORE_UTILITIES_STRING_HPP
# define QT_CORE_UTILITIES_STRING_HPP

# include "Error.hpp"

# include <CommonUtilities/CopyAndMoveSemantics.hpp>

# include <QByteArray>
# include <QString>

# include <string>


namespace QtUtilities
{
std::string qStringToString(const QString & qStr);


const QString & falseString();
const QString & trueString();


inline QString toQString(const std::string & str)
{
    return QString::fromUtf8(str.data(), static_cast<int>(str.size()));
}

inline QString toQString(bool value)
{
    return value ? trueString() : falseString();
}

inline QString toQString(long double value)
{
    return toQString(std::to_string(value));
}

template <typename Number>
inline QString toQString(Number number)
{
    return QString::number(number);
}


class StringError : public Error
{
public:
    explicit StringError(const QString & sWhat) : Error(sWhat) {}
    COPYABLE_AND_MOVABLE(StringError)
    ~StringError() noexcept override;
};

/// @brief Converts QString to other types.
/// @throw StringError If str has wrong format.
namespace ConvertQString
{
template <typename T> T to(const QString & str);

template <> std::string to<std::string>(const QString & str);

template <> bool to<bool>(const QString & str);

template <> signed char to<signed char>(const QString & str);
template <> short to<short>(const QString & str);
template <> int to<int>(const QString & str);
template <> long to<long>(const QString & str);
template <> long long to<long long>(const QString & str);

template <> unsigned char to<unsigned char>(const QString & str);
template <> unsigned short to<unsigned short>(const QString & str);
template <> unsigned int to<unsigned int>(const QString & str);
template <> unsigned long to<unsigned long>(const QString & str);
template <> unsigned long long to<unsigned long long>(const QString & str);

template <> float to<float>(const QString & str);
template <> double to<double>(const QString & str);
template <> long double to<long double>(const QString & str);

}

inline std::string qStringToString(const QString & qStr)
{
    return ConvertQString::to<std::string>(qStr);
}


inline QString byteArrayToQString(const QByteArray & byteArray)
{
    return QString::fromLatin1(byteArray.toBase64());
}

/// @param string Must be Base64-encoded.
inline QByteArray qStringToByteArray(const QString & string)
{
    return QByteArray::fromBase64(string.toLatin1());
}

}

# endif // QT_CORE_UTILITIES_STRING_HPP
