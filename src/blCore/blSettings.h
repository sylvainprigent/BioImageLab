#pragma once

#include <QtWidgets>
#include "blCoreExport"

/// \class blSettings
/// \brief Class containg any settings as key = value
class BLCORE_EXPORT blSettings
{
public:
    blSettings();

public:
    // setters getters
    void add(QString key, QString value, QString type = "string");
    QString value(QString key, bool createIfNotExists = false);
    QString type(QString key);
    QMap<QString, QStringList> map();

public:
    void print();
    friend QDataStream & operator <<(QDataStream &s, const blSettings &c);
    friend QDataStream & operator >>(QDataStream& stream, blSettings& c);

protected:
    QMap<QString, QStringList> m_map; // 0: value, 1:type(number, string, url)
};
