/// \file blCreateMiniature.cpp
/// \brief blCreateMiniature
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blCreateMiniature.h"
#include <blCore>
#include <QColor>
#include <QDebug>
#include <QFileInfo>
#include <QProcess>
#include <QPainter>



QImage blCreateMiniature::getMiniature(QString imageURL){

    QString smallFileUrl = imageURL + "_small.png";
    QFileInfo smallFile(smallFileUrl);
    if (smallFile.exists()){
        return QImage(smallFileUrl);
    }
    else{
            QImage img(120,120, QImage::Format_RGB888);

            QPainter p(&img);

            p.setPen(QPen(Qt::white));
            p.setFont(QFont("Times", 10, QFont::Bold));
            p.drawText(img.rect(), Qt::AlignCenter, "thumbnail \n not found");

            return img;
    }
}

void blCreateMiniature::makeThumbnail(QString imageURL, QString thumbnailFileUrl){


    QString program = "C:\\app\\Fiji.app\\ImageJ-win64.exe --headless -macro C:\\Users\\sprigent\\Documents\\codes\\BioImageLab_dist\\tools\\FijiMakeMiniature\\make_miniature.ijm \"'$inputImage' $height '$outputImage'\"";

    program = program.replace("$inputImage", imageURL);
    program = program.replace("$height", "150");
    program = program.replace("$outputImage", thumbnailFileUrl);

    qDebug() << "make makeThumbnail : " << program;

    QProcess *myProcess = new QProcess();
    myProcess->start(program);
    myProcess->waitForFinished();
    myProcess->close();
}


blCreateMiniatureThread::blCreateMiniatureThread(QObject* parent) : QThread(parent){

}

void blCreateMiniatureThread::setData(QStringList imagesNames, QList<unsigned int> rowIdxs, unsigned columnIdx, QString mainColName){
    m_imagesNames = imagesNames;
    m_rowIdxs = rowIdxs;
    m_columnIdx = columnIdx;
    m_mainColName = mainColName;
}

void blCreateMiniatureThread::run(){

    for (int i = 0 ; i < m_imagesNames.count() ; ++i){

        blCreateMiniature::makeThumbnail(m_imagesNames[i], m_imagesNames[i] + "_small.png");

        emit thumbnailCreated(m_mainColName, m_rowIdxs[i], m_columnIdx, m_imagesNames[i]);
    }
}



