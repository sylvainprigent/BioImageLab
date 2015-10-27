#include "blFinderAdminDefaultWidget.h"
#include "../model/blFinderAuthorInfo.h"
#include "../view/blFinderAdminBar.h"
#include "../view/blFinderAdminAuthorTable.h"
#include "../view/blFinderAdminAuthorEdit.h"
#include "../view/blFinderAdminCategoriesTable.h"
#include "../view/blFinderAdminCategoryEdit.h"
#include "../model/blFinderAccess.h"
#include "../model/blFinderKeywordInfo.h"
#include "../view/blFinderAdminKeywordsTable.h"
#include "../view/blFinderAdminKeywordEdit.h"
#include "../view/blFinderAdminSectionsTable.h"
#include "../view/blFinderAdminSectionEdit.h"
#include "../model/blFinderSectionsLinkInfo.h"
#include "../view/blFinderAdminSectionsLinksTable.h"
#include "../view/blFinderAdminSectionsLinkEdit.h"
#include "../view/blFinderAdminTutorialsTable.h"
#include "../view/blFinderAdminTutorialEdit.h"
#include "../view/blFinderAdminOriginsTable.h"
#include "../view/blFinderAdminOriginEdit.h"
#include "../view/blFinderAdminTutorialsLinksTable.h"
#include "../view/blFinderAdminTutorialsLinkEdit.h"

blFinderAdminDefaultWidget::blFinderAdminDefaultWidget(QWidget *parent) : QWidget(parent)
{

    /*
    blFinderAccess::instance()->database()->viewTable("blf_j_tutorial_keyword");
    blFinderAccess::instance()->database()->viewTable("blf_j_tutorial_author");
    blFinderAccess::instance()->database()->viewTable("blf_tutorials");
*/
    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);

    // global layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    blFinderAdminBar *bar = new blFinderAdminBar(this);
    QSplitter *splitter = new QSplitter(this);
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(m_layout);
    splitter->addWidget(centralWidget);
    splitter->addWidget(bar);
    layout->addWidget(splitter);

    connect(bar, SIGNAL(authorsList()), this, SLOT(authors()));
    connect(bar, SIGNAL(authorAdd()), this, SLOT(authorAdd()));
    connect(bar, SIGNAL(categoriesList()), this, SLOT(categories()));
    connect(bar, SIGNAL(categoriesAdd()), this, SLOT(categoryAdd()));
    connect(bar, SIGNAL(keywordsList()), this, SLOT(keywords()));
    connect(bar, SIGNAL(keywordsAdd()), this, SLOT(keywordAdd()));
    connect(bar, SIGNAL(sectionsList()), this, SLOT(sections()));
    connect(bar, SIGNAL(sectionsAdd()), this, SLOT(sectionAdd()));
    connect(bar, SIGNAL(sectionsLinks()), this, SLOT(sectionsLinks()));
    connect(bar, SIGNAL(sectionsLinksAdd()), this, SLOT(sectionsLinksAdd()));
    connect(bar, SIGNAL(tutorialsLinks()), this, SLOT(tutorialsLinks()));
    connect(bar, SIGNAL(tutorialsLinksAdd()), this, SLOT(tutorialsLinksAdd()));
    connect(bar, SIGNAL(originsList()), this, SLOT(origins()));
    connect(bar, SIGNAL(originAdd()), this, SLOT(originAdd()));
    connect(bar, SIGNAL(tutorialsList()), this, SLOT(tutorials()));
    connect(bar, SIGNAL(tutorialAdd()), this, SLOT(tutorialAdd()));

    this->setObjectName("blFinderAdminDefaultWidget");
}


// ------------------------
//       Authors
// ------------------------
void blFinderAdminDefaultWidget::authors(){

    // get authors list
    blFinderDatabase *database = blFinderAccess::instance()->database();
    QList<blFinderAuthorInfo> authors = database->authors();
    // create view
    blFinderAdminAuthorTable *table = new blFinderAdminAuthorTable(this);
    table->fillTable(authors);
    connect(table, SIGNAL(edit(int)), this, SLOT(authorUpdate(int)));

    this->setCentralWidget(table, false);
}

