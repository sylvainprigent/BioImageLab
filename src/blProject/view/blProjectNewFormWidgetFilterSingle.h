/// \file blProjectNewFormWidgetFilterSingle.h
/// \brief blProjectNewFormWidgetFilterSingle
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QtWidgets>

/// \fn blProjectNewFormWidgetFilterSingle
/// \brief Widget that discplay a single filter to extract
/// files from a folder
class BLPROJECT_EXPORT blProjectNewFormWidgetFilterSingle : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectNewFormWidgetFilterSingle(QString title, int idx = 0, QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] title Title of the filter
    /// \param[in] idx Index of the filter for the filter list
    /// \param[in] parent Qt parent system
    explicit blProjectNewFormWidgetFilterSingle(QString title, int idx = 0, QWidget *parent = 0);
    
signals:
    void close(QWidget*);
    void close(int idx);

public slots:
    QStringList getFilterInfo();
    void decreaseIdxByOne();
    int idx();

private slots:
    void emitClose();

private:
    QLineEdit *startLineEdit;
    QLineEdit *containsLineEdit;
    QLineEdit *endsLineEdit;
    QLabel *titleLabel;
    int m_idx;
};
