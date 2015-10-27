#include "blToolHistoryWidgetList.h"

blToolHistoryWidgetList::blToolHistoryWidgetList(QString datatype, QString text, QString desc, QWidget *parent)
    :QWidget(parent){


    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    QLabel *label = new QLabel(text, this);
    QPushButton *button = new QPushButton(tr("Open"), this);
    button->setObjectName("btnDefault");

    layout->addWidget(label, 1, Qt::AlignLeft);
    layout->addWidget(button, 0, Qt::AlignRight);

    m_text = text;
    m_description = desc;
    m_datatype = datatype;
    connect(button, SIGNAL(pressed()), this, SLOT(emitClicked()));
}

void blToolHistoryWidgetList::emitClicked(){
    emit clicked(m_datatype, m_text, m_description);
    //qDebug() << "emit: " << m_text << ", " << m_description;
}

