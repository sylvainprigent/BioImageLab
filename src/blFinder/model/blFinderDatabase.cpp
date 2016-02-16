/// \file blFinderDatabase.cpp
/// \brief blFinderDatabase
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2015

#include "blFinderDatabase.h"
#include <QDebug>
#include <iostream>

blFinderDatabase::blFinderDatabase()
{
}

blFinderDatabase::blFinderDatabase(QString databaseFile){
    setDatabaseFile(databaseFile);
    connect();
}


// IO
void blFinderDatabase::setDatabaseFile(QString databaseFile){
    m_databaseFile = databaseFile;
}

void blFinderDatabase::connect(){
    m_connectionName = "name" + QString::number(rand());

    // load database
    m_db = QSqlDatabase::addDatabase("QSQLITE", m_connectionName);
    m_db.setDatabaseName(m_databaseFile);

    // open
    if (m_db.open()){
        qDebug() << "You are connected to the Tool database";
    }
    else{
        qDebug() << "Impossible to connect to the Tool database from file " + m_databaseFile;
    }

    createDatabase();
}

// queries
void blFinderDatabase::createDatabase(){

    QString authorsTable =
            QString("CREATE TABLE IF NOT EXISTS blf_authors (") +
            QString("id INTEGER NULL , ") +
            QString("name VARCHAR(100) NULL , ") +
            QString("firstname VARCHAR(100) NULL , ") +
            QString(" PRIMARY KEY (id) );") +
            QString() ;

    QString finder_categoriesTable =
            QString("CREATE TABLE IF NOT EXISTS blf_finder_categories (") +
            QString("id INTEGER NULL , ") +
            QString("name VARCHAR(100) NULL , ") +
            QString("description TEXT NULL , ") +
            QString("image_url varchar(200) NULL , ") +
            QString("children_title varchar(200) NULL , ") +
            QString("display_order INTEGER NULL , ") +
            QString(" PRIMARY KEY (id) );") +
            QString() ;

    QString finder_j_categoriesTable =
            QString("CREATE TABLE IF NOT EXISTS blf_finder_j_categories (") +
            QString("id_parent INTEGER NULL , ") +
            QString("id_child INTEGER NULL );") +
            QString() ;

    QString finder_j_tutoTable =
            QString("CREATE TABLE IF NOT EXISTS blf_finder_j_tuto (") +
            QString("id_category INTEGER NULL , ") +
            QString("id_tuto INTEGER NULL);") +
            QString() ;

    QString j_tutorial_authorTable =
            QString("CREATE TABLE IF NOT EXISTS blf_j_tutorial_author (") +
            QString("id_tuto INTEGER NULL , ") +
            QString("id_author INTEGER NULL);") +
            QString() ;

    QString j_tutorial_keywordTable =
            QString("CREATE TABLE IF NOT EXISTS blf_j_tutorial_keyword (") +
            QString("id_tuto INTEGER NULL , ") +
            QString("id_keyword INTEGER NULL);") +
            QString() ;

    QString keywordsTable =
            QString("CREATE TABLE IF NOT EXISTS blf_keywords (") +
            QString("id INTEGER NULL , ") +
            QString("word VARCHAR(100) NULL , ") +
            QString("category_id INTEGER NULL , ") +
            QString(" PRIMARY KEY (id) );") +
            QString() ;

    QString keywords_categoriesTable =
            QString("CREATE TABLE IF NOT EXISTS blf_keywords_categories (") +
            QString("id INTEGER NULL , ") +
            QString("name VARCHAR(100) NULL , ") +
            QString(" PRIMARY KEY (id) );") +
            QString() ;

    QString originsTable =
            QString("CREATE TABLE IF NOT EXISTS blf_origins (") +
            QString("id INTEGER NULL , ") +
            QString("name VARCHAR(100) NULL , ") +
            QString(" PRIMARY KEY (id) );") +
            QString() ;

    QString tutorialsTable =
           QString("CREATE TABLE IF NOT EXISTS blf_tutorials (") +
           QString("id INTEGER NULL, ") +
           QString("title VARCHAR(30) NULL, ") +
           QString("language VARCHAR(30) NULL, ") +
           QString("origin INTEGER NULL, ") +
           QString("image_url VARCHAR(150) NULL, ") +
           QString("view_name VARCHAR(150) NULL, ") +
           QString("xml_url VARCHAR(150) NULL, ") +
           QString("doc_url VARCHAR(150) NULL, ") +
           QString("PRIMARY KEY (id) ") +
           QString(");");

    QSqlQuery query(m_db);
    query.prepare(authorsTable);
    query.exec();

    QSqlQuery query1(m_db);
    query1.prepare(finder_categoriesTable);
    query1.exec();

    QSqlQuery query2(m_db);
    query2.prepare(finder_j_categoriesTable);
    query2.exec();

    QSqlQuery query3(m_db);
    query3.prepare(finder_j_tutoTable);
    query3.exec();

    QSqlQuery query4(m_db);
    query4.prepare(j_tutorial_authorTable);
    query4.exec();

    QSqlQuery query41(m_db);
    query41.prepare(j_tutorial_keywordTable);
    query41.exec();

    QSqlQuery query5(m_db);
    query5.prepare(keywordsTable);
    query5.exec();

    QSqlQuery query6(m_db);
    query6.prepare(keywords_categoriesTable);
    query6.exec();

    QSqlQuery query7(m_db);
    query7.prepare(tutorialsTable);
    query7.exec();

    QSqlQuery query8(m_db);
    query8.prepare(originsTable);
    query8.exec();
}

