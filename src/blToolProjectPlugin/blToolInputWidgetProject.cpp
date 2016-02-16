#include "blToolInputWidgetProject.h"

blToolInputWidgetProject::blToolInputWidgetProject(QWidget *parent)
    : blToolInputWidget(parent){

    QPushButton *button = new QPushButton(tr("Select"), this);
    button->setObjectName("btnDefault");
    m_layout->insertWidget(0,button);

    this->connect(button, SIGNAL(pressed()), this, SLOT(browse()));
    this->createBrowserWidget();
}

void blToolInputWidgetProject::createBrowserWidget(){

    m_browser = new QWidget;
    QGridLayout *layout = new QGridLayout;
    m_browser->setLayout(layout);

    m_columnBox = new QComboBox;
    connect(m_columnBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeSubColumns(QString)));
    m_subColumnBox = new QComboBox;

    layout->addWidget(new QLabel(tr("Column"), this), 0, 0, 1, 1);
    layout->addWidget(m_columnBox, 0, 1, 1, 1);

    layout->addWidget(new QLabel(tr("Sub column"), this), 1, 0, 1, 1);
    layout->addWidget(m_subColumnBox, 1, 1, 1, 1);

    QPushButton *seeButton = new QPushButton(tr("See"), this);
    connect(seeButton, SIGNAL(released()), this, SLOT(seeSelection()));
    seeButton->setObjectName("btnDefault");
    layout->addWidget(seeButton, 2, 0, 1, 1);

    m_tableWidget = new QTableWidget(this);
    m_tableWidget->setVisible(false);
    //m_tableWidget->verticalHeader()->setVisible(false);
    layout->addWidget(m_tableWidget, 3, 0, 1, 3);

    QPushButton *okButton = new QPushButton(tr("Ok"), this);
    okButton->setObjectName("btnPrimary");
    QPushButton *cancelButton = new QPushButton(tr("Cancel"), this);
    cancelButton->setObjectName("btnDefault");
    connect(okButton, SIGNAL(released()), this, SLOT(hideBrowser()));
    connect(cancelButton, SIGNAL(released()), this, SLOT(hideBrowser()));
    layout->addWidget(okButton, 4, 1, 1, 1);
    layout->addWidget(cancelButton, 4, 2, 1, 1);
}

void blToolInputWidgetProject::browse(){
    m_browser->setVisible(true);
}

void blToolInputWidgetProject::hideBrowser(){
    m_browser->setVisible(false);
}

void blToolInputWidgetProject::setProject(blProjectModel* projectModel){
    m_projectModel = projectModel;

    m_columnBox->clear();
    m_columnBox->addItems(m_projectModel->mainColumnsName());
    m_tableWidget->setVisible(false);
}

void blToolInputWidgetProject::changeSubColumns(QString mainColumnName){

    m_subColumnBox->clear();
    m_subColumnBox->addItems(m_projectModel->columnsName(mainColumnName));
}

void blToolInputWidgetProject::seeSelection(){
    QList<QStringList> dataList = blToolInputWidgetProject::getData();

    int row = -1;
    m_tableWidget->setColumnCount(1);
    for(int i = 0;  i < dataList.count();  ++i)
    {
        row++;
        m_tableWidget->setRowCount(row+1);
        m_tableWidget->setItem(row,0, new QTableWidgetItem(dataList[i][1]));
    }
    m_tableWidget->setVisible(true);
}

QList<QStringList> blToolInputWidgetProject::getData(){

    QList<QStringList> dataList;

    blProjectModelColumn column = m_projectModel->columnData(m_columnBox->currentText(), m_subColumnBox->currentText());
    QMap<unsigned int, QString> map = column.data();
    QMap<unsigned int, QString>::Iterator it;
    m_tableWidget->clear();
    m_tableWidget->setColumnCount(1);
    for( it = map.begin();  it != map.end();  ++it)
    {
        QStringList inter;
        inter.append(QString(it.key()));
        inter.append(it.value());
        dataList.append(inter);
    }
    return dataList;

}
