/// \file blProjectAddImageWidget.h
/// \brief blProjectAddImageWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include "blProjectExport.h"
#include <QtWidgets>


/// \class blProjectAddImageWidget
/// \brief Widget containing forms to add/import new
/// images to the project
class BLPROJECT_EXPORT blProjectSplitLabelWidget : public QWidget
{
    Q_OBJECT
public:
    /// \fn explicit blProjectSplitLabelWidget(QWidget *parent = 0);
    /// \brief Constructor
    /// \param[in] parent Constructor
    explicit blProjectSplitLabelWidget(QStringList mainColumnNames, QWidget* parent = 0);
    
signals:
    void cancel();
    void askSubColumnNames(QString);
    void askSplitLabels(QString, QString, QString, QString);

public slots:
    void setSubColumnList(QStringList columnsNames);

private slots:
    void emitSplitLabel();

private:
    QComboBox *m_mainColumnSelector;
    QComboBox *m_subColumnSelector;
    QLineEdit* m_separatorEdit;
    QLineEdit* m_labelsTitlesEdit;
};
