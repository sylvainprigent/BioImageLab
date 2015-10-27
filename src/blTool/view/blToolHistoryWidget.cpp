#include "blToolHistoryWidget.h"
#include "../blWidgets/blhideableWidget.h"
#include "blToolHistoryWidgetList.h"

blToolHistoryWidget::blToolHistoryWidget(QString historyFile, QWidget *parent) : QWidget(parent)
{

    m_history.load(historyFile);

    // layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);

    QScrollArea *scroll = new QScrollArea(this);
    scroll->setObjectName("blToolHistoryWidget");
    scroll->setWidgetResizable(true);
    QWidget *globalWidget = new QWidget(this);
    globalWidget->setObjectName("blToolHistoryWidget");
    QVBoxLayout *globalLayout = new QVBoxLayout;
    globalLayout->setContentsMargins(0,0,0,0);
    globalLayout->addWidget(scroll);
    globalWidget->setLayout(layout);
    scroll->setWidget(globalWidget);
    this->setLayout(globalLayout);

    // add tool info
    layout->addWidget(toolTable(m_history.toolInfo()), 0, Qt::AlignTop);

    // add parameters
    layout->addWidget(parametersTable(m_history.parameters()), 0, Qt::AlignTop);

    // add inputs
    layout->addWidget(ioTable(tr("Inputs"), m_history.inputData(), true), 0, Qt::AlignTop);

    // add outputs
    layout->addWidget(ioTable(tr("Outputs"), m_history.outputData(), false), 0, Qt::AlignTop);

    // fill widget
    layout->addWidget(new QWidget(this), 1, Qt::AlignTop);

}

QWidget* blToolHistoryWidget::toolTable(blToolInfo* toolInfo){
    blHideableWidget* hideWidget = new blHideableWidget(tr("Tool"), 2, this);

    QTableWidget *toolTable = new QTableWidget(this);
    toolTable->verticalHeader()->setVisible(false);
    toolTable->horizontalHeader()->setStretchLastSection( true );
    //toolTable->setEditTriggers(QAbstractItemView::EditTriggers(0));
    QStringList tableHeader;
    tableHeader.append("Info");
    tableHeader.append("Value");
    toolTable->setRowCount(3);
    toolTable->setColumnCount(2);
    toolTable->setHorizontalHeaderLabels(tableHeader);
    toolTable->setItem(0, 0, new QTableWidgetItem(tr("Name")));
    toolTable->setItem(0, 1, new QTableWidgetItem(toolInfo->name()));
    toolTable->setItem(1, 0, new QTableWidgetItem(tr("Description")));
    toolTable->setItem(1, 1, new QTableWidgetItem(toolInfo->description()));
    toolTable->setItem(2, 0, new QTableWidgetItem(tr("Command")));
    toolTable->setItem(2, 1, new QTableWidgetItem(toolInfo->command()));
    toolTable->setFixedHeight((5)*30);
    hideWidget->addWidget(toolTable);
    return hideWidget;
}

QWidget* blToolHistoryWidget::parametersTable(blioParameters* parameters){

    if (parameters->count() > 0){
        blHideableWidget* hideWidget = new blHideableWidget(tr("Parameters"), 2,  this);

        QTableWidget *toolTable = new QTableWidget(this);
        toolTable->verticalHeader()->setVisible(false);
        toolTable->horizontalHeader()->setStretchLastSection( true );
        toolTable->setEditTriggers(QAbstractItemView::EditTriggers(0));
        QStringList tableHeader;
        tableHeader.append("Key");
        tableHeader.append("Value");
        toolTable->setRowCount(parameters->count());
        toolTable->setColumnCount(2);
        toolTable->setHorizontalHeaderLabels(tableHeader);
        for(unsigned int i = 0 ; i < parameters->count() ; ++i){
            toolTable->setItem(i, 0, new QTableWidgetItem(parameters->keyAt(i)));
            toolTable->setItem(i, 1, new QTableWidgetItem(parameters->valueAt(i)));
        }

        if (parameters->count() <= 10){
            toolTable->setFixedHeight((parameters->count()+1)*30);
        }
        else{
            toolTable->setFixedHeight((10+1)*30);
        }
        hideWidget->addWidget(toolTable);
        return hideWidget;
    }
    return NULL;
}

