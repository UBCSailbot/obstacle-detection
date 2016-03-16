#include "Resources.h"

std::string Resources::RESOURCE_DIR = "resources";
std::string Resources::CONFIG = "config";

std::string Resources::getResourcePath(const std::string &pathWithinResourceDir) {
    QString qPath = QString::fromStdString(pathWithinResourceDir);
    return QDir( RESOURCE_DIR.c_str() ).filePath(qPath).toStdString();
}

std::string Resources::getImagePath(const std::string &pathWithinImageDir) {
    QString qPath = QString::fromStdString(pathWithinImageDir);
    return getResourcePath( QDir("img").filePath(qPath).toStdString() );
}

std::string Resources::getConfigFilePath(const std::string &configFileName) {
    QString qPath = QString::fromStdString(configFileName);
    return getResourcePath( QDir(CONFIG.c_str()).filePath(qPath).toStdString() );
}

std::string Resources::getConfigDir() {
  return getResourcePath( QDir(CONFIG.c_str()).path().toStdString() );
}
