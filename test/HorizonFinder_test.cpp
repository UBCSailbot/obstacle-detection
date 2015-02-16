//#include <QtTest/QtTest>
//#include "../img_proc.hpp"
//
//class TestHorizonFinder: public QObject
// {
//     Q_OBJECT
// private slots:
//     void testAngles();
// };
//
//void TestHorizonFinder::testAngles()
//{
//    QVERIFY(normalize_angle_ret(30.0) == 31);
//}
//
//QTEST_MAIN(TestHorizonFinder)

#include <assert.h>
#include "horizon_finder.h"

int main(){

	assert(normalize_angle_ret(30.0) == 30);

}
