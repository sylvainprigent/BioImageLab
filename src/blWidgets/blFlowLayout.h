/// \file blFlowLayout.h
/// \brief blFlowLayout
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2014

#pragma once

#include <QWidget>
#include <QLayout>
#include <QRect>
#include <QWidgetItem>
#include <QStyle>
#include "blWidgetsExport.h"

/// \class blFlowLayout
/// \brief Layout that add widget as a flow
class BLWIDGETS_EXPORT blFlowLayout : public QLayout
{
public:
    /// \fn blFlowLayout(QWidget *parent, int margin = -1, int hSpacing = -1, int vSpacing = -1);
    /// \brief Constructor
    /// \param[in] parent Qt parent system
    /// \param[in] margin Margin around the layout
    /// \param[in] hSpacing Horizontal spacing between widgets
    /// \param[in] vSpacing Vertical spacing between widgets
    blFlowLayout(QWidget *parent, int margin = -1, int hSpacing = -1, int vSpacing = -1);
    /// \fn blFlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1);
    /// \brief Constructor
    /// \param[in] margin Margin around the layout
    /// \param[in] hSpacing Horizontal spacing between widgets
    /// \param[in] vSpacing Vertical spacing between widgets
    blFlowLayout(int margin = -1, int hSpacing = -1, int vSpacing = -1);
    /// \fn ~blFlowLayout();
    /// \brief Destructor
    ~blFlowLayout();

public:
    /// \fn void addItem(QLayoutItem *item);
    /// \param[in] item Item to add to the layout
    void addItem(QLayoutItem *item);
    /// \fn int horizontalSpacing() const;
    /// \return the horizontal spacing
    int horizontalSpacing() const;
    /// \fn int verticalSpacing() const;
    /// \return the vertical spacing
    int verticalSpacing() const;
    /// \fn Qt::Orientations expandingDirections() const;
    /// \return the expanding directions
    Qt::Orientations expandingDirections() const;
    /// \fn bool hasHeightForWidth() const;
    /// \return true if has height for width
    bool hasHeightForWidth() const;
    /// \fn int heightForWidth(int) const;
    /// \param[in] width Width
    /// return the height for the width given as input
    int heightForWidth(int width) const;
    /// \fn int count() const;
    /// \return the number of widget in the layout
    int count() const;
    /// \fn QLayoutItem *itemAt(int index) const;
    /// \param[in] index Index of the item to get
    /// \return the item at index "index"
    QLayoutItem *itemAt(int index) const;
    /// \fn QSize minimumSize() const;
    /// \return the minimun size
    QSize minimumSize() const;
    /// \fn void setGeometry(const QRect &rect);
    /// \brief set the layout geometry
    /// \param[in] rect Rectangle geometry
    void setGeometry(const QRect &rect);
    /// \fn QSize sizeHint() const;
    /// \return the size
    QSize sizeHint() const;
    /// \fn QLayoutItem *takeAt(int index);
    /// \param[in] index Index of the item to get
    /// \return the item at index "index"
    QLayoutItem *takeAt(int index);

private:
    /// \fn int doLayout(const QRect &rect, bool testOnly) const;
    /// \brief internal method
    /// \param[in] rect Geometry
    /// \param[in] testOnly set geometry if not testOnly
    int doLayout(const QRect &rect, bool testOnly) const;
    /// \fn int smartSpacing(QStyle::PixelMetric pm) const;
    /// \brief Calculate a smart spicing
    /// \param[in] pm Pixel metric
    /// \return the calculated spicing
    int smartSpacing(QStyle::PixelMetric pm) const;

    QList<QLayoutItem *> itemList; ///< item list
    int m_hSpace; ///< horizontal space
    int m_vSpace; ///< vertical space
};
