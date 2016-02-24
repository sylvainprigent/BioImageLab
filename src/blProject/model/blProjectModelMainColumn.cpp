/// \file blProjectModelMainColumn.cpp
/// \brief blProjectModelMainColumn
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectModelMainColumn.h"

#include <QFile>
#include <QDebug>
#include <QDataStream>

blProjectModelMainColumn::blProjectModelMainColumn(){

}

blProjectModelMainColumn::blProjectModelMainColumn(QString file){
    m_file = file;
}


// file
void blProjectModelMainColumn::setFile(QString file){
    m_file = file;
}

QString blProjectModelMainColumn::file(){
    return m_file;
}


// setters
void blProjectModelMainColumn::addColumn(QString name){
    blProjectModelColumn column;
    m_columns[name] = column;
}

void blProjectModelMainColumn::removeColumn(QString columnName){
    m_columns.remove(columnName);
}

void blProjectModelMainColumn::addColumn(QString name, blProjectModelColumn& data){
    m_columns[name] = data;
}

QMap<QString, blProjectModelColumn> blProjectModelMainColumn::columns(){
    return m_columns;
}

blProjectModelColumn& blProjectModelMainColumn::column(QString name){
    return m_columns[name];
}

void blProjectModelMainColumn::setName(QString name){
    m_name = name;
}

QString blProjectModelMainColumn::name(){
    return m_name;
}

// IO
void blProjectModelMainColumn::load(){

    QFile file(m_file);
    if (file.exists()){
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "ERROR: Cannot open the file " + m_file + " to load columns " + file.errorString();
            return;
        }
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_2);
        in >> m_name;
        in >> m_columns;
    }
}

void blProjectModelMainColumn::save(){

    QFile file(m_file);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "ERROR: Cannot open the file " + m_file + " to save column " + file.errorString();
        return;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_2);
    out << m_name;
    out << m_columns;
}

bool blProjectModelMainColumn::isColumn(QString name){

    QMap<QString, blProjectModelColumn>::iterator i = m_columns.begin();
     while (i != m_columns.end()) {
         if (i.key() == name){
             return true;
         }
         ++i;
     }
     return false;
}
