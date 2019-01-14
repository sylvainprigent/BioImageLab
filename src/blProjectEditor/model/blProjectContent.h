/// \file blProjectContent.h
/// \brief blProjectContent
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#pragma once

#include "blProjectEditorExport.h"
#include <QString>
#include <QList>
#include <QStringList>

#include "blProjectTag.h"
#include "blProjectTagValue.h"
#include "blProjectData.h"

#include <QtWidgets>

/// \class blProjectContent
/// \brief Contains the informations of a blProjectData
class BLPROJECTEDITOR_EXPORT blProjectContent
{
public:
    /// \fn blProjectContent();
    /// \brief Constructor
    blProjectContent();
    /// \fn ~blProjectContent();
    /// \brief Destructor
    ~blProjectContent();

public:
    // setters
    void setTags(QList<blProjectTag*> tags);
    void setData(QList<blProjectData*> data);
    void setDataTag(blProjectTagValue *tag);

public:
    // getters
    int count();
    QList<blProjectTag*> getTags();
    blProjectTagValue* getTag(blProjectData* data, blProjectTag* tag);
    blProjectData* getData(int dataIdx);

public:
    void print();

private:
    unsigned int m_count; ///< number of data in the project
    QList< blProjectTag* > m_tags; ///< list of tags
    QList< blProjectTagValue* > m_tagsValues; ///< table of tags values
    QList< blProjectData* > m_data; ///< list of data
};
