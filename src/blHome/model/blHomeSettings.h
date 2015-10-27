#pragma once

#include <QtWidgets>
#include "blHomeExport"

/// \class blHomeSettings
/// \brief Class containg any settings as key = value
class BLHOME_EXPORT blHomeSettings
{
public:
    blHomeSettings();

public:
    // setters getters
    void add(QString key, QString value, QString type = "string");
    QString value(QString key);
    QString type(QString key);
    QMap<QString, QStringList> map();

public:
    void print();
    friend QDataStream & operator <<(QDataStream &s, const blHomeSettings &c);
    friend QDataStream & operator >>(QDataStream& stream, blHomeSettings& c);

protected:
    QMap<QString, QStringList> m_map; // 0: value, 1:type(number, string, url)
};
