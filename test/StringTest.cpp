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

# include <QtCoreUtilities/String.hpp>

# include <CommonUtilities/Testing.hpp>

# include <QByteArray>
# include <QString>
# include <QObject>
# include <QTest>

# include <limits>
# include <algorithm>
# include <array>
# include <vector>
# include <string>
# include <iterator>
# include <iostream>


Q_DECLARE_METATYPE(std::string)

namespace QTest
{
template<>
char * toString(const std::string & str)
{
    return qstrdup(str.c_str());
}

template<>
char * toString(const signed char & n)
{
    return toString(std::to_string(int(n)));
}

template<>
char * toString(const unsigned char & n)
{
    return toString(std::to_string(int(n)));
}

}


namespace QtUtilities
{
using namespace CommonUtilities::Testing;

namespace
{
const char sourceName[] = "source", qStrName[] = "qStr";

void printStringError(const StringError & error);

template <typename T, typename Converter>
void tTest(Converter tConverter);
template <typename T>
void tBidirectionalTest();

template <typename T>
void addSourceColumn();
template <typename T>
void addSourceAndQStrColumns();

template <typename Str>
void stringData();
template <typename Str>
void sourceColumnAndStringData();
template <typename Str>
void base64Data();


struct Test {
    int source;
    QString qStr;
};
template <typename Integral>
struct BidirectionalTest {
    void operator()(const Test & test) const;
};

template <template<class> class F, class TestCollection>
void signedCollectionTest(const TestCollection & collection);
template <template<class> class F, class TestCollection>
void unsignedCollectionTest(const TestCollection & collection);
template <template<class> class F, class TestCollection>
void floatingPointCollectionTest(const TestCollection & collection);

void signedBidirectionalTest(const std::vector<Test> & tests);
void integralBidirectionalTest(const std::vector<Test> & tests);

template <typename FloatingPoint>
void floatingPointTest(FloatingPoint number);
void longDoubleTest(long double number);
void doubleTest(double number);
void floatTest(float number);


template <typename Destination>
struct ExceptionTest {
    void operator()(const QString & badSource) const;
};
typedef std::vector<QString> ExceptionTests;
void unsignedExceptionTest(const ExceptionTests & tests);
void integralExceptionTest(const ExceptionTests & tests);
void numberExceptionTest(const ExceptionTests & tests);

template <typename Number>
struct MinAndMaxNumberTest {
    void operator()(int) const;
};

}

class StringTest: public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();

    /// std::string, QByteArray.
    void fromString_data();
    void toString_data();
    void fromByteArray_data();
    void toByteArray_data();
    void toStringConvenience_data();

    void fromString();
    void toString();
    void fromByteArray();
    void toByteArray();
    void toStringConvenience();


    void boolBidirectional_data();
    void boolBidirectional();

    void integralBidirectional();
    void floatingPoint();

    void boolException();
    void numberException();
    void minAndMaxNumber();
};


