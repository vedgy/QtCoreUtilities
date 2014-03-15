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

# ifndef QT_CORE_UTILITIES_ERROR_HPP
# define QT_CORE_UTILITIES_ERROR_HPP

# include <QString>

# include <stdexcept>


namespace QtUtilities
{
class Error : public std::exception
{
public:
    explicit Error(const QString & sWhat);

    ~Error() noexcept override {}

    const QString & message() const noexcept { return message_; }
    const char * what() const noexcept override;

protected:
    QString message_;
};

}

# endif // QT_CORE_UTILITIES_ERROR_HPP
