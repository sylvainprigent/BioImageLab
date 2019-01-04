/// \file blProjectEditorInfoWidget.h
/// \brief blProjectEditorInfoWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectEditorExport.h"
#include <QtWidgets>
#include "blProjectCore/model/blProjectInfo.h"

/// \class blProjectBrowserWidget
/// \brief Widget that shows the list of project
/// and a tool bar to create a new project
class BLPROJECTEDITOR_EXPORT blProjectEditorInfoWidget : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectEditorWidget(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent systeme
    explicit blProjectEditorInfoWidget(QWidget *parent = 0);

signals:
    void askEditProject(blProjectInfo* info);

public slots:
    void setData(blProjectInfo* info);

private slots:
    void emitEditedProject();

private:
    void buildWidget();

public:
    void editView();

private:
    int m_projectId;
    QLineEdit *m_nameEdit;
    QTextEdit *m_descriptionEdit;
    QPushButton *m_saveButton;
};
