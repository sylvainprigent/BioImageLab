/// \file blProjectViewColumnHeader.h
/// \brief blProjectViewColumnHeader
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include "blProjectViewColumnSelector.h"
#include "blProjectViewColumnParameters.h"

/// \class blProjectViewColumnHeader
/// \brief Widget that contains the header of a main column for
/// the project viewer
class BLPROJECT_EXPORT blProjectViewColumnHeader : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectViewColumnHeader(QString title, QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] title Title of the column
    /// \param[in] parent Qt parent system
    explicit blProjectViewColumnHeader(QString title, QWidget *parent = 0);
    
signals:
    void visibleColumns(QStringList);
    void askDeleteColumn(QString);
    void askOpenCompo(QString);
    void askComputeThumbnails(QString);
    void askAddRemoveColumns(QString);

public slots:
    void addColumn(QString columnName);
    void setTitle(QString title);
    void setTrashVisible(bool value);
    void setParamVisible(bool value);

public:
    QString title();
    blProjectViewColumnSelector* selector();
    blProjectViewColumnParameters* parameterEditor();

private slots:
    void emitVisibleColumns(QStringList selectedHeaders);
    void emitDeleteColumn();
    void emitComputeThumbnails();
    void emitAddRemoveColumns();

private:
    blProjectViewColumnSelector *m_selectorWidget; ///< selector widget
    QLabel *m_titleLabel; ///< label containing the title
    blClickableIcon* m_deleteWidget; ///< to delete the column
    QPushButton* m_calculateThumbnail; ///< to start the sumbnail calculation
    QPushButton* m_addRemoveColumns; ///< to start ad remove column widget
    blProjectViewColumnParameters* m_paramWidget; ///< to show the parameters (composition used to generate results)
};
