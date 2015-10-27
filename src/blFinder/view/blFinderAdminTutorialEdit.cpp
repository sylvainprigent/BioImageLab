#include "blFinderAdminTutorialEdit.h"

blFinderAdminTutorialEdit::blFinderAdminTutorialEdit(QList<blFinderOriginInfo> origins, QList<blFinderAuthorInfo> authors, QList<blFinderKeywordInfo> keywords, QWidget *parent)
    : QWidget(parent){

    m_id = 0;

    QGridLayout *layout = new QGridLayout;
    this->setLayout(layout);

    // title
    QLabel *title = new QLabel(tr("Edit Tutorial"), this);
    layout->addWidget(title, 0, 0, 1, 5);
    title->setObjectName("blFinderAdminTableTitle");

    // name
    QLabel *nameLabel = new QLabel(tr("Title"), this);
    m_title = new QLineEdit(this);
    layout->addWidget(nameLabel, 1,0,1,4);
    layout->addWidget(m_title, 1,1,1,4);


    // language
    QLabel *languageLabel = new QLabel(tr("Language"), this);
    m_language = new QLineEdit(this);
    layout->addWidget(languageLabel, 2,0,1,4);
    layout->addWidget(m_language, 2,1,1,4);

    // origin
    QLabel *originLabel = new QLabel(tr("Origin"), this);
    m_origin = new QComboBox(this);
    layout->addWidget(originLabel, 3,0,1,4);
    layout->addWidget(m_origin, 3,1,1,4);
    for(int i = 0 ; i < origins.count() ; ++i){
        blFinderOriginInfo cat = origins[i];
        m_origin->addItem(cat.name(), cat.id());
    }

    // Image
    QLabel *imageLabel = new QLabel(tr("Image URL"), this);
    m_image_url = new QLineEdit(this);
    layout->addWidget(imageLabel, 4,0,1,4);
    layout->addWidget(m_image_url, 4,1,1,4);

    // XML
    QLabel *xmlLabel = new QLabel(tr("XML URL"), this);
    m_xml_url = new QLineEdit(this);
    layout->addWidget(xmlLabel, 5,0,1,4);
    layout->addWidget(m_xml_url, 5,1,1,4);

    // Doc
    QLabel *docLabel = new QLabel(tr("Doc URL"), this);
    m_doc_url = new QLineEdit(this);
    layout->addWidget(docLabel, 6,0,1,4);
    layout->addWidget(m_doc_url, 6,1,1,4);

    // authors
    QLabel *authorsLabel = new QLabel(tr("Authors"), this);
    QStringList authorsNames;
    QList<int> authorsIDs;
    for (int i = 0 ; i < authors.count() ; ++i){
        blFinderAuthorInfo auth = authors[i];
        authorsIDs.append(auth.id());
        authorsNames.append(auth.name() + " " + auth.firstname());
    }
    m_authors = new blMultipleComboBox(authorsNames, authorsIDs, this);
    layout->addWidget(authorsLabel, 7,0,1,4);
    layout->addWidget(m_authors, 7,1,1,4);

    // keywords
    QLabel *keywordsLabel = new QLabel(tr("Keywords"), this);
    QStringList keywordsNames;
    QList<int> keywordsIDs;
    for (int i = 0 ; i < keywords.count() ; ++i){
        blFinderKeywordInfo info = keywords[i];
        keywordsIDs.append(info.id());
        keywordsNames.append(info.name());
    }
    m_keywords = new blMultipleComboBox(keywordsNames, keywordsIDs, this);
    layout->addWidget(keywordsLabel, 8,0,1,4);
    layout->addWidget(m_keywords, 8,1,1,4);

    // buttons
    QPushButton *save = new QPushButton(tr("Save"), this);
    save->setObjectName("btnPrimary");
    QPushButton *cancel = new QPushButton(tr("Cancel"), this);
    cancel->setObjectName("btnDefault");
    m_removeButton = new QPushButton(tr("Delete"), this);
    m_removeButton->setObjectName("btnDanger");
    m_removeButton->setVisible(false);
    layout->addWidget(save, 9, 2, 1, 1);
    layout->addWidget(cancel, 9, 3, 1, 1);
    layout->addWidget(m_removeButton, 9, 4, 1, 1);

    connect(save, SIGNAL(pressed()), this, SLOT(emitEditInfo()));
    connect(cancel, SIGNAL(pressed()), this, SIGNAL(cancel()));
    connect(m_removeButton, SIGNAL(pressed()), this, SLOT(emitRemove()));
}

void blFinderAdminTutorialEdit::setInfo(blFinderTutorialInfo info){
    m_id = info.id();
    m_title->setText(info.title());
    m_language->setText(info.language());
    m_origin->setCurrentText(info.originName());
    m_image_url->setText(info.imageUrl());
    m_xml_url->setText(info.xmlUrl());
    m_doc_url->setText(info.docUrl());
    for (int i = 0 ; i < info.countAuthors() ; ++i){
        m_authors->addComboBox(info.authorAt(i));
    }
    for (int i = 0 ; i < info.countKeywords() ; ++i){
        m_keywords->addComboBox(info.keywordAt(i));
    }
    m_removeButton->setVisible(true);
}

void blFinderAdminTutorialEdit::emitEditInfo(){
    blFinderTutorialInfo info;
    info.setId(m_id);
    info.setTitle(m_title->text());
    info.setLanguage(m_language->text());
    info.setOrigin(m_origin->currentData().toInt());
    info.setXmlUrl(m_xml_url->text());
    info.setDocUrl(m_doc_url->text());
    info.setImageUrl(m_image_url->text());
    info.setAuthorsIds(m_authors->indexes());
    info.setKeywordsIds(m_keywords->indexes());
    emit editInfo(info);
}

void blFinderAdminTutorialEdit::emitRemove(){
    int reponse = QMessageBox::question(this, tr("Delete tutorial"), tr("Delete this tutorial ?"), QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        emit remove(m_id);
    }
}
