/// \file blProjectViewColumnParameters.h
/// \brief blProjectViewColumnParameters
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QtWidgets>
#include <blWidgets/blClickableIcon.h>

/// \class blProjectViewColumnParameters
/// \brief Widget that display a summary of the tool used to generate the column data
class BLPROJECT_EXPORT blProjectViewColumnParameters : public blClickableIcon
{
    Q_OBJECT
public:
    /// \fn explicit blProjectViewColumnParameters(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent system
    explicit blProjectViewColumnParameters(QWidget *parent = 0);
    
signals:
    void askOpenCompo(QString);
    
public slots:
    /// \fn void setDate(QString date);
    /// \param[in] data Date when the tool were ran
    void setDate(QString date);

    /// \fn void setCompoUrl(QString url);
    /// \brief url URL of the tool composition
    void setCompoUrl(QString url);

private slots:
    void emitOpenCompo();
    void hideEditor();
    void showEditor();

private:
    void createEditor();

private:
    QLabel *m_dateLabel; ///< label the display the date
    QString m_compoUrl;  ///< URL of the tool composition
    QWidget* m_editor;    ///< widget containing the editor

};