namespace
{
void printStringError(const StringError & error)
{
    std::cout << "StringError: " << error.what() << std::endl;
}

template <typename T, typename Converter>
void tTest(Converter tConverter)
{
    QFETCH(T, source);
    QCOMPARE(tConverter(source), source);
}

template <typename T>
void tBidirectionalTest()
{
    QFETCH(T, source);
    QFETCH(QString, qStr);
    QCOMPARE(toQString(source), qStr);
    QCOMPARE(ConvertQString::to<T>(qStr), source);
}

template <typename T>
void addSourceColumn()
{
    QTest::addColumn<T>(sourceName);
}

template <typename T>
void addSourceAndQStrColumns()
{
    addSourceColumn<T>();
    QTest::addColumn<QString>(qStrName);
}


template <typename Str>
void stringData()
{
    QTest::newRow("ASCII") << Str("$~&%[{}(=*)+]!#` 4;:,<.>\tpD/?@^\\|-_'\"\n");
    QTest::newRow("Unicode") << Str("тіыґҐъїёщЪєэµ¹¶æŗỸή");
}

template <typename Str>
void sourceColumnAndStringData()
{
    addSourceColumn<Str>();
    stringData<Str>();
}

template <typename Str>
void base64Data()
{
    QTest::newRow("Base64 text") << Str("AdnQywABAAAAAAMsAAABoQAABfkAAANwA"
                                        "AADMQAAAboAAAX0AAADawAAAAAAAA==");
}


template <typename Integral>
void BidirectionalTest<Integral>::operator()(const Test & test) const
{
    try {
        if (toQString(Integral(test.source)) == test.qStr &&
                ConvertQString::to<Integral>(test.qStr) ==
                Integral(test.source)) {
            return;
        }
        std::cout << "Wrong conversion ";
        printForType<Integral>(false, ".\n");
    }
    catch (const StringError & error) {
        printStringError(error);
    }
    print("source", test.source, "qStr", qStringToString(test.qStr));
    QFAIL("");
}


template < template<class> class F, class TestCollection>
void signedCollectionTest(const TestCollection & collection)
{
    std::for_each(std::begin(collection), std::end(collection),
    [](typename TestCollection::const_reference t) {
        F<signed char>()(t);
        F<short>()(t);
        F<int>()(t);
        F<long>()(t);
        F<long long>()(t);
    });
}

template <template<class> class F, class TestCollection>
void unsignedCollectionTest(const TestCollection & collection)
{
    std::for_each(std::begin(collection), std::end(collection),
    [](typename TestCollection::const_reference t) {
        F<unsigned char>()(t);
        F<unsigned short>()(t);
        F<unsigned>()(t);
        F<unsigned long>()(t);
        F<unsigned long long>()(t);
    });
}

template <template<class> class F, class TestCollection>
void floatingPointCollectionTest(const TestCollection & collection)
{
    std::for_each(std::begin(collection), std::end(collection),
    [](typename TestCollection::const_reference t) {
        F<float>()(t);
        F<double>()(t);
        F<long double>()(t);
    });
}


void signedBidirectionalTest(const std::vector<Test> & tests)
{
    signedCollectionTest<BidirectionalTest>(tests);
}

void integralBidirectionalTest(const std::vector<Test> & tests)
{
    signedBidirectionalTest(tests);
    unsignedCollectionTest<BidirectionalTest>(tests);
}

template <typename FloatingPoint>
void floatingPointTest(const FloatingPoint number)
{
    FloatingPoint converted;
    bool passed = true;
    try {
        converted = ConvertQString::to<FloatingPoint>(toQString(number));

        constexpr FloatingPoint eps = 1E-6f, multiplier = 1.1f;
        if (converted >= 0 && converted < eps)
            passed = number > - eps && number < eps * multiplier;
        else if (converted < 0 && converted > - eps)
            passed = number > - eps * multiplier && number < eps;
        else {
            const FloatingPoint ratio = number / converted;
            passed = ratio > 1 / multiplier && ratio < multiplier;
        }

        if (passed)
            return;
        std::cout << "Converted value ";
        printForType<FloatingPoint>(false, " ");
        std::cout << "diverges too much from the original." << std::endl;
    }
    catch (const StringError & error) {
        printStringError(error);
    }

    compactPrint("number", number);
    if (! passed) { // if (no StringError)
        std::cout << ", ";
        compactPrint("converted", converted);
    }
    std::cout << '.' << std::endl;
    QFAIL("");
}

void longDoubleTest(const long double number)
{
    floatingPointTest<long double>(number);
}

void doubleTest(const double number)
{
    floatingPointTest<double>(number);
    longDoubleTest(number);
}

void floatTest(const float number)
{
    floatingPointTest<float>(number);
    doubleTest(number);
}


template <typename Destination>
void ExceptionTest<Destination>::operator()(const QString & badSource) const
{
    try {
        ConvertQString::to<Destination>(badSource);

        printForType<Destination>(true);
        print("badSource", qStringToString(badSource));
        QFAIL(missingExceptionMessage());
    }
    catch (const StringError &) {
    }
}

void unsignedExceptionTest(const ExceptionTests & tests)
{
    unsignedCollectionTest<ExceptionTest>(tests);
}

void integralExceptionTest(const ExceptionTests & tests)
{
    unsignedExceptionTest(tests);
    signedCollectionTest<ExceptionTest>(tests);
}

void numberExceptionTest(const ExceptionTests & tests)
{
    integralExceptionTest(tests);
    floatingPointCollectionTest<ExceptionTest>(tests);
}

template <typename Number>
void MinAndMaxNumberTest<Number>::operator()(int) const
{
    typedef std::numeric_limits<Number> Limits;
    for (Number number : { Limits::min(), Limits::max() }) {
        const QString str = toQString(number);
        if (str.isEmpty())
            std::cout << "Empty conversion result!" << std::endl;
        else {
            try {
                ConvertQString::to<Number>(str);
                ExceptionTest<Number>()("-1." + str);
                continue;
            }
            catch (const StringError & error) {
                printStringError(error);
            }
        }

        printForType<Number>(true);
        print("number", number, "str", qStringToString(str));
        QFAIL("");
    }
}

}