void blFinderDatabase::addTestEntries(){

    // add author
    blFinderAuthorInfo author;
    author.setFirstname("Sylvain");
    author.setName("Prigent");
    this->editAuthor(author);

    // add categories
    blFinderCategoryInfo category1; category1.setName("Software");
    this->editCategory(category1);
    blFinderCategoryInfo category2; category2.setName("Method");
    this->editCategory(category2);
    blFinderCategoryInfo category3; category3.setName("Application");
    this->editCategory(category3);

    // add keywords
    blFinderKeywordInfo keyword1; keyword1.setName("Fiji"); keyword1.setCategoryID(1);
    this->editKeyword(keyword1);
    blFinderKeywordInfo keyword2; keyword2.setName("Ilastik"); keyword2.setCategoryID(1);
    this->editKeyword(keyword2);
    blFinderKeywordInfo keyword3; keyword3.setName("Segmentation"); keyword3.setCategoryID(3);
    this->editKeyword(keyword3);
    blFinderKeywordInfo keyword4; keyword4.setName("Machine learning"); keyword4.setCategoryID(2);
    this->editKeyword(keyword4);
    blFinderKeywordInfo keyword5; keyword5.setName("Macro"); keyword5.setCategoryID(2);
    this->editKeyword(keyword5);
    blFinderKeywordInfo keyword6; keyword6.setName("Icy"); keyword6.setCategoryID(1);
    this->editKeyword(keyword6);
    blFinderKeywordInfo keyword7; keyword7.setName("BioImageLib"); keyword7.setCategoryID(1);
    this->editKeyword(keyword7);
    blFinderKeywordInfo keyword8; keyword8.setName("Detection"); keyword8.setCategoryID(3);
    this->editKeyword(keyword8);

    // add origin
    blFinderOriginInfo origin1; origin1.setName("Biogenouest");
    this->editOrigin(origin1);

    // tuto
    blFinderTutorialInfo tuto1;
    tuto1.setTitle("TopHat Detector");
    tuto1.setLanguage("Français");
    tuto1.setImageUrl("blTophatDetector/icon.png");
    tuto1.setDocUrl("blTophatDetector/doc/index.html");
    tuto1.setXmlUrl("blMpp\\blMpp.xml");
    tuto1.setOrigin(1);
    tuto1.addAuthor(1);
    tuto1.addKeyword(7); // bioImageLib
    tuto1.addKeyword(8); // detection
    this->editTutorial(tuto1);

    // finder
    blFinderSectionInfo section1;
    section1.setName("Détection d'objets");
    section1.setDescription("Détection d'objets	Ensemble d'outils permettant de détecter et analyser des objets dans une image. Un objet peut être un marquage, une cellule, un noyau...");
    section1.setImageUrl("finder/detection.png");
    section1.setChildrenTitle("Quel type d'objets souhaitez vous analyser ?");
    section1.setDisplayOrder(1);
    this->editSection(section1);

    blFinderSectionInfo section2;
    section2.setName("Détecteurs de spots");
    section2.setDescription("Outils permettant d'analyser des \"spots\" dans une image. Un spot est un objet dont la taille est proche de la résolution de l'image.");
    section2.setImageUrl("finder/detection_spots.png");
    section2.setChildrenTitle("");
    section2.setDisplayOrder(1);
    this->editSection(section2);

    blFinderSectionInfo section3;
    section3.setName("Recalage");
    section3.setDescription("Recaler plusieurs images entre elles. Alignement par transformation rigide, affine ou déformable");
    section3.setImageUrl("finder/recalage.png");
    section3.setChildrenTitle("");
    section3.setDisplayOrder(4);
    this->editSection(section3);

    blFinderSectionInfo section4;
    section4.setName("Tracking");
    section4.setDescription("Suivi d'objets (cellules, noyauxn, ADN, vésicules, neurones... ) sur une série temporelle d'image. Suivi automatique manuel supervisé. Suivi d'un objet seul ou d'un groupe d'objets.");
    section4.setImageUrl("finder/tracking.png");
    section4.setChildrenTitle("");
    section4.setDisplayOrder(5);
    this->editSection(section4);

    blFinderSectionInfo section5;
    section5.setName("Colocalisation");
    section5.setDescription("Quantification de colocalisation de différents marqueurs");
    section5.setImageUrl("finder/coloc.png");
    section5.setChildrenTitle("");
    section5.setDisplayOrder(6);
    this->editSection(section5);

    blFinderSectionInfo section6;
    section6.setName("Segmentation/Classification");
    section6.setDescription("La segmentation et la classification consiste à extraire des formes ou structures de l'image pour quantifier leur intensité, leur homogénéité, leur forme...");
    section6.setImageUrl("finder/classification.png");
    section6.setChildrenTitle("");
    section6.setDisplayOrder(2);
    this->editSection(section6);

    blFinderSectionInfo section7;
    section7.setName("Réseaux");
    section7.setDescription("L'analyse de réseau consiste à quantifier la structure d'un réseau. Suivant le type de réseau, cette quantification peut se faire par mesure de densité, ou par extraction et modélisation des embranchements du réseau");
    section7.setImageUrl("finder/reseau.png");
    section7.setChildrenTitle("");
    section7.setDisplayOrder(3);
    this->editSection(section7);

    blFinderSectionInfo section8;
    section8.setName("root");
    section8.setDescription("root category");
    section8.setImageUrl("no image");
    section8.setChildrenTitle("Quelle est votre domaine application ?");
    section8.setDisplayOrder(0);
    this->editSection(section8);

    blFinderSectionInfo section9;
    section9.setName("Astuces logiciels");
    section9.setDescription("Des tutoriels et astuces pour utiliser les logiciels d'analyse d'image");
    section9.setImageUrl("finder/logiciels.png");
    section9.setChildrenTitle("Quel logiciel ?");
    section9.setDisplayOrder(7);
    this->editSection(section9);

    blFinderSectionInfo section10;
    section10.setName("Détecteurs de formes");
    section10.setDescription("Les outils regroupés dans cette catégorie permettent d'analyser des objets de formes déterminées par un modèle. Le model peut être géométrique ou empirique. L'utilisation d'un modèle permet de dissocier des objets collés dans l'image.");
    section10.setImageUrl("finder/detection_model.png");
    section10.setChildrenTitle("Outils disponibles:");
    section10.setDisplayOrder(2);
    this->editSection(section10);

    blFinderSectionInfo section11;
    section11.setName("Détecteurs par segmentation");
    section11.setDescription("Outils permettant d'extraire des objets d'une image en les segmentant. Des contraintes de taille et de forme sont utilisés par certains de ces outils pour modéliser les objets à analyser");
    section11.setImageUrl("finder/detection_seg.png");
    section11.setChildrenTitle("Outils disponibles:");
    section11.setDisplayOrder(3);
    this->editSection(section11);

    // link sections
    blFinderSectionsLinkInfo link1; link1.setParentID(1); link1.setChildID(2);
    this->editSectionsLink(link1);

    blFinderSectionsLinkInfo link2; link2.setParentID(8); link2.setChildID(5);
    this->editSectionsLink(link2);

    blFinderSectionsLinkInfo link3; link3.setParentID(8); link3.setChildID(1);
    this->editSectionsLink(link3);

    blFinderSectionsLinkInfo link4; link4.setParentID(8); link4.setChildID(3);
    this->editSectionsLink(link4);

    blFinderSectionsLinkInfo link5; link5.setParentID(8); link5.setChildID(7);
    this->editSectionsLink(link5);

    blFinderSectionsLinkInfo link6; link6.setParentID(8); link6.setChildID(6);
    this->editSectionsLink(link6);

    blFinderSectionsLinkInfo link7; link7.setParentID(8); link7.setChildID(4);
    this->editSectionsLink(link7);

    blFinderSectionsLinkInfo link8; link8.setParentID(8); link8.setChildID(9);
    this->editSectionsLink(link8);

    blFinderSectionsLinkInfo link9; link9.setParentID(1); link9.setChildID(10);
    this->editSectionsLink(link9);

    blFinderSectionsLinkInfo link10; link10.setParentID(1); link10.setChildID(11);
    this->editSectionsLink(link10);

    // link tuto category
    blFinderTutorialsLinkInfo linkinfo1; linkinfo1.setCategoryID(2); linkinfo1.setTutorialID(1);
    this->editTutorialsLink(linkinfo1);
}

