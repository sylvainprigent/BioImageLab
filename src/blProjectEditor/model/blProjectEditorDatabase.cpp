//// \file blProjectEditorDatabase.cpp
/// \brief blProjectEditorDatabase
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioImageLab 2019

#include "blProjectEditorDatabase.h"
#include <QDebug>
#include <iostream>

blProjectEditorDatabase::blProjectEditorDatabase()
{
}

blProjectEditorDatabase::blProjectEditorDatabase(QString databaseFile){
    setDatabaseFile(databaseFile);
    connect();
}

// IO
void blProjectEditorDatabase::setDatabaseFile(QString databaseFile){
    m_databaseFile = databaseFile;
}

void blProjectEditorDatabase::connect(){
    m_connectionName = "blProjectEditorDatabase" + QString::number(rand());

    // load database
    m_db = QSqlDatabase::addDatabase("QSQLITE", m_connectionName);
    m_db.setDatabaseName(m_databaseFile);

    // open
    if (m_db.open()){
        //qDebug() << "You are connected to the blProjectEditorDatabase";
    }
    else{
        qDebug() << "Impossible to connect to the blProjectEditorDatabase from file " + m_databaseFile;
    }

    createDatabase();
}

void blProjectEditorDatabase::disconnect(){
    m_db.close();
}

// queries
void blProjectEditorDatabase::createDatabase(){

    QString tagsTable =
            QString("CREATE TABLE IF NOT EXISTS blp_tags (") +
            QString("id INTEGER NULL , ") +
            QString("name VARCHAR(150) NULL , ") +
            QString(" PRIMARY KEY (id) );") +
            QString() ;

    QString dataTable =
            QString("CREATE TABLE IF NOT EXISTS blp_data (") +
            QString("id INTEGER NULL , ") +
            QString("url VARCHAR(500) NULL , ") +
            QString(" PRIMARY KEY (id) );") +
            QString() ;

    QString dataTagTable =
            QString("CREATE TABLE IF NOT EXISTS blp_data_tags (") +
            QString("id INTEGER NULL , ") +
            QString("id_data INTEGER NULL , ") +
            QString("id_tag INTEGER NULL , ") +
            QString("value VARCHAR(200) NULL , ") +
            QString(" PRIMARY KEY (id) );") +
            QString() ;

    QString processTable =
            QString("CREATE TABLE IF NOT EXISTS blp_processes (") +
            QString("id INTEGER NULL , ") +
            QString("name VARCHAR(200) NULL , ") +
            QString("url_info VARCHAR(500) NULL , ") +
            QString(" PRIMARY KEY (id) );") +
            QString() ;

    QString processOutputsTable =
            QString("CREATE TABLE IF NOT EXISTS blp_processes_outputs (") +
            QString("id INTEGER NULL , ") +
            QString("id_process INTEGER NULL , ") +
            QString("name VARCHAR(200) NULL , ") +
            QString(" PRIMARY KEY (id) );") +
            QString() ;

    QString processDataTable =
            QString("CREATE TABLE IF NOT EXISTS blp_processes_outputs (") +
            QString("id INTEGER NULL , ") +
            QString("id_process INTEGER NULL , ") +
            QString("id_data INTEGER NULL , ") +
            QString("url VARCHAR(500) NULL , ") +
            QString(" PRIMARY KEY (id) );") +
            QString() ;


    QSqlQuery query(m_db);
    query.prepare(tagsTable);
    query.exec();

    QSqlQuery query1(m_db);
    query1.prepare(dataTable);
    query1.exec();

    QSqlQuery query2(m_db);
    query2.prepare(dataTagTable);
    query2.exec();

    QSqlQuery query3(m_db);
    query3.prepare(processTable);
    query3.exec();

    QSqlQuery query4(m_db);
    query4.prepare(processOutputsTable);
    query4.exec();

    QSqlQuery query5(m_db);
    query5.prepare(processDataTable);
    query5.exec();

}

