#include "blHomeWidgetTile.h"

blHomeWidgetTile::blHomeWidgetTile(QWidget *parent) :
    QWidget(parent)
{
    buildButton();
}

blHomeWidgetTile::blHomeWidgetTile(blHomeTileInfo info, QWidget *parent) :
    QWidget(parent)
{
    m_info = info;
    buildButton();
    setText(m_info.name());
    setIcon(m_info.iconeUrl());
    this->setToolTip(m_info.tooltip());

}

void blHomeWidgetTile::buildButton(){

    QWidget *wt = new QWidget(this);
    QVBoxLayout *tlayout = new QVBoxLayout;
    this->setLayout(tlayout);
    tlayout->addWidget(wt);
    wt->setObjectName("blHomeWidgetTile");


    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(2,3,2,3);
    layout->setSpacing(0);
    wt->setLayout(layout);

    m_label = new QLabel;
    m_label->setObjectName("blHomeButtonLabel");

    m_button = new QPushButton;
    m_button->setObjectName("blHomeButton");
    connect(m_button, SIGNAL(clicked()), this, SLOT(emitClicked()));

    layout->addWidget(m_button, 0, Qt::AlignBottom );
    layout->addWidget(m_label, 0, Qt::AlignTop );

    //this->setLayout(layout);
    this->setCursor(QCursor(Qt::PointingHandCursor));
}

void blHomeWidgetTile::setText(QString text){
    m_label->setText(text);
}

void blHomeWidgetTile::setIcon(QString iconFile){
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *iconLabel = new QLabel;

    iconLabel->setPixmap(QPixmap::fromImage(QImage(iconFile)).scaledToHeight(56,Qt::SmoothTransformation));
    layout->addWidget(iconLabel, 0, Qt::AlignCenter);
    m_button->setLayout(layout);
}

void blHomeWidgetTile::emitClicked(){
    emit clicked();
    emit clicked(m_info);
}
