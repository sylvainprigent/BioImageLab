/// \file blProjectTagValue.h
/// \brief blProjectTagValue
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#pragma once

#include "blProjectEditorExport.h"
#include <QString>

/// \class blProjectTagValue
/// \brief Contains the value of a blProjectTag for a give tag and data
class BLPROJECTEDITOR_EXPORT blProjectTagValue
{
public:
    /// \fn blProjectTag();
    /// \brief Constructor
    blProjectTagValue();
    /// \fn ~blProjectTag();
    /// \brief Destructor
    ~blProjectTagValue();

public:
    // setters
    void setId(unsigned int id);
    void setIdTag(unsigned int id);
    void setIdData(unsigned int id);
    void setValue(QString value);

public:
    // getters
    unsigned int getId();
    unsigned int getIdTag();
    unsigned int getIdData();
    QString getValue();

public:
    void print();

private:
    unsigned int m_id;
    unsigned int m_idTag;
    unsigned int m_idData;
    QString m_value;

};
