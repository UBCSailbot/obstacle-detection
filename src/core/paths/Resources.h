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
     * @param pathWithinResourceDir - the path to a particular resource,
     *  relative to this project's resources directory
     *
     * @return the path to that resource, relative to the top project directory
     */
    static std::string getResourcePath(const std::string &pathWithinResourceDir);

    /**
     * @param pathWithinImageDir - the path to a particular image file in the
     *  resources directory, relative to the "img" subdirectory.
     *
     * @return the path to that image file, relative to the top project directory
     */
    static std::string getImagePath(const std::string &pathWithinImageDir);

    /**
     * Generates a path for the config file with the given name, relative to the
     *  top directory of this project.
     * Config files are assumed to be stored in resources/config/.
     *
     * @param configFileName - the name of a file in the config/ sub-directory.
     *
     * @return the path to that config file, relative to the top project directory
     */
    static std::string getConfigFilePath(const std::string &configFileName);

private:
    
};


#endif //OBSTACLE_AVOIDANCE_RESOURCES_H
