/// \file blTwoSideRightContainer.h
/// \brief blTwoSideRightContainer
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLib 2014

#pragma once
#include <QtWidgets>

#include "blWidgetsExport.h"

/// \class blTwoSideRightContainer
/// \brief Container for the right widget of a blTwoSideWidget
class BLWIDGETS_EXPORT blTwoSideRightContainer : public QWidget
{
    Q_OBJECT
public:
    /// \fn blTwoSideRightContainer(QWidget* parent = 0);
    /// \brief Constructor
    /// \param[in] parent For the Qt parent system
    blTwoSideRightContainer(QWidget* parent = 0);
    /// \fn void addWidget(QWidget* widget);
    /// \param[in] widget Widget to add to the container
    void addWidget(QWidget* widget);

private:
    QVBoxLayout *m_layout; ///< layout
};