// ///////////////////////////////////////////////////// //
//                  queries tags
// //////////////////////////////////////////////////// //
blProjectTag* blProjectEditorDatabase::setTag(blProjectTag *tag){
    if (this->isTag(tag->id())){
        QSqlQuery query(m_db);
        query.prepare("UPDATE blp_tags SET name=? WHERE id=?");
        query.addBindValue(tag->name());
        query.addBindValue(tag->id());
        query.exec();
    }
    else{
        QSqlQuery query(m_db);
        query.prepare( QString( "INSERT INTO blp_tags(name)") +
                       QString( "VALUES (:name)") );
        query.bindValue(":name", tag->name());
        query.exec();
        tag->setId(qvariant_cast<int>(query.lastInsertId()));
    }
    return tag;
}

QList<blProjectTag*> blProjectEditorDatabase::getTags(){
    QList<blProjectTag*> tags;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blp_tags");
    query.exec();
    while (query.next()){
        blProjectTag *tag = new blProjectTag();
        tag->setId(query.value(0).toInt());
        tag->setName(query.value(1).toString());
        tags.append(tag);
    }
    return tags;
}

QList<blProjectTag *> blProjectEditorDatabase::setTags(QList<blProjectTag *> tags){
    QList<blProjectTag*> outputTags;

    for (int i = 0; i < tags.count(); ++i){
        blProjectTag *tag = tags[i];
        outputTags.append(this->setTag(tag ));
    }
    return outputTags;
}

bool blProjectEditorDatabase::isTag(int id){
    QSqlQuery queryId(m_db);
    queryId.prepare("SELECT id FROM blp_tags WHERE id=?");
    queryId.addBindValue(id);
    queryId.exec();
    if (queryId.first()){
        return true;
    }
    else{
        return false;
    }
}

QString blProjectEditorDatabase::tagName(int tagId){
    QSqlQuery query(m_db);
    query.prepare("SELECT name FROM blp_tags WHERE id=?");
    query.addBindValue(tagId);
    query.exec();
    if (query.first()){
        return query.value(0).toString();
    }
    return "";
}

int blProjectEditorDatabase::removeTag(blProjectTag* tag){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM blp_tags WHERE id=?");
    query.addBindValue(tag->id());
    return query.exec();
}

// ///////////////////////////////////////////////////// //
//                    data
// //////////////////////////////////////////////////// //
blProjectData* blProjectEditorDatabase::setData(blProjectData *data){
    if (this->isData(data->id())){
        QSqlQuery query(m_db);
        query.prepare("UPDATE blp_data SET url=? WHERE id=?");
        query.addBindValue(data->url());
        query.addBindValue(data->id());
        query.exec();
    }
    else{
        QSqlQuery query(m_db);
        query.prepare( QString( "INSERT INTO blp_data(url)") +
                       QString( "VALUES (:url)") );
        query.bindValue(":url", data->url());
        query.exec();
        data->setId(qvariant_cast<int>(query.lastInsertId()));
    }
    return data;
}

QList<blProjectData*> blProjectEditorDatabase::getData(){
    QList<blProjectData*> data;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blp_data");
    query.exec();
    while (query.next()){
        blProjectData *dat = new blProjectData();
        dat->setId(query.value(0).toInt());
        dat->setUrl(query.value(1).toString());
        data.append(dat);
    }
    return data;
}

bool blProjectEditorDatabase::isData(int id){
    QSqlQuery queryId(m_db);
    queryId.prepare("SELECT id FROM blp_data WHERE id=?");
    queryId.addBindValue(id);
    queryId.exec();
    if (queryId.first()){
        return true;
    }
    else{
        return false;
    }
}

// ///////////////////////////////////////////////////// //
//                    data tag
// //////////////////////////////////////////////////// //
void blProjectEditorDatabase::setDataTag(int id_data, int id_tag, QString value){
    if (this->isDataTag(id_data, id_tag)){
        QSqlQuery query(m_db);
        query.prepare("UPDATE blp_data_tags SET value=? WHERE id_data=? AND id_tag=?");
        query.addBindValue(value);
        query.addBindValue(id_data);
        query.addBindValue(id_tag);
        query.exec();
    }
    else{
        QSqlQuery query(m_db);
        query.prepare( QString( "INSERT INTO blp_data_tags(id_data, id_tag, value)") +
                       QString( "VALUES (:id_data, :id_tag, :value)") );
        query.bindValue(":id_data", id_data);
        query.bindValue(":id_tag", id_tag);
        query.bindValue(":value", value);
        query.exec();
    }
}

