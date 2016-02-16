/// \file blImageView.cpp
/// \brief blImageView
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2014

#include "blImageView.h"

blImageView::blImageView(QString imagePath, QString textAdress){
    m_textAdtress = textAdress;

    QLabel *imageLabel = new QLabel;
    imageLabel->setFixedHeight(150);

    QFileInfo infoDesctination(imagePath);
    qDebug() << "image path = " << imagePath;
    qDebug() << "image suffix = " << infoDesctination.suffix();
    if (infoDesctination.suffix() == "png" || infoDesctination.suffix() == "jpg"
            || infoDesctination.suffix() == "tif" || infoDesctination.suffix() == "tiff"){
        imageLabel->setPixmap(QPixmap::fromImage(QImage(imagePath).scaledToHeight(150)));
        imageLabel->setStyleSheet("border: 0px solid black;");
    }
    else{
        imageLabel->setText("?");
        imageLabel->setStyleSheet("background-color: gray; font-size: 75px; border: 0px solid black; qproperty-alignment: AlignCenter; ");
    }

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(imageLabel);
    this->setLayout(layout);
}

blImageView::blImageView(QImage image, QString textAdress){

    m_textAdtress = textAdress;

    QLabel *imageLabel = new QLabel;
    imageLabel->setFixedHeight(150);

    //imageLabel->setPixmap(QPixmap::fromImage(image.scaledToHeight(150)));
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->setStyleSheet("border: 0px solid black;");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(imageLabel);
    this->setLayout(layout);
}


QString blImageView::text(){
    return m_textAdtress;
}

QString blImageView::widgetName(){
    return "blImageView";
}
