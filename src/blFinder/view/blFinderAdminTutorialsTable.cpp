#include "blFinderAdminTutorialsTable.h"
#include "../blWidgets/blButtonId.h"

blFinderAdminTutorialsTable::blFinderAdminTutorialsTable(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);

    QLabel* title = new QLabel(tr("Tutorials"));
    title->setObjectName("blFinderAdminTableTitle");
    layout->addWidget(title);
    m_tableWidget = new QTableWidget;
    layout->addWidget(m_tableWidget);

}

void blFinderAdminTutorialsTable::fillTable(QList<blFinderTutorialInfo> tutorialsInfo){

    //m_tableWidget->horizontalHeader()->setStretchLastSection( true );

    QStringList tableHeader;
    tableHeader.append("ID");
    tableHeader.append("Title");
    tableHeader.append("");

    m_tableWidget->setRowCount(tutorialsInfo.count());
    m_tableWidget->setColumnCount(3);
    m_tableWidget->setHorizontalHeaderLabels(tableHeader);
    m_tableWidget->verticalHeader()->setVisible(false);

    for(int i = 0 ; i < tutorialsInfo.count() ; ++i){
        blFinderTutorialInfo info = tutorialsInfo[i];
        m_tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(info.id())));
        m_tableWidget->setItem(i, 1, new QTableWidgetItem(info.title()));

        blButtonId *button = new blButtonId(tr("Edit"), this);
        button->setMaximumWidth(75);
        button->setObjectName("btnPrimary");
        button->setId(info.id());

        QWidget *btnW = new QWidget(this);
        QHBoxLayout *btnLayout = new QHBoxLayout;
        btnLayout->setContentsMargins(0,0,0,0);
        btnW->setLayout(btnLayout);
        btnLayout->addWidget(button);
        connect(button, SIGNAL(clicked(int)), this, SIGNAL(edit(int)));

        m_tableWidget->setCellWidget(i, 2, btnW);
    }
}
