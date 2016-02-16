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

class blClosableComboBox;
// ////////////////////////////////////////////////
//  blTagsWidget
// ////////////////////////////////////////////////
/// \class blMultipleComboBox
/// \brief Widget that contains a dynamic list of line edit
class BLWIDGETS_EXPORT blMultipleComboBox : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blMultipleComboBox(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent For Qt parent sytem
    explicit blMultipleComboBox(QStringList comboList, QList<int> comboIds, QWidget *parent = 0);
    
signals:
    
public slots:
    void addComboBox(QString curentTxt = "", bool closable = true);
    /// \fn QStringList texts();
    /// \return the tags text list
    QStringList texts();
    QList<int> indexes();
    /// \fn void removeAllTags();
    /// \brief remove all the tags
    void removeAll();

private slots:
    void buttonAddComboBox();

private:
    QVBoxLayout *m_layout; ///< layout
    QStringList m_comboList;
    QList<int> m_comboIds;
};

// ////////////////////////////////////////////////
//  blClosableComboBox
// ////////////////////////////////////////////////
/// \class blClosableComboBox
/// \brief Widget that display a single tag
class blClosableComboBox : public QWidget{
    Q_OBJECT

public:
    /// \fn blClosableComboBox(bool closable = true);
    /// \brief Contructor
    /// \param[in] closable True if the tag can be removed
    blClosableComboBox(QStringList comboList, QList<int> comboIds, bool closable = true, QWidget *parent = 0);

public:
    QString text();
    int index();
    void setCurrentText(QString text);

private slots:
    /// \fn void autoDesctroy();
    /// \brief Internal slot to free the widget
    void autoDesctroy();

private:
    QComboBox *m_comboBox;
};
