#pragma once

#include <QtWidgets>
#include "blFinderExport.h"

class BLFINDER_EXPORT blFinderTutorialInfo
{

public:
    blFinderTutorialInfo();

public:
    // setters
    void setId(int);
    void setTitle(QString title);
    void setLanguage(QString language);
    void setOrigin(int origin);
    void setOriginName(QString origin);
    void setImageUrl(QString imageUrl);
    void setViewName(QString viewName);
    void setXmlUrl(QString url);
    void setDocUrl(QString url);

    void addKeyword(int id, QString word = "");
    void setKeywordsIds(QList<int> ids);
    int countKeywords();
    int keywordIdAt(int index);
    QString keywordAt(int index);

    void addAuthor(int id, QString printName = "");
    void setAuthorsIds(QList<int> ids);
    int countAuthors();
    int authorIdAt(int index);
    QString authorAt(int index);

public:
    // getters
    int id();
    QString title();
    QString language();
    int origin();
    QString originName();
    QString imageUrl();
    QString viewName();
    QString xmlUrl();
    QString docUrl();

private:
    int m_id;
    QString m_title;
    QString m_language;
    int m_origin;
    QString m_originName;
    QString m_image_url;
    QString m_view_name;
    QString m_xml_url;
    QString m_doc_url;
    QStringList m_authorsNames;
    QList<int> m_authorsIDs;
    QStringList m_keywords;
    QList<int> m_keywordsIDs;
};