void blFinderDatabase::editAuthor(blFinderAuthorInfo authorInfo){

    if (authorInfo.id() > 0){
        // update
        QSqlQuery query(m_db);
        query.prepare("UPDATE blf_authors SET name=?, firstname=?  WHERE id=?");
        query.addBindValue(authorInfo.name());
        query.addBindValue(authorInfo.firstname());
        query.addBindValue(authorInfo.id());
        query.exec();
    }
    else{
        // add
        QSqlQuery query(m_db);
        query.prepare( QString( "INSERT INTO blf_authors(name, firstname)") +
                       QString( "VALUES (:name, :firstname)") );
        query.bindValue(":name", authorInfo.name());
        query.bindValue(":firstname", authorInfo.firstname());
        query.exec();
    }
}

blFinderAuthorInfo blFinderDatabase::authorInfo(int id){
    blFinderAuthorInfo aut;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blf_authors where id = ?");
    query.addBindValue(id);
    query.exec();
    if (query.next()){
        aut.setID(query.value(0).toInt());
        aut.setName(query.value(1).toString());
        aut.setFirstname(query.value(2).toString());
    }
    return aut;
}

QString blFinderDatabase::authorFullName(int id){
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blf_authors where id = ?");
    query.addBindValue(id);
    query.exec();
    if (query.next()){
        return query.value(1).toString() + " " + query.value(2).toString();
    }
    return "";
}

QString blFinderDatabase::authorShortName(int id){
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blf_authors where id = ?");
    query.addBindValue(id);
    query.exec();
    if (query.next()){
        QString firstname = query.value(2).toString();
        if (firstname.count() > 0){
            firstname = firstname.at(0);
        }
        return firstname + ". " + query.value(1).toString();
    }
    return "";
}

