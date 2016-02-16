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
#include "blProjectControler.h"

/// \class blProjectAddRemoveSubColumnWidget
/// \brief Widget containing forms to add/remove a project sub column
class BLPROJECT_EXPORT blProjectAddRemoveSubColumnWidget : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectAddRemoveSubColumnWidget(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Constructor
    explicit blProjectAddRemoveSubColumnWidget(QWidget *parent = 0);
    
public:
    void setMainColumnName(QString name);
    void setSubColumnsNames(QStringList names);

signals:
    /// \fn void askAddSubColumn(QString mainColumnName, QString subColumnName);
    /// \brief Signal emited when the validate button of add column
    /// is clicked
    /// \param[in] mainColumnName main column name
    /// \param[in] subColumnName new sub column name
    void askAddRemoveSubColumn(QString mainColumnName, QString subColumnName, bool add);
    /// \fn void cancel();
    /// \brief Signal emmited when the cancel button is clicked
    void cancel();

private slots:
    /// \fn void emitAdd();
    /// \brief Emit the signal askAddRemoveSubColumn
    void emitAdd();
    /// \fn void emitRemove();
    /// \brief Emit the signal askAddRemoveSubColumn
    void emitRemove();

private:
    /// \fn QWidget *createAddWidget();
    /// \return the add form widget
    QWidget *createAddWidget();
    /// \fn QWidget *createRemoveWidget();
    /// \return the remove form widget
    QWidget *createRemoveWidget();

private:
    QString m_mainColumnName;

private:
    QLineEdit* m_addColumnNameEdit;
    QComboBox* m_removeColumnNamesBox;

};
