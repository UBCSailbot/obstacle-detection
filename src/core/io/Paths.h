//
// Created by paul on 15/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_PATHS_H
#define OBSTACLE_AVOIDANCE_PATHS_H


#include <string>
#include <vector>
#include <QDir>

class Paths {

public:

    static std::string join(const std::string &path1, const std::string path2);

    static std::vector<std::string> generateListOfFiles(const std::string &inputFrameDir,
                                                        const std::string &fileNameFilter);
private:
    /**
    * PARAM: A std string that describes a directory in the file system.
    * RETURN: A QDir object corresponding to the same path.
    */
    static QDir pathStringToQDir(const std::string &inputPath);

};


#endif //OBSTACLE_AVOIDANCE_PATHS_H
