#include "blHomeSettingsView.h"

blHomeSettingsView::blHomeSettingsView(blHomeSettings settings, QWidget *parent)
    :QWidget(parent){

    m_settings = settings;

    m_layout = new QGridLayout;
    this->setLayout(m_layout);

    m_titleLabel = new QLabel(this);
    m_titleLabel->setVisible(false);
    m_titleLabel->setObjectName("blHomeSettingsViewTitle");
    m_layout->addWidget(m_titleLabel, 0, 0, 1, 2, Qt::AlignTop);

    QMapIterator<QString, QStringList> i(settings.map());
    int cmpt=0;
    while (i.hasNext()) {
        i.next();
        cmpt++;
        QStringList values = i.value();
        blHomeSettingsWidgetLineEdit *lineEdit = new blHomeSettingsWidgetLineEdit(i.key(), values[0], values[1], this );
        QLabel *keyLabel = new QLabel(i.key(), this);
        keyLabel->setObjectName("blHomeSettingsViewKeyLabel");
        m_layout->addWidget(keyLabel, cmpt, 0, 1, 1);
        m_layout->addWidget(lineEdit, cmpt, 1, 1, 1);
    }
}

void blHomeSettingsView::setTitle(QString title){
    m_titleLabel->setText(title);
    m_titleLabel->setVisible(true);
}

QString blHomeSettingsView::title(){
    return m_titleLabel->text();
}

void blHomeSettingsView::setTitleVisible(bool value){
    m_titleLabel->setVisible(value);
}

blHomeSettings blHomeSettingsView::settings(){

    blHomeSettings settings;
    for (int i = m_layout->count()-1 ; i >= 0 ; i--){
        QLayoutItem* item = m_layout->itemAt(i);
        QWidget *w = item->widget();
        if (w){
            blHomeSettingsWidget* settingWidget = qobject_cast<blHomeSettingsWidget*>(w);
            if (settingWidget){
                settings.add(settingWidget->key(), settingWidget->value(), settingWidget->type());
            }
        }
    }
    return settings;
}

// ////////////////////////////////////////
//          blHomeSettingsWidget
// ////////////////////////////////////////
blHomeSettingsWidget::blHomeSettingsWidget(QString key, QString value, QString type, QWidget *parent)
    : QWidget(parent){

    m_key = key;
    m_value = value;
    m_type = type;
}

QString blHomeSettingsWidget::key(){
    return m_key;
}

QString blHomeSettingsWidget::type(){
    return m_type;
}

// ////////////////////////////////////////
//      blHomeSettingsWidgetLineEdit
// ////////////////////////////////////////
blHomeSettingsWidgetLineEdit::blHomeSettingsWidgetLineEdit(QString key, QString value, QString type, QWidget *parent)
    :blHomeSettingsWidget(key, value, type, parent){

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    m_lineEdit = new QLineEdit(this);
    layout->addWidget(m_lineEdit);
    m_lineEdit->setText(value);
    this->setLayout(layout);
}


QString blHomeSettingsWidgetLineEdit::value(){
    return m_lineEdit->text();
}
