#include "blFinderItem.h"

blFinderItem::blFinderItem(blFinderTutorialInfo info, QWidget *parent) : QWidget(parent)
{

    m_id = info.id();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(2,2,2,2);
    layout->setSpacing(0);
    QWidget *totalWidget = new QWidget(this);
    QVBoxLayout *totalLayout = new QVBoxLayout;
    totalLayout->setContentsMargins(2,2,2,2);
    totalWidget->setLayout(layout);
    this->setLayout(totalLayout);
    totalLayout->addWidget(totalWidget);
    totalWidget->setObjectName("blFinderItem");

    // image
    QLabel *imageLabel = new QLabel(this);
    imageLabel->setCursor(Qt::PointingHandCursor);
    imageLabel->setPixmap(QPixmap::fromImage(QImage(info.imageUrl())).scaled(300, 200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    layout->addWidget(imageLabel);

    // title
    QLabel *titleLabel = new QLabel(info.title(), this);
    titleLabel->setCursor(Qt::PointingHandCursor);
    titleLabel->setObjectName("blFinderItemTitle");
    layout->addWidget(titleLabel);



    QWidget *widget = new QWidget(this);
    //widget->setStyleSheet("QWidget{background-color:#404040;}");

    QGridLayout *grid = new QGridLayout;
    grid->setContentsMargins(0,0,0,0);
    grid->setSpacing(0);
    widget->setLayout(grid);


    QWidget *cont = new QWidget(this);
    QVBoxLayout *contLayout = new QVBoxLayout;
    contLayout->setContentsMargins(0,0,0,0);
    cont->setLayout(contLayout);
    contLayout->addWidget(widget);
    layout->addWidget(cont);
    //cont->setStyleSheet("QWidget{background-color:#404040;}");
    cont->setObjectName("blFinderItemInfoArea");

    // language
    QPushButton *languageIcon = new QPushButton(this);
    languageIcon->setObjectName("blFinderItemLanguageButton");
    languageIcon->setFixedWidth(32);
    QLabel *languageLabel = new QLabel(info.language(), this);
    languageLabel->setObjectName("blFinderItemInfoLabel");
    grid->addWidget(languageIcon, 0, 0, 1, 1);
    grid->addWidget(languageLabel, 0, 1, 1, 1);

    // origin
    QPushButton *originIcon = new QPushButton(this);
    originIcon->setObjectName("blFinderItemOriginButton");
    originIcon->setFixedWidth(32);
    QLabel *originLabel = new QLabel(info.originName(), this);
    originLabel->setObjectName("blFinderItemInfoLabel");
    grid->addWidget(originIcon, 1, 0, 1, 1);
    grid->addWidget(originLabel, 1, 1, 1, 1);

    // author
    QPushButton *authorIcon = new QPushButton(this);
    authorIcon->setObjectName("blFinderItemAuthorButton");
    authorIcon->setFixedWidth(32);
    QString authors = "";
    for (int i = 0 ; i < info.countAuthors() ; ++i){
        authors += info.authorAt(i);
        if (i < info.countAuthors()-1){
            authors += ", ";
        }
    }

    QLabel *authorLabel = new QLabel(authors, this);
    authorLabel->setObjectName("blFinderItemInfoLabel");
    grid->addWidget(authorIcon, 2, 0, 1, 1);
    grid->addWidget(authorLabel, 2, 1, 1, 1);
}

blFinderItem::blFinderItem(blFinderSectionInfo info, QWidget *parent)
    : QWidget(parent){


    m_id = info.id();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setContentsMargins(2,2,2,2);
    QWidget *totalWidget = new QWidget(this);
    QVBoxLayout *totalLayout = new QVBoxLayout;
    totalLayout->setContentsMargins(2,2,2,2);
    totalWidget->setLayout(layout);
    this->setLayout(totalLayout);
    totalLayout->addWidget(totalWidget);
    totalWidget->setObjectName("blFinderItem");

    // image
    QLabel *imageLabel = new QLabel(this);
    imageLabel->setCursor(Qt::PointingHandCursor);
    imageLabel->setPixmap(QPixmap::fromImage(QImage(info.imageUrl())).scaled(300, 200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    layout->addWidget(imageLabel);

    // title
    QLabel *titleLabel = new QLabel(info.name(), this);
    titleLabel->setCursor(Qt::PointingHandCursor);
    titleLabel->setObjectName("blFinderItemTitle");
    layout->addWidget(titleLabel);

    // desc
    QTextEdit *descEdit = new QTextEdit(this);
    descEdit->setText(info.description());
    descEdit->setObjectName("blFinderItemDesc");
    descEdit->setReadOnly(true);
    layout->addWidget(descEdit);
}

void blFinderItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        clicked(m_id);
    }
}
