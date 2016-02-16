/// \file blClickableIcon.h
/// \brief blClickableIcon
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioImageLab 2014

#pragma once

#include <QLabel>
#include <QString>
#include <QMouseEvent>
#include "blWidgetsExport.h"

/// \class blClickableIcon
/// \brief Class defining a icon that can be clicked and that stor an id to be used in a icone list
class BLWIDGETS_EXPORT blClickableIcon : public QLabel
{
    Q_OBJECT
public:
    /// \fn blClickableIcon(QString cheminImage, QString textIcone , int large,int haut, int marge,QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] cheminImage Path to the icon image
    /// \param[in] textIcone Description text that is transmitted in one of the clicked signal
    /// \param[in] large width of the icon
    /// \param[in] haut heigh of the icon
    /// \param[in] marge Margin that is added to the width and heigh values
    /// \param[in] parent Pointer to the parent widget
    blClickableIcon(QString cheminImage, QString textIcone , int large,int haut, int marge,QWidget *parent = 0);

private:
    QString text_icone; ///< text icon
    int largeM; ///< width
    int hautM; ///< heigh
    int margeM; ///< margin
    int m_posInFolder; ///< position in folder

signals:
    /// \fn void iconClicked(QString);
    /// \brief Signal emitted when the icon is clicked
    /// \param[in] def_text Text defining the icon
    void iconClicked(QString def_text);

    /// \fn oid iconClicked(int id);
    /// \brief Signal emitted when the icon is clicked
    /// \param[in] id Id of the icon
    void iconClicked(int id);

    /// \fn void clicked();
    /// \brief Signal emitted when the icon is clicked
    void clicked();

public slots:
    /// \fn void ChangeIcon(QString textIcone);
    /// \brief Slot that allows to modify the icon
    /// \param[in] textIcone Path of the new image for the icon
    void ChangeIcon(QString textIcone);

    /// \fn void setPositionNumber(int pos);
    /// \brief Slot that allows to set an id to the icon
    /// \param[in] pos Id value
    void setPositionNumber(int pos);

    /// \fn void setIdx(int idx);
    /// \brief The blClickableIcon can store an idx to be able to
    /// index it
    /// \param[in] idx Index to store
    void setIdx(int idx);
    /// \fn int idx();
    /// \return the blClickableIcon index
    int idx();

protected:
    /// \fn virtual void mouseReleaseEvent(QMouseEvent *);
    /// \brief Reimplement from QWidget to handle left click event
    virtual void mouseReleaseEvent(QMouseEvent *);

private:
    int m_idx; ///< idx
};
