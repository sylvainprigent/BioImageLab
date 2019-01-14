/// \file blProjectDatabase.cpp
/// \brief blProjectDatabase
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectDatabase.h"

#include <iostream>

blProjectDatabase::blProjectDatabase()
{
}

blProjectDatabase::blProjectDatabase(QString databaseFile){
    setDatabaseFile(databaseFile);
    connect();
}


// IO
void blProjectDatabase::setDatabaseFile(QString databaseFile){
    m_databaseFile = databaseFile;
}

void blProjectDatabase::connect(){
    m_connectionName = "project" + QString::number(rand());

    // load database
    m_db = QSqlDatabase::addDatabase("QSQLITE", m_connectionName);
    m_db.setDatabaseName(m_databaseFile);

    // open
    if (m_db.open()){
        //qDebug() << "You are connected to the project database";
    }
    else{
        qDebug() << "Impossible to connect to the project database from file " + m_databaseFile;
    }

    createDatabase();
}

// queries
void blProjectDatabase::createDatabase(){

    QString projectsTable =
            QString("CREATE TABLE IF NOT EXISTS projects (") +
            QString("id INTEGER NULL , ") +
            QString("name VARCHAR(100) NULL , ") +
            QString("description TEXT NULL , ") +
            QString("url VARCHAR(400) NULL , ") +
            QString("created_date VARCHAR(100) NULL , ") +
            QString("modified_date VARCHAR(100) NULL , ") +
            QString(" UNIQUE(name) , ") +
            QString(" PRIMARY KEY (id) );") +
            QString() ;

    QSqlQuery query(m_db);
    query.prepare(projectsTable);
    if(!query.exec()){
        qDebug() << "blProjectDatabase:: Cannot create the database";
    }
}

bool blProjectDatabase::addProject(blProjectInfo* projectInfo){

    QSqlQuery query(m_db);
    query.prepare( QString( "INSERT INTO projects(name, description, id_type, url, created_date, modified_date)") +
                   QString( "VALUES (:name, :description, :id_type, :url, :created_date, :modified_date)") );
    query.bindValue(":name", projectInfo->name());
    query.bindValue(":description", projectInfo->description());
    query.bindValue(":id_type", projectInfo->typeId());
    query.bindValue(":url", projectInfo->url());
    query.bindValue(":created_date", projectInfo->createdDate());
    query.bindValue(":modified_date", projectInfo->lastModifiedDate());
    if( query.exec() ){
        // get the id
        QSqlQuery queryId(m_db);
        queryId.prepare("SELECT id FROM projects WHERE name=?");
        queryId.addBindValue(projectInfo->name());
        queryId.exec();
        if (queryId.first()){
            projectInfo->setId( queryId.value(0).toInt() );
            return true;
        }
        else{
            qDebug() << "add project return false cannot find the new added project";
            return false;
        }
    }
    qDebug() << "add project return false cannot add project";
    return false;
}

bool blProjectDatabase::editProject(blProjectInfo* projectInfo){
    if(projectInfo->id() == 0){
        return this->addProject(projectInfo);
    }
    else{
        return this->updateProject(projectInfo);
    }
}

bool blProjectDatabase::updateProject(blProjectInfo* projectInfo){
    QSqlQuery query(m_db);
    query.prepare("UPDATE projects SET name=?, description=?, id_type=?, url=?, created_date=?, modified_date=? WHERE id=?");
    query.addBindValue(projectInfo->name());
    query.addBindValue(projectInfo->description());
    query.addBindValue(projectInfo->typeId());
    query.addBindValue(projectInfo->url());
    query.addBindValue(projectInfo->createdDate());
    query.addBindValue(projectInfo->lastModifiedDate());
    query.addBindValue(projectInfo->id());
    return query.exec();
}

