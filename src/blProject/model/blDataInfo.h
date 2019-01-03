/// \file blDataInfo.h
/// \brief blDataInfo
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2016

#pragma once

#include <QString>

class blDataInfo{

public:
    blDataInfo();

public:
    void setid(int value);
    void setline_id(int value);
    void seturl(QString value);
    void setthumbnail(QString value);
    void setid_main_col(int value);
    void setid_sub_column(int value);
    void setmain_col_name(QString value);
    void setid_sub_column_name(QString value);

public:
    int id();
    int line_id();
    QString url();
    QString thumbnail();
    int id_main_col();
    int id_sub_column();
    QString main_col_name();
    QString id_sub_column_name();

private:
    int m_id;
    int m_line_id;
    QString m_url;
    QString m_thumbnail;
    int m_id_main_col;
    int m_id_sub_column;
    QString m_main_col_name;
    QString m_id_sub_column_name;
};