QList<blFinderAuthorInfo> blFinderDatabase::authors(){

    QList<blFinderAuthorInfo> auths;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blf_authors");
    query.exec();
    QStringList names;
    while (query.next()){
        blFinderAuthorInfo aut;
        aut.setID(query.value(0).toInt());
        aut.setName(query.value(1).toString());
        aut.setFirstname(query.value(2).toString());
        auths.append(aut);
    }
    return auths;
}

void blFinderDatabase::deleteAuthor(int id){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM blf_authors WHERE id = ?");
    query.addBindValue(id);
    query.exec();
}


// ---------------
//  categories
// ---------------
QList<blFinderCategoryInfo> blFinderDatabase::categories(){
    QList<blFinderCategoryInfo> auths;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blf_keywords_categories");
    query.exec();
    while (query.next()){
        blFinderCategoryInfo aut;
        aut.setID(query.value(0).toInt());
        aut.setName(query.value(1).toString());
        auths.append(aut);
    }
    return auths;
}

blFinderCategoryInfo blFinderDatabase::categoryInfo(int id){
    blFinderCategoryInfo info;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blf_keywords_categories where id = ?");
    query.addBindValue(id);
    query.exec();
    if (query.next()){
        info.setID(query.value(0).toInt());
        info.setName(query.value(1).toString());
    }
    return info;
}

QString blFinderDatabase::categoryName(int id){
    QSqlQuery query(m_db);
    query.prepare("SELECT name FROM blf_keywords_categories where id = ?");
    query.addBindValue(id);
    query.exec();
    if (query.next()){
        return query.value(0).toString();
    }
    return "";
}

int blFinderDatabase::categoryId(QString name){
    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM blf_keywords_categories where name = ?");
    query.addBindValue(name);
    query.exec();
    if (query.next()){
        return query.value(0).toInt();
    }
    return 0;
}

void blFinderDatabase::editCategory(blFinderCategoryInfo info){
    if (info.id() > 0){
        // update
        QSqlQuery query(m_db);
        query.prepare("UPDATE blf_keywords_categories SET name=?  WHERE id=?");
        query.addBindValue(info.name());
        query.addBindValue(info.id());
        query.exec();
    }
    else{
        // add
        QSqlQuery query(m_db);
        query.prepare( QString( "INSERT INTO blf_keywords_categories(name)") +
                       QString( "VALUES (:name)") );
        query.bindValue(":name", info.name());
        query.exec();
    }
}

void blFinderDatabase::deleteCategory(int id){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM blf_keywords_categories WHERE id = ?");
    query.addBindValue(id);
    query.exec();
}

// -------------
//    Keywords
// -------------
QList<blFinderKeywordInfo> blFinderDatabase::keywords(){
    QList<blFinderKeywordInfo> auths;
    QSqlQuery query(m_db);

    query.prepare(QString("SELECT * FROM blf_keywords"));
    query.exec();
    while (query.next()){
        blFinderKeywordInfo aut;
        aut.setID(query.value(0).toInt());
        aut.setName(query.value(1).toString());
        aut.setCategoryID(query.value(2).toInt());
        aut.setCategoryName(this->categoryName(query.value(2).toInt()));
        auths.append(aut);
    }
    return auths;
}

QList<blFinderKeywordInfo> blFinderDatabase::keywordsByCategory(QString category){

    int category_id = this->categoryId(category);

    QList<blFinderKeywordInfo> auths;
    QSqlQuery query(m_db);

    query.prepare(QString("SELECT * FROM blf_keywords WHERE category_id=?  ORDER BY word ASC"));
    query.addBindValue(category_id);
    query.exec();
    while (query.next()){
        blFinderKeywordInfo aut;
        aut.setID(query.value(0).toInt());
        aut.setName(query.value(1).toString());
        aut.setCategoryID(query.value(2).toInt());
        aut.setCategoryName(category);
        auths.append(aut);
    }
    return auths;

}

QStringList blFinderDatabase::allKeywords(){
    QStringList wordList;
    QSqlQuery query(m_db);

    query.prepare(QString("SELECT word FROM blf_keywords"));
    query.exec();
    while (query.next()){
        wordList.append(query.value(0).toString());
    }
    return wordList;
}

blFinderKeywordInfo blFinderDatabase::keywordInfo(int id){
    blFinderKeywordInfo info;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blf_keywords where id = ?");
    query.addBindValue(id);
    query.exec();
    if (query.next()){
        info.setID(query.value(0).toInt());
        info.setName(query.value(1).toString());
        info.setCategoryID(query.value(2).toInt());
    }
    return info;
}

QString blFinderDatabase::keywordWord(int id){
    QSqlQuery query(m_db);
    query.prepare("SELECT word FROM blf_keywords where id = ?");
    query.addBindValue(id);
    query.exec();
    if (query.next()){
        return query.value(0).toString();
    }
    return "";
}

int blFinderDatabase::keywordId(QString word){
    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM blf_keywords where word = ?");
    query.addBindValue(word);
    query.exec();
    if (query.next()){
        return query.value(0).toInt();
    }
    return 0;
}

void blFinderDatabase::editKeyword(blFinderKeywordInfo info){

    //qDebug() << "add keyword: " << info.name() << ", " << info.categoryID();
    if (info.id() > 0){
        // update
        QSqlQuery query(m_db);
        query.prepare("UPDATE blf_keywords SET word=?, category_id=?  WHERE id=?");
        query.addBindValue(info.name());
        query.addBindValue(info.categoryID());
        query.addBindValue(info.id());
        query.exec();
    }
    else{
        // add
        QSqlQuery query(m_db);
        query.prepare( QString( "INSERT INTO blf_keywords(word, category_id)") +
                       QString( "VALUES (:name, :category_id)") );
        query.bindValue(":name", info.name());
        query.bindValue(":category_id", info.categoryID());
        query.exec();
    }
}

