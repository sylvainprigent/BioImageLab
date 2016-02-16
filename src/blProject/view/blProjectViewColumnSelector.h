/// \file blProjectViewColumnSelector.h
/// \brief blProjectViewColumnSelector
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QtWidgets>
#include <blWidgets/blClickableIcon.h>

/// \class blProjectViewColumnSelector
/// \brief Widget that display a list of main column to be able to
/// show/hide a main column af a project
class BLPROJECT_EXPORT blProjectViewColumnSelector : public QPushButton
{
    Q_OBJECT
public:
    /// \fn explicit blProjectViewColumnSelector(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent system
    explicit blProjectViewColumnSelector(QWidget *parent = 0);
    
signals:
    void visibleColumns(QStringList);
    
public slots:
    void addColumn(QString columnName);
    void setChecked(QString title, bool checked);
    void selectAll();
    void removeColumn(QString columnName);

private slots:
    void showSelector();
    void hideSelector();
    void uncheckSelectAll();
    void selectAllClicked(bool checked);

private:
    void createSelector();

private:
    QWidget *m_selector; ///< selector
    QVBoxLayout *m_columnListLayout; ///< column list layout
    QCheckBox *m_selectAllBox; ///< box select all
    QScrollArea *m_selectrorScroll; ///< scroll area containing the selector
};
