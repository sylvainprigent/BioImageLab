#ifndef BLIODATALIST_H
#define BLIODATALIST_H

#include <QStringList>
#include <QDataStream>
#include "blToolExport.h"

///
/// \brief The blioDataList class
///
class BLTOOL_EXPORT blioDataList
{
public:
    blioDataList();

    void add(QString datatype, QString id, QString url);
    unsigned int count();
    QString urlAt(unsigned int index);
    QString urlAt(QString id);
    QString idAt(unsigned int index);
    QString datatypeAt(unsigned int index);

    QStringList inputIDs();
    QStringList inputUrls();
    QStringList datatypes();

    // save, print
    friend QDataStream & operator <<(QDataStream &s, const blioDataList &c);
    friend QDataStream & operator >>(QDataStream& stream, blioDataList& c);
    void print();

private:
    QStringList m_inputsID;
    QStringList m_inputsURL;
    QStringList m_inputsDatatype;

};

#endif // BLIODATALIST_H