void blFinderDatabase::deleteKeyword(int id){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM blf_keywords WHERE id = ?");
    query.addBindValue(id);
    query.exec();
}

// ----------------
//      Sections
// ----------------
void blFinderDatabase::editSection(blFinderSectionInfo info){
    if (info.id() > 0){
        // update
        QSqlQuery query(m_db);
        query.prepare("UPDATE blf_finder_categories SET name=?, description=?, image_url=?, children_title=?, display_order=? WHERE id=?");
        query.addBindValue(info.name());
        query.addBindValue(info.description());
        query.addBindValue(info.imageUrl());
        query.addBindValue(info.childrenTitle());
        query.addBindValue(info.displayOrder());
        query.addBindValue(info.id());
        query.exec();
    }
    else{
        // add
        QSqlQuery query(m_db);
        query.prepare( QString( "INSERT INTO blf_finder_categories(name, description, image_url, children_title, display_order)") +
                       QString( "VALUES (:name, :description, :image_url, :children_title, :display_order)") );
        query.bindValue(":name", info.name());
        query.bindValue(":description", info.description());
        query.bindValue(":image_url", info.imageUrl());
        query.bindValue(":children_title", info.childrenTitle());
        query.bindValue(":display_order", info.displayOrder());
        query.exec();
    }
}

QList<blFinderSectionInfo> blFinderDatabase::sections(){
    QList<blFinderSectionInfo> list;
    QSqlQuery query(m_db);

    query.prepare(QString("SELECT * FROM blf_finder_categories"));
    query.exec();
    while (query.next()){
        blFinderSectionInfo info;
        info.setID(query.value(0).toInt());
        info.setName(query.value(1).toString());
        info.setDescription(query.value(2).toString());
        info.setImageUrl(query.value(3).toString());
        info.setChildrenTitle(query.value(4).toString());
        info.setDisplayOrder(query.value(5).toInt());
        list.append(info);
    }
    return list;
}

blFinderSectionInfo blFinderDatabase::sectionInfo(int id){
    blFinderSectionInfo info;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blf_finder_categories where id = ?");
    query.addBindValue(id);
    query.exec();
    if (query.next()){
        info.setID(query.value(0).toInt());
        info.setName(query.value(1).toString());
        info.setDescription(query.value(2).toString());
        info.setImageUrl(query.value(3).toString());
        info.setChildrenTitle(query.value(4).toString());
        info.setDisplayOrder(query.value(5).toInt());
    }
    return info;
}

QString blFinderDatabase::sectionName(int id){
    QSqlQuery query(m_db);
    query.prepare("SELECT name FROM blf_finder_categories where id = ?");
    query.addBindValue(id);
    query.exec();
    if (query.next()){
        return query.value(0).toString();
    }
    return "";
}

void blFinderDatabase::deleteSection(int id){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM blf_finder_categories WHERE id = ?");
    query.addBindValue(id);
    query.exec();
}

// -----------------
//   sections links
// -----------------
QList<blFinderSectionsLinkInfo> blFinderDatabase::sectionsLinks(){
    QList<blFinderSectionsLinkInfo> list;
    QSqlQuery query(m_db);

    query.prepare(QString("SELECT * FROM blf_finder_j_categories"));
    query.exec();
    while (query.next()){
        //qDebug() << "sections links :" << query.value(0).toInt() << ", " << query.value(1).toInt();
        blFinderSectionsLinkInfo info;
        info.setParentID(query.value(0).toInt());
        info.setChildID(query.value(1).toInt());
        info.setParentName(this->sectionName(query.value(0).toInt()));
        info.setChildName(this->sectionName(query.value(1).toInt()));
        list.append(info);
    }
    return list;
}

void blFinderDatabase::editSectionsLink(blFinderSectionsLinkInfo info){

    QSqlQuery query(m_db);
    query.prepare( QString( "INSERT INTO blf_finder_j_categories(id_parent, id_child)") +
                   QString( "VALUES (:idp, :idc)") );
    query.bindValue(":idp", info.parentID());
    query.bindValue(":idc", info.childID());
    query.exec();
}

void blFinderDatabase::deleteSectionsLink(int id1, int id2){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM blf_finder_j_categories WHERE id_parent = ? AND id_child = ?");
    query.addBindValue(id1);
    query.addBindValue(id2);
    query.exec();
}

// -----------------
//   tutorials links
// -----------------
QList<blFinderTutorialsLinkInfo> blFinderDatabase::tutorialsLinks(){
    QList<blFinderTutorialsLinkInfo> list;
    QSqlQuery query(m_db);

    query.prepare(QString("SELECT * FROM blf_finder_j_tuto"));
    query.exec();
    while (query.next()){
        //qDebug() << "tutorials links :" << query.value(0).toInt() << ", " << query.value(1).toInt();
        blFinderTutorialsLinkInfo info;
        info.setCategoryID(query.value(0).toInt());
        info.setTutorialID(query.value(1).toInt());
        info.setCategoryName(this->categoryName(query.value(0).toInt()));
        info.setTutorialName(this->tutorialTitle(query.value(1).toInt()));
        list.append(info);
    }
    return list;
}

