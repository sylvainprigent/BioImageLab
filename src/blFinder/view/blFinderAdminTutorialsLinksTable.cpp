#include "blFinderAdminTutorialsLinksTable.h"
#include "../blWidgets/blButtonId2.h"

blFinderAdminTutorialsLinksTable::blFinderAdminTutorialsLinksTable(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);

    QLabel* title = new QLabel(tr("Tutorials Links"));
    title->setObjectName("blFinderAdminTableTitle");
    layout->addWidget(title);
    m_tableWidget = new QTableWidget;
    layout->addWidget(m_tableWidget);

}

void blFinderAdminTutorialsLinksTable::fillTable(QList<blFinderTutorialsLinkInfo> tutorialsLinkInfo){

    m_tableWidget->horizontalHeader()->setStretchLastSection( true );

    QStringList tableHeader;
    tableHeader.append("Tutorial");
    tableHeader.append("Category");
    tableHeader.append("");

    m_tableWidget->setRowCount(tutorialsLinkInfo.count());
    m_tableWidget->setColumnCount(3);
    m_tableWidget->setHorizontalHeaderLabels(tableHeader);
    m_tableWidget->verticalHeader()->setVisible(false);

    for(int i = 0 ; i < tutorialsLinkInfo.count() ; ++i){
        blFinderTutorialsLinkInfo info = tutorialsLinkInfo[i];
        m_tableWidget->setItem(i, 0, new QTableWidgetItem(info.tutorialName()));
        m_tableWidget->setItem(i, 1, new QTableWidgetItem(info.categoryName()));

        blButtonId2 *button = new blButtonId2(tr("Delete"), this);
        button->setMaximumWidth(75);
        button->setObjectName("btnDanger");
        button->setId1(info.tutorialID());
        button->setId2(info.categoryID());
        connect(button, SIGNAL(clicked(int, int)), this, SLOT(emitRemove(int, int)));

        QWidget *btnW = new QWidget(this);
        QHBoxLayout *btnLayout = new QHBoxLayout;
        btnLayout->setContentsMargins(0,0,0,0);
        btnW->setLayout(btnLayout);
        btnLayout->addWidget(button);

        m_tableWidget->setCellWidget(i, 2, btnW);
    }
}

void blFinderAdminTutorialsLinksTable::emitRemove(int id1, int id2){
    int reponse = QMessageBox::question(this, tr("Delete link"), tr("Delete this link ?"), QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        emit removeLink(id1, id2);
    }
}
