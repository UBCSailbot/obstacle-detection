#include "GPIO.h"

GPIO::GPIO(std::string gnum) {
    _gpioNum = gnum;
}

int GPIO::exportGPIO() {
    std::string export_str = "/sys/class/gpio/export";
    std::ofstream exportgpio(
            // Open "export" file. Convert C++ string to C string. Required for all Linux pathnames:
            export_str.c_str());
    if (!exportgpio.good()) {
        std::cout << " OPERATION FAILED: Unable to export GPIO" << _gpioNum << " ." << std::endl;
        return -1;
    }

    exportgpio << _gpioNum;
    exportgpio.close();
    return 0;
}

int GPIO::unexportGPIO() {
    std::string unexport_str = "/sys/class/gpio/unexport";
    std::ofstream unexportgpio(unexport_str.c_str());
    if (!unexportgpio.good()) {
        std::cout << " OPERATION FAILED: Unable to unexport GPIO" << _gpioNum << " ." << std::endl;
        return -1;
    }

    unexportgpio << _gpioNum;
    unexportgpio.close();
    return 0;
}

int GPIO::setDirGPIO(std::string dir) {

    std::string setdir_str = "/sys/class/gpio/gpio" + _gpioNum + "/direction";
    std::ofstream setdirgpio(setdir_str.c_str());
    if (!setdirgpio.good()) {
        std::cout << " OPERATION FAILED: Unable to set direction of GPIO" << _gpioNum << " ." << std::endl;
        return -1;
    }

    setdirgpio << dir;
    setdirgpio.close();
    return 0;
}

int GPIO::setValGPIO(std::string val) {

    std::string setval_str = "/sys/class/gpio/gpio" + _gpioNum + "/value";
    std::ofstream setvalgpio(setval_str.c_str());
    if (!setvalgpio.good()) {
        std::cout << " OPERATION FAILED: Unable to set the value of GPIO" << _gpioNum << " ." << std::endl;
        return -1;
    }

    setvalgpio << val;
    setvalgpio.close();
    return 0;
}

int GPIO::getValGPIO(std::string &val) {

    std::string getval_str = "/sys/class/gpio/gpio" + _gpioNum + "/value";
    std::ifstream getvalgpio(getval_str.c_str());
    if (!getvalgpio.good()) {
        std::cout << " OPERATION FAILED: Unable to get value of GPIO" << _gpioNum << " ." << std::endl;
        return -1;
    }

    getvalgpio >> val;

    if (val != "0") {
        val = "1";
    }
    else {
        val = "0";
    }

    getvalgpio.close();
    return 0;
}

std::string GPIO::gpioNum() {

    return _gpioNum;

}
