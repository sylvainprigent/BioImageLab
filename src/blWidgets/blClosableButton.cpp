#include "blClosableButton.h"

blClosableButton::blClosableButton(bool closable, QWidget *parent)
    :QPushButton(parent){

/*
    QVBoxLayout *tlayout = new QVBoxLayout;
    tlayout->setContentsMargins(0,0,0,0);
    m_button = new QPushButton(this);
    tlayout->addWidget(m_button);
    m_button->setCheckable(true);
    this->setLayout(tlayout);
    */


    if (closable){
        QVBoxLayout *layout = new QVBoxLayout;
        layout->setContentsMargins(0,0,0,0);
        QPushButton *closeButton = new QPushButton(this);
        closeButton->setObjectName("blCloseButton");
        closeButton->setFixedSize(12,12);
        layout->addWidget(closeButton, 1, Qt::AlignTop | Qt::AlignRight);
        this->setLayout(layout);
        connect(closeButton, SIGNAL(pressed()), this, SLOT(emitClosed()));
    }

    connect(this, SIGNAL(pressed()), this, SLOT(emitClicked()));
}

int blClosableButton::id(){
    return m_id;
}

void blClosableButton::setId(int id){
    m_id = id;
}

void blClosableButton::emitClicked(){
    emit clicked(m_id);
}

void blClosableButton::emitClosed(){
    emit closed(m_id);
}

/*
void blClosableButton::setChecked(bool value){
    m_button->setChecked(value);
}

QPushButton *blClosableButton::button(){
    return m_button;
}
*/
