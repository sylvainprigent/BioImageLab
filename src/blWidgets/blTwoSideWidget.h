/// \file blTwoSideWidget.h
/// \brief blTwoSideWidget
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLib 2014

#pragma once

#include <QtWidgets>

#include "blWidgetsExport.h"

/// \class blTwoSideWidget
/// \brief Widget that can display a list of widget in the
/// left area and a single widget in a "bubble" in the right side
class BLWIDGETS_EXPORT blTwoSideWidget : public QWidget
{
    Q_OBJECT
    
public:
    /// \fn blTwoSideWidget(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent For the Qt parent system
    blTwoSideWidget(QWidget *parent = 0);
    /// \fn ~blTwoSideWidget();
    /// \brief Destructor
    ~blTwoSideWidget();


public slots:
    /// \fn void addLeftWidget(QWidget *widget);
    /// \param[in] widget Widget to add in the left container
    void addLeftWidget(QWidget *widget);
    /// \fn void setRightWidget(int row, QWidget *widget, int expanding = 100);
    /// \param[in] row Row index of the left widget where the bubble point at
    /// \param[in] widget Widget to set in the bubble right container
    /// \param[in] expanding Expanding factor of the bubble along the left widgets
    void setRightWidget(int row, QWidget *widget, int expanding = 100);
    /// \fn void setFixedLeftWidth(int width);
    /// \param[in] width Width of the left widget container
    void setFixedLeftWidth(int width);
    /// \fn void free();
    /// \brief remove the widgets inside the contaiers
    void free();

public:
    /// \fn void setRowDelta(int rowDelta);
    /// \param[in] rowDelta Row delta
    /// \brief Row delta correspond to the shift of the bubble top
    /// due to the left widgets. default = 0
    void setRowDelta(int rowDelta);

private:
    int m_numberLeftWidget; ///< number of left widget
    int m_curentRightWidgetIdx; ///< curent right widget idx
    int m_curentLeftWidgetIdx; ///< curent left widget idx
    int m_rowDelta; ///< row delta
    int m_leftWidth; ///< left width

private:
    QGridLayout *m_layout; ///< layout
    QWidget *m_widget; ///< widget
    QVBoxLayout *totalLayout; ///< total layout
};
