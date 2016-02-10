//
// Created by paul on 15/06/15.
//

#ifndef OBSTACLE_AVOIDANCE_PATHS_H
#define OBSTACLE_AVOIDANCE_PATHS_H


#include <string>
#include <vector>
#include <QDir>

/**
 * An accessory class containing functions that are useful in manipulating
 *  paths to files on the file system.
 */
class Paths {

public:

    /**
     * Concatenates two paths, usually a full directory path with the name of
     *  a particular file in that directory.
     *
     * This function performs string concatenation, it will not check that
     *  the paths actually exist or are otherwise meaningful.
     *
     * PARAM: path1 - the left part of the path. This usually corresponds to the full
     *  path of a directory. Trailing forward slash is optional.
     * PARAM: path2 - the right part of the path. This is usually just the name of a
     *  file or directory, though your use case may also include a relative path.
     *
     * RETURN: a string that looks like "path1/path2", where the forward slash will
     *  only be added if it wasn't already in one of the path names.
     */
    static std::string join(const std::string &path1, const std::string path2);

    /**
     * Generates a list of all the names of files found in the specified
     *  directory that match the given filter. For example, giving the filter
     *  "*.png" returns all files whose names end in .png. To get all the files
     *  in that directory, just use "*".
     *
     * Note that this just returns a list of file names, not a list of full
     *  paths to each file.
     *
     * PARAM: inputDir - the directory containing the files for which we want a list
     * PARAM: fileNameFilter - a string specifying a filter to place on the files
     *  to be included in the list.
     *
     * RETURN: a list of the files in the specified directory whose names match
     *  the specified filter.
     */
    static std::vector<std::string> generateListOfFiles(const std::string &inputDir,
                                                        const std::string &fileNameFilter);
private:
    /**
    * PARAM: A std string that describes a directory in the file system.
    * RETURN: A QDir object corresponding to the same path.
    */
    static QDir pathStringToQDir(const std::string &inputPath);

};


#endif //OBSTACLE_AVOIDANCE_PATHS_H
