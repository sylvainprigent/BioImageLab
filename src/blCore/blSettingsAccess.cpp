/// \file blSettingsAccess.cpp
/// \brief blSettingsAccess
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blSettingsAccess.h"

blSettingsAccess::blSettingsAccess(){
    m_settings = new blSettingsGroups;
}

blSettingsAccess::~blSettingsAccess(){

}

// setters
void blSettingsAccess::setSettingsFile(QString fileUrl){
    m_fileUrl = fileUrl;
}

// load/save
void blSettingsAccess::load(){
    m_settings->load(m_fileUrl);
}

// getters
blSettingsGroups *blSettingsAccess::settings(){
    return m_settings;
}
