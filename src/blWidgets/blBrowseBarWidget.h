/// \file blBrowseBarWidget.h
/// \brief blBrowseBarWidget
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2014

#pragma once

#include <QWidget>
#include <QLineEdit>

#include "blWidgetsExport.h"

/// \class khBrowseBarWidget
/// \brief Create a line edit widget with a browse button to select a file
class BLWIDGETS_EXPORT blBrowseBarWidget : public QWidget{
    Q_OBJECT
public:
    /// \fn blBrowseBarWidget(bool isFolder = false, QString iconFile = "", QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] isFolder true to browse a folder, and false to browse file
    /// \param[in] iconFile if empty the widget have a browse button, else have an icone
    ///                     inside the bar (aligned right) with the icon iconFile
    /// \param[in] parent Qt parent system
    blBrowseBarWidget(bool isFolder = false, QString iconFile = "", QWidget *parent = 0);

signals:
    /// \fn void pathChanged(QString);
    /// \brief Signal emitted when the path is changed
    /// \param[in] path Path writen in the line edit
    void pathChanged(QString path);

public slots:
    /// \fn void setText(QString txt);
    /// \param[in] txt Path writen in the line edit
    void setText(QString txt);
    /// \fn QString text();
    /// \return the path in the line edit
    QString text();
    /// \fn QLineEdit * getLineEdit();
    /// \return a pointer of the line edit
    QLineEdit * getLineEdit();

private slots:
    /// \fn void browse();
    /// \brief internal slot to browse the file system
    void browse();
    /// \fn void emitPathChanged(QString path);
    /// \brief emit the signal pathChanged
    /// \param[in] path Path writen in the line edit
    void emitPathChanged(QString path);
    /// \fn void emitPathChanged();
    /// \brief emit the signal pathChanged
    void emitPathChanged();

private:
    QLineEdit *m_lineEdit; ///< line edit
    bool m_isFolder; ///< is folder
};
