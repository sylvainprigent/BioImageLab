/// \file blProjectNewFormWidgetImport.h
/// \brief blProjectNewFormWidgetImport
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QtWidgets>

/// \class blProjectNewFormWidgetImport
/// \brief Widget to select a folder
class BLPROJECT_EXPORT blProjectNewFormWidgetImport : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectNewFormWidgetImport(QWidget *parent = 0);
    /// \brief parent Qt parent system
    explicit blProjectNewFormWidgetImport(QWidget *parent = 0);
    
signals:
    
public slots:
    /// \fn QString getPath();
    /// \return the selected folder path
    QString getPath();
    /// \fn bool isRecursive();
    /// \return true if the recursive check box is checked
    bool isRecursive();

private slots:
    /// \fn void browse();
    /// \brief open the folder browser widget
    void browse();

private:
    QLineEdit *m_folderEdit; ///< Folder path line edit
    QCheckBox *m_checkBox; ///< recursive check box
    
};
