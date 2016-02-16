/// \file blProjectAddImageWidget.h
/// \brief blProjectAddImageWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QWidget>
#include <blWidgets/blBrowseBarWidget.h>
#include "blProjectControler.h"

/// \class blProjectAddImageWidget
/// \brief Widget containing forms to add/import new
/// images to the project
class BLPROJECT_EXPORT blProjectAddImageWidget : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectAddImageWidget(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Constructor
    explicit blProjectAddImageWidget(QString viewersDir, QString binariesDir, QWidget *parent = 0);
    
signals:
    /// \fn void askAddSingleImage(QString file);
    /// \brief Signal emited when the validate button of add image
    /// is clicked
    /// \param[in] file Path of the image to add
    void askAddSingleImage(QString file);
    /// \fn void cancel();
    /// \brief Signal emmited when the cancel button is clicked
    void cancel();
    /// \fn void askAddProject(blProjectControler*);
    /// \brief Signal clicked when the validate button of add
    /// image folder is clicked
    /// \param[in] controler Controler containing the information about the images to import
    void askAddProject(blProjectControler* controler);
    /// \fn void validated();
    /// \brief Signal emitted when a validate button is clicked
    void validated();

private slots:
    /// \fn void emitAddSingleImage();
    /// \brief Emit the signal askAddSingleImage
    void emitAddSingleImage();
    /// \fn void emitAskAddProject(blProjectControler* controler);
    /// \brief Emmit the signal askAddProject
    void emitAskAddProject(blProjectControler* controler);

private:
    /// \fn QWidget *createAddSingleImageWidget();
    /// \return the add single form widget
    QWidget *createAddSingleImageWidget();
    /// \fn QWidget *createAddMultipleImageWidget();
    /// \return the add folder form widget
    QWidget *createAddMultipleImageWidget();

private:
    QString m_viewersDir;
    QString m_binariesDir;
    blBrowseBarWidget *m_browseBar; ///< browse bar for single form widget
};
