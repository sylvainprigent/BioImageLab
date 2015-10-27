#include "blButtonId2.h"

blButtonId2::blButtonId2(QString title, QWidget *parent)
    :QPushButton(title, parent){

    connect(this, SIGNAL(pressed()), this, SLOT(emitClicked()));
}

int blButtonId2::id1(){
    return m_id1;
}

int blButtonId2::id2(){
    return m_id2;
}

void blButtonId2::setId1(int id){
    m_id1 = id;
}

void blButtonId2::setId2(int id){
    m_id2 = id;
}


void blButtonId2::emitClicked(){
    emit clicked(m_id1, m_id2);
}
