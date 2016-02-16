/// \file blTagsWidget.h
/// \brief blTagsWidget
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab

#pragma once

#include <QtWidgets>
#include "blWidgetsExport.h"

class blClosableLineEdit;
// ////////////////////////////////////////////////
//  blTagsWidget
// ////////////////////////////////////////////////
/// \class blMultipleLineEdit
/// \brief Widget that contains a dynamic list of line edit
class BLWIDGETS_EXPORT blMultipleLineEdit : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blMultipleLineEdit(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent For Qt parent sytem
    explicit blMultipleLineEdit(QWidget *parent = 0);
    
signals:
    
public slots:
    void addLineEdit(bool closable);
    /// \fn QStringList texts();
    /// \return the tags text list
    QStringList texts();
    /// \fn void removeAllTags();
    /// \brief remove all the tags
    void removeAll();

private:
    QVBoxLayout *m_layout; ///< layout
};

// ////////////////////////////////////////////////
//  blClosableLineEdit
// ////////////////////////////////////////////////
/// \class blClosableLineEdit
/// \brief Widget that display a single tag
class blClosableLineEdit : public QWidget{
    Q_OBJECT

public:
    /// \fn blClosableLineEdit(bool closable = true);
    /// \brief Contructor
    /// \param[in] closable True if the tag can be removed
    blClosableLineEdit(bool closable = true, QWidget *parent = 0);

public:
    QString text();

private slots:
    /// \fn void autoDesctroy();
    /// \brief Internal slot to free the widget
    void autoDesctroy();

private:
    QLineEdit *m_lineEdit;
};
