#include "blSettings.h"

blSettings::blSettings(){

}

void blSettings::add(QString key, QString value, QString type){
    QStringList data;
    data.append(value);
    data.append(type);
    m_map[key] = data;
    //qDebug() << " ++++++++++++++ add key to the settings";
}

void blSettings::set(QString key, QString value, QString type){
    QStringList data;
    data.append(value);
    data.append(type);
    m_map[key] = data;
}

QString blSettings::value(QString key, bool createIfNotExists){
    if (m_map.contains(key)){
        return m_map[key][0];
    }
    else{
        if (createIfNotExists){
            this->add(key, "", "");
        }
    }
    return "";
}

QString blSettings::type(QString key){
    return m_map[key][1];
}

QMap<QString, QStringList> blSettings::map(){
    return m_map;
}

void blSettings::print(){
    QMapIterator<QString, QStringList> i(m_map);
    while (i.hasNext()) {
        i.next();
        qDebug() << "key: " << i.key() << ", value: " << i.value()[0] << ", type: " << i.value()[1];
    }
}

QDataStream & operator <<(QDataStream &s, const blSettings &c)
{
    s << c.m_map;
    return s;
}

QDataStream & operator >>(QDataStream& stream, blSettings& c){

    stream>>c.m_map;
    return stream;
}

