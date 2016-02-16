/// \file blTwoSideLeftContainer.h
/// \brief blTwoSideLeftContainer
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLib 2014

#pragma once

#include <QtWidgets>

#include "blWidgetsExport.h"

/// \class blTwoSideLeftContainer
/// \brief Container for the left widget of a blTwoSideWidget
class BLWIDGETS_EXPORT blTwoSideLeftContainer : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blTwoSideLeftContainer(QWidget *parent = 0);
    /// \brief Contructor
    /// \param[in] parent For Qt parent system
    explicit blTwoSideLeftContainer(QWidget *parent = 0);
    
signals:
    
public slots:
    /// \fn void setWidget(QWidget *widget);
    /// \brief Set a widget into the container
    /// \param[in] widget Widget to add
    void setWidget(QWidget *widget);
    /// \fn void setClicked(bool value);
    /// \param[in] value True if clicked, false otherwise
    void setClicked(bool value);

private:
    QHBoxLayout *m_layout; ///< layout
    QLabel *m_bubleWidget; ///< bubble widget
};
