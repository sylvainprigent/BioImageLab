//// \file blProjectTagDatabase.cpp
/// \brief blProjectTagDatabase
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioImageLab 2019

#include "blProjectIndex.h"
#include <QDebug>
#include <iostream>

blProjectIndex::blProjectIndex()
{
}

blProjectIndex::blProjectIndex(QString databaseFile){
    setDatabaseFile(databaseFile);
    connect();
}

// IO
void blProjectIndex::setDatabaseFile(QString databaseFile){
    m_databaseFile = databaseFile;
}

void blProjectIndex::connect(){
    m_connectionName = "pindex" + QString::number(rand());

    // load database
    m_db = QSqlDatabase::addDatabase("QSQLITE", m_connectionName);
    m_db.setDatabaseName(m_databaseFile);

    // open
    if (m_db.open()){
        qDebug() << "You are connected to the project index";
    }
    else{
        qDebug() << "Impossible to connect to the project index from file " + m_databaseFile;
    }

    createDatabase();
}

void blProjectIndex::disconnect(){
    m_db.close();
}

// queries
void blProjectIndex::createDatabase(){

    QString mainColTable =
            QString("CREATE TABLE IF NOT EXISTS blp_maincol (") +
            QString("id INTEGER NULL , ") +
            QString("name VARCHAR(100) NULL , ") +
            QString("origin_url VARCHAR(500) NULL , ") +
            QString(" PRIMARY KEY (id) );") +
            QString() ;

    QString subColTable =
            QString("CREATE TABLE IF NOT EXISTS blp_subcol (") +
            QString("id INTEGER NULL , ") +
            QString("name VARCHAR(100) NULL , ") +
            QString("id_main_col INTEGER NULL , ") +
            QString("datatype VARCHAR(100) NULL , ") +
            QString(" PRIMARY KEY (id) );") +
            QString() ;

    QString dataTable =
            QString("CREATE TABLE IF NOT EXISTS blp_data (") +
            QString("id INTEGER NULL , ") +
            QString("line_idx INTEGER NULL , ") +
            QString("url VARCHAR(500) NULL , ") +
            QString("thumbnail_url VARCHAR(500) NULL , ") +
            QString("id_main_col INTEGER NULL , ") +
            QString("id_sub_col INTEGER NULL , ") +
            QString(" PRIMARY KEY (id) );") +
            QString() ;

    QString tagsTable =
            QString("CREATE TABLE IF NOT EXISTS blp_tags (") +
            QString("id INTEGER NULL , ") +
            QString("name VARCHAR(150) NULL , ") +
            QString("id_subcol INTEGER NULL , ") +
            QString(" PRIMARY KEY (id) );") +
            QString() ;

    QSqlQuery query(m_db);
    query.prepare(mainColTable);
    query.exec();

    QSqlQuery query1(m_db);
    query1.prepare(subColTable);
    query1.exec();

    QSqlQuery query2(m_db);
    query2.prepare(dataTable);
    query2.exec();

    QSqlQuery query3(m_db);
    query3.prepare(tagsTable);
    query3.exec();

}

// ///////////////////////////////////////////////////// //
//                  queries
// //////////////////////////////////////////////////// //

// add
int blProjectIndex::addMainColumn(QString name, QString originUrl){
    QSqlQuery query(m_db);
    query.prepare( QString( "INSERT INTO blp_maincol(name, origin_url)") +
                   QString( "VALUES (:name, :origin_url)") );
    query.bindValue(":name", name);
    query.bindValue(":origin_url", originUrl);
    query.exec();
    return qvariant_cast<int>(query.lastInsertId());
}

int blProjectIndex::addSubColumn(QString name, int id_main_col, QString datatype){
    QSqlQuery query(m_db);
    query.prepare( QString( "INSERT INTO blp_subcol(name, id_main_col, datatype)") +
                   QString( "VALUES (:name, :id_main_col, :datatype)") );
    query.bindValue(":name", name);
    query.bindValue(":id_main_col", id_main_col);
    query.bindValue(":datatype", datatype);
    query.exec();

    QSqlQuery queryId(m_db);
    queryId.prepare("SELECT id FROM blp_subcol WHERE name=?");
    queryId.addBindValue(name);
    queryId.exec();
    if (queryId.first()){
        return queryId.value(0).toInt();
    }
    return 0;
    //return qvariant_cast<int>(query.lastInsertId());
}

