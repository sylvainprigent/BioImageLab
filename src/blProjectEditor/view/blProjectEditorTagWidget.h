/// \file blProjectEditorTagWidget.h
/// \brief blProjectEditorTagWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2019
///
/// Copyright (C) BioimageLab 2019

#pragma once

#include "blProjectEditorExport.h"
#include "blProjectEditor/model/blProjectTag.h"
#include <QtWidgets>

/// \class blProjectEditorTagWidget
/// \brief Widget that shows a tag
/// and a tool bar to create a new project
class BLPROJECTEDITOR_EXPORT blProjectEditorTagWidget : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectEditorTagWidget(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Qt parent systeme
    explicit blProjectEditorTagWidget(blProjectTag *tag, QWidget *parent = 0);

    blProjectTag *tag();

signals:
    void askRemoveTag(blProjectTag*);

private slots:
    void emitAskRemoveTag();

private:
    blProjectTag *m_tag;
};
