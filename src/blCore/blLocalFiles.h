#pragma once

#include <QtWidgets>
#include "blCoreExport.h"

/// \class blSettings
/// \brief Class containg any settings as key = value
class BLCORE_EXPORT blLocalFiles
{
public:
    blLocalFiles();

public:
    // setters getters
    QString getThemeFile();
    QString getIconDir();
    QString getSettingsFile();

};
