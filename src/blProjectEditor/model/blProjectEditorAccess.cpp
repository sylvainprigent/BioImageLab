/// \file blProjectEditorAccess.cpp
/// \brief blProjectEditorAccess
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2019

#include "blProjectEditorAccess.h"

blProjectEditorAccess::blProjectEditorAccess(){
    m_database = new blProjectEditorDatabase;
}

blProjectEditorAccess::~blProjectEditorAccess(){

}

// setters
void blProjectEditorAccess::setDatabaseFile(QString databaseFile){
    m_databaseFile = databaseFile;
}

// load/save
void blProjectEditorAccess::load(){
    m_database->setDatabaseFile(m_databaseFile);
    m_database->connect();
}

// getters
blProjectEditorDatabase *blProjectEditorAccess::database(){
    m_database->connect();
    return m_database;
}
