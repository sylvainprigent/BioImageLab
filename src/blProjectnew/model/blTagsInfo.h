/// \file blTagsInfo.h
/// \brief blTagsInfo
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2016

#pragma once

#include <QMap>
#include <QString>

// //////////////////////////////////////// //
//              blTaginfo
// //////////////////////////////////////// //
class blTagInfo{

public:
    blTagInfo();

public:
    void setId(int id);
    void setName(QString name);
    void setSubColId(int subColId);
    void setSubColName(QString subColName);

public:
    int id();
    QString name();
    int subColId();
    QString subColName();

private:
    int m_id;
    QString m_name;
    int m_subColId;
    QString m_subColName;
};

// //////////////////////////////////////////////
//              blTagsInfo
// //////////////////////////////////////////////
class blTagsInfo{

public:
    blTagsInfo();

    void set(int id, blTagInfo tagInfo);
    void add(blTagInfo tagInfo);
    blTagInfo get(int id);
    QList<blTagInfo> all();

private:
    QList<blTagInfo> m_tagsInfo;
};


