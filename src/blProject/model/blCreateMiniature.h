/// \file blCreateMiniature.h
/// \brief blCreateMiniature
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QImage>

#include "blWidgets/blImageView.h"

/// \class blCreateMiniature
/// \brief Create a small image from an image file
class BLPROJECT_EXPORT blCreateMiniature{

public:
    static QImage getMiniature(QString imageURL);
    static void makeThumbnail(QString imageURL, QString thumbnailFileUrl);

};

/**
 * @brief The blCreateMiniatureThread class
 */
class blCreateMiniatureThread : public QThread{
    Q_OBJECT
public:
    blCreateMiniatureThread(QObject *parent);
    void setData(QStringList imagesNames, QList<unsigned int> rowIdxs, unsigned columnIdx, QString mainColName);

signals:
    void thumbnailCreated(QString mainColName, unsigned int rowIdxs, unsigned int  columnIdx, QString imageName);

protected:
    void run();

private:
    QStringList m_imagesNames;
    QList<unsigned int> m_rowIdxs;
    unsigned m_columnIdx;
    QString m_mainColName;
};
