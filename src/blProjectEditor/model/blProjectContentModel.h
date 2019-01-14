/// \file blProjectContentModel.h
/// \brief blProjectContentModel
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#pragma once

#include "blProjectEditorExport.h"

#include "blProjectContent.h"

/// \class blProjectContent
/// \brief Contains the informations of a blProjectData
class BLPROJECTEDITOR_EXPORT blProjectContentModel : QAbstractTableModel
{
public:
    /// \fn blProjectContent();
    /// \brief Constructor
    blProjectContentModel();
    /// \fn ~blProjectContent();
    /// \brief Destructor
    ~blProjectContentModel();

protected:
    QStandardItemModel _horizontalHeaderModel;
    QStandardItemModel _verticalHeaderModel;
    blProjectModel *m_model;

    QMap<int, blSubColumnInfo> m_subColumnsInfo;
    QMap<int, int> m_subColumnIdxInTable;
    int m_colCount;

};
