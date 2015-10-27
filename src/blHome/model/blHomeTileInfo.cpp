#include "blHomeTileInfo.h"

blHomeTileInfo::blHomeTileInfo(){

}

blHomeTileInfo::blHomeTileInfo(QString action, QString name, QString tooltip, QString iconeUrl){
    m_action = action;
    m_name = name;
    m_tooltip = tooltip;
    m_iconeUrl = iconeUrl;
}


// setters
void blHomeTileInfo::setAction(QString action){
    m_action = action;
}

void blHomeTileInfo::setName(QString name){
    m_name = name;
}

void blHomeTileInfo::setTooltip(QString tooltip){
    m_tooltip = tooltip;
}

void blHomeTileInfo::setIconeUrl(QString url){
    m_iconeUrl = url;
}

// getters
QString blHomeTileInfo::action(){
    return m_action;
}

QString blHomeTileInfo::name(){
    return m_name;
}

QString blHomeTileInfo::tooltip(){
    return m_tooltip;
}

QString blHomeTileInfo::iconeUrl(){
    return m_iconeUrl;
}