int blProjectIndex::addData(int line_idx, QString url, QString thumbnail_url, int id_main_col, int id_sub_col){
    QSqlQuery query(m_db);
    query.prepare( QString( "INSERT INTO blp_data(line_idx, url, thumbnail_url, id_main_col, id_sub_col)") +
                   QString( "VALUES (:line_idx, :url, :thumbnail_url, :id_main_col, :id_sub_col)") );
    query.bindValue(":line_idx", line_idx);
    query.bindValue(":url", url);
    query.bindValue(":thumbnail_url", thumbnail_url);
    query.bindValue(":id_main_col", id_main_col);
    query.bindValue(":id_sub_col", id_sub_col);
    //query.exec();
    if (!query.exec()){
        qDebug() << "add data query error: " << query.lastError().text();
    }
    return qvariant_cast<int>(query.lastInsertId());
}

// edit
void blProjectIndex::editMainColumn(int id, QString name, QString originUrl){
    QSqlQuery query(m_db);
    query.prepare("UPDATE blp_maincol SET name=?, origin_url=?  WHERE id=?");
    query.addBindValue(name);
    query.addBindValue(originUrl);
    query.addBindValue(id);
    query.exec();

}

blSubColumnInfo blProjectIndex::setSubColumnInfo(blSubColumnInfo info){
    if (info.id() > 0){
        this->editSubColumn(info.id(), info.name(), info.id_main_col(), info.datatype());
    }
    else{
        int id = this->addSubColumn(info.name(), info.id_main_col(), info.datatype());
        info.setId(id);
    }
    return info;
}

blMainColumnInfo blProjectIndex::setMainColumn(blMainColumnInfo info){
    if (info.id() > 0){
        this->editMainColumn(info.id(), info.name(), info.origin_url());
    }
    else{
        int id = this->addMainColumn(info.name(), info.origin_url());
        info.setId(id);
    }
    return info;
}

void blProjectIndex::editSubColumn(int id, QString name, int id_main_col, QString datatype){
    QSqlQuery query(m_db);
    query.prepare("UPDATE blp_subcol SET name=?, id_main_col=?, datatype=?  WHERE id=?");
    query.addBindValue(name);
    query.addBindValue(id_main_col);
    query.addBindValue(datatype);
    query.addBindValue(id);
    query.exec();
}

void blProjectIndex::editData(int id, int line_idx, QString url, QString thumbnail_url, int id_main_col, int id_sub_col){
    QSqlQuery query(m_db);
    query.prepare("UPDATE blp_data SET line_idx=?, url=?, thumbnail_url=?, id_main_col=?, id_sub_col=?  WHERE id=?");
    query.addBindValue(line_idx);
    query.addBindValue(url);
    query.addBindValue(thumbnail_url);
    query.addBindValue(id_main_col);
    query.addBindValue(id_sub_col);
    query.addBindValue(id);
    query.exec();
}

blDataInfo blProjectIndex::setData(blDataInfo data){
    if (data.id() > 0){
        this->editData(data.id(), data.line_id(), data.url(), data.thumbnail(), data.id_main_col(), data.id_sub_column());
    }
    else{
        int id = this->addData(data.line_id(), data.url(), data.thumbnail(), data.id_main_col(), data.id_sub_column());
        data.setid(id);
    }
    return data;
}

blTagInfo blProjectIndex::setTag(blTagInfo info){
    if (info.id() > 0){
        this->setTag(info.id(), info.name(), info.subColId());
    }
    else{
        int id = this->addTag(info.name(), info.subColId());
        info.setId(id);
    }
    return info;
}

int  blProjectIndex::setTag(int id, QString name, int id_subcol){

    if (this->isTag(id)){
        QSqlQuery query(m_db);
        query.prepare("UPDATE blp_tags SET name=?, id_subcol=?  WHERE id=?");
        query.addBindValue(name);
        query.addBindValue(id_subcol);
        query.addBindValue(id);
        query.exec();
        return id;
    }
    else{
        QSqlQuery query(m_db);
        query.prepare( QString( "INSERT INTO blp_tags(name, id_subcol)") +
                       QString( "VALUES (:name, :id_subcol)") );
        query.bindValue(":name", name);
        query.bindValue(":id_subcol", id_subcol);
        query.exec();
        return qvariant_cast<int>(query.lastInsertId());
    }
}

int blProjectIndex::addTag(QString name, int id_subcol){
    QSqlQuery query(m_db);
    query.prepare( QString( "INSERT INTO blp_tags(name, id_subcol)") +
                   QString( "VALUES (:name, :id_subcol)") );
    query.bindValue(":name", name);
    query.bindValue(":id_subcol", id_subcol);
    query.exec();
    return qvariant_cast<int>(query.lastInsertId());
}

