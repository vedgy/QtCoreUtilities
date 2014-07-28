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

# ifndef QT_CORE_UTILITIES_MISCELLANEOUS_HPP
# define QT_CORE_UTILITIES_MISCELLANEOUS_HPP

# include <QString>

# include <string>


namespace QtUtilities
{
/// @brief Creates the path to given filename (it may be absolute or relative).
/// The function will create all parent directories necessary to create the
/// file, but will not create the file itself.
/// @return true if successful; otherwise returns false.
/// NOTE: if the path to filename already exists when this function is called,
/// it will return true.
bool makePathTo(const QString & filename);
/// @return makePathTo(toQString(filename)).
bool makePathTo(const std::string & filename);

}

# endif // QT_CORE_UTILITIES_MISCELLANEOUS_HPP
