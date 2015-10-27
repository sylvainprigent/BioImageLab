/// \file blSlidingStackedWidget.h
/// \brief blSlidingStackedWidget
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2015

#pragma once

#include <QStackedWidget>
#include <QtGui>
#include <QWidget>
#include <QDebug>
#include <QEasingCurve>

#include "blWidgetsExport.h"

/// \class blSlidingStackedWidget
/// \brief blSlidingStackedWidget is a class that is derived from QtStackedWidget
///        and allows smooth side shifting of widgets, in addition
///        to the original hard switching from one to another as offered by
///        QStackedWidget itself.
class BLWIDGETS_EXPORT blSlidingStackedWidget : public QStackedWidget
{
        Q_OBJECT

public:
        //! This enumeration is used to define the animation direction
        enum t_direction {
                LEFT2RIGHT,
                RIGHT2LEFT,
                TOP2BOTTOM,
                BOTTOM2TOP,
                AUTOMATIC
        };

        /// \fn blSlidingStackedWidget(QWidget *parent);
        /// \brief Constructor
        /// \param[in] parent Qt parent system
        blSlidingStackedWidget(QWidget *parent);
        /// \fn ~blSlidingStackedWidget(void);
        /// \brief Destructor
        ~blSlidingStackedWidget(void);


public slots:
        /// \fn void setSpeed(int speed);
        /// \param[in] speed Animation duration in milliseconds
        void setSpeed(int speed);
        /// \fn void setAnimation(enum QEasingCurve::Type animationtype);
        /// \brief check out the QEasingCurve documentation for different styles
        /// \param[in] animationtype animation style
        void setAnimation(enum QEasingCurve::Type animationtype);
        /// \fn void setVerticalMode(bool vertical=true);
        /// \param[in] vertical True for vertical, false for horizontal
        void setVerticalMode(bool vertical=true);
        /// \fn void setWrap(bool wrap);
        /// \brief wrapping is related to slideInNext/Prev;
        /// it defines the behaviour when reaching last/first page
        /// \param[in] wrap Wrap boolean
        void setWrap(bool wrap);

        /// \fn void slideInNext();
        /// \brief Slide to next widget
        void slideInNext();
        /// \fn void slideInPrev();
        /// \brief Slide to previous widget
        void slideInPrev();
        /// \fn void slideInIdx(int idx, enum t_direction direction=AUTOMATIC);
        /// \brief Slide to the widex at index idx
        /// \param[in] idx Index of the widget to slide to
        /// \param[in] direction Direction of the sliding
        void slideInIdx(int idx, enum t_direction direction=AUTOMATIC);


signals:
        /// \fn void animationFinished(void);
        /// \brief this is used for internal purposes in the class engine
        void animationFinished(void);

protected slots:
        /// \fn void animationDoneSlot(void);
        /// \brief this is used for internal purposes in the class engine
        void animationDoneSlot(void);

public slots:
        /// \fn void slideInWgt(QWidget * widget, enum t_direction direction=AUTOMATIC);
        /// \brief this is used for internal purposes in the class engine
        /// \param[in] widget Widget to slide in
        /// \param[in] direction Sliding direction
        void slideInWgt(QWidget * widget, enum t_direction direction=AUTOMATIC);

protected:
        QWidget *m_mainwindow; ///< main window

        int m_speed; ///< speed
        enum QEasingCurve::Type m_animationtype; ///< animation type
        bool m_vertical; ///< vertical
        int m_now; ///< now
        int m_next; ///< next
        bool m_wrap; ///< wrap
        QPoint m_pnow; ///< pnow
        bool m_active; ///< active

        QList<QWidget*> blockedPageList; ///< blocked page list
};
