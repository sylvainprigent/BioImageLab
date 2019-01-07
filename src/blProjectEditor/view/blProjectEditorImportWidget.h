/// \file blProjectEditorImportWidget.h
/// \brief blProjectEditorImportWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#pragma once

#include "blProjectEditorExport.h"
#include "blProjectEditor/model/blProjectData.h"
#include <QtWidgets>

/// \class blProjectEditorImportWidget
/// \brief Widget that shows the list of tags
/// and a tool bar to create a new project
class BLPROJECTEDITOR_EXPORT blProjectEditorImportWidget : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectEditorImportWidget(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent systeme
    explicit blProjectEditorImportWidget(QWidget *parent = 0);

signals:
    void askImportData(blProjectData*);
    void askRemoveData(blProjectData*);

private slots:
    void emitAskImportData();
    void browse();

private:
    QLineEdit* m_addEdit;
};
