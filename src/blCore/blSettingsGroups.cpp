#include "blSettingsGroups.h"

blSettingsGroups::blSettingsGroups(){

}

// setters / getters
void blSettingsGroups::add(QString group, QString key, QString value){

    int idx = this->groupIdx(group);
    if (idx >= 0){
        blSettings settings = m_settings.at(idx);
        settings.add(key, value);
        m_settings[idx] = settings;
    }
    else{
        blSettings settings;
        settings.add(key, value);
        m_settings.append(settings);
        m_groups.append(group);
    }
}

void blSettingsGroups::set(QString group, QString key, QString value){
    int idx = this->groupIdx(group);
    if (idx >= 0){
        blSettings settings = m_settings.at(idx);
        settings.set(key, value);
        m_settings[idx] = settings;
    }
    else{
        blSettings settings;
        settings.add(key, value);
        m_settings.append(settings);
        m_groups.append(group);
    }
}

void blSettingsGroups::add(QString group, blSettings settings){
    m_groups.append(group);
    m_settings.append(settings);
}

void blSettingsGroups::clear(){
    m_settings.clear();
    m_groups.clear();
}

QString blSettingsGroups::value(QString group, QString key, bool createIfNotExist){

    for (int i = 0 ; i < m_groups.count() ; ++i){
        if (m_groups[i] == group){
            return m_settings[i].value(key, createIfNotExist);
        }
    }
    return "";
}

int blSettingsGroups::groupsCount(){
    return m_groups.count();
}

QString blSettingsGroups::groupTitleAt(int i){
    return m_groups.at(i);
}

blSettings blSettingsGroups::groupAt(int i){
    return m_settings.at(i);
}

int blSettingsGroups::groupIdx(QString group){
    for (int i = 0 ; i < m_groups.count() ; ++i){
        if (m_groups[i] == group){
            return i;
        }
    }
    return -1;
}

void blSettingsGroups::load(QString fileUrl){
    QFile file(fileUrl);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    in >> m_settings ;
    in >> m_groups;

}

void blSettingsGroups::save(QString fileUrl){
    QFile file(fileUrl);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << m_settings;
    out << m_groups;
}

void blSettingsGroups::print(){
    qDebug() << "groups content:";
    for (int i = 0 ; i < m_groups.count() ; ++i){
        qDebug() << "setting groupe :" << m_groups.at(i);
        m_settings[i].print();
    }
}


QDataStream & operator <<(QDataStream &s, const blSettingsGroups &c){
    s << c.m_settings;
    s << c.m_groups;
    return s;
}

QDataStream & operator >>(QDataStream& stream, blSettingsGroups& c){
    stream>>c.m_settings;
    stream>>c.m_groups;
    return stream;
}


