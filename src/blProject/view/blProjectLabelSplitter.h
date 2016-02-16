/// \file blProjectLabelSplitter.h
/// \brief blProjectLabelSplitter
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"

#include "blProjectControler.h"
#include "blProjectAddImageWidget.h"
#include "blProjectSplitLabelWidget.h"
#include "blWidgets/blHoverWidget.h"
#include "blWidgets/blHoverableWidget.h"

/// \class blProjectViewTab
/// \brief Create a new sub column in a project by splitting the label of an other subcolumn
class BLPROJECT_EXPORT blProjectLabelSplitter : public QObject
{
    Q_OBJECT
public:
    /// \fn blProjectLabelSplitter(QObject *parent);
    /// \brief Contructor
    /// \param[in] parent Qt parent system
    blProjectLabelSplitter(QObject *parent = 0);

public:
    void setColumnName(QString columnName);
    void setSubColumnName(QString subColumnName);
    void setSeparator(QString separator);
    void setNewSubColumnsNames(QString newSubColumnsNames);

public:
    void run(blProjectControler* project);

private:
    QString m_columnName; ///< Name of the column to process
    QString m_subColumnName; ///< Name of the subColumn to process
    QString m_separator; ///< separator caractere for split
    QString m_newSubColumnsNames; ///< names separated with ','
};
