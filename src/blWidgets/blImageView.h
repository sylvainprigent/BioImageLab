/// \file blImageView.h
/// \brief blImageView
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2014

#pragma once

#include <QtWidgets>
#include "blWidgetsExport.h"

/// \class blImageView
/// \brief Widget that view an image as an icon
class BLWIDGETS_EXPORT blImageView : public QWidget{

    Q_OBJECT

public:
    /// \fn blImageView(QString imagePath, QString textAdress);
    /// \brief Constructor
    /// \param[in] imagePath Path of the image to view
    /// \param[in] textAdress String associated to the image
    blImageView(QString imagePath, QString textAdress);

    /// \fn blImageView(QImage image, QString textAdress);
    /// \brief Constructor
    /// \param[in] image Image to view
    /// \param[in] textAdress String associated to the image
    blImageView(QImage image, QString textAdress);

public:
    /// \fn QString text();
    /// \return the string associated to the image
    QString text();
    /// \fn QString widgetName();
    /// \return the name of the widget
    QString widgetName();

private:
    QString m_textAdtress; ///< String associated to the image
};
