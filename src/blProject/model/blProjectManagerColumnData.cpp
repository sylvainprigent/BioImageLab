#include "khProjectManagerColumnData.h"

khProjectManagerColumnData::khProjectManagerColumnData(){
}

khProjectManagerColumnData::khProjectManagerColumnData(unsigned int lineId, QString data){
    m_lineId = lineId;
    m_dataUrl = data;
}

khProjectManagerColumnData::khProjectManagerColumnData(unsigned int lineId, float data){
    m_lineId = lineId;
    m_dataNumber = data;
}

// getters
unsigned int khProjectManagerColumnData::lineId(){
    return m_lineId;
}

QString khProjectManagerColumnData::dataString(){
    return m_dataUrl;
}

float khProjectManagerColumnData::dataNumber(){
    return m_dataNumber;
}

// setters
void khProjectManagerColumnData::setLineId(unsigned int lineId){
    m_lineId = lineId;
}

void khProjectManagerColumnData::setDataString(QString dataString){
    m_dataUrl = dataString;
}

void khProjectManagerColumnData::setDataNumber(float dataNumber){
    m_dataNumber = dataNumber;
}
