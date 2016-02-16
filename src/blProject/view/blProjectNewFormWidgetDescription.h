/// \file blProjectNewFormWidgetDescription.h
/// \brief blProjectNewFormWidgetDescription
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QtWidgets>

/// \fn blProjectNewFormWidgetDescription
/// \brief Widget that display a form for the use
/// to set a project description
class BLPROJECT_EXPORT blProjectNewFormWidgetDescription : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectNewFormWidgetDescription(bool emptyProjectButton = false, QWidget *parent = 0);
    /// \brief Contructor
    /// \param[in] emptyProjectButton True to add a button to create empty project
    /// \param[in] parent Qt parent system
    explicit blProjectNewFormWidgetDescription(bool emptyProjectButton = false, QWidget *parent = 0);

signals:
    void askCreateEmptyProject();
    
public:
    QGridLayout *layout();

public slots:
    QString getName();
    QString getDescription();

    void setName(QString name);
    void setDescription(QString desc);

private slots:
    void emitEmptyProject();

private:
    QLineEdit *m_projectNameEdit;
    QTextEdit *m_projectDescriptionEdit;
    QGridLayout* m_layout;

};