void blFinderAdminDefaultWidget::authorAdd(){

    blFinderAdminAuthorEdit *edit = new blFinderAdminAuthorEdit(this);
    this->setCentralWidget(edit);

    connect(edit, SIGNAL(cancel()), this, SLOT(authors()));
    connect(edit, SIGNAL(editInfo(blFinderAuthorInfo)), this, SLOT(editAuthor(blFinderAuthorInfo)));
}

void blFinderAdminDefaultWidget::authorUpdate(int id){

    blFinderAdminAuthorEdit *edit = new blFinderAdminAuthorEdit(this);
    edit->setInfo(blFinderAccess::instance()->database()->authorInfo(id));
    this->setCentralWidget(edit);

    connect(edit, SIGNAL(cancel()), this, SLOT(authors()));
    connect(edit, SIGNAL(editInfo(blFinderAuthorInfo)), this, SLOT(editAuthor(blFinderAuthorInfo)));
    connect(edit, SIGNAL(remove(int)), this, SLOT(removeAuthor(int)));
}

void blFinderAdminDefaultWidget::editAuthor(blFinderAuthorInfo info){

    blFinderAccess::instance()->database()->editAuthor(info);
    this->authors();
}

void blFinderAdminDefaultWidget::removeAuthor(int id){
    blFinderAccess::instance()->database()->deleteAuthor(id);
    this->authors();
}

// ------------------------
//       Categories
// ------------------------
void blFinderAdminDefaultWidget::categories(){

    // get authors list
    blFinderDatabase *database = blFinderAccess::instance()->database();
    QList<blFinderCategoryInfo> categories = database->categories();
    // create view
    blFinderAdminCategoriesTable *table = new blFinderAdminCategoriesTable(this);
    table->fillTable(categories);

    connect(table, SIGNAL(edit(int)), this, SLOT(categoryUpdate(int)));
    this->setCentralWidget(table, false);
}

void blFinderAdminDefaultWidget::categoryAdd(){

    blFinderAdminCategoryEdit *edit = new blFinderAdminCategoryEdit(this);
    this->setCentralWidget(edit);

    connect(edit, SIGNAL(cancel()), this, SLOT(categories()));
    connect(edit, SIGNAL(editInfo(blFinderCategoryInfo)), this, SLOT(editCategory(blFinderCategoryInfo)));
}

void blFinderAdminDefaultWidget::categoryUpdate(int id){

    blFinderAdminCategoryEdit *edit = new blFinderAdminCategoryEdit(this);
    edit->setInfo(blFinderAccess::instance()->database()->categoryInfo(id));
    this->setCentralWidget(edit);

    connect(edit, SIGNAL(cancel()), this, SLOT(categories()));
    connect(edit, SIGNAL(editInfo(blFinderCategoryInfo)), this, SLOT(editCategory(blFinderCategoryInfo)));
    connect(edit, SIGNAL(remove(int)), this, SLOT(removeCategory(int)));
}

void blFinderAdminDefaultWidget::editCategory(blFinderCategoryInfo info){

    blFinderAccess::instance()->database()->editCategory(info);
    this->categories();
}

void blFinderAdminDefaultWidget::removeCategory(int id){
    blFinderAccess::instance()->database()->deleteCategory(id);
    this->categories();
}

// ------------------------
//       Keywords
// ------------------------
void blFinderAdminDefaultWidget::keywords(){

    // get authors list
    blFinderDatabase *database = blFinderAccess::instance()->database();
    QList<blFinderKeywordInfo> keywords = database->keywords();
    // create view
    blFinderAdminKeywordsTable *table = new blFinderAdminKeywordsTable(this);
    table->fillTable(keywords);

    connect(table, SIGNAL(edit(int)), this, SLOT(keywordUpdate(int)));
    this->setCentralWidget(table, false);
}

