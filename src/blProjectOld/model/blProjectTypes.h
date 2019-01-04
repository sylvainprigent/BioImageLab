#ifndef BLPROJECTTYPES_H
#define BLPROJECTTYPES_H

#include <QString>
#include <QList>

class blProjectType
{
public:
    blProjectType();
    blProjectType(int id, QString name);

public:
    int id();
    QString name();

public:
    void setId(int id);
    void setName(QString name);

private:
    int m_id;
    QString m_name;
};


class blProjectTypes
{
public:
    blProjectTypes();

public:
    int count();
    blProjectType at(int i);
    void add(blProjectType projectType);

private:
    QList<blProjectType> m_projectsTypes;

};




#endif // BLPROJECTTYPES_H
