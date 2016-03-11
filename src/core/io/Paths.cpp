//
// Created by paul on 15/06/15.
//

#include "Paths.h"


std::string Paths::join(const std::string &path1, const std::string path2) {
    QString qPath1 = QString::fromStdString(path1);
    QString qPath2 = QString::fromStdString(path2);

    return QDir(qPath1).filePath(qPath2).toStdString();
}

std::vector <std::string> Paths::generateListOfFiles(const std::string &inputDir,
                                                     const std::string &fileNameFilter) {
    QString imageFileExt = QString::fromStdString(fileNameFilter);
    QStringList nameFilters(imageFileExt);

    QDir inputFrameQDir = pathStringToQDir(inputDir);
    QStringList frameQList = inputFrameQDir.entryList(nameFilters, QDir::Files);

    std::vector <std::string> frameList;
    for (int i = 0; i < frameQList.count(); i++) {
        frameList.push_back(frameQList[i].toStdString());
    }

    return frameList;
}

QDir Paths::pathStringToQDir(const std::string &inputPath) {
    QString intermediary = QString::fromStdString(inputPath);

    return QDir(intermediary);
}
