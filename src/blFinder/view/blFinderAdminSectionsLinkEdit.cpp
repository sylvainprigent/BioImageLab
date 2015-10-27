#include "blFinderAdminSectionsLinkEdit.h"

blFinderAdminSectionsLinkEdit::blFinderAdminSectionsLinkEdit(QList<blFinderSectionInfo> sections, QWidget *parent)
    : QWidget(parent){

    m_id = 0;

    QGridLayout *layout = new QGridLayout;
    this->setLayout(layout);

    // title
    QLabel *title = new QLabel(tr("Add sections link"), this);
    layout->addWidget(title, 0, 0, 1, 5);
    title->setObjectName("blFinderAdminTableTitle");

    // parent
    QLabel *parentLabel = new QLabel(tr("Parent"), this);
    m_parentSectionsList = new QComboBox(this);
    layout->addWidget(parentLabel, 1,0,1,4);
    layout->addWidget(m_parentSectionsList, 1,1,1,4);
    for(int i = 0 ; i < sections.count() ; ++i){
        blFinderSectionInfo cat = sections[i];
        m_parentSectionsList->addItem(cat.name(), cat.id());
    }

    // child
    QLabel *childLabel = new QLabel(tr("Child"), this);
    m_childSectionsList = new QComboBox(this);
    layout->addWidget(childLabel, 2,0,1,4);
    layout->addWidget(m_childSectionsList, 2,1,1,4);
    for(int i = 0 ; i < sections.count() ; ++i){
        blFinderSectionInfo cat = sections[i];
        m_childSectionsList->addItem(cat.name(), cat.id());
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

void blFinderAdminSectionsLinkEdit::emitEditInfo(){
    blFinderSectionsLinkInfo info;
    info.setParentID(m_parentSectionsList->currentData().toInt());
    info.setChildID(m_childSectionsList->currentData().toInt());
    emit editInfo(info);
}
