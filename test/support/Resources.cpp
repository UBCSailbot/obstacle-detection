//
// Created by paul on 09/06/15.
//

#include "Resources.h"

std::string Resources::RESOURCE_DIR = "resources";

QString Resources::QSTRING_RESOURCE_DIR = QString::fromStdString(RESOURCE_DIR);

std::string Resources::getResourcePath(const std::string &pathWithinResourceDir) {
    QString qPath = QString::fromStdString(pathWithinResourceDir);
    return QDir( QSTRING_RESOURCE_DIR ).filePath(qPath).toStdString();
}

std::string Resources::getImagePath(const std::string &pathWithinImageDir) {
    QString qPath = QString::fromStdString(pathWithinImageDir);
    return getResourcePath( QDir("img").filePath(qPath).toStdString() );
}
