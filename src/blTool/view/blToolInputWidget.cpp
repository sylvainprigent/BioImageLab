#include "blToolInputWidget.h"

blToolInputWidget::blToolInputWidget(QWidget *parent) : QWidget(parent)
{

    m_layout = new QHBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);
    this->setLayout(m_layout);

    m_helpButton = new QPushButton;
    m_helpButton->setObjectName("blToolInputWidgetHelpButton");
    m_layout->addWidget(m_helpButton, 0, Qt::AlignRight);

    connect(m_helpButton, SIGNAL(pressed()), this, SLOT(emitHelp()));
}

void blToolInputWidget::setHelpButtonVisible(bool visible){
    m_helpButton->setVisible(visible);
}

void blToolInputWidget::emitHelp(){
    //qDebug() << "ask help = " << m_help;
    emit help(m_help);
}

QString blToolInputWidget::datatype(){
    return m_dataType;
}

QString blToolInputWidget::key(){
    return m_key;
}

QString blToolInputWidget::value(){
    return m_value;
}

QString blToolInputWidget::help(){
    return m_help;
}

bool blToolInputWidget::isAdvanced(){
    return m_advanced;
}

void blToolInputWidget::setAdvanced(bool adv){
    m_advanced = adv;
}

void blToolInputWidget::setKey(QString key){
    m_key = key;
}

void blToolInputWidget::setValue(QString value){
    m_value = value;
}

void blToolInputWidget::setDatatype(QString datatype){
    m_dataType = datatype;
}

void blToolInputWidget::setHelp(QString help){
    m_help = help;
}


// ///////////////////////////////////////////////// //
//                blToolInputValue                   //
// ///////////////////////////////////////////////// //
blToolInputValue::blToolInputValue(QWidget *parent)
    : blToolInputWidget(parent){

    m_valueEdit = new QLineEdit(this);
    m_layout->insertWidget(0,m_valueEdit);
    connect(m_valueEdit, SIGNAL(textChanged(QString)), this, SLOT(updateValue(QString)));
}


void blToolInputValue::updateValue(QString value){
    m_value = value;
}

void blToolInputValue::setValue(QString value){
    m_value = value;
    m_valueEdit->setText(m_value);
}

// ///////////////////////////////////////////////// //
//                blToolInputSelect
// ///////////////////////////////////////////////// //
blToolInputSelect::blToolInputSelect(QWidget *parent)
        : blToolInputWidget(parent){

    m_conbobox = new QComboBox(this);
    m_layout->insertWidget(0,m_conbobox);
    connect(m_conbobox, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateValue(QString)));
    connect(m_conbobox, SIGNAL(currentIndexChanged(QString)), this, SLOT(emitValueChanged(QString)));
}

void blToolInputSelect::emitValueChanged(QString value){
    emit valueChanged(m_key, value);
}

void blToolInputSelect::setContent(QString content){
    QStringList contentList = content.split(";");
    this->setContent(contentList);
}

void blToolInputSelect::setContent(QStringList content){
    for(int i = 0 ; i < content.count() ; ++i){
        QString item = content[i];
        item = item.simplified();
        if (!item.isEmpty()){
            m_conbobox->addItem(item);
        }
    }
}

void blToolInputSelect::updateValue(QString value){
    m_value = value;
}

// ///////////////////////////////////////////////// //
//                blToolInputBrowser
// ///////////////////////////////////////////////// //
blToolInputBrowser::blToolInputBrowser(QWidget *parent, bool isDir)
    : blToolInputWidget(parent){

    m_isDir = isDir;
    m_pathEdit = new QLineEdit(this);
    QPushButton *button = new QPushButton(tr("..."), this);
    button->setObjectName("btnDefault");
    m_layout->insertWidget(0,m_pathEdit);
    m_layout->insertWidget(1,button);

    connect(button, SIGNAL(pressed()), this, SLOT(browse()));
    connect(m_pathEdit, SIGNAL(textChanged(QString)), this, SLOT(updateValue(QString)));
}

void blToolInputBrowser::browse(){

    if (!m_isDir){
        QString file = QFileDialog::getOpenFileName(this, "open data", QString(), "");
        m_pathEdit->setText(file);
    }
    else{
        QString dir = QFileDialog::getExistingDirectory(this);
        m_pathEdit->setText(dir);
    }
}

void blToolInputBrowser::updateValue(QString value){
    m_value = value;
}
