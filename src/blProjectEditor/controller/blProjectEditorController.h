/// \file blProjectEditorController.h
/// \brief blProjectEditorController
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#pragma once

#include <QWidget>

#include "blProjectEditorExport.h"

#include "blProjectEditor/view/blProjectEditorWidget.h"
#include "blProjectEditor/view/blProjectEditorInfoWidget.h"
#include "blProjectCore/model/blProjectInfo.h"

/// \class blProjectWidget
/// \brief Widget organized with tab that contains
/// the projects widgets
class BLPROJECTEDITOR_EXPORT blProjectEditorController : public QWidget{
    Q_OBJECT
    
public:
    /// \fn blProjectEditorController(blProjectInfo *projectInfo, QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent system
    blProjectEditorController(blProjectInfo *projectInfo, QWidget *parent = 0);
    /// \fn ~blProjectWidget();
    /// \brief Destructor
    ~blProjectEditorController();

signals:
    void askOpenProject(blProjectInfo *projectInfo);
    void askNewProject();

private:
    void createWidgets(blProjectInfo *projectInfo);

private slots:
    void showInfo();
    void editProjectInfo(blProjectInfo* projectInfo);

protected:
    blProjectEditorWidget* m_projectEditorWidget;
    blProjectEditorInfoWidget* m_porjectEditorInfo;

};
