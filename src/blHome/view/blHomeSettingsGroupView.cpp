#include "blHomeSettingsGroupView.h"
#include "../../blWidgets/blHideableWidget.h"
#include "blHomeSettingsView.h"

blHomeSettingsGroupView::blHomeSettingsGroupView(blSettingsGroups settings, QWidget *parent)
    : QWidget(parent){

    m_settings = settings;
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);
    for (int i = 0 ; i < settings.groupsCount() ; ++i){
        blHideableWidget *hideable = new blHideableWidget(settings.groupTitleAt(i), 2, this);
        blHomeSettingsView *settingsView = new blHomeSettingsView(settings.groupAt(i),this);
        settingsView->setTitle(settings.groupTitleAt(i));
        settingsView->setTitleVisible(false);
        hideable->addWidget(settingsView);
        layout->addWidget(hideable);
        m_settingWidgets.append(settingsView);
    }

    QPushButton *button = new QPushButton(tr("Save"), this);
    button->setObjectName("btnPrimary");
    layout->addWidget(button, 1, Qt::AlignRight);
    connect(button, SIGNAL(pressed()), this, SLOT(emitSave()));

    // fill
    layout->addWidget(new QWidget(this), 1, Qt::AlignTop);
}

void blHomeSettingsGroupView::emitSave(){

    blSettingsGroups settings;
    for(int i = 0 ; i < m_settingWidgets.count() ; ++i){
        settings.add(m_settingWidgets[i]->title(),m_settingWidgets[i]->settings());
    }

    emit save(settings);
}

