/// \file blProjectModelColumn.h
/// \brief blProjectModelColumn
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QString>
#include <QMap>

/// \fn blProjectModelColumn
/// \brief Define methods to load/save a column
/// data and manage the data
class BLPROJECT_EXPORT blProjectModelColumn {

public:
    /// \fn blProjectModelColumn();
    /// \brief Constructor
    blProjectModelColumn();

    /// \fn blProjectModelColumn();
    /// \brief Constructor
    /// \param[in] isMultiLine true if there is one data per line
    /// \param[in] dataType Type of data to store (see list below)
    blProjectModelColumn(bool isMultiLine, QString dataType);

public:
    // data types
    static const QString NUMBER; ///< number data type
    static const QString STRING; ///< string data type
    static const QString IMAGE_URL; ///< image URL data type

public:
    // setters
    /// \fn void addData(unsigned int lineId, QString data);
    /// \param[in] lineId id of the line to add data
    /// \param[in] data Data to add
    void addData(unsigned int lineId, QString data);
    /// \fn void addData(unsigned int lineId, float data);
    /// \param[in] lineId id of the line to add data
    /// \param[in] data Data to add
    void addData(unsigned int lineId, float data);
    /// \fn void updateData(unsigned int lineId, QString data);
    /// \brief Update a line data
    /// \param[in] lineId id of the line to add data
    /// \param[in] data Data to add
    void updateData(unsigned int lineId, QString data);
    /// \fn void updateData(unsigned int lineId, float data);
    /// \brief Update a line data
    /// \param[in] lineId id of the line to add data
    /// \param[in] data Data to add
    void updateData(unsigned int lineId, float data);

    // getters
    /// \fn QString dataStringAt(unsigned int lineId);
    /// \return the data string at line "lineId"
    /// \param[in] lineId Line to get the data
    QString dataStringAt(unsigned int lineId);
    /// \fn float dataFloatAt(unsigned int lineId);
    /// \return the data float at line "lineId"
    /// \param[in] lineId Line to get the data
    float dataFloatAt(unsigned int lineId);

public:
    // getters for serialisation
    /// \fn bool isMultiLine() const;
    /// \return true the column is of type one data per line
    bool isMultiLine() const;
    /// \fn QString dataType() const;
    /// \return the data type
    QString dataType() const;
    /// \fn QMap<unsigned int, QString> data() const;
    /// \return the data
    QMap<unsigned int, QString> data() const;

    // setters for serialisation
    /// \fn void setIsMultiLine(bool isMultiLine);
    /// \param[in] isMultiLine true the column is of type one data per line
    void setIsMultiLine(bool isMultiLine);
    /// \fn void setDataType(QString dataType);
    /// \param[in] dataType Type of data to store
    void setDataType(QString dataType);
    /// \fn void setData(QMap<unsigned int, QString> &data);
    /// \param[in] data Data to store in the column
    void setData(QMap<unsigned int, QString> &data);

private:
    bool m_isMultiLine; ///< true if there is one data per line
    QString m_dataType; ///< type of data to store
    QMap<unsigned int, QString> m_data; ///< data for the column
};

/// \fn QDataStream & operator << (QDataStream & out, const blProjectModelColumn & column);
/// \brief implement stream operator for blProjectModelColumn
/// \param[in] out Stream
/// \param[in] column Column to parse
/// \return the data stream containing the parsed column
QDataStream & operator << (QDataStream & out, const blProjectModelColumn & column);
/// \fn QDataStream & operator >> (QDataStream & in, blProjectModelColumn & column);
/// \brief implement stream operator for blProjectModelColumn
/// \param[in] out Stream
/// \param[in] column Column to parse
/// \return the data stream containing the parsed column
QDataStream & operator >> (QDataStream & in, blProjectModelColumn & column);
