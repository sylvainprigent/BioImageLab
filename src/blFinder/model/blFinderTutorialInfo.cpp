#include "blFinderTutorialInfo.h"

blFinderTutorialInfo::blFinderTutorialInfo(){
    m_id = 0;
}

// setters
void blFinderTutorialInfo::setId(int id){
    m_id = id;
}

void blFinderTutorialInfo::setTitle(QString title){
    m_title = title;
}

void blFinderTutorialInfo::setLanguage(QString language){
    m_language = language;
}

void blFinderTutorialInfo::setOrigin(int origin){
    m_origin = origin;
}

void blFinderTutorialInfo::setOriginName(QString origin){
    m_originName = origin;
}

void blFinderTutorialInfo::setImageUrl(QString imageUrl){
    m_image_url = imageUrl;
}

void blFinderTutorialInfo::setViewName(QString viewName){
    m_view_name = viewName;
}

void blFinderTutorialInfo::setXmlUrl(QString url){
    m_xml_url = url;
}

void blFinderTutorialInfo::setDocUrl(QString url){
    m_doc_url = url;
}

// getters
int blFinderTutorialInfo::id(){
    return m_id;
}

QString blFinderTutorialInfo::title(){
    return m_title;
}

QString blFinderTutorialInfo::language(){
    return m_language;
}

int blFinderTutorialInfo::origin(){
    return m_origin;
}

QString blFinderTutorialInfo::originName(){
    return m_originName;
}

QString blFinderTutorialInfo::imageUrl(){
    return m_image_url;
}

QString blFinderTutorialInfo::viewName(){
    return m_view_name;
}


void blFinderTutorialInfo::addKeyword(int id, QString word){
    m_keywords.append(word);
    m_keywordsIDs.append(id);
}

void blFinderTutorialInfo::setKeywordsIds(QList<int> ids){
    m_keywordsIDs = ids;
}

int blFinderTutorialInfo::countKeywords(){
    //if (m_keywordsIDs.count() == m_keywords.count()){
        return m_keywordsIDs.count();
    //}
    //return 0;
}

int blFinderTutorialInfo::keywordIdAt(int index){
    return m_keywordsIDs[index];
}

QString blFinderTutorialInfo::keywordAt(int index){
    return m_keywords[index];
}

void blFinderTutorialInfo::addAuthor(int id, QString printName){
    m_authorsIDs.append(id);
    m_authorsNames.append(printName);
}

int blFinderTutorialInfo::countAuthors(){
    //if (m_authorsIDs.count() == m_authorsNames.count()){
        return m_authorsIDs.count();
    //}
    //return 0;
}

int blFinderTutorialInfo::authorIdAt(int index){
    return m_authorsIDs[index];
}

QString blFinderTutorialInfo::authorAt(int index){
    return m_authorsNames[index];
}

void blFinderTutorialInfo::setAuthorsIds(QList<int> ids){
    m_authorsIDs = ids;
}

QString blFinderTutorialInfo::xmlUrl(){
    return m_xml_url;
}

QString blFinderTutorialInfo::docUrl(){
    return m_doc_url;
}
