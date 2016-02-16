#pragma once

#include <QtCore>
#include "blCoreExport.h"

/// \class blDir
/// \brief Define directory operations
class BLCORE_EXPORT blDir{

public:
    /// \fn static bool copyFolder(QString sourceFolder, QString destFolder);
    /// \brief recursively copy one folder to an other one
    /// \param[in] sourceFolder Origin folder
    /// \param[in] destFolder Destination folder
    static bool copyFolder(QString sourceFolder, QString destFolder);

    /// \fn static bool deleteFolder(const QString &dirName);
    /// \brief recursively delete a folder and subfolders
    static bool deleteFolder(const QString &dirName);
};
