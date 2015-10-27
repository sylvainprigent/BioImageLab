#include "blFinderAdminOriginsTable.h"
#include "../blWidgets/blButtonId.h"

blFinderAdminOriginsTable::blFinderAdminOriginsTable(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);

    QLabel* title = new QLabel(tr("Origins"));
    title->setObjectName("blFinderAdminTableTitle");
    layout->addWidget(title);
    m_tableWidget = new QTableWidget;
    layout->addWidget(m_tableWidget);

}

void blFinderAdminOriginsTable::fillTable(QList<blFinderOriginInfo> OriginInfo){

    //m_tableWidget->horizontalHeader()->setStretchLastSection( true );

    QStringList tableHeader;
    tableHeader.append("ID");
    tableHeader.append("Name");
    tableHeader.append("");

    m_tableWidget->setRowCount(OriginInfo.count());
    m_tableWidget->setColumnCount(3);
    m_tableWidget->setHorizontalHeaderLabels(tableHeader);
    m_tableWidget->verticalHeader()->setVisible(false);

    for(int i = 0 ; i < OriginInfo.count() ; ++i){
        blFinderOriginInfo info = OriginInfo[i];
        m_tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(info.id())));
        m_tableWidget->setItem(i, 1, new QTableWidgetItem(info.name()));

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

        m_tableWidget->setCellWidget(i, 2, btnW);
    }
}
