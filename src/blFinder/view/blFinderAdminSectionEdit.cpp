#include "blFinderAdminSectionEdit.h"

blFinderAdminSectionEdit::blFinderAdminSectionEdit(QWidget *parent)
    : QWidget(parent){

    m_id = 0;

    QGridLayout *layout = new QGridLayout;
    this->setLayout(layout);

    // title
    QLabel *title = new QLabel(tr("Edit Section"), this);
    layout->addWidget(title, 0, 0, 1, 5);
    title->setObjectName("blFinderAdminTableTitle");

    // name
    QLabel *nameLabel = new QLabel(tr("Name"), this);
    m_name = new QLineEdit(this);
    layout->addWidget(nameLabel, 1,0,1,4);
    layout->addWidget(m_name, 1,1,1,4);

    // description
    QLabel *descLabel = new QLabel(tr("Description"), this);
    m_description = new QLineEdit(this);
    layout->addWidget(descLabel, 2,0,1,4);
    layout->addWidget(m_description, 2,1,1,4);

    // image URL
    QLabel *imLabel = new QLabel(tr("Image URL"), this);
    m_imageUrl = new QLineEdit(this);
    layout->addWidget(imLabel, 3,0,1,4);
    layout->addWidget(m_imageUrl, 3,1,1,4);

    // image URL
    QLabel *childLabel = new QLabel(tr("Child title"), this);
    m_childrenTitle = new QLineEdit(this);
    layout->addWidget(childLabel, 4,0,1,4);
    layout->addWidget(m_childrenTitle, 4,1,1,4);

    // image URL
    QLabel *orderLabel = new QLabel(tr("Display order"), this);
    m_displayOrder = new QLineEdit(this);
    layout->addWidget(orderLabel, 5,0,1,4);
    layout->addWidget(m_displayOrder, 5,1,1,4);

    // buttons
    QPushButton *save = new QPushButton(tr("Save"), this);
    save->setObjectName("btnPrimary");
    QPushButton *cancel = new QPushButton(tr("Cancel"), this);
    cancel->setObjectName("btnDefault");
    m_removeButton = new QPushButton(tr("Delete"), this);
    m_removeButton->setObjectName("btnDanger");
    m_removeButton->setVisible(false);

    layout->addWidget(save, 6, 2, 1, 1);
    layout->addWidget(cancel, 6, 3, 1, 1);
    layout->addWidget(m_removeButton, 6, 4, 1, 1);

    connect(save, SIGNAL(pressed()), this, SLOT(emitEditInfo()));
    connect(cancel, SIGNAL(pressed()), this, SIGNAL(cancel()));
    connect(m_removeButton, SIGNAL(pressed()), this, SLOT(emitRemove()));
}

void blFinderAdminSectionEdit::setInfo(blFinderSectionInfo info){
    m_id = info.id();
    m_name->setText(info.name());
    m_description->setText(info.description());
    m_imageUrl->setText(info.imageUrl());
    m_childrenTitle->setText(info.childrenTitle());
    m_displayOrder->setText(QString::number(info.displayOrder()));

    m_removeButton->setVisible(true);
}

void blFinderAdminSectionEdit::emitEditInfo(){
    blFinderSectionInfo info;
    info.setID(m_id);
    info.setName(m_name->text());
    info.setDescription(m_description->text());
    info.setImageUrl(m_imageUrl->text());
    info.setChildrenTitle(m_childrenTitle->text());
    info.setDisplayOrder(m_displayOrder->text().toInt());
    emit editInfo(info);
}

void blFinderAdminSectionEdit::emitRemove(){
    int reponse = QMessageBox::question(this, tr("Delete section"), tr("Delete this section ?"), QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        emit remove(m_id);
    }
}