void blFinderAdminDefaultWidget::keywordAdd(){

    blFinderDatabase *database = blFinderAccess::instance()->database();
    QList<blFinderCategoryInfo> categories = database->categories();

    blFinderAdminKeywordEdit *edit = new blFinderAdminKeywordEdit(categories, this);
    this->setCentralWidget(edit);

    connect(edit, SIGNAL(cancel()), this, SLOT(keywords()));
    connect(edit, SIGNAL(editInfo(blFinderKeywordInfo)), this, SLOT(editKeyword(blFinderKeywordInfo)));
}

void blFinderAdminDefaultWidget::keywordUpdate(int id){

    blFinderDatabase *database = blFinderAccess::instance()->database();
    QList<blFinderCategoryInfo> categories = database->categories();

    blFinderAdminKeywordEdit *edit = new blFinderAdminKeywordEdit(categories, this);
    edit->setInfo(blFinderAccess::instance()->database()->keywordInfo(id));
    this->setCentralWidget(edit);

    connect(edit, SIGNAL(cancel()), this, SLOT(keywords()));
    connect(edit, SIGNAL(editInfo(blFinderKeywordInfo)), this, SLOT(editKeyword(blFinderKeywordInfo)));
    connect(edit, SIGNAL(remove(int)), this, SLOT(removeKeyword(int)));
}

void blFinderAdminDefaultWidget::editKeyword(blFinderKeywordInfo info){

    blFinderAccess::instance()->database()->editKeyword(info);
    this->keywords();
}

void blFinderAdminDefaultWidget::removeKeyword(int id){
    blFinderAccess::instance()->database()->deleteKeyword(id);
    this->keywords();
}

// ------------------------
//       sections
// ------------------------
void blFinderAdminDefaultWidget::sections(){

    // get sections list
    blFinderDatabase *database = blFinderAccess::instance()->database();
    QList<blFinderSectionInfo> sections = database->sections();
    // create view
    blFinderAdminSectionsTable *table = new blFinderAdminSectionsTable(this);
    table->fillTable(sections);
    connect(table, SIGNAL(edit(int)), this, SLOT(sectionUpdate(int)));

    this->setCentralWidget(table, false);
}

void blFinderAdminDefaultWidget::sectionAdd(){

    blFinderAdminSectionEdit *edit = new blFinderAdminSectionEdit(this);
    this->setCentralWidget(edit);

    connect(edit, SIGNAL(cancel()), this, SLOT(sections()));
    connect(edit, SIGNAL(editInfo(blFinderSectionInfo)), this, SLOT(editSection(blFinderSectionInfo)));
}

void blFinderAdminDefaultWidget::sectionUpdate(int id){

    blFinderAdminSectionEdit *edit = new blFinderAdminSectionEdit(this);
    edit->setInfo(blFinderAccess::instance()->database()->sectionInfo(id));
    this->setCentralWidget(edit);

    connect(edit, SIGNAL(cancel()), this, SLOT(sections()));
    connect(edit, SIGNAL(editInfo(blFinderSectionInfo)), this, SLOT(editSection(blFinderSectionInfo)));
    connect(edit, SIGNAL(remove(int)), this, SLOT(removeSection(int)));
}

void blFinderAdminDefaultWidget::editSection(blFinderSectionInfo info){

    blFinderAccess::instance()->database()->editSection(info);
    this->sections();
}

void blFinderAdminDefaultWidget::removeSection(int id){
    blFinderAccess::instance()->database()->deleteSection(id);
    this->sections();
}

// -----------------------
//    Sections Links
// -----------------------
void blFinderAdminDefaultWidget::sectionsLinks(){

    // get sections links list
    blFinderDatabase *database = blFinderAccess::instance()->database();
    QList<blFinderSectionsLinkInfo> sections = database->sectionsLinks();
    // create view
    blFinderAdminSectionsLinksTable *table = new blFinderAdminSectionsLinksTable(this);
    table->fillTable(sections);
    connect(table, SIGNAL(removeLink(int,int)), this, SLOT(removeSectionsLink(int, int)));

    this->setCentralWidget(table, false);
}

