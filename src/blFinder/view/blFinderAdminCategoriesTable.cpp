#include "blFinderAdminCategoriesTable.h"
#include "../blWidgets/blButtonId.h"

blFinderAdminCategoriesTable::blFinderAdminCategoriesTable(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);

    QLabel* title = new QLabel(tr("Categories"));
    title->setObjectName("blFinderAdminTableTitle");
    layout->addWidget(title);
    m_tableWidget = new QTableWidget;
    layout->addWidget(m_tableWidget);

}

void blFinderAdminCategoriesTable::fillTable(QList<blFinderCategoryInfo> categoryInfo){

    //m_tableWidget->horizontalHeader()->setStretchLastSection( true );

    QStringList tableHeader;
    tableHeader.append("ID");
    tableHeader.append("Name");
    tableHeader.append("");

    m_tableWidget->setRowCount(categoryInfo.count());
    m_tableWidget->setColumnCount(3);
    m_tableWidget->setHorizontalHeaderLabels(tableHeader);
    m_tableWidget->verticalHeader()->setVisible(false);

    for(int i = 0 ; i < categoryInfo.count() ; ++i){
        blFinderCategoryInfo info = categoryInfo[i];
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
