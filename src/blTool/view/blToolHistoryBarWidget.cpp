#include "blToolHistoryBarWidget.h"

blToolHistoryBarWidget::blToolHistoryBarWidget(blToolHistoryInfo history, QWidget *parent) : QWidget(parent)
{
    m_history = history;
    QGridLayout *layout = new QGridLayout;
    layout->setContentsMargins(3,3,3,3);
    layout->setVerticalSpacing(5);
    layout->setHorizontalSpacing(0);

    // description
    QLabel *titleLabel = new QLabel(this);
    titleLabel->setText(m_history.toolName() + "<br/>" + m_history.lastModified());
    layout->addWidget(titleLabel, 0, 0, 2, 1);

    // buttons
    QPushButton *viewButton = new QPushButton(this);
    viewButton->setObjectName("blToolHistoryBarWidgetViewButton");
    QPushButton *deleteButton = new QPushButton(this);
    deleteButton->setObjectName("blToolHistoryBarWidgetDeleteButton");
    viewButton->setFixedSize(26,26);
    deleteButton->setFixedSize(26,26);
    layout->addWidget(viewButton, 0, 1, 1, 1);
    layout->addWidget(deleteButton, 0, 2, 1, 1);

    QWidget *under = new QWidget(this);
    under->setObjectName("blToolHistoryBarWidgetUnder");
    under->setFixedWidth(100);
    layout->addWidget(under, 1, 0, 1, 3, Qt::AlignHCenter);

    // container
    QWidget *container = new QWidget;
    container->setObjectName("blToolHistoryBarWidget");
    QHBoxLayout *containerLayout = new QHBoxLayout;
    containerLayout->setContentsMargins(0,0,0,0);
    containerLayout->addWidget(container);
    container->setLayout(layout);
    this->setLayout(containerLayout);

    // actions
    connect(viewButton, SIGNAL(pressed()), this, SLOT(askOpenHistory()));
    connect(deleteButton, SIGNAL(pressed()), this, SLOT(askDeleteHistory()));
}

int blToolHistoryBarWidget::id(){
    return m_history.id();
}

void blToolHistoryBarWidget::askOpenHistory(){
    emit openHistory(m_history);
    emit openHistory(m_history.fileUrl());
}

void blToolHistoryBarWidget::askDeleteHistory(){
    int reponse = QMessageBox::question(this, tr("Delete history"), tr("This will delete the history and all the data associated"), QMessageBox ::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes)
    {
        emit deleteHistory(m_history);
        emit deleteHistory(m_history.fileUrl());
        emit deleteHistory(m_history.id());
    }
}