void blFinderAdminDefaultWidget::sectionsLinksAdd(){

    QList<blFinderSectionInfo> sections = blFinderAccess::instance()->database()->sections();
    blFinderAdminSectionsLinkEdit *edit = new blFinderAdminSectionsLinkEdit(sections, this);
    this->setCentralWidget(edit);

    connect(edit, SIGNAL(cancel()), this, SLOT(sections()));
    connect(edit, SIGNAL(editInfo(blFinderSectionsLinkInfo)), this, SLOT(editSectionsLink(blFinderSectionsLinkInfo)));
}

void blFinderAdminDefaultWidget::editSectionsLink(blFinderSectionsLinkInfo info){
    blFinderAccess::instance()->database()->editSectionsLink(info);
    this->sectionsLinks();
}

void blFinderAdminDefaultWidget::removeSectionsLink(int id1, int id2){
    blFinderAccess::instance()->database()->deleteSectionsLink(id1, id2);
    this->sectionsLinks();
}

// -----------------------
//    Tutrials Links
// -----------------------
void blFinderAdminDefaultWidget::tutorialsLinks(){

    // get sections links list
    blFinderDatabase *database = blFinderAccess::instance()->database();
    QList<blFinderTutorialsLinkInfo> tutorials = database->tutorialsLinks();
    // create view
    blFinderAdminTutorialsLinksTable *table = new blFinderAdminTutorialsLinksTable(this);
    table->fillTable(tutorials);
    connect(table, SIGNAL(removeLink(int,int)), this, SLOT(removeTutorialsLink(int, int)));

    this->setCentralWidget(table, false);
}

void blFinderAdminDefaultWidget::tutorialsLinksAdd(){

    QList<blFinderCategoryInfo> categories = blFinderAccess::instance()->database()->categories();
    QList<blFinderTutorialInfo> tutorials = blFinderAccess::instance()->database()->tutorials();
    blFinderAdminTutorialsLinkEdit *edit = new blFinderAdminTutorialsLinkEdit(categories, tutorials, this);
    this->setCentralWidget(edit);

    connect(edit, SIGNAL(cancel()), this, SLOT(sections()));
    connect(edit, SIGNAL(editInfo(blFinderTutorialsLinkInfo)), this, SLOT(editTutorialsLink(blFinderTutorialsLinkInfo)));
}

void blFinderAdminDefaultWidget::editTutorialsLink(blFinderTutorialsLinkInfo info){
    blFinderAccess::instance()->database()->editTutorialsLink(info);
    this->tutorialsLinks();
}

void blFinderAdminDefaultWidget::removeTutorialsLink(int id1, int id2){
    blFinderAccess::instance()->database()->deleteTutorialsLink(id1, id2);
    this->tutorialsLinks();
}

// -----------------------
//      Tutorials
// -----------------------
void blFinderAdminDefaultWidget::tutorials(){
    // get sections links list
    blFinderDatabase *database = blFinderAccess::instance()->database();
    QList<blFinderTutorialInfo> tutorials = database->tutorials();
    // create view
    blFinderAdminTutorialsTable *table = new blFinderAdminTutorialsTable(this);
    table->fillTable(tutorials);
    connect(table, SIGNAL(edit(int)), this, SLOT(tutorialUpdate(int)));

    this->setCentralWidget(table, false);
}

void blFinderAdminDefaultWidget::tutorialAdd(){
    QList<blFinderOriginInfo> origins = blFinderAccess::instance()->database()->origins();
    QList<blFinderAuthorInfo> authors = blFinderAccess::instance()->database()->authors();
    QList<blFinderKeywordInfo> keywords = blFinderAccess::instance()->database()->keywords();
    blFinderAdminTutorialEdit *edit = new blFinderAdminTutorialEdit(origins, authors, keywords, this);
    this->setCentralWidget(edit);

    connect(edit, SIGNAL(cancel()), this, SLOT(tutorials()));
    connect(edit, SIGNAL(editInfo(blFinderTutorialInfo)), this, SLOT(editTutorial(blFinderTutorialInfo)));
}

