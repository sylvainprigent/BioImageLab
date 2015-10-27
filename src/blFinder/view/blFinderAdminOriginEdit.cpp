#include "blFinderAdminOriginEdit.h"

blFinderAdminOriginEdit::blFinderAdminOriginEdit(QWidget *parent)
    : QWidget(parent){

    m_id = 0;

    QGridLayout *layout = new QGridLayout;
    this->setLayout(layout);

    // title
    QLabel *title = new QLabel(tr("Edit Origin"), this);
    layout->addWidget(title, 0, 0, 1, 5);
    title->setObjectName("blFinderAdminTableTitle");

    // name
    QLabel *nameLabel = new QLabel(tr("Name"), this);
    m_name = new QLineEdit(this);
    layout->addWidget(nameLabel, 1,0,1,4);
    layout->addWidget(m_name, 1,1,1,4);

    // buttons
    QPushButton *save = new QPushButton(tr("Save"), this);
    save->setObjectName("btnPrimary");
    QPushButton *cancel = new QPushButton(tr("Cancel"), this);
    cancel->setObjectName("btnDefault");
    m_removeButton = new QPushButton(tr("Delete"), this);
    m_removeButton->setObjectName("btnDanger");
    m_removeButton->setVisible(false);

    layout->addWidget(save, 2, 2, 1, 1);
    layout->addWidget(cancel, 2, 3, 1, 1);
    layout->addWidget(m_removeButton, 2, 4, 1, 1);

    connect(save, SIGNAL(pressed()), this, SLOT(emitEditInfo()));
    connect(cancel, SIGNAL(pressed()), this, SIGNAL(cancel()));
    connect(m_removeButton, SIGNAL(pressed()), this, SLOT(emitRemove()));
}

void blFinderAdminOriginEdit::setInfo(blFinderOriginInfo info){
    m_id = info.id();
    m_name->setText(info.name());
    m_removeButton->setVisible(true);
}

void blFinderAdminOriginEdit::emitEditInfo(){
    blFinderOriginInfo info;
    info.setID(m_id);
    info.setName(m_name->text());
    emit editInfo(info);
}

void blFinderAdminOriginEdit::emitRemove(){
    int reponse = QMessageBox::question(this, tr("Delete Origin"), tr("Delete this Origin ?"), QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        emit remove(m_id);
    }
}
