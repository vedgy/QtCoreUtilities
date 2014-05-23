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

# include <QtCoreUtilities/Error.hpp>
# include <QtCoreUtilities/Validation.hpp>

# include <CommonUtilities/Testing.hpp>

# include <QObject>
# include <QTest>

# include <string>
# include <iostream>


namespace QtUtilities
{
using namespace CommonUtilities::Testing;

namespace
{
/// a <= b <= c for both validate overloads.
template <typename T>
void validate(const T & a, const T & b);
template <typename T>
void validate(const T & a, const T & b, const T & c);

/// a < b < c for both validateException overloads and validateBoth.
template <typename T>
void validateException(const T & a, const T & b);
template <typename T>
void validateException(const T & a, const T & b, const T & c);

template <typename T>
void validateBoth(const T & a, const T & b, const T & c);


template <typename T>
void print(const T & a, const T & b, const T & c);

/// !(a <= b <= c)
template <typename T>
void validateWrongOrder(const T & a, const T & b, const T & c);

}

class ValidationTest: public QObject
{
    Q_OBJECT
private slots:
    void test();
};


namespace
{
template <typename T>
void validate(const T & a, const T & b)
{
    checkMinValue(b, a);
    checkMaxValue(a, b);
}

template <typename T>
void validate(const T & a, const T & b, const T & c)
{
    try {
        validate(a, b);
        validate(b, c);
        validate(a, c);
        checkRange(b, a, c);
    }
    catch (const Error & error) {
        std::cout << "Error: " << error.what() << std::endl;
        printForType<T>(true);
        print(a, b, c);
        QFAIL("");
    }
}

template <typename T>
void validateException(const T & a, const T & b)
{
    bool success = true;
    try {
        checkMinValue(a, b);

        success = false;
        std::cout << "checkMinValue(a, b)" << std::endl;
    }
    catch (const Error &) {
    }

    try {
        checkMaxValue(b, a);

        success = false;
        std::cout << "checkMaxValue(b, a)" << std::endl;
    }
    catch (const Error &) {
    }

    if (! success) {
        printForType<T>(true);
        CommonUtilities::Testing::print("a", a, "b", b);
        QFAIL(missingExceptionMessage());
    }
}

template <typename T>
void validateException(const T & a, const T & b, const T & c)
{
    validateException(a, b);
    validateException(b, c);
    validateException(a, c);
    validateWrongOrder(a, c, b);
    validateWrongOrder(b, a, c);
    validateWrongOrder(b, c, a);
    validateWrongOrder(c, a, b);
    validateWrongOrder(c, b, a);
}

template <typename T>
void validateBoth(const T & a, const T & b, const T & c)
{
    validate(a, b, c);
    validateException(a, b, c);
}


template <typename T>
void print(const T & a, const T & b, const T & c)
{
    CommonUtilities::Testing::print("a", a, "b", b, "c", c);
}

template <typename T>
void validateWrongOrder(const T & a, const T & b, const T & c)
{
    try {
        checkRange(b, a, c);

        printForType<T>(true);
        print(a, b, c);
        QFAIL(missingExceptionMessage());
    }
    catch (const Error &) {
    }
}

}


void ValidationTest::test()
{
    const auto s = [](const char * c) { return std::string(c); };

    validate(5, 5, 5);
    validate(1.0, 1.8, 1.8);
    validate(-11L, -11L, 22L);
    validate(s("a"), s("za"), s("za"));

    validateBoth(1u, 11u, 242u);
    validateBoth(2.2f, 3.5f, 1E10f);
    validateBoth('a', 'e', 'z');
    validateBoth(1.2E2L, 1112.9L, 2000.0L);
    validateBoth(s("u"), s("unity"), s("weight"));
}

}


QTEST_MAIN(QtUtilities::ValidationTest)


# include "ValidationTest.moc"
