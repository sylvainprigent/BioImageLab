/// \file blFinderAccess.cpp
/// \brief blFinderAccess
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2015
///
/// Copyright (C) BioImageLab 2015

#include "blFinderAccess.h"

blFinderAccess::blFinderAccess(){
    m_database = new blFinderDatabase;
}

blFinderAccess::~blFinderAccess(){

}

// setters
void blFinderAccess::setDatabaseFile(QString databaseFile){
    m_databaseFile = databaseFile;
}

// load/save
void blFinderAccess::load(){
    m_database->setDatabaseFile(m_databaseFile);
    m_database->connect();
}

// getters
blFinderDatabase *blFinderAccess::database(){
    return m_database;
}
