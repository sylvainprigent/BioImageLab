/// \file blImportDataInfo.h
/// \brief blImportDataInfo
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2016

#pragma once

#include "blProjectnewExport.h"
#include "blTagsInfo.h"
#include "blMainColumnInfo.h"
#include "blSubColumnInfo.h"
#include "blDataInfo.h"
#include <QString>
#include <QStringList>
#include <QList>

/// \class blImportDataInfo
/// \brief Contains the informations of data import
class blImportDataInfo
{
public:
    /// \fn blImportDataInfo();
    /// \brief Constructor
    blImportDataInfo();
    /// \fn ~blImportDataInfo();
    /// \brief Destructor
    ~blImportDataInfo();

public:
    // setters
    void setTags(blTagsInfo tags);
    void setData(QList<blDataInfo> data);
    void setMainColumnInfo(blMainColumnInfo mainColumnInfo);
    void setSubColumnsInfos(QList<blSubColumnInfo> subColumnsInfos);

public:
    // getters
    blTagsInfo tags();
    QList<blDataInfo> data();
    blMainColumnInfo mainColumnInfo();
    QList<blSubColumnInfo> subColumnsInfos();

private:
    blTagsInfo m_tags;
    QList<blDataInfo> m_data;
    blMainColumnInfo m_mainColumnInfo;
    QList<blSubColumnInfo> m_subColumnsInfos;
};