void blFinderDatabase::editTutorialsLink(blFinderTutorialsLinkInfo info){

    QSqlQuery query(m_db);
    query.prepare( QString( "INSERT INTO blf_finder_j_tuto(id_category, id_tuto)") +
                   QString( "VALUES (:idp, :idc)") );
    query.bindValue(":idp", info.categoryID());
    query.bindValue(":idc", info.tutorialID());
    query.exec();
}

void blFinderDatabase::deleteTutorialsLink(int id1, int id2){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM blf_finder_j_tuto WHERE id_category = ? AND id_tuto = ?");
    query.addBindValue(id1);
    query.addBindValue(id2);
    query.exec();
}

// ---------------
//    tutorials
// ---------------
void blFinderDatabase::deleteTutorial(int id){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM blf_tutorials WHERE id = ?");
    query.addBindValue(id);
    query.exec();

    QSqlQuery query2(m_db);
    query2.prepare("DELETE FROM blf_j_tutorial_keyword WHERE id_tuto = ?");
    query2.addBindValue(id);
    query2.exec();

    QSqlQuery query3(m_db);
    query3.prepare("DELETE FROM blf_j_tutorial_author WHERE id_tuto = ?");
    query3.addBindValue(id);
    query3.exec();
}

QString blFinderDatabase::tutorialTitle(int id){
    QSqlQuery query(m_db);
    query.prepare("SELECT title FROM blf_tutorials where id = ?");
    query.addBindValue(id);
    query.exec();
    if (query.next()){
        return query.value(0).toString();
    }
    return "";
}

blFinderTutorialInfo blFinderDatabase::tutorialInfo(int id, QString toolShedDir){
    blFinderTutorialInfo info;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blf_tutorials where id = ?");
    query.addBindValue(id);
    query.exec();
    if (query.next()){
        info.setId(query.value(0).toInt());
        info.setTitle(query.value(1).toString());
        info.setLanguage(query.value(2).toString());
        info.setOrigin(query.value(3).toInt());
        info.setImageUrl(toolShedDir + query.value(4).toString());
        info.setViewName(query.value(5).toString());
        info.setXmlUrl(toolShedDir + query.value(6).toString());
        info.setDocUrl(toolShedDir + query.value(7).toString());

        info.setOriginName(this->OriginName(query.value(3).toInt()));

        // get the authors
        QList<int> authorsId = this->tutorialAuthors(id);
        //qDebug() << "authors ids count = " << authorsId.count();
        for (int i = 0 ; i < authorsId.count() ; ++i){
            info.addAuthor(authorsId[i], this->authorFullName(authorsId[i]));
        }

        // get the authors

        QList<int> keywordsIds = this->tutorialKeywords(id);
        //qDebug() << "keywordsIds ids count = " << keywordsIds.count();
        for(int i = 0 ; i < keywordsIds.count() ; ++i){
            info.addKeyword(keywordsIds[i], this->keywordWord(keywordsIds[i]));
        }
    }
    return info;
}

QList<int> blFinderDatabase::tutorialKeywords(int id){

    //qDebug() << "select keywords for tuto id = " << id;
    QList<int> keywords;
    QSqlQuery query(m_db);
    query.prepare("SELECT id_keyword FROM blf_j_tutorial_keyword where id_tuto = ?");
    query.addBindValue(id);
    query.exec();
    while (query.next()){
        keywords.append(query.value(0).toInt());
    }
    return keywords;
}

QList<int> blFinderDatabase::tutorialAuthors(int id){
    QList<int> authors;
    QSqlQuery query(m_db);
    query.prepare("SELECT id_author FROM blf_j_tutorial_author where id_tuto = ?");
    query.addBindValue(id);
    query.exec();
    while (query.next()){
        authors.append(query.value(0).toInt());
    }
    return authors;
}

QList<blFinderTutorialInfo> blFinderDatabase::tutorials(){
    QList<blFinderTutorialInfo> list;
    QSqlQuery query(m_db);

    query.prepare(QString("SELECT * FROM blf_tutorials"));
    query.exec();
    while (query.next()){
        blFinderTutorialInfo info;
        info.setId(query.value(0).toInt());
        info.setTitle(query.value(1).toString());
        info.setLanguage(query.value(2).toString());
        info.setOrigin(query.value(3).toInt());
        info.setOriginName(this->OriginName(query.value(3).toInt()));
        info.setImageUrl(query.value(4).toString());
        info.setViewName(query.value(5).toString());
        info.setXmlUrl(query.value(6).toString());
        info.setDocUrl(query.value(7).toString());
        list.append(info);
    }
    return list;
}

