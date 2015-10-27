#pragma once

#include <QtWidgets>
#include "blFinderExport.h"
#include "../model/blFinderTutorialInfo.h"
#include "../model/blFinderAuthorInfo.h"
#include "../model/blFinderKeywordInfo.h"
#include "../model/blFinderOriginInfo.h"
#include "../../blWidgets/blMultipleComboBox.h"

class BLFINDER_EXPORT blFinderAdminTutorialEdit : public QWidget
{
    Q_OBJECT
public:
    explicit blFinderAdminTutorialEdit(QList<blFinderOriginInfo> origins, QList<blFinderAuthorInfo> authors, QList<blFinderKeywordInfo> keywords, QWidget *parent = 0);


signals:
    void editInfo(blFinderTutorialInfo info);
    void cancel();
    void remove(int id);

public:
    void setInfo(blFinderTutorialInfo info);

private slots:
    void emitEditInfo();
    void emitRemove();

private:
    int m_id;
    QLineEdit *m_title;
    QLineEdit *m_language;
    QComboBox *m_origin;
    QLineEdit *m_image_url;
    QLineEdit *m_xml_url;
    QLineEdit *m_doc_url;
    blMultipleComboBox* m_authors;
    blMultipleComboBox* m_keywords;

private:
    QPushButton *m_removeButton;
};
