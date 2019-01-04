/// \file blProjectEditorWidget.h
/// \brief blProjectEditorWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include <QWidget>

#include "blProjectEditorExport.h"
#include "blProjectCore/model/blProjectInfo.h"
#include "blProjectEditorToolbarWidget.h"
#include "blProjectEditorTableWidget.h"
#include "blProjectEditorFooterWidget.h"


/// \class blProjectBrowserWidget
/// \brief Widget that shows the list of project
/// and a tool bar to create a new project
class BLPROJECTEDITOR_EXPORT blProjectEditorWidget : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectEditorWidget(blProjectInfo *projectInfo, QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent systeme
    explicit blProjectEditorWidget(blProjectInfo *projectInfo, QWidget *parent = 0);

signals:
    void askImport();
    void askTags();
    void askProcess();
    void askViews();
    void askInfo();

public slots:
    void setProjectInfo(blProjectInfo* projectInfo);

protected:
    blProjectEditorToolbarWidget *m_toolbar;
    blProjectEditorTableWidget *m_table;
    blProjectEditorFooterWidget *m_footer;

};
