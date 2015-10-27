#include "blHomeSettingsGroups.h"

blHomeSettingsGroups::blHomeSettingsGroups(){

}

// setters / getters
void blHomeSettingsGroups::add(QString group, QString key, QString value){

    int idx = this->groupIdx(group);
    if (idx >= 0){
        blHomeSettings settings = m_settings.at(idx);
        settings.add(key, value);
        m_settings[idx] = settings;
    }
    else{
        blHomeSettings settings;
        settings.add(key, value);
        m_settings.append(settings);
        m_groups.append(group);
    }
}

void blHomeSettingsGroups::add(QString group, blHomeSettings settings){
    m_groups.append(group);
    m_settings.append(settings);
}

QString blHomeSettingsGroups::value(QString group, QString key){

    for (int i = 0 ; i < m_groups.count() ; ++i){
        if (m_groups[i] == group){
            return m_settings[i].value(key);
        }
    }
    return "";
}

int blHomeSettingsGroups::groupsCount(){
    return m_groups.count();
}

QString blHomeSettingsGroups::groupTitleAt(int i){
    return m_groups.at(i);
}

blHomeSettings blHomeSettingsGroups::groupAt(int i){
    return m_settings.at(i);
}

int blHomeSettingsGroups::groupIdx(QString group){
    for (int i = 0 ; i < m_groups.count() ; ++i){
        if (m_groups[i] == group){
            return i;
        }
    }
    return -1;
}

void blHomeSettingsGroups::load(QString fileUrl){
    QFile file(fileUrl);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    in >> m_settings ;
    in >> m_groups;

}

void blHomeSettingsGroups::save(QString fileUrl){
    QFile file(fileUrl);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << m_settings;
    out << m_groups;
}

void blHomeSettingsGroups::print(){
    qDebug() << "groups content:";
    for (int i = 0 ; i < m_groups.count() ; ++i){
        qDebug() << "setting groupe :" << m_groups.at(i);
        m_settings[i].print();
    }
}


QDataStream & operator <<(QDataStream &s, const blHomeSettingsGroups &c){
    s << c.m_settings;
    s << c.m_groups;
    return s;
}

QDataStream & operator >>(QDataStream& stream, blHomeSettingsGroups& c){
    stream>>c.m_settings;
    stream>>c.m_groups;
    return stream;
}


