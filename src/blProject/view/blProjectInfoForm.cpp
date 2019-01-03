#include "blProjectInfoForm.h"

blProjectInfoForm::blProjectInfoForm(blProjectTypes &projectTypes, QWidget *parent) :
    QWidget(parent)
{

    // initialize the data
    m_projectId = 0;

    // build the form
    this->buildWidget(projectTypes);

}

void blProjectInfoForm::setData(blProjectInfo *info){
    ;

    m_projectId = info->id();
    m_nameEdit->setText(info->name());
    m_descriptionEdit->setText(info->description());
    m_typeEdit->setCurrentIndex(m_typeEdit->findData(info->typeId()));

    this->editView();
}

void blProjectInfoForm::editView(){
    if (m_projectId == 0){
        m_saveButton->setText(tr("Next"));
    }
    else{
        m_saveButton->setText(tr("Save"));
        m_typeEdit->setEnabled(false);
    }
}

void blProjectInfoForm::buildWidget(blProjectTypes &projectTypes){

    m_twoSideWidget = new blTwoSideWidget;

    QVBoxLayout* totallayout = new QVBoxLayout;
    totallayout->setContentsMargins(0,0,0,0);
    totallayout->addWidget(m_twoSideWidget, 1, Qt::AlignTop);
    this->setLayout(totallayout);

    QGridLayout *layout = new QGridLayout;
    QWidget *w = new QWidget(this);
    w->setFixedWidth(400);
    w->setLayout(layout);

    QLabel *title = new QLabel(tr("Project Informations"), this);
    title->setObjectName("blLabelFormHeader1");
    layout->addWidget(title, 0, 0, 1, 3);

    QPushButton *help = new QPushButton("?", this);
    help->setMaximumWidth(32);
    help->setObjectName("btnDefault");
    connect(help, SIGNAL(released()), this, SLOT(showHelp()));
    layout->addWidget(help, 1, 2, 1, 1, Qt::AlignRight);

    QLabel *nameLabel = new QLabel("Name", this);
    m_nameEdit = new QLineEdit(this);
    layout->addWidget(nameLabel, 2, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(m_nameEdit, 2, 1, 1, 2);

    QLabel *descriptionLabel = new QLabel("Description", this);
    m_descriptionEdit = new QTextEdit(this);
    layout->addWidget(descriptionLabel, 3, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(m_descriptionEdit, 3, 1, 1, 2);

    QLabel *typeLabel = new QLabel("Project type", this);
    m_typeEdit = new QComboBox(this);
    for(int i = 0 ; i < projectTypes.count() ; i++){
        blProjectType type = projectTypes.at(i);
        m_typeEdit->addItem(type.name(), type.id());
    }

    layout->addWidget(typeLabel, 4, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(m_typeEdit, 4, 1, 1, 2);

    m_saveButton = new QPushButton("Save");
    m_saveButton->setObjectName("btnPrimary");
    m_saveButton->setMaximumWidth(150);
    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(emitEditedProject()));
    layout->addWidget(m_saveButton, 5, 2, 1, 1);

    m_twoSideWidget->addLeftWidget(w);
    m_twoSideWidget->addLeftWidget(new QWidget(this));
}

void blProjectInfoForm::emitEditedProject(){
    blProjectInfo* info = new blProjectInfo();
    info->setId(m_projectId);
    info->setName(m_nameEdit->text());
    info->setDescription(m_descriptionEdit->toPlainText());
    info->setTypeId(qvariant_cast<int>(m_typeEdit->currentData()));
    emit askEditProject(info);
}

void blProjectInfoForm::showHelp(){
    QLabel *helpWidget = new QLabel("Type and add the conditions names");
    helpWidget->setMinimumHeight(150);
    m_twoSideWidget->setRightWidget(0,helpWidget,100);
}
