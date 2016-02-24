/// \file blProjectModelColumn.cpp
/// \brief blProjectModelColumn
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectModelColumn.h"

#include <QFile>
#include <QDataStream>
#include <QDebug>

const QString blProjectModelColumn::NUMBER = "number";
const QString blProjectModelColumn::STRING = "string";
const QString blProjectModelColumn::IMAGE_URL = "image_url";

blProjectModelColumn::blProjectModelColumn(){

}

blProjectModelColumn::blProjectModelColumn(bool isMultiLine, QString dataType){
    m_isMultiLine = isMultiLine;
    m_dataType = dataType;
}

// setters
void blProjectModelColumn::addData(unsigned int lineId, QString data){

    m_data[lineId] = data;
}

void blProjectModelColumn::addData(unsigned int lineId, float data){

    m_data[lineId] = QString::number(data);
}

void blProjectModelColumn::updateData(unsigned int lineId, QString data){
    m_data[lineId] = data;
}

void blProjectModelColumn::updateData(unsigned int lineId, float data){
    m_data[lineId] = QString::number(data);
}

// getters
QString blProjectModelColumn::dataStringAt(unsigned int lineId){
    return m_data[lineId];
}

float blProjectModelColumn::dataFloatAt(unsigned int lineId){
    return m_data[lineId].toFloat();
}

// getters for serialisation
bool blProjectModelColumn::isMultiLine() const{
    return m_isMultiLine;
}

QString blProjectModelColumn::dataType() const{
    return m_dataType;
}

QMap<unsigned int, QString> blProjectModelColumn::data() const{
    return m_data;
}

void blProjectModelColumn::setIsMultiLine(bool isMultiLine){
    m_isMultiLine = isMultiLine;
}

void blProjectModelColumn::setDataType(QString dataType){
    m_dataType = dataType;
}

void blProjectModelColumn::setData(QMap<unsigned int, QString> &data){
    m_data = data;
}

// datastream
QDataStream & operator << (QDataStream & out, const blProjectModelColumn & column)
{
    out.setVersion(QDataStream::Qt_5_2);
    out << quint8(column.isMultiLine()) << column.dataType() << column.data() ;
    return out;
}

QDataStream & operator >> (QDataStream & in, blProjectModelColumn & column){
    in.setVersion(QDataStream::Qt_5_2);
    quint8 isml;
    QString dataType;
    QMap<unsigned int, QString> data;

    in >> isml >> dataType >> data ;

    if (isml == 1){column.setIsMultiLine(true);}
    else {column.setIsMultiLine(false);}
    column.setDataType(dataType);
    column.setData(data);

    return in;
}
