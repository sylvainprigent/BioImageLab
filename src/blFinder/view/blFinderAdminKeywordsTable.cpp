#include "blFinderAdminKeywordsTable.h"
#include "../blWidgets/blButtonId.h"


blFinderAdminKeywordsTable::blFinderAdminKeywordsTable(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);

    QLabel* title = new QLabel(tr("Keywords"));
    title->setObjectName("blFinderAdminTableTitle");
    layout->addWidget(title);
    m_tableWidget = new QTableWidget;
    layout->addWidget(m_tableWidget);

}

void blFinderAdminKeywordsTable::fillTable(QList<blFinderKeywordInfo> keywordInfo){

    //m_tableWidget->horizontalHeader()->setStretchLastSection( true );

    QStringList tableHeader;
    tableHeader.append("ID");
    tableHeader.append("Name");
    tableHeader.append("");
    tableHeader.append("");

    m_tableWidget->setRowCount(keywordInfo.count());
    m_tableWidget->setColumnCount(4);
    m_tableWidget->setHorizontalHeaderLabels(tableHeader);
    m_tableWidget->verticalHeader()->setVisible(false);

    for(int i = 0 ; i < keywordInfo.count() ; ++i){
        blFinderKeywordInfo info = keywordInfo[i];
        m_tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(info.id())));
        m_tableWidget->setItem(i, 1, new QTableWidgetItem(info.name()));
        m_tableWidget->setItem(i, 2, new QTableWidgetItem(info.categoryName()));

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

        m_tableWidget->setCellWidget(i, 3, btnW);
    }
}
