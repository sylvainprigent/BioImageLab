#include "blHomeSettings.h"

blHomeSettings::blHomeSettings(){

}

void blHomeSettings::add(QString key, QString value, QString type){
    QStringList data;
    data.append(value);
    data.append(type);
    m_map[key] = data;
}

QString blHomeSettings::value(QString key){
    return m_map[key][0];
}

QString blHomeSettings::type(QString key){
    return m_map[key][1];
}

QMap<QString, QStringList> blHomeSettings::map(){
    return m_map;
}

void blHomeSettings::print(){
    QMapIterator<QString, QStringList> i(m_map);
    while (i.hasNext()) {
        i.next();
        qDebug() << "key: " << i.key() << ", value: " << i.value()[0] << ", type: " << i.value()[1];
    }
}

QDataStream & operator <<(QDataStream &s, const blHomeSettings &c)
{
    s << c.m_map;
    return s;
}

QDataStream & operator >>(QDataStream& stream, blHomeSettings& c){

    stream>>c.m_map;
    return stream;
}

