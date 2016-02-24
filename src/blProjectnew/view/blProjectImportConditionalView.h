/// \file blProjectImportConditionalView.h
/// \brief blProjectImportConditionalView.h
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#pragma once

#include <QtWidgets>
#include "blProjectnewExport.h"
#include "blTagsWidget.h"
#include "blWidgets/blTwoSideWidget.h"
#include "../model/blImportDataInfo.h"
#include "../model/blProjectModel.h"

/// \class blProjectImportConditionalView.h
/// \brief Form to import data in a conditional project
class BLPROJECTNEW_EXPORT blProjectImportConditionalView : public QWidget
{
    Q_OBJECT
public:
    /// \fn blProjectImportConditionalView(QWidget *parent = 0);
    /// \brief Contructor
    /// \param[in] parent Qt parent system
    blProjectImportConditionalView(QWidget *parent = 0);

signals:
    void askImport(blImportDataInfo *importInfo);

public:
    void load(blProjectModel* model);

private slots:
    void browse();
    void updateComboList();

private slots:
    void showTagsHelp();
    void showImportHelp();
    void emitAskImport();


private:
    QWidget* createTagsWidget();
    QWidget* createImportWidget();

private:
    QTextEdit *m_filesList;
    QTableWidget *m_tableWidget;
    blTagManagerWidget *m_tagSelector;
    QPushButton *m_addTagButton;
    QComboBox *m_conditionSelector;

    blTwoSideWidget* m_twoSideWidget;

private:
    QStringList m_files;

};
