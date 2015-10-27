#include "blFinderAdminTutorialsLinkEdit.h"

blFinderAdminTutorialsLinkEdit::blFinderAdminTutorialsLinkEdit(QList<blFinderCategoryInfo> categories, QList<blFinderTutorialInfo> tutorials, QWidget *parent)
    : QWidget(parent){

    m_id = 0;

    QGridLayout *layout = new QGridLayout;
    this->setLayout(layout);

    // title
    QLabel *title = new QLabel(tr("Add Tutorial link"), this);
    layout->addWidget(title, 0, 0, 1, 5);
    title->setObjectName("blFinderAdminTableTitle");

    // parent
    QLabel *parentLabel = new QLabel(tr("Tutorial"), this);
    m_tutorialsList = new QComboBox(this);
    layout->addWidget(parentLabel, 1,0,1,4);
    layout->addWidget(m_tutorialsList, 1,1,1,4);
    for(int i = 0 ; i < tutorials.count() ; ++i){
        blFinderTutorialInfo cat = tutorials[i];
        m_tutorialsList->addItem(cat.title(), cat.id());
    }

    // child
    QLabel *childLabel = new QLabel(tr("Category"), this);
    m_categoriesList = new QComboBox(this);
    layout->addWidget(childLabel, 2,0,1,4);
    layout->addWidget(m_categoriesList, 2,1,1,4);
    for(int i = 0 ; i < categories.count() ; ++i){
        blFinderCategoryInfo cat = categories[i];
        m_categoriesList->addItem(cat.name(), cat.id());
    }

    // buttons
    QPushButton *save = new QPushButton(tr("Save"), this);
    save->setObjectName("btnPrimary");
    QPushButton *cancel = new QPushButton(tr("Cancel"), this);
    cancel->setObjectName("btnDefault");
    layout->addWidget(save, 3, 2, 1, 1);
    layout->addWidget(cancel, 3, 3, 1, 1);

    connect(save, SIGNAL(pressed()), this, SLOT(emitEditInfo()));
    connect(cancel, SIGNAL(pressed()), this, SIGNAL(cancel()));
}

void blFinderAdminTutorialsLinkEdit::emitEditInfo(){
    blFinderTutorialsLinkInfo info;
    info.setCategoryID(m_categoriesList->currentData().toInt());
    info.setTutorialID(m_tutorialsList->currentData().toInt());
    emit editInfo(info);
}
