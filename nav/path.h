#ifndef NAVEO_CONFIGURATION_PATH_H
#define NAVEO_CONFIGURATION_PATH_H
#include <QtCore>
#include <QDir>
#define naveoConfigurationPath (QString("%1/.config/naveo").arg(QDir::homePath()))
#endif