void blFinderDatabase::editTutorial(blFinderTutorialInfo info){

    int id = 0;
    if (info.id() > 0){
        id = info.id();
        // update
        QSqlQuery query(m_db);
        query.prepare("UPDATE blf_tutorials SET title=?, language=?, origin=?, image_url=?, view_name=?, xml_url=?, doc_url=? WHERE id=?");
        query.addBindValue(info.title());
        query.addBindValue(info.language());
        query.addBindValue(info.origin());
        query.addBindValue(info.imageUrl());
        query.addBindValue(info.viewName());
        query.addBindValue(info.xmlUrl());
        query.addBindValue(info.docUrl());
        query.addBindValue(info.id());
        query.exec();
    }
    else{
        // add
        QSqlQuery query(m_db);
        query.prepare( QString( "INSERT INTO blf_tutorials(title, language, origin, image_url, view_name, xml_url, doc_url)") +
                       QString( "VALUES (:title, :language, :origin, :image_url, :view_name, :xml_url, :doc_url)") );
        query.bindValue(":title", info.title());
        query.bindValue(":language", info.language());
        query.bindValue(":origin", info.origin());
        query.bindValue(":image_url", info.imageUrl());
        query.bindValue(":view_name", info.viewName());
        query.bindValue(":xml_url", info.xmlUrl());
        query.bindValue(":doc_url", info.docUrl());
        query.exec();
        id = query.lastInsertId().toInt();
    }

    //qDebug() << "add tutorial id=" << id;
    if (id > 0){

        // authors
        // remove all the authors
        QSqlQuery query(m_db);
        query.prepare("DELETE FROM blf_j_tutorial_author WHERE id_tuto = ?");
        query.addBindValue(id);
        query.exec();

        // add the authors
        //qDebug() << "count author = " << info.countAuthors();
        for (int i = 0 ; i < info.countAuthors() ; ++i){
            QSqlQuery query(m_db);
            query.prepare( QString( "INSERT INTO blf_j_tutorial_author(id_tuto, id_author)") +
                           QString( "VALUES (:id_tuto, :id_author)") );
            query.bindValue(":id_tuto", id);
            query.bindValue(":id_author", info.authorIdAt(i));
            query.exec();
        }

        // keywords
        // remove all the keywords
        QSqlQuery query2(m_db);
        query2.prepare("DELETE FROM blf_j_tutorial_keyword WHERE id_tuto = ?");
        query2.addBindValue(id);
        query2.exec();

        // add the keywords
        //qDebug() << "count keyword = " << info.countKeywords();
        for (int i = 0 ; i < info.countKeywords() ; ++i){
            QSqlQuery query(m_db);
            query.prepare( QString( "INSERT INTO blf_j_tutorial_keyword(id_tuto, id_keyword)") +
                           QString( "VALUES (:id_tuto, :id_keyword)") );
            query.bindValue(":id_tuto", id);
            query.bindValue(":id_keyword", info.keywordIdAt(i));
            query.exec();
        }
    }
}


// -----------
//  Origins
// -----------
QList<blFinderOriginInfo> blFinderDatabase::origins(){
    QList<blFinderOriginInfo> auths;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blf_origins");
    query.exec();
    while (query.next()){
        blFinderOriginInfo aut;
        aut.setID(query.value(0).toInt());
        aut.setName(query.value(1).toString());
        auths.append(aut);
    }
    return auths;
}

blFinderOriginInfo blFinderDatabase::OriginInfo(int id){
    blFinderOriginInfo info;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blf_origins where id = ?");
    query.addBindValue(id);
    query.exec();
    if (query.next()){
        info.setID(query.value(0).toInt());
        info.setName(query.value(1).toString());
    }
    return info;
}

QString blFinderDatabase::OriginName(int id){
    QSqlQuery query(m_db);
    query.prepare("SELECT name FROM blf_origins where id = ?");
    query.addBindValue(id);
    query.exec();
    if (query.next()){
        return query.value(0).toString();
    }
    return "";
}

void blFinderDatabase::editOrigin(blFinderOriginInfo info){
    if (info.id() > 0){
        // update
        QSqlQuery query(m_db);
        query.prepare("UPDATE blf_origins SET name=?  WHERE id=?");
        query.addBindValue(info.name());
        query.addBindValue(info.id());
        query.exec();
    }
    else{
        // add
        QSqlQuery query(m_db);
        query.prepare( QString( "INSERT INTO blf_origins(name)") +
                       QString( "VALUES (:name)") );
        query.bindValue(":name", info.name());
        query.exec();
    }
}

void blFinderDatabase::deleteOrigin(int id){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM blf_keywords_Origin WHERE id = ?");
    query.addBindValue(id);
    query.exec();
}

// ---------------
//   finder queries
// ---------------
QList<blFinderTutorialInfo> blFinderDatabase::tutorialsByKeyword(QString keyword, QString toolshedDir){

    // get the keyword id
    int idk = this->keywordId(keyword);

    // tuto ids
    QList<blFinderTutorialInfo> list;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blf_tutorials WHERE id IN (SELECT id_tuto FROM blf_j_tutorial_keyword where id_keyword = ?)");
    query.addBindValue(idk);
    query.exec();
    while (query.next()){
        blFinderTutorialInfo info;
        info.setId(query.value(0).toInt());
        info.setTitle(query.value(1).toString());
        info.setLanguage(query.value(2).toString());
        info.setOrigin(query.value(3).toInt());
        info.setOriginName(this->OriginName(query.value(3).toInt()));
        info.setImageUrl(toolshedDir + query.value(4).toString());
        info.setViewName(query.value(5).toString());
        info.setXmlUrl(toolshedDir + query.value(6).toString());
        info.setDocUrl(toolshedDir + query.value(7).toString());

        // get the authors
        QList<int> authorsId = this->tutorialAuthors(query.value(0).toInt());
        for (int i = 0 ; i < authorsId.count() ; ++i){
            info.addAuthor(authorsId[i], this->authorShortName(authorsId[i]));
        }
        list.append(info);
    }
    return list;
}

