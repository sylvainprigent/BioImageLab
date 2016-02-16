/// \file blProjectNewFormWidgetLabel.h
/// \brief blProjectNewFormWidgetLabel
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QtWidgets>

/// \class blProjectNewFormWidgetLabel
/// \brief Widget that display the possible filters for
/// extraction labels on selected files path
class BLPROJECT_EXPORT blProjectNewFormWidgetLabel : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectNewFormWidgetLabel(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent system
    explicit blProjectNewFormWidgetLabel(QWidget *parent = 0);
    
signals:
    /// \fn void askView();
    /// \brief signal emitted when the user click on view
    void askView();

public:
    /// \fn QStringList regExpList();
    /// \return the regexp list
    QStringList regExpList();
    
private slots:
    /// \fn void emitView();
    /// \brief Slot that emit the signal "view"
    void emitView();
    /// \fn void setFoldersCheckBoxVisible(bool visible);
    /// \param[in] visible True if visible
    void setFoldersCheckBoxVisible(bool visible);

public slots:
    /// \fn QStringList filtersList();
    /// \return the list of filters
    QStringList filtersList();


private:
    QVBoxLayout *layout; ///< layout
    QCheckBox *m_checkBoxFolders; ///< check box for folder label extraction
    QCheckBox *m_checkBoxDate; ///< check box for date label extraction
};
