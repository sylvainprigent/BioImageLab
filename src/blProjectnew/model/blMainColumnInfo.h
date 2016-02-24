#ifndef blMainColumnInfo_H
#define blMainColumnInfo_H

#include <QString>

class blMainColumnInfo
{
public:
    blMainColumnInfo();
    blMainColumnInfo(int id, QString name, QString origin_url);

public:
    int id();
    QString name();
    QString origin_url();

public:
    void setId(int id);
    void setName(QString name);
    void setOriginUrl(QString url);

private:
    int m_id;
    QString m_name;
    QString m_origin_url;

};

#endif // blMainColumnInfo_H
