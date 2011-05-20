/*
This file is part of ILM.

    ILM is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ILM is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ILM.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QtCore/QString>
#include <QtTest/QtTest>

class TMDB_TestTest : public QObject
{
    Q_OBJECT

public:
    TMDB_TestTest();

private Q_SLOTS:
    void testCase1();
};

TMDB_TestTest::TMDB_TestTest()
{
}

void TMDB_TestTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TMDB_TestTest);

#include "tst_tmdb_testtest.moc"
