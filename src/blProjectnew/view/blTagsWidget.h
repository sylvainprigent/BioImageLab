/// \file blTagsWidget.h
/// \brief blTagsWidget
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) blimbio 2014

#pragma once

#include <QtWidgets>
#include "blWidgets/blFlowLayout.h"
#include "../model/blTagsInfo.h"

class blTagContainer;
class blTagsWidget;

// ////////////////////////////////////////////////
//                blTagManagerWidget
// ////////////////////////////////////////////////
class blTagManagerWidget : public QWidget
{
    Q_OBJECT
public:
    blTagManagerWidget(QWidget *parent=0);

signals:
    void tagAdded();

public:
    blTagsInfo getTagsInfo();
    void setTags(QList<blTagInfo> tags);

private slots:
    void addTag();

private:
    QLineEdit *m_addTagEdit;
    QPushButton *m_addTagButton;
    blTagsWidget* m_tags;
};

// ////////////////////////////////////////////////
//  blTagsWidget
// ////////////////////////////////////////////////
/// \class blTagsWidget
/// \brief Widget that contains a list of tags. Tags
///  can be dynalically added an erased
class blTagsWidget : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blTagsWidget(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent For Qt parent sytem
    explicit blTagsWidget(QWidget *parent = 0);
    
signals:
    void tagAdded();
    
public slots:
    /// \fn void addTag(QString tag, bool closable = true);
    /// \brief add a tag to the list
    /// \param[in] tag Text of the tag to add
    /// \param[in] closable True if the tag can be removed from the list
    void addTag(int id, QString tag, bool closable = true);
    /// \fn void addTags(QStringList tags, bool closable = true);
    /// \param[in] tags Text of the tags to add
    /// \param[in] closable True if the tag can be removed from the list
    void addTags(QList<int> id, QStringList tags, bool closable);
    /// \fn QStringList tags();
    /// \return the tags text list
    QStringList tags();
    blTagsInfo tagsInfo();
    /// \fn void removeAllTags();
    /// \brief remove all the tags
    void removeAllTags();

    int lastId();

private:
    blFlowLayout *m_layout; ///< layout
};

// ////////////////////////////////////////////////
//  blTagContainer
// ////////////////////////////////////////////////
/// \class blTagContainer
/// \brief Widget that display a single tag
class blTagContainer : public QWidget{
    Q_OBJECT

public:
    /// \fn blTagContainer(QString name, bool closable = true);
    /// \brief Contructor
    /// \param[in] name Text of the tag
    /// \param[in] closable True if the tag can be removed
    blTagContainer(int id, QString name, bool closable = true);

public:
    /// \fn QString name();
    /// \return the text of the tag
    QString name();
    /// \fn void setName(QString name);
    /// \param[in] name Text of the tag
    void setName(QString name);

    int id();
    void setId(int id);

private slots:
    /// \fn void autoDesctroy();
    /// \brief Internal slot to free the widget
    void autoDesctroy();

private:
    QLabel* m_label; ///< label
    int m_id;
};
