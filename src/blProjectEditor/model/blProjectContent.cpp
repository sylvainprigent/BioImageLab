/// \file blProjectContent.cpp
/// \brief blProjectContent
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#include "blProjectContent.h"
#include <QDebug>
#include <iostream>

blProjectContent::blProjectContent(){
    m_count = 0;
}

blProjectContent::~blProjectContent(){

}

// setters
void blProjectContent::setTags(QList<blProjectTag*> tags){
    m_tags = tags;
}

void blProjectContent::setData(QList<blProjectData*> data){
    m_data = data;
    m_count = data.count();
}

void blProjectContent::setDataTag(blProjectTagValue* tag){
    m_tagsValues.append(tag);
}

// getters
int blProjectContent::count(){
    return m_count;
}

QList<blProjectTag*> blProjectContent::getTags(){
    return m_tags;
}

blProjectTagValue* blProjectContent::getTag(blProjectData* data, blProjectTag* tag){

    for(int i = 0 ; i < m_tagsValues.count() ; i++){
        blProjectTagValue* tv = m_tagsValues[i];
        if ( tv->getIdData() == data->id() && tv->getIdTag() == tag->id() ){
            return tv;
        }
    }
    return NULL;
}

blProjectData* blProjectContent::getData(int dataIdx){
    return m_data[dataIdx];
}

void blProjectContent::print(){
    std::cout << "project content:" << std::endl;
    std::cout << "----------------" << std::endl;

    // header
    std::cout << "Data | ";
    for (int c = 0 ; c < m_tags.count() ; c++){
        std::cout << m_tags[c]->name().toStdString() + " | ";
    }
    std::cout << std::endl;

    // content
    for (int r = 0 ; r < m_count ; r++){

        std::cout << m_data[r]->url().toStdString() + " | ";
        for (int c = 0 ; c < m_tags.count() ; c++){

            blProjectTagValue *tv = this->getTag(m_data[r], m_tags[c]);
            if (tv){
                std::cout << tv->getValue().toStdString() + " | ";
            }
            else{
                std::cout << "NULL | ";
            }

        }
        std::cout << std::endl;
    }
    std::cout << "----------------" << std::endl;
}
