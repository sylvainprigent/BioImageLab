#include "blButtonId.h"

blButtonId::blButtonId(QString title, QWidget *parent)
    :QPushButton(title, parent){

    connect(this, SIGNAL(pressed()), this, SLOT(emitClicked()));
}

int blButtonId::id(){
    return m_id;
}

void blButtonId::setId(int id){
    m_id = id;
}

void blButtonId::emitClicked(){
    emit clicked(m_id);
}
