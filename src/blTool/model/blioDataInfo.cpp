#include "blioDataInfo.h"
#include <iostream>

// ////////////////////////////////// //
//         blioDataInfo
// ////////////////////////////////// //
blioDataInfo::blioDataInfo(){

}

unsigned int blioDataInfo::count(){
    return m_dataList.count();
}

blioDataList blioDataInfo::at(unsigned int index){
    return m_dataList[index];
}

void blioDataInfo::add(blioDataList dataList){
    m_dataList.append(dataList);
}

void blioDataInfo::saveAs(QString url){
    m_fileURL = url;
    /// \todo implement this
}

void blioDataInfo::save(){
    /// \todo implement this
}

void blioDataInfo::load(QString url){
    /// \todo implement this
    m_fileURL = url;
}

void blioDataInfo::print(){
    for(int i = 0 ; i < m_dataList.count() ; ++i){
        std::cout << "blioDataInfo list #" + QString::number(i).toStdString() << std::endl;
        m_dataList[i].print();
    }
}

QDataStream & operator <<(QDataStream &s, const blioDataInfo &c)
{
    s << c.m_dataList << c.m_fileURL;
    return s;
}

QDataStream & operator >>(QDataStream& stream, blioDataInfo& c){

    stream>>c.m_dataList;
    stream>>c.m_fileURL;
    return stream;
}