void StringTest::initTestCase()
{
    qRegisterMetaType<std::string>("std::string");
}


void StringTest::fromString_data()
{
    sourceColumnAndStringData<std::string>();
}

void StringTest::toString_data()
{
    sourceColumnAndStringData<QString>();
}

void StringTest::fromByteArray_data()
{
    sourceColumnAndStringData<QByteArray>();
    base64Data<QByteArray>();
}

void StringTest::toByteArray_data()
{
    addSourceColumn<QString>();
    base64Data<QString>();
}

void StringTest::toStringConvenience_data()
{
    sourceColumnAndStringData<QString>();
}


void StringTest::fromString()
{
    tTest<std::string>([](const std::string & source) {
        return ConvertQString::to<std::string>(toQString(source));
    });
}

void StringTest::toString()
{
    tTest<QString>([](const QString & source) {
        return toQString(ConvertQString::to<std::string>(source));
    });
}

void StringTest::fromByteArray()
{
    tTest<QByteArray>([](const QByteArray & source) {
        return qStringToByteArray(byteArrayToQString(source));
    });
}

void StringTest::toByteArray()
{
    tTest<QString>([](const QString & source) {
        return byteArrayToQString(qStringToByteArray(source));
    });
}

void StringTest::toStringConvenience()
{
    QFETCH(QString, source);
    QCOMPARE(qStringToString(source), ConvertQString::to<std::string>(source));
}


void StringTest::boolBidirectional_data()
{
    addSourceAndQStrColumns<bool>();
    QTest::newRow("true") << true << trueString();
    QTest::newRow("false") << false << falseString();
}

void StringTest::boolBidirectional()
{
    try {
        tBidirectionalTest<bool>();
    }
    catch (const StringError & error) {
        printStringError(error);
        QFAIL("");
    }
}


void StringTest::integralBidirectional()
{
    integralBidirectionalTest( {
        { 0, "0" }, { 1, "1" }, { 58, "58" }, { 127, "127" }
    });
    signedBidirectionalTest( {
        { -1, "-1" }, { -79, "-79" }, { -100, "-100" }
    });
}


void StringTest::floatingPoint()
{
    floatTest(2);
    floatTest(1.0f);
    floatTest(0);
    floatTest(1.31E-13f);
    floatTest(-51 * 10000.90319f);
    floatTest(-2.2E11f);
    doubleTest(1.13515E-30);
    longDoubleTest(1.53E-200);
}


void StringTest::boolException()
{
    ExceptionTest<bool>()("");
    ExceptionTest<bool>()(trueString() + falseString());
}

void StringTest::numberException()
{
    unsignedExceptionTest( { "-1", "-22" });
    integralExceptionTest( { "0.4", "-1e2", ".8" });
    numberExceptionTest( { "u", "--", "-", "0.2u", "ab" });
}

void StringTest::minAndMaxNumber()
{
    constexpr std::array<int, 1> dummy {{ 0 }};
    signedCollectionTest<MinAndMaxNumberTest>(dummy);
    unsignedCollectionTest<MinAndMaxNumberTest>(dummy);
    floatingPointCollectionTest<MinAndMaxNumberTest>(dummy);
}

}


QTEST_MAIN(QtUtilities::StringTest)


# include "StringTest.moc"
