#ifndef blSubColumnInfo_H
#define blSubColumnInfo_H

#include <QString>

class blSubColumnInfo
{
public:
    blSubColumnInfo();
    blSubColumnInfo(int id, QString name, int id_main_col, QString datatype);

public:
    int id();
    QString name();
    int id_main_col();
    QString datatype();

public:
    void setId(int id);
    void setName(QString name);
    void set_id_main_col(int id);
    void setDatatype(QString datatype);

private:
    int m_id;
    QString m_name;
    int m_id_main_col;
    QString m_datatype;
};

#endif // blSubColumnInfo_H
