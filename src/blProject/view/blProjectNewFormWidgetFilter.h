/// \file blProjectNewFormWidgetFilter.h
/// \brief blProjectNewFormWidgetFilter
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QtWidgets>
#include "blProjectNewFormWidgetFilter.h"

/// \class blProjectNewFormWidgetFilter
/// \brief Widget that display a form to add filters on
/// the folder to extract images
class BLPROJECT_EXPORT blProjectNewFormWidgetFilter : public QWidget
{
    Q_OBJECT
public:
    /// \fn blProjectNewFormWidgetFilter(QWidget* parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent system
    blProjectNewFormWidgetFilter(QWidget* parent = 0);

private slots:
    /// \fn void addFilter();
    /// \brief Add a filter
    void addFilter();
    void emitViewFiltering();
    void closeFilter(int idx);

public slots:
    QList<QStringList> getFiltersInfo();

signals:
    void askViewFiltering();

private:
    QVBoxLayout *m_layout;
    int m_countor;

};
