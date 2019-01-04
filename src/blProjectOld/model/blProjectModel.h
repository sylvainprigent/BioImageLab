/// \file blProjectInfo.h
/// \brief blProjectInfo
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include "blProjectInfo.h"
#include "blTagsInfo.h"
#include "blImportDataInfo.h"
#include "blProjectIndex.h"
#include <QString>

/// \class blProjectInfo
/// \brief Contains the informations of a blProject
class BLPROJECT_EXPORT blProjectModel
{
public:
    /// \fn blProjectModel();
    /// \brief Constructor
    blProjectModel();
    /// \fn ~blProjectInfo();
    /// \brief Destructor
    ~blProjectModel();

public:
    void setProjectInfo(blProjectInfo* info);
    blProjectIndex *index();

public:
    QString createProject(blProjectInfo* info);
    QString importData(blProjectInfo* projectInfo,  blImportDataInfo *importInfo);
    QList<blMainColumnInfo> mainColumns();
    QList<blSubColumnInfo> subColumns(int mainColumnId);

private:
    blProjectInfo* m_info;
    blProjectIndex *m_index;
};
