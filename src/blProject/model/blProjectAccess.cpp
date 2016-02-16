/// \file blProjectAccess.cpp
/// \brief blProjectAccess
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectAccess.h"

blProjectAccess::blProjectAccess(){
    m_database = new blProjectDatabase;
}

blProjectAccess::~blProjectAccess(){

}

// setters
void blProjectAccess::setDatabaseFile(QString databaseFile){
    m_databaseFile = databaseFile;
}

// load/save
void blProjectAccess::load(){
    m_database->setDatabaseFile(m_databaseFile);
    m_database->connect();
}

// getters
blProjectDatabase *blProjectAccess::database(){
    return m_database;
}
