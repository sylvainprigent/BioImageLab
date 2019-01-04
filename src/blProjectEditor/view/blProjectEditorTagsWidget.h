/// \file blProjectEditorTagsWidget.h
/// \brief blProjectEditorTagsWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#pragma once

#include "blProjectEditorExport.h"
#include "blProjectCore/model/blProjectInfo.h"
#include <QtWidgets>

/// \class blProjectEditorTagsWidget
/// \brief Widget that shows the list of tags
/// and a tool bar to create a new project
class BLPROJECTEDITOR_EXPORT blProjectEditorTagsWidget : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectEditorTagsWidget(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent systeme
    explicit blProjectEditorTagsWidget(QWidget *parent = 0);

private:
    QLineEdit* m_addEdit;
};
