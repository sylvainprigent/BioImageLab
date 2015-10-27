/// \file blToolInfo.cpp
/// \brief blToolInfo
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2015
///
/// Copyright (C) BioImageLab 2014

#include "blToolInfo.h"
#include <QDebug>
#include <iostream>
#include <QDataStream>

blToolInfo::blToolInfo(){
    m_id = 0;
}

blToolInfo::~blToolInfo(){

}

// setters
void blToolInfo::setId(int id){
    m_id = id;
}

void blToolInfo::setName(QString name){
    m_name = name;
}

void blToolInfo::setTitle(QString title){
    m_title = title;
}

void blToolInfo::setVersion(QString version){
    m_version = version;
}

void blToolInfo::setToolbox(QString toolbox){
    m_toolbox = toolbox;
}

void blToolInfo::setInterpreter(QString interpreter){
    m_interpreter = interpreter;
}

void blToolInfo::setDatatype(QString type){
    m_datatype = type;
}

void blToolInfo::setDescription(QString description){
    m_description = description;
}

void blToolInfo::setDoc(QString doc){
    m_doc = doc;
}

void blToolInfo::setCommand(QString command){
    m_command = command;
}

void blToolInfo::setXmlUrl(QString url){
    m_xmlurl = url;
}

void blToolInfo::setKeywords(QStringList &keywords){
    m_keywords = keywords;
}

void blToolInfo::setIO(blToolIO &io){
    m_io = io;
}

void blToolInfo::setParameters(blToolParameters parameters){
    m_parameters = parameters;
}

void blToolInfo::setIdInWorkflow(QString id){
    m_idInWorkflow = id;
}

// getters
int blToolInfo::id(){
    return m_id;
}

QString blToolInfo::name(){
    return m_name;
}

QString blToolInfo::title(){
    return m_title;
}

QString blToolInfo::version(){
    return m_version;
}

QString blToolInfo::toolbox(){
    return m_toolbox;
}

QString blToolInfo::interpreter(){
    return m_interpreter;
}

QString blToolInfo::datatype(){
    return m_datatype;
}

QString blToolInfo::description(){
    return m_description;
}

QString blToolInfo::doc(){
    return m_doc;
}

QString blToolInfo::command(){
    return m_command;
}

QString blToolInfo::xmlurl(){
    return m_xmlurl;
}

QStringList blToolInfo::keywords(){
    return m_keywords;
}

blToolIO blToolInfo::getIO(){
    return m_io;
}

blToolParameters blToolInfo::parameters(){
    return m_parameters;
}

void blToolInfo::print(){

    std::cout << "m_id=" << m_id << std::endl;
    std::cout << "m_name=" << m_name.toStdString()<< std::endl;
    std::cout << "m_title=" << m_title.toStdString()<< std::endl;
    std::cout << "m_version=" << m_version.toStdString()<< std::endl;
    std::cout << "m_toolbox=" << m_toolbox.toStdString()<< std::endl;
    std::cout << "m_interpreter=" << m_interpreter.toStdString()<< std::endl;
    std::cout << "m_datatype=" << m_datatype.toStdString()<< std::endl;
    std::cout << "m_description=" << m_description.toStdString()<< std::endl;
    std::cout << "m_urlDoc=" << m_doc.toStdString()<< std::endl;
    std::cout << "m_command=" << m_command.toStdString()<< std::endl;
    std::cout << "m_xmlurl=" << m_xmlurl.toStdString()<< std::endl;
    //std::cout << "m_keywords=" << m_keywords<< std::endl;
    std::cout << "m_idInWorkflow=" << m_idInWorkflow.toStdString()<< std::endl;
    m_io.print();
}

QDataStream & operator <<(QDataStream &s, const blToolInfo &c)
{
    s << c.m_id;
    s << c.m_name;
    s << c.m_title;
    s << c.m_version;
    s << c.m_toolbox;
    s << c.m_interpreter;
    s << c.m_datatype;
    s << c.m_description;
    s << c.m_doc;
    s << c.m_command;
    s << c.m_xmlurl;
    s << c.m_keywords;
    s << c.m_idInWorkflow;
    return s;
}

QDataStream & operator >>(QDataStream& s, blToolInfo& c){

    s >> c.m_id;
    s >> c.m_name;
    s >> c.m_title;
    s >> c.m_version;
    s >> c.m_toolbox;
    s >> c.m_interpreter;
    s >> c.m_datatype;
    s >> c.m_description;
    s >> c.m_doc;
    s >> c.m_command;
    s >> c.m_xmlurl;
    s >> c.m_keywords;
    s >> c.m_idInWorkflow;
    return s;
}