QList<blFinderTutorialInfo> blFinderDatabase::tutorialsByOrigin(int origin, QString toolshedDir){

    // tuto ids
    QList<blFinderTutorialInfo> list;
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM blf_tutorials WHERE origin = ?");
    query.addBindValue(origin);
    query.exec();
    while (query.next()){
        blFinderTutorialInfo info;
        info.setId(query.value(0).toInt());
        info.setTitle(query.value(1).toString());
        info.setLanguage(query.value(2).toString());
        info.setOrigin(query.value(3).toInt());
        info.setOriginName(this->OriginName(query.value(3).toInt()));
        info.setImageUrl(toolshedDir + query.value(4).toString());
        info.setViewName(query.value(5).toString());
        info.setXmlUrl(toolshedDir + query.value(6).toString());
        info.setDocUrl(toolshedDir + query.value(7).toString());

        // get the authors
        QList<int> authorsId = this->tutorialAuthors(query.value(0).toInt());
        for (int i = 0 ; i < authorsId.count() ; ++i){
            info.addAuthor(authorsId[i], this->authorShortName(authorsId[i]));
        }
        list.append(info);
    }
    return list;

}

blFinderSectionInfo blFinderDatabase::root(){

    blFinderSectionInfo root;
    QSqlQuery query(m_db);

    query.prepare(QString("SELECT * FROM blf_finder_categories WHERE name=?"));
    query.addBindValue("root");
    query.exec();
    if (query.next()){
        root.setID(query.value(0).toInt());
        root.setName(query.value(1).toString());
        root.setDescription(query.value(2).toString());
        root.setImageUrl(query.value(3).toString());
        root.setChildrenTitle(query.value(4).toString());
        root.setDisplayOrder(query.value(5).toInt());
    }
    return root;
}

blFinderSectionInfo blFinderDatabase::section(int id){
    blFinderSectionInfo root;
    QSqlQuery query(m_db);

    query.prepare(QString("SELECT * FROM blf_finder_categories WHERE id=?"));
    query.addBindValue(id);
    query.exec();
    if (query.next()){
        root.setID(query.value(0).toInt());
        root.setName(query.value(1).toString());
        root.setDescription(query.value(2).toString());
        root.setImageUrl(query.value(3).toString());
        root.setChildrenTitle(query.value(4).toString());
        root.setDisplayOrder(query.value(5).toInt());
    }
    return root;
}


QList<blFinderSectionInfo> blFinderDatabase::children(int section, QString toolshedDir){

    QList<blFinderSectionInfo> list;
    QSqlQuery query(m_db);

    query.prepare(QString("SELECT * FROM blf_finder_categories WHERE id IN (SELECT id_child FROM blf_finder_j_categories WHERE id_parent=?)"));
    query.addBindValue(section);
    query.exec();
    while (query.next()){

        blFinderSectionInfo root;
        root.setID(query.value(0).toInt());
        root.setName(query.value(1).toString());
        root.setDescription(query.value(2).toString());
        root.setImageUrl(toolshedDir + query.value(3).toString());
        root.setChildrenTitle(query.value(4).toString());
        root.setDisplayOrder(query.value(5).toInt());
        list.append(root);
    }
    return list;
}

QList<blFinderTutorialInfo>  blFinderDatabase::childrenTutorials(int section, QString toolshedDir){
    QList<blFinderTutorialInfo> list;
    QSqlQuery query(m_db);

    query.prepare(QString("SELECT * FROM blf_tutorials WHERE id IN (SELECT id_tuto FROM blf_finder_j_tuto WHERE id_category=?)"));
    query.addBindValue(section);
    query.exec();
    while (query.next()){
        blFinderTutorialInfo info;
        info.setId(query.value(0).toInt());
        info.setTitle(query.value(1).toString());
        info.setLanguage(query.value(2).toString());
        info.setOrigin(query.value(3).toInt());
        info.setOriginName(this->OriginName(query.value(3).toInt()));
        info.setImageUrl(toolshedDir + query.value(4).toString());
        info.setViewName(query.value(5).toString());
        info.setXmlUrl(toolshedDir + query.value(6).toString());
        info.setDocUrl(toolshedDir + query.value(7).toString());

        // get the authors
        QList<int> authorsId = this->tutorialAuthors(query.value(0).toInt());
        for (int i = 0 ; i < authorsId.count() ; ++i){
            info.addAuthor(authorsId[i], this->authorShortName(authorsId[i]));
        }
        list.append(info);
    }
    return list;
}

// ---------------
//  View
// ---------------
// view table
void blFinderDatabase::viewTable(const QString tableName)
{
    qDebug() << "blToolsDatabase::ViewTable ";
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

void blFinderDatabase::viewTableHeader(const QString tableName, const QString orientation)
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

void blFinderDatabase::viewTablesList()
{
    QStringList tabl=m_db.tables();
    std::cout<< "Tables are :"<<std::endl;
    for (int t=0 ; t<tabl.size() ; t++)
    {
        std::cout<< t << "- " << (tabl.at(t).toStdString())<<std::endl;
    }
}
