/// \file blProjectSplitLabelWidget.cpp
/// \brief blProjectSplitLabelWidget
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectSplitLabelWidget.h"

blProjectSplitLabelWidget::blProjectSplitLabelWidget(QStringList mainColumnNames, QWidget *parent) :
    QWidget(parent)
{

    qDebug() << "blProjectSplitLabelWidget constructor begin";
    QWidget *globalWidget = new QWidget(this);
    globalWidget->setMaximumWidth(800);
    globalWidget->setStyleSheet("QWidget{background-color: #fff;}");
    QVBoxLayout* globalLayout = new QVBoxLayout;
    globalLayout->addWidget(globalWidget,1, Qt::AlignCenter);
    this->setLayout(globalLayout);


    QGridLayout *layout = new QGridLayout;
    layout->setContentsMargins(25,25,25,25);
    globalWidget->setLayout(layout);

    QLabel *title = new QLabel(this);
    title->setObjectName("blHideableWidgetTitleLevel2");
    title->setText(tr("Split label"));
    layout->addWidget(title, 0, 0, 1, 3);

    // select main column
    QLabel *mainColumnSelectorTitle = new QLabel(this);
    mainColumnSelectorTitle->setText(tr("Column to process"));
    m_mainColumnSelector = new QComboBox(this);
    m_mainColumnSelector->addItems(mainColumnNames);
    layout->addWidget(mainColumnSelectorTitle, 1, 0, 1, 1);
    layout->addWidget(m_mainColumnSelector, 1, 1, 1, 2);
    connect(m_mainColumnSelector, SIGNAL(currentIndexChanged(QString)), this, SIGNAL(askSubColumnNames(QString)));

    // select sub column
    QLabel *subColumnSelectorTitle = new QLabel(this);
    subColumnSelectorTitle->setText(tr("Sub column to process"));
    m_subColumnSelector = new QComboBox(this);
    layout->addWidget(subColumnSelectorTitle, 2, 0, 1, 1);
    layout->addWidget(m_subColumnSelector, 2, 1, 1, 2);

    // separator
    QLabel *seperatorEditTitle = new QLabel(this);
    seperatorEditTitle->setText(tr("Separator"));
    m_separatorEdit = new QLineEdit(this);
    layout->addWidget(seperatorEditTitle, 3, 0, 1, 1);
    layout->addWidget(m_separatorEdit, 3, 1, 1, 2);

    // labels titles
    QLabel *labelsTitlesEditTitle = new QLabel(this);
    labelsTitlesEditTitle->setText(tr("Labels titles (separated with ',')"));
    m_labelsTitlesEdit = new QLineEdit(this);
    layout->addWidget(labelsTitlesEditTitle, 4, 0, 1, 1);
    layout->addWidget(m_labelsTitlesEdit, 4, 1, 1, 2);

    // save/cancel buttons
    QPushButton *validate = new QPushButton(tr("Ok"), this);
    validate->setObjectName("btnDefault");
    QPushButton *cancel = new QPushButton(tr("Cancel"), this);
    cancel->setObjectName("btnDefault");

    connect(validate, SIGNAL(clicked()), this, SLOT(emitSplitLabel()));
    connect(cancel, SIGNAL(clicked()), this, SIGNAL(cancel()));

    layout->addWidget(cancel, 5, 2, 1, 1);
    layout->addWidget(validate, 5, 3, 1, 1);

    qDebug() << "blProjectSplitLabelWidget constructor end";
}

void blProjectSplitLabelWidget::emitSplitLabel(){
    emit askSplitLabels(m_mainColumnSelector->currentText(),
                        m_subColumnSelector->currentText(),
                        m_separatorEdit->text(),
                        m_labelsTitlesEdit->text()
                        );
}

void blProjectSplitLabelWidget::setSubColumnList(QStringList columnsNames){
    /*
    for (int i = m_subColumnSelector->count()-1 ; i >=0 ; i--){
        m_subColumnSelector->removeItem(i);
    }
    */
    m_subColumnSelector->clear();
    m_subColumnSelector->addItems(columnsNames);
}
