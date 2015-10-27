#include "blFinderAdminKeywordEdit.h"

blFinderAdminKeywordEdit::blFinderAdminKeywordEdit(QList<blFinderCategoryInfo> categories, QWidget *parent)
    : QWidget(parent){

    m_id = 0;

    QGridLayout *layout = new QGridLayout;
    this->setLayout(layout);

    // title
    QLabel *title = new QLabel(tr("Edit Keyword"), this);
    layout->addWidget(title, 0, 0, 1, 5);
    title->setObjectName("blFinderAdminTableTitle");

    // name
    QLabel *nameLabel = new QLabel(tr("Name"), this);
    m_name = new QLineEdit(this);
    layout->addWidget(nameLabel, 1,0,1,4);
    layout->addWidget(m_name, 1,1,1,4);

    // category
    QLabel *categoryLabel = new QLabel(tr("Category"), this);
    m_categoriesList = new QComboBox(this);
    layout->addWidget(categoryLabel, 2,0,1,4);
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
    m_removeButton = new QPushButton(tr("Delete"), this);
    m_removeButton->setObjectName("btnDanger");
    m_removeButton->setVisible(false);
    layout->addWidget(save, 3, 2, 1, 1);
    layout->addWidget(cancel, 3, 3, 1, 1);
    layout->addWidget(m_removeButton, 3, 4, 1, 1);

    connect(save, SIGNAL(pressed()), this, SLOT(emitEditInfo()));
    connect(cancel, SIGNAL(pressed()), this, SIGNAL(cancel()));
    connect(m_removeButton, SIGNAL(pressed()), this, SLOT(emitRemove()));
}

void blFinderAdminKeywordEdit::setInfo(blFinderKeywordInfo info){
    m_id = info.id();
    m_name->setText(info.name());
    for (int i = 0 ; i < m_categoriesList->count() ; ++i){
        if (m_categoriesList->itemData(i).toInt() == info.categoryID()){
            m_categoriesList->setCurrentIndex(i);
            break;
        }
    }
    m_removeButton->setVisible(true);
}

void blFinderAdminKeywordEdit::emitEditInfo(){
    blFinderKeywordInfo info;
    info.setID(m_id);
    info.setName(m_name->text());
    info.setCategoryID(m_categoriesList->currentData().toInt());
    emit editInfo(info);
}

void blFinderAdminKeywordEdit::emitRemove(){
    int reponse = QMessageBox::question(this, tr("Delete keyword"), tr("Delete this keyword ?"), QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        emit remove(m_id);
    }
}
