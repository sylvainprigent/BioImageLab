/// \file blProjectDataModel.h
/// \brief blProjectDataModel
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#pragma once

#include "blProjectEditorExport.h"
#include "blProjectData.h"
#include "blProjectCore/model/blProjectInfo.h"
#include <QString>

/// \class blProjectInfo
/// \brief Contains the informations of a blProjectData
class BLPROJECTEDITOR_EXPORT blProjectDataModel
{
public:
    /// \fn blProjectDataModel();
    /// \brief Constructor
    blProjectDataModel();
    /// \fn ~blProjectDataModel();
    /// \brief Destructor
    ~blProjectDataModel();

public:
    blProjectData *importData(blProjectInfo* project, blProjectData *data);

};
