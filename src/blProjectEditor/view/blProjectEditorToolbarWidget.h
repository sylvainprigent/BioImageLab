/// \file blProjectEditorToolbarWidget.h
/// \brief blProjectEditorToolbarWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#pragma once

#include "blProjectEditorExport.h"
#include "blProjectCore/model/blProjectInfo.h"
#include <QtWidgets>

/// \class blProjectEditorToolbarWidget
/// \brief Widget that shows toolbar for project editor
/// and a tool bar to create a new project
class BLPROJECTEDITOR_EXPORT blProjectEditorToolbarWidget : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectEditorToolbarWidget(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent systeme
    explicit blProjectEditorToolbarWidget(QString projectName, QWidget *parent = 0);

signals:
    void askImport();
    void askTags();
    void askProcess();
    void askViews();
    void askInfo();

public slots:
    void setProjectName(QString projectName);

protected slots:
    void emitAskImport(bool);
    void emitAskTags(bool);
    void emitAskProcess(bool);
    void emitAskViews(bool);
    void emitAskInfo(bool);

private:
    QLabel* m_projectNameLabel;
};
