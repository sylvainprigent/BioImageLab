/// \file blProjectEditorFooterWidget.h
/// \brief blProjectEditorFooterWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#pragma once

#include "blProjectEditorExport.h"
#include "blProjectCore/model/blProjectInfo.h"
#include <QWidget>

/// \class blProjectEditorFooterWidget
/// \brief Widget that shows the list of project
/// and a tool bar to create a new project
class BLPROJECTEDITOR_EXPORT blProjectEditorFooterWidget : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectEditorFooterWidget(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent systeme
    explicit blProjectEditorFooterWidget(QWidget *parent = 0);

};
