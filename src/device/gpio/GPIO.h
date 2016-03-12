#ifndef GPIO_H
#define GPIO_H

#include <string>
#include <fstream>
#include <iostream>

/* GPIO Class
 * Purpose: Each object instantiated from this class will control a GPIO pin
 * The GPIO pin number must be passed to the class constructor
 *
 * This code was taken from http://www.hertaville.com/introduction-to-accessing-the-raspberry-pis-gpio-in-c.html
 */
class GPIO {
public:

    GPIO(std::string x);

    int exportGPIO();

    int unexportGPIO();

    int setDirGPIO(std::string dir);

    int setValGPIO(std::string val);

    int getValGPIO(std::string &val);

    std::string gpioNum();

private:
    std::string _gpioNum;
};

#endif