QList<blProjectInfo*> blProjectDatabase::allProjects(){
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM projects");
    query.exec();

    QList<blProjectInfo*> projectList;
    while (query.next()){
        blProjectInfo *info = new blProjectInfo;
        info->setId( query.value(0).toInt() );
        info->setName( query.value(1).toString() );
        info->setDescription(query.value(2).toString());
        info->setTypeId(query.value(3).toInt());
        info->setUrl( query.value(4).toString() );
        info->setCreatedDate( query.value(5).toString() );
        info->setLastModifiedDate( query.value(6).toString() );
        projectList.append(info);
    }
    return projectList;
}

bool blProjectDatabase::updateProjectURL(blProjectInfo* projectInfo){
    QSqlQuery query(m_db);
    query.prepare("UPDATE projects SET url=? WHERE id=?");
    query.addBindValue(projectInfo->url());
    query.addBindValue(projectInfo->id());
    return query.exec();
}

blProjectInfo* blProjectDatabase::findProjectById(unsigned int id){
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM projects WHERE id=?");
    query.addBindValue(id);
    query.exec();
    if (query.first()){
        blProjectInfo *info = new blProjectInfo;
        info->setId( query.value(0).toInt() );
        info->setName( query.value(1).toString() );
        info->setDescription(query.value(2).toString());
        info->setUrl( query.value(3).toString() );
        info->setTypeId(query.value(4).toInt());
        info->setCreatedDate( query.value(5).toString() );
        info->setLastModifiedDate( query.value(6).toString() );
        return info;
    }
    else{
        return NULL;
    }
}

blProjectInfo* blProjectDatabase::findProjectByName(QString name){
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM projects WHERE name=?");
    query.addBindValue(name);
    query.exec();
    if (query.first()){
        blProjectInfo *info = new blProjectInfo;
        info->setId( query.value(0).toInt() );
        info->setName( query.value(1).toString() );
        info->setDescription(query.value(2).toString());
        info->setUrl( query.value(3).toString() );
        info->setTypeId(query.value(4).toInt());
        info->setCreatedDate( query.value(5).toString() );
        info->setLastModifiedDate( query.value(6).toString() );
        return info;
    }
    else{
        return NULL;
    }
}

bool blProjectDatabase::removeProject(int id){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM projects WHERE id=?");
    query.addBindValue(id);
    return query.exec();
}

// view table
void blProjectDatabase::viewDatabase(){

    QStringList tabl=m_db.tables();
    std::cout<< "Project database content :"<<std::endl;
    std::cout<< "--------------------------"<<std::endl;
    for (int t = 0 ; t < tabl.size() ; t++)
    {
        this->viewTable(tabl.at(t));
        std::cout << std::endl;
    }
    std::cout<< "--------------------------"<<std::endl;

}

void blProjectDatabase::viewTable(const QString tableName)
{
    //std::cout << "blProjectDatabase::ViewTable " << std::endl;
    QSqlQuery query(m_db);
    query.prepare("select * from "+tableName+" " );
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
            std::cout << (query.value(t).toString()).toStdString() << "\t|\t";
        }
        std::cout<< std::endl;
    }
    std::cout << "------------------------------" << std::endl;
    std::cout << std::endl;
}

void blProjectDatabase::viewTableHeader(const QString tableName, const QString orientation)
{
    QSqlQuery query(m_db);
    query.prepare("PRAGMA table_info("+tableName+") ");
    query.exec();
    if (orientation==QString("horizontal"))
    {
        while (query.next())
        {
            std::cout << (query.value(1).toString()).toStdString() << "\t|\t";
        }
        std::cout << std::endl;
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

void blProjectDatabase::viewTablesList()
{
    QStringList tabl=m_db.tables();
    std::cout<< "Tables are :"<<std::endl;
    std::cout<< "------------"<<std::endl;
    for (int t=0 ; t<tabl.size() ; t++)
    {
        std::cout<< t << "- " << (tabl.at(t).toStdString())<<std::endl;
    }
    std::cout<< "------------"<<std::endl;
}

