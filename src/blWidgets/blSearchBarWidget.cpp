#include "blSearchBarWidget.h"

#include <QHBoxLayout>
#include <QPushButton>

blSearchBarWidget::blSearchBarWidget(QWidget *parent) :
    QLineEdit(parent)
{
    m_defaultText = tr("Search");
    this->setText(m_defaultText);

    QPushButton *valideRecherche = new QPushButton("", this);
    valideRecherche->setObjectName("blSearchBarWidgetButton");
    QHBoxLayout *rechercheLayout = new QHBoxLayout;
    this->setLayout(rechercheLayout);

    rechercheLayout->addWidget(valideRecherche, 0, Qt::AlignRight);
    rechercheLayout->setContentsMargins(0,0,0,0);
    rechercheLayout->setSpacing(0);
    rechercheLayout->setMargin(2);

    connect(this, SIGNAL(returnPressed()), this, SLOT(emitSearch()));
    connect(this, SIGNAL(selectionChanged()), this, SLOT(removeSearch()));
    connect(valideRecherche, SIGNAL(clicked()), this, SLOT(emitSearch()));
}

void blSearchBarWidget::emitSearch(){
    emit search(this->text());
}

void blSearchBarWidget::removeSearch(){
    if (this->text() == m_defaultText){
        this->setText("");
    }
}

void blSearchBarWidget::setAutoComplete(QStringList wordList){

    QCompleter *completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    this->setCompleter(completer);
}