void blFinderAdminDefaultWidget::tutorialUpdate(int id){
    QList<blFinderOriginInfo> origins = blFinderAccess::instance()->database()->origins();
    QList<blFinderAuthorInfo> authors = blFinderAccess::instance()->database()->authors();
    QList<blFinderKeywordInfo> keywords = blFinderAccess::instance()->database()->keywords();
    blFinderAdminTutorialEdit *edit = new blFinderAdminTutorialEdit(origins, authors, keywords, this);
    //qDebug() << "set info ";
    blFinderTutorialInfo info = blFinderAccess::instance()->database()->tutorialInfo(id);
    //qDebug() << "set info query done";
    edit->setInfo(info);
    //qDebug() << "set info done ";
    this->setCentralWidget(edit);

    connect(edit, SIGNAL(cancel()), this, SLOT(keywords()));
    connect(edit, SIGNAL(editInfo(blFinderTutorialInfo)), this, SLOT(editTutorial(blFinderTutorialInfo)));
    connect(edit, SIGNAL(remove(int)), this, SLOT(removeTutorial(int)));
}

void blFinderAdminDefaultWidget::editTutorial(blFinderTutorialInfo info){
    qDebug() << "edit tutorial = " << info.xmlUrl();
    blFinderAccess::instance()->database()->editTutorial(info);
    this->tutorials();
}

void blFinderAdminDefaultWidget::removeTutorial(int id){
    blFinderAccess::instance()->database()->deleteTutorial(id);
    this->tutorials();
}

// ------------------------
//       Origins
// ------------------------
void blFinderAdminDefaultWidget::origins(){

    // get authors list
    blFinderDatabase *database = blFinderAccess::instance()->database();
    QList<blFinderOriginInfo> origins = database->origins();
    // create view
    blFinderAdminOriginsTable *table = new blFinderAdminOriginsTable(this);
    table->fillTable(origins);

    connect(table, SIGNAL(edit(int)), this, SLOT(originUpdate(int)));
    this->setCentralWidget(table, false);
}

void blFinderAdminDefaultWidget::originAdd(){

    blFinderAdminOriginEdit *edit = new blFinderAdminOriginEdit(this);
    this->setCentralWidget(edit);

    connect(edit, SIGNAL(cancel()), this, SLOT(origins()));
    connect(edit, SIGNAL(editInfo(blFinderOriginInfo)), this, SLOT(editOrigin(blFinderOriginInfo)));
}

void blFinderAdminDefaultWidget::originUpdate(int id){

    blFinderAdminOriginEdit *edit = new blFinderAdminOriginEdit(this);
    edit->setInfo(blFinderAccess::instance()->database()->OriginInfo(id));
    this->setCentralWidget(edit);

    connect(edit, SIGNAL(cancel()), this, SLOT(origins()));
    connect(edit, SIGNAL(editInfo(blFinderOriginInfo)), this, SLOT(editOrigin(blFinderOriginInfo)));
    connect(edit, SIGNAL(remove(int)), this, SLOT(removeOrigin(int)));
}

void blFinderAdminDefaultWidget::editOrigin(blFinderOriginInfo info){

    blFinderAccess::instance()->database()->editOrigin(info);
    this->origins();
}

void blFinderAdminDefaultWidget::removeOrigin(int id){
    blFinderAccess::instance()->database()->deleteOrigin(id);
    this->origins();
}

// -----------------------
//    private methods
// -----------------------
void blFinderAdminDefaultWidget::setCentralWidget(QWidget * widget, bool alignTop){

    if (m_layout->count() > 0){
        QWidget* w = m_layout->itemAt(0)->widget();
        if (w){
            delete w;
        }
    }

    /*
    QWidget *w2 = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout;
    w2->setLayout(layout);
    //widget->setMinimumWidth(650);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(new QWidget, 1, Qt::AlignRight);
    layout->addWidget(widget, 0, Qt::AlignHCenter);
    layout->addWidget(new QWidget, 1, Qt::AlignLeft);
    */

    if (alignTop){
        m_layout->addWidget(widget, 1, Qt::AlignTop);
    }
    else{
        m_layout->addWidget(widget);
    }
    //m_layout->insertWidget(1, w2, 1, Qt::AlignTop);
}
