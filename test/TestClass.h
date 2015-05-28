//
// Created by paul on 26/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_TESTCLASS_H
#define OBSTACLE_AVOIDANCE_TESTCLASS_H

#include <string>
#include <iomanip>

using namespace std;

class TestClass {

public:
    virtual void runTests() = 0;
    virtual std::string getClassTitle() const = 0;

    void assertEquals(bool const &actual, bool const &expected, string const &title) const;
};


#endif //OBSTACLE_AVOIDANCE_TESTCLASS_H

void TestClass::assertEquals(bool const &actual, bool const &expected, string const &testTitle) const {
    if (expected == actual)
        cout << setiosflags(ios::left) << this->getClassTitle() << ", " <<
        setw(30) << testTitle << ": pass" << endl;
    else
        cout << setiosflags(ios::left) << this->getClassTitle() << ", " <<
        setw(30) << testTitle << ": failed" << endl;
}
