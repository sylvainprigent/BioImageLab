/// \file blToolIO.cpp
/// \brief blToolIO
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2015
///
/// Copyright (C) BioImageLab 2015

#include "blToolIO.h"
#include <QDebug>

blToolIO::blToolIO(){

}

/// \fn ~blToolIO();
/// \brief Destructor
blToolIO::~blToolIO(){

}

// getters/setters
void blToolIO::addInput(QString name, QString type){
    m_inputsNames.append(name);
    m_inputsTypes.append(type);
}

void blToolIO::addOutput(QString name, QString type){
    m_outputsNames.append(name);
    m_outputsTypes.append(type);
}

unsigned int blToolIO::inputsCount(){
    return m_inputsNames.count();
}

unsigned int blToolIO::outputsCount(){
    return m_outputsNames.count();
}

QString blToolIO::inputNameAt(unsigned int i){
    return m_inputsNames[i];
}

QString blToolIO::inputTypeAt(unsigned int i){
    return m_inputsTypes[i];
}

QString blToolIO::outputNameAt(unsigned int i){
    return m_outputsNames[i];
}

QString blToolIO::outputTypeAt(unsigned int i){
    return m_outputsTypes[i];
}

QStringList blToolIO::inputsNames(){
    return m_inputsNames;
}

QStringList blToolIO::inputsTypes(){
    return m_inputsTypes;
}

QStringList blToolIO::outputsNames(){
    return m_outputsNames;
}

QStringList blToolIO::outputsTypes(){
    return m_outputsTypes;
}


void blToolIO::print(){

    qDebug() << "m_inputsNames=" << m_inputsNames;
    qDebug() << "m_inputsTypes=" << m_inputsTypes;
    qDebug() << "m_outputsNames=" << m_outputsNames;
    qDebug() << "m_outputsTypes=" << m_outputsTypes;
}
