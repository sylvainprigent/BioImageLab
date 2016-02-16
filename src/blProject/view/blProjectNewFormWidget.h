/// \file blProjectNewFormWidget.h
/// \brief blProjectNewFormWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QWidget>
#include "blProjectView.h"
#include "blProjectNewFormWidgetImport.h"
#include "blProjectNewFormWidgetFilter.h"
#include "blProjectNewFormWidgetLabel.h"
#include "blProjectNewFormWidgetDescription.h"
#include <blWidgets/blTwoSideWidget.h>
#include "blProjectControler.h"

/// \class blProjectNewFormWidget
/// \brief Widget showing a form to create
/// a new project
class BLPROJECT_EXPORT blProjectNewFormWidget : public QWidget{

    Q_OBJECT
public:
    /// \fn blProjectNewFormWidget();
    /// \brief Constructor
    /// \param[in] parent Qt parent system
    /// \param[in] useDescription True to add the description form
    blProjectNewFormWidget(QString viewerDir, QString binariesDir, QWidget *parent = 0, bool useDescription = true);
    ~blProjectNewFormWidget();

public:

    /// \fn QString name();
    /// \return the name of the project
    QString name();
    /// \fn QString objective();
    /// \return the description of the project
    QString objective();
    /// \fn QStringList tags();
    /// \return the tags/keywords associated to the project
    QStringList tags();

signals:
    void askCreateProject(blProjectControler *);
    void askCreateProject(blProjectControler *, blProjectNewFormWidget*);
    void askEmptyProject(blProjectNewFormWidget*);
    void askCancel(blProjectNewFormWidget *);
    void askCancel();

private:
    blTwoSideWidget *twoSideWidget;
    blProjectNewFormWidgetImport *m_importFolder;
    blProjectNewFormWidgetFilter *m_filter;
    blProjectNewFormWidgetLabel *m_labeling;
    blProjectNewFormWidgetDescription* m_description;


private slots:
    void showDescriptionHelp();
    void showImportFolderHelp();
    void showFilterHelp();
    void showLabelingHelp();
    void showFilteringView(bool show = true);
    void showLabelView();
    blProjectControler *createDataTable();
    blProjectControler* createLabelTable();

    void validateClicked();
    void emptyProjectClicked();
    void cancelClicked();

private:
    QString m_viewerDir, m_binariesDir;
    QStringList m_imagesPaths; ///< images to add to the project
    bool m_useDescription; ///< True to add the description form
};
