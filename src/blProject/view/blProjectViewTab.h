/// \file blProjectViewTab.h
/// \brief blProjectViewTab
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"

#include "blProjectControler.h"
#include "blProjectAddImageWidget.h"
#include "blProjectSplitLabelWidget.h"
#include "blWidgets/blHoverWidget.h"
#include "blWidgets/blHoverableWidget.h"
#include "blProjectAddRemoveSubColumnWidget.h"

/// \class blProjectViewTab
/// \brief Widget that contains a QProjectView and the
/// widgets needed to modify the project
class BLPROJECT_EXPORT blProjectViewTab : public blHoverableWidget
{
    Q_OBJECT
public:
    /// \fn blProjectViewTab(blProjectControler* controler, QWidget *parent);
    /// \brief Contructor
    /// \param[in] controler Controler containing the project data
    /// \param[in] parent Qt parent system
    blProjectViewTab(blProjectControler* controler, QWidget *parent);

signals:
    void askCloseProject();
    void askCloseProject(QString name);

public slots:
    void addImages();
    void editLabels();
    void addSelectorWidget(blProjectViewColumnSelector* selectorWidget);
    void saveMessageBox();
    void addRemoveColumns(QString);

private slots:
    void hideHoverAddImagesWidget();
    void hideHoverSplitLabelWidget();
    void hideHoverAddRemoveSubColumnWidget();
    void displayAddDataError(QString message);
    void addProject(blProjectControler* controler);
    void splitLabelSubColumnsNames(QString mainColumnName);
    void splitLabels(QString colName, QString subColName, QString separator, QString newLabelsTiles);

private:
    void createAddImagesWidget();
    void createSplitLabelsWidget();
    void createAddRemoveSubColumnWidget();
    void createToolBar();

private:
    blProjectControler* m_controler;
    blProjectAddImageWidget *m_addImageWidget;
    blProjectSplitLabelWidget* m_splitLabelsWidget;
    blProjectAddRemoveSubColumnWidget* m_addRemoveSubColumnWidget;
    bool m_addImageWidgetCreated;
    bool m_splitLabelsWidgetCreated;
    bool m_addRemoveSubColumnWidgetCreated;
    blHoverWidget *m_hoverWidgetAddImage;
    blHoverWidget *m_hoverWidgetSplitLabel;
    blHoverWidget *m_hoverWidgetAddRemoveSubColumn;


private:
    QToolBar* m_toolBar; ///< toolbar
};
