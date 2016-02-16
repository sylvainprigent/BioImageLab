/// \file blHoverWidget.h
/// \brief blHoverWidget
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2014

#pragma once

#include <QtWidgets>
#include "blHoverableWidget.h"
#include "blWidgetsExport.h"

/// \class blHoverWidget
/// \brief Widget that can be displayed over a blHoverableWidget
class BLWIDGETS_EXPORT blHoverWidget : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blHoverWidget(blHoverableWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent system
    explicit blHoverWidget(blHoverableWidget *parent = 0);
    
signals:
    /// \fn void askClose();
    /// \brief Signal emitted when the close button is clicked
    void askClose();
    /// \fn void askClose(blHoverWidget*);
    /// \brief Signal emitted when the close button is clicked
    /// \param[in] pointer Pointer to this widget
    void askClose(blHoverWidget* pointer);
    
public slots:
    /// \fn void addWidget(QWidget *w);
    /// \brief Add a widget to this widget layout
    /// \param[in] w Widget to add
    void addWidget(QWidget *w);
    /// \fn void emitClose();
    /// \brief Emit the close signal
    void emitClose();

private slots:
    /// \fn void resizeSlot(int w, int h);
    /// \brief Resize the widget
    /// \param[in] w Width
    /// \param[in] h Heigh
    void resizeSlot(int w, int h);

private:
    QVBoxLayout *m_layout; ///< layout
    
};