bool blProjectIndex::isTag(int id){
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

QList<blTagInfo> blProjectIndex::setTags(blTagsInfo tags){
    QList<blTagInfo> outputTags;
    QList<blTagInfo> tagsInfos = tags.all();
    for (int i = 0; i < tagsInfos.count(); ++i){
        blTagInfo tag = tagsInfos[i];
        int id = this->setTag(tag.id(), tag.name(), tag.subColId() );
        tag.setId(id);
        outputTags.append(tag);
    }
    return outputTags;
}

QList<blMainColumnInfo> blProjectIndex::mainColumns(){
    QList<blMainColumnInfo> cols;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blp_maincol");
    query.exec();
    while (query.next()){
        blMainColumnInfo col;
        col.setId(query.value(0).toInt());
        col.setName(query.value(1).toString());
        col.setOriginUrl(query.value(2).toString());
        cols.append(col);
    }
    return cols;
}

QString blProjectIndex::getSubColDataType(int colId){
    QSqlQuery query(m_db);
    query.prepare("SELECT datatype FROM blp_subcol WHERE id=?");
    query.addBindValue(colId);
    query.exec();
    if (query.first()){
        return query.value(0).toString();
    }
    return "";
}

QString blProjectIndex::tagName(int tagId){
    QSqlQuery query(m_db);
    query.prepare("SELECT name FROM blp_tags WHERE id=?");
    query.addBindValue(tagId);
    query.exec();
    if (query.first()){
        return query.value(0).toString();
    }
    return "";
}

QList<blSubColumnInfo> blProjectIndex::subColumns(int mainColumnId){
    QList<blSubColumnInfo> cols;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blp_subcol WHERE id_main_col=?");
    query.addBindValue(mainColumnId);
    query.exec();
    while (query.next()){
        blSubColumnInfo col;
        col.setId(query.value(0).toInt());
        col.setName(query.value(1).toString());
        col.set_id_main_col(query.value(3).toInt());
        col.setDatatype(query.value(3).toString());
        cols.append(col);
    }
    return cols;
}

QList<blDataInfo> blProjectIndex::getDataLine(int lineIdx){
    QList<blDataInfo> dataList;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blp_data WHERE line_idx=?");
    query.addBindValue(lineIdx);
    query.exec();
    while (query.next()){
        blDataInfo data;
        data.setid(query.value(0).toInt());
        data.setline_id(query.value(1).toInt());
        data.seturl(query.value(2).toString());
        data.setthumbnail(query.value(3).toString());
        data.setid_main_col(query.value(4).toInt());
        data.setid_sub_column(query.value(5).toInt());
        dataList.append(data);
    }
    return dataList;
}

QList<blTagInfo> blProjectIndex::tags(){
    QList<blTagInfo> tagsList;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blp_tags");
    query.exec();
    while (query.next()){
        blTagInfo tag;
        tag.setId(query.value(0).toInt());
        tag.setName(query.value(1).toString());
        tag.setSubColId(query.value(2).toInt());
        tagsList.append(tag);
    }
    return tagsList;
}

int blProjectIndex::maxLineIdx(){
    QSqlQuery query(m_db);
    query.prepare("SELECT MAX(line_idx) FROM blp_data");
    query.exec();
    if (query.first()){
        return query.value(0).toInt();
    }
    return 0;
}

// view table
void blProjectIndex::viewTable(const QString tableName)
{
    qDebug() << "blProjectIndex::ViewTable ";
    // Fait la requete
    QSqlQuery query(m_db);
    query.prepare("select * from "+tableName+" " );
    query.exec();
    QSqlRecord rec = query.record();
    qDebug() << "Number of columns: " << rec.count();

    std::cout << tableName.toStdString() << " : " << std::endl;
    viewTableHeader(tableName, QString("horizontal") );
    while (query.next())
    {
        for (int t=0 ; t<rec.count() ; t++)
        {
            std::cout<< (query.value(t).toString()).toStdString()<<"\t";
        }
        std::cout<< std::endl;
    }
    std::cout << std::endl << std::endl;
}

void blProjectIndex::viewTableHeader(const QString tableName, const QString orientation)
{
    QSqlQuery query(m_db);
    query.prepare("PRAGMA table_info("+tableName+") ");
    query.exec();
    if (orientation==QString("horizontal"))
    {
        while (query.next())
        {
            std::cout<< (query.value(1).toString()).toStdString()<<"\t";
        }
        std::cout<<std::endl;
    }
    else if (orientation==QString("vertical"))
    {
        while (query.next())
        {
            std::cout<< (query.value(1).toString()).toStdString()<<"\n";
        }
        std::cout<<std::endl;
    }
}

void blProjectIndex::viewTablesList()
{
    QStringList tabl=m_db.tables();
    std::cout<< "Tables are :"<<std::endl;
    for (int t=0 ; t<tabl.size() ; t++)
    {
        std::cout<< t << "- " << (tabl.at(t).toStdString())<<std::endl;
    }
}
