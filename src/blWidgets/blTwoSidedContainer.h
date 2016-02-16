/// \file blTwoSidedContainer.h
/// \brief blTwoSidedContainer
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLib 2014

#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>

#include "blWidgetsExport.h"

class BLWIDGETS_EXPORT blLeftTwoSidedSingleWidgetContainer;
// ////////////////////////////////////////////////
//           blTwoSidedContainer
// ////////////////////////////////////////////////
/// \class blTwoSidedContainer
/// \brief Widget that display a list of widget on the left side
/// and any other widget on the right area
class blTwoSidedContainer : public QWidget
{
    Q_OBJECT
public:
    blTwoSidedContainer(QWidget *parent = 0);

signals:
    void clicked(QWidget*);

public slots:
    void addLeftWidget(QWidget* widget);
    void removeLeftWidget(QWidget *widget);
    void setRightWidget(QWidget *widget);
    void free();
    void setFixedLeftWidth(int width);
    void setSelectedLeftWidget(int row);
    void resetRightWidget();

private slots:
    void changeSelectedWidget(blLeftTwoSidedSingleWidgetContainer* selectedWidget);

private:
    QWidget *leftWidget;
    QVBoxLayout *m_leftLayout;
    QVBoxLayout *m_rightLayout;
    QScrollArea *scrollArea;
    QWidget *rightWidget;
};

// ////////////////////////////////////////////////
//        blLeftTwoSidedSingleWidgetContainer
// ////////////////////////////////////////////////
class blLeftTwoSidedSingleWidgetContainer : public QWidget
{
    Q_OBJECT
public:
    blLeftTwoSidedSingleWidgetContainer(QWidget *widget, QWidget* parent=0);

signals:
    void clicked(blLeftTwoSidedSingleWidgetContainer* w);

public slots:
    void setSelected(bool selected);

public:
    QWidget *widget();

private:
    QWidget* m_widget;

private:
    QLabel *m_rightMargin;


protected:
    void mouseReleaseEvent ( QMouseEvent * e );
};