QWidget* blToolHistoryWidget::ioTable(QString title, blioDataInfo* data, bool isInput){

    QString desc = "Output: ";
    if(isInput){
        desc = "Input: ";
    }
    if (data->count() == 1){
        blHideableWidget* hideWidget = new blHideableWidget(title, 2, this);
        QTableWidget *toolTable = new QTableWidget(this);
        toolTable->verticalHeader()->setVisible(false);
        toolTable->horizontalHeader()->setStretchLastSection( true );
        toolTable->setEditTriggers(QAbstractItemView::EditTriggers(0));
        QStringList tableHeader;
        tableHeader.append("Key");
        tableHeader.append("Data type");
        tableHeader.append("Value");
        toolTable->setRowCount(data->at(0).count());
        toolTable->setColumnCount(3);
        toolTable->setHorizontalHeaderLabels(tableHeader);
        for(unsigned int j = 0 ; j < data->at(0).count() ; ++j){
            toolTable->setItem(j, 0, new QTableWidgetItem(data->at(0).idAt(j)));
            toolTable->setItem(j, 1, new QTableWidgetItem(data->at(0).datatypeAt(j)));
            blToolHistoryWidgetList *w = new blToolHistoryWidgetList(data->at(0).datatypeAt(j),
                                                                     data->at(0).urlAt(j),
                                                                     desc + data->at(0).idAt(j),
                                                                     this);
            w->setObjectName("blTableButton");
            connect(w, SIGNAL(clicked(QString,QString,QString)), this, SIGNAL(openData(QString, QString, QString)));
            toolTable->setCellWidget(j,2,w);
        }
        toolTable->verticalHeader()->setStretchLastSection(false);
        toolTable->setFixedHeight((data->at(0).count()+1)*30);
        hideWidget->addWidget(toolTable);
        return hideWidget;
    }
    else if (data->count() > 1){

        blHideableWidget* hideWidget = new blHideableWidget(title, 2, this);
        for (unsigned int i = 0 ; i < data->count() ; ++i){

            blHideableWidget* hideWidget2 = new blHideableWidget("data " + QString::number(i), 3, this);
            QTableWidget *toolTable = new QTableWidget(this);
            toolTable->verticalHeader()->setVisible(false);
            toolTable->horizontalHeader()->setStretchLastSection( true );
            QStringList tableHeader;
            tableHeader.append("Key");
            tableHeader.append("Data type");
            tableHeader.append("Value");
            toolTable->setRowCount(data->at(i).count());
            toolTable->setColumnCount(3);
            toolTable->setHorizontalHeaderLabels(tableHeader);
            for(unsigned int j = 0 ; j < data->at(i).count() ; ++j){
                toolTable->setItem(j, 0, new QTableWidgetItem(data->at(i).idAt(j)));
                toolTable->setItem(j, 1, new QTableWidgetItem(data->at(i).datatypeAt(j)));
                blToolHistoryWidgetList *w = new blToolHistoryWidgetList(data->at(i).datatypeAt(j),
                                                                         data->at(i).urlAt(j),
                                                                         desc + data->at(0).idAt(j),
                                                                         this);
                w->setObjectName("blTableButton");
                connect(w, SIGNAL(clicked(QString,QString,QString)), this, SIGNAL(openData(QString, QString,QString)));
                toolTable->setCellWidget(j,2,w);
            }
            toolTable->setFixedHeight((data->at(i).count()+1)*30);
            hideWidget2->addWidget(toolTable);
            hideWidget->addWidget(hideWidget2);
        }
        return hideWidget;
    }
    return NULL;
}
