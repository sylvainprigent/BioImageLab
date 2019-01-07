/// \file blProjectNewController.h
/// \brief blProjectNewController
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#pragma once

#include <QWidget>

#include "blProjectEditorExport.h"
#include "blProjectCore/model/blProjectInfo.h"

/// \class blProjectNewController
/// \brief Widget to create a new project
class BLPROJECTEDITOR_EXPORT blProjectNewController : public QWidget{
    Q_OBJECT
    
public:
    /// \fn blProjectNewController(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent system
    blProjectNewController(QString projectsDir, QWidget *parent = 0);
    /// \fn ~blProjectWidget();
    /// \brief Destructor
    ~blProjectNewController();

signals:
    void projectCreated(blProjectInfo *projectInfo);

private slots:
    void createProject(blProjectInfo* projectInfo);

private:
    QString m_projectsDir;
};
