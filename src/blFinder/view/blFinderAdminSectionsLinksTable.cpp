#include "blFinderAdminSectionsLinksTable.h"
#include "../blWidgets/blButtonId2.h"

blFinderAdminSectionsLinksTable::blFinderAdminSectionsLinksTable(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);

    QLabel* title = new QLabel(tr("Sections Links"));
    title->setObjectName("blFinderAdminTableTitle");
    layout->addWidget(title);
    m_tableWidget = new QTableWidget;
    layout->addWidget(m_tableWidget);

}

void blFinderAdminSectionsLinksTable::fillTable(QList<blFinderSectionsLinkInfo> sectionLinkInfo){

    m_tableWidget->horizontalHeader()->setStretchLastSection( true );

    QStringList tableHeader;
    tableHeader.append("Parent");
    tableHeader.append("Child");
    tableHeader.append("");

    m_tableWidget->setRowCount(sectionLinkInfo.count());
    m_tableWidget->setColumnCount(3);
    m_tableWidget->setHorizontalHeaderLabels(tableHeader);
    m_tableWidget->verticalHeader()->setVisible(false);

    for(int i = 0 ; i < sectionLinkInfo.count() ; ++i){
        blFinderSectionsLinkInfo info = sectionLinkInfo[i];
        m_tableWidget->setItem(i, 0, new QTableWidgetItem(info.parentName()));
        m_tableWidget->setItem(i, 1, new QTableWidgetItem(info.childName()));

        blButtonId2 *button = new blButtonId2(tr("Delete"), this);
        button->setMaximumWidth(75);
        button->setObjectName("btnDanger");
        button->setId1(info.parentID());
        button->setId2(info.childID());
        connect(button, SIGNAL(clicked(int, int)), this, SLOT(emitRemove(int, int)));

        QWidget *btnW = new QWidget(this);
        QHBoxLayout *btnLayout = new QHBoxLayout;
        btnLayout->setContentsMargins(0,0,0,0);
        btnW->setLayout(btnLayout);
        btnLayout->addWidget(button);

        m_tableWidget->setCellWidget(i, 2, btnW);
    }
}

void blFinderAdminSectionsLinksTable::emitRemove(int id1, int id2){
    int reponse = QMessageBox::question(this, tr("Delete link"), tr("Delete this link ?"), QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        emit removeLink(id1, id2);
    }

}
