/// \file blHoverableWidget.h
/// \brief blHoverableWidget
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2014

#pragma once

#include <QtWidgets>
#include "blWidgetsExport.h"

/// \class blHoverableWidget
/// \brief Widget than can display an other widget (a khHoverWidget)
/// hover itself
class BLWIDGETS_EXPORT blHoverableWidget : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blHoverableWidget(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent system
    explicit blHoverableWidget(QWidget *parent = 0);
    
signals:
    /// \fn void resized(int, int);
    /// \brief Signal emitted when this widget is resized
    /// \param[in] w Width
    /// \param[in] h Heigh
    void resized(int w, int h);

protected:
    /// \fn void resizeEvent ( QResizeEvent * event );
    /// \brief Reimplement the resize Event from QWidget
    /// \param[in] event Event
    void resizeEvent ( QResizeEvent * event );
    
};
