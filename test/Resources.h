//
// Created by paul on 09/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_RESOURCES_H
#define OBSTACLE_AVOIDANCE_RESOURCES_H

#include <string>
#include <QDir>

/**
 * Manages this project's use of resource files.
 *
 * Resources consist of files stored locally within the project directory
 *  hierarchy that are loaded by other parts of the project via file I/O.
 *  They can include images, text files, or almost anything else that is not
 *  compiled code.
 */
class Resources {

public:

    /**
     * The path of the directory containing resource files, relative to the top
     *  directory of this project.
     */
    static std::string RESOURCE_DIR;

    /**
     * PARAM: the path to a particular resource, relative to this project's
     *  resources directory
     * RETURN: the path to that resource, relative to the top project directory
     */
    static std::string getResourcePath(const std::string &pathWithinResourceDir);

    /**
     * PARAM: the path to a particular image file in the resources directory,
     *  relative to the "img" subdirectory.
     * RETURN: the path to that resource, relative to the top project directory
     */
    static std::string getImagePath(const std::string &pathWithinImageDir);

private:
    static QString QSTRING_RESOURCE_DIR;

};


#endif //OBSTACLE_AVOIDANCE_RESOURCES_H
