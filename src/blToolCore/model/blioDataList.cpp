#include "blioDataList.h"
#include <iostream>


// ////////////////////////////////// //
//           blioDataList
// ////////////////////////////////// //
blioDataList::blioDataList(){

}

void blioDataList::add(QString datatype, QString id, QString url, QStringList metaInfo){
    m_inputsDatatype.append(datatype);
    m_inputsID.append(id);
    m_inputsURL.append(url);
    m_metaInfo.append(metaInfo);
}

unsigned int blioDataList::count(){
    return m_inputsID.count();
}

QString blioDataList::urlAt(unsigned int index){
    return m_inputsURL[index];
}

QString blioDataList::urlAt(QString id){
    for(int i = 0 ; i < m_inputsID.count() ; ++i){
        if (m_inputsID[i] == id){
            return m_inputsURL[i];
        }
    }
    return "";
}

QStringList blioDataList::metaInfoAt(unsigned int index){
    return m_metaInfo[index];
}

QString blioDataList::idAt(unsigned int index){
    return m_inputsID[index];
}

QString blioDataList::datatypeAt(unsigned int index){
    return m_inputsDatatype[index];
}

QStringList blioDataList::inputIDs(){
    return m_inputsID;
}

QStringList blioDataList::inputUrls(){
    return m_inputsURL;
}

QStringList blioDataList::datatypes(){
    return m_inputsDatatype;
}

QList<QStringList> blioDataList::metaInfo(){
    return m_metaInfo;
}

void blioDataList::print(){
    for(int i = 0 ; i < m_inputsID.count() ; ++i){
        std::cout << m_inputsID[i].toStdString() << " = (" << m_inputsDatatype[i].toStdString() << ", " << m_inputsURL[i].toStdString() << ")" << std::endl;
    }
}

QDataStream & operator <<(QDataStream &s, const blioDataList &c)
{
    s << c.m_inputsID << c.m_inputsURL << c.m_inputsDatatype;
    return s;
}

QDataStream & operator >>(QDataStream& stream, blioDataList& c){

    stream>>c.m_inputsID;
    stream>>c.m_inputsURL;
    stream>>c.m_inputsDatatype;
    return stream;
}
