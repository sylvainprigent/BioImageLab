#include "blFinderAdminAuthorEdit.h"

blFinderAdminAuthorEdit::blFinderAdminAuthorEdit(QWidget *parent)
    : QWidget(parent){

    m_id = 0;

    QGridLayout *layout = new QGridLayout;
    this->setLayout(layout);

    // title
    QLabel *title = new QLabel(tr("Edit author"), this);
    layout->addWidget(title, 0, 0, 1, 4);
    title->setObjectName("blFinderAdminTableTitle");

    // name
    QLabel *nameLabel = new QLabel(tr("Name"), this);
    m_name = new QLineEdit(this);
    layout->addWidget(nameLabel, 1,0,1,4);
    layout->addWidget(m_name, 1,1,1,4);

    // firstname
    QLabel *firstnameLabel = new QLabel(tr("Firstname"), this);
    m_firstname = new QLineEdit(this);
    layout->addWidget(firstnameLabel, 2,0,1,4);
    layout->addWidget(m_firstname, 2,1,1,4);

    // buttons
    QPushButton *save = new QPushButton(tr("Save"), this);
    save->setObjectName("btnPrimary");
    QPushButton *cancel = new QPushButton(tr("Cancel"), this);
    cancel->setObjectName("btnDefault");
    m_deleteButton = new QPushButton(tr("Delete"), this);
    m_deleteButton->setObjectName("btnDanger");
    m_deleteButton->setVisible(false);
    layout->addWidget(save, 3, 2, 1, 1);
    layout->addWidget(cancel, 3, 3, 1, 1);
    layout->addWidget(m_deleteButton, 3, 4, 1, 1);

    connect(save, SIGNAL(pressed()), this, SLOT(emitEditInfo()));
    connect(cancel, SIGNAL(pressed()), this, SIGNAL(cancel()));
    connect(m_deleteButton, SIGNAL(pressed()), this, SLOT(emitDelete()));
}

void blFinderAdminAuthorEdit::setInfo(blFinderAuthorInfo info){
    m_id = info.id();
    m_name->setText(info.name());
    m_firstname->setText(info.firstname());
    m_deleteButton->setVisible(true);
}

void blFinderAdminAuthorEdit::emitEditInfo(){
    blFinderAuthorInfo info;
    info.setID(m_id);
    info.setName(m_name->text());
    info.setFirstname(m_firstname->text());
    emit editInfo(info);
}

void blFinderAdminAuthorEdit::emitDelete(){
    int reponse = QMessageBox::question(this, tr("Delete author"), tr("Delete this author ?"), QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        emit remove(m_id);
    }
}
