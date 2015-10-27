#include "blFinderBar.h"
#include "../../blWidgets/blSearchBarWidget.h"
#include "../../blWidgets/blHideableWidget.h"
#include "../../blWidgets/blButtonId.h"
#include "../model/blFinderAccess.h"

blFinderBar::blFinderBar(QWidget *parent) : QWidget(parent)
{

    QVBoxLayout *layout = new QVBoxLayout;
    QWidget *content = new QWidget(this);
    m_contentLayout = new QGridLayout;
    content->setLayout(m_contentLayout);
    layout->addWidget(content);
    layout->addWidget(new QWidget(this), 1, Qt::AlignTop);

    // authors area
    createSearchArea();
    createFinderArea();
    createOrigin();
    createCategoriesArea();
    m_contentLayout->addWidget(new QWidget, 4, 0, 1, 1, Qt::AlignLeft );

    QWidget *container = new QWidget(this);
    container->setLayout(layout);

    QHBoxLayout *containerLayout = new QHBoxLayout;
    containerLayout->setContentsMargins(0,0,0,0);
    containerLayout->addWidget(container);
    this->setLayout(containerLayout);
    container->setObjectName("blFinderBar");
}

void blFinderBar::createSearchArea(){
    m_searchBar = new blSearchBarWidget(this);
    m_contentLayout->addWidget(m_searchBar, 0, 0, 1, 1);

    connect(m_searchBar, SIGNAL(search(QString)), this, SIGNAL(search(QString)));
}

void blFinderBar::createFinderArea(){

    QPushButton *finderButton = new QPushButton(tr("Finder"), this);
    finderButton->setObjectName("blFinderBarFinderButton");
    m_contentLayout->addWidget(finderButton, 1, 0, 1, 1);

    connect(finderButton, SIGNAL(pressed()), this, SIGNAL(finder()));
}

void blFinderBar::createOrigin(){

    blHideableWidget *originsWidget = new blHideableWidget(tr("Origins"), 4, this);

    QWidget *originsList = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(2);
    originsList->setLayout(layout);
    originsWidget->addWidget(originsList);

    QList<blFinderOriginInfo> origins = blFinderAccess::instance()->database()->origins();
    for (int i = 0 ; i < origins.count() ; ++i){
        blFinderOriginInfo origin = origins[i];
        blButtonId *button = new blButtonId( origin.name() , this);
        button->setId(origin.id());
        button->setObjectName("blFinderBarSubButton");
        layout->addWidget(button);

        connect(button, SIGNAL(clicked(int)), this, SIGNAL(origin(int)));
    }

    m_contentLayout->addWidget(originsWidget, 2, 0, 1, 1);
}

void blFinderBar::createCategoriesArea(){

    blHideableWidget *categoriesWidget = new blHideableWidget(tr("Softwares"), 4, this);

    QWidget *categoriesList = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(2);
    categoriesList->setLayout(layout);
    categoriesWidget->addWidget(categoriesList);

    QList<blFinderKeywordInfo> categories = blFinderAccess::instance()->database()->keywordsByCategory("Software");
    for (int i = 0 ; i < categories.count() ; ++i){
        blFinderKeywordInfo category = categories[i];
        blButtonId *button = new blButtonId( category.name() , this);
        button->setObjectName("blFinderBarSubButton");
        button->setId(category.id());
        layout->addWidget(button);

        connect(button, SIGNAL(clicked(int)), this, SIGNAL(category(int)));
    }

    m_contentLayout->addWidget(categoriesWidget, 3, 0, 1, 1);

}

blSearchBarWidget *blFinderBar::searchBar(){
    return m_searchBar;
}
