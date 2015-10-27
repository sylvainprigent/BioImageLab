#include "blFinderAdminSectionsTable.h"
#include "../blWidgets/blButtonId.h"

blFinderAdminSectionsTable::blFinderAdminSectionsTable(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);

    QLabel* title = new QLabel(tr("Finder sections"));
    title->setObjectName("blFinderAdminTableTitle");
    layout->addWidget(title);
    m_tableWidget = new QTableWidget;
    layout->addWidget(m_tableWidget);

}

void blFinderAdminSectionsTable::fillTable(QList<blFinderSectionInfo> sectionInfo){

    m_tableWidget->horizontalHeader()->setStretchLastSection( true );

    QStringList tableHeader;
    tableHeader.append("ID");
    tableHeader.append("Name");
    tableHeader.append("Description");
    tableHeader.append("Image URL");
    tableHeader.append("Children title");
    tableHeader.append("Display order");
    tableHeader.append("");

    m_tableWidget->setRowCount(sectionInfo.count());
    m_tableWidget->setColumnCount(7);
    m_tableWidget->setHorizontalHeaderLabels(tableHeader);
    m_tableWidget->verticalHeader()->setVisible(false);

    for(int i = 0 ; i < sectionInfo.count() ; ++i){
        blFinderSectionInfo info = sectionInfo[i];
        m_tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(info.id())));
        m_tableWidget->setItem(i, 1, new QTableWidgetItem(info.name()));
        m_tableWidget->setItem(i, 2, new QTableWidgetItem(info.description()));
        m_tableWidget->setItem(i, 3, new QTableWidgetItem(info.imageUrl()));
        m_tableWidget->setItem(i, 4, new QTableWidgetItem(info.childrenTitle()));
        m_tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(info.displayOrder())));

        blButtonId *button = new blButtonId(tr("Edit"), this);
        button->setMaximumWidth(75);
        button->setObjectName("btnPrimary");
        button->setId(info.id());
        connect(button, SIGNAL(clicked(int)), this, SIGNAL(edit(int)));

        QWidget *btnW = new QWidget(this);
        QHBoxLayout *btnLayout = new QHBoxLayout;
        btnLayout->setContentsMargins(0,0,0,0);
        btnW->setLayout(btnLayout);
        btnLayout->addWidget(button);

        m_tableWidget->setCellWidget(i, 6, btnW);
    }
}