blProjectTagValue *blProjectEditorDatabase::getDataTag(int id_data, int id_tag){

    blProjectTagValue *tv = new blProjectTagValue();
    tv->setIdData(id_data);
    tv->setIdTag(id_tag);

    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blp_data_tags WHERE id_data=? AND id_tag=?");
    query.addBindValue(id_data);
    query.addBindValue(id_tag);
    query.exec();
    if (query.first()){
        tv->setId(query.value(0).toInt());
        tv->setIdData(query.value(1).toInt());
        tv->setIdTag(query.value(2).toInt());
        tv->setValue(query.value(3).toString());
    }
    return tv;
}

bool blProjectEditorDatabase::isDataTag(int id_data, int id_tag){
    QSqlQuery queryId(m_db);
    queryId.prepare("SELECT id FROM blp_data_tags WHERE id_data=? AND id_tag=?");
    queryId.addBindValue(id_data);
    queryId.addBindValue(id_tag);
    queryId.exec();
    if (queryId.first()){
        return true;
    }
    else{
        return false;
    }
}

// ///////////////////////////////////////////////////// //
//                    Load Content
// //////////////////////////////////////////////////// //
blProjectContent* blProjectEditorDatabase::getContent(){

    blProjectContent* content = new blProjectContent();

    QList<blProjectTag*> tags = this->getTags();
    content->setTags(tags);

    QList<blProjectData*> data = this->getData();
    content->setData(data);

    for(int r = 0 ; r < data.count() ; r++){
        for(int c = 0 ; c < tags.count() ; c++){
            content->setDataTag(this->getDataTag(data[r]->id(), tags[c]->id()));
        }
    }

    return content;

}

// ///////////////////////////////////////////////////// //
//                    view table
// //////////////////////////////////////////////////// //
void blProjectEditorDatabase::viewDatabase(){

    QStringList tabl=m_db.tables();
    std::cout << "Project database content :" << std::endl;
    std::cout << "--------------------------" << std::endl;
    for (int t=0 ; t<tabl.size() ; t++)
    {
        this->viewTable(tabl.at(t));
        std::cout << std::endl;
    }
    std::cout << "--------------------------" << std::endl;
    std::cout << std::endl;
}

void blProjectEditorDatabase::viewTable(const QString tableName)
{
    //std::cout << "blProjectEditorDatabase::ViewTable " << std::endl;
    QSqlQuery query(m_db);
    query.prepare("select * from " + tableName + " " );
    query.exec();
    QSqlRecord rec = query.record();
    //std::cout << "Number of columns: " << rec.count() << std::endl;

    std::cout << tableName.toStdString() << " : " << std::endl;
    std::cout << "------------------------------" << std::endl;
    viewTableHeader(tableName, QString("horizontal") );
    while (query.next())
    {
        for (int t = 0 ; t < rec.count() ; t++)
        {
            std::cout<< (query.value(t).toString()).toStdString() << "\t|\t";
        }
        std::cout << std::endl;
    }
    std::cout << "------------------------------" << std::endl;
    std::cout << std::endl;
}

void blProjectEditorDatabase::viewTableHeader(const QString tableName, const QString orientation)
{
    QSqlQuery query(m_db);
    query.prepare("PRAGMA table_info("+tableName+") ");
    query.exec();
    if (orientation == QString("horizontal"))
    {
        while (query.next())
        {
            std::cout << (query.value(1).toString()).toStdString() << "\t|\t";
        }
        std::cout<<std::endl;
    }
    else if (orientation==QString("vertical"))
    {
        while (query.next())
        {
            std::cout << (query.value(1).toString()).toStdString()<<"\n";
        }
        std::cout << std::endl;
    }
}

void blProjectEditorDatabase::viewTablesList()
{
    QStringList tabl = m_db.tables();
    std::cout<< "Tables are :" << std::endl;
    std::cout<< "------------" << std::endl;
    for (int t=0 ; t<tabl.size() ; t++)
    {
        std::cout << t << "- " << (tabl.at(t).toStdString()) << std::endl;
    }
    std::cout<< "------------" << std::endl;
}
