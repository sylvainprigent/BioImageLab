#ifndef BLIOPARAMETERS_H
#define BLIOPARAMETERS_H

#include <QStringList>
#include "blToolExport.h"

///
/// \brief The blioParameters class
///
class BLTOOL_EXPORT blioParameters
{
public:
    blioParameters();

    void add(QString key, QString value);
    unsigned int count();
    QString valueAt(unsigned int index);
    QString valueAt(QString id);
    QString keyAt(unsigned int index);

public:
    void print();
    friend QDataStream & operator <<(QDataStream &s, const blioParameters &c);
    friend QDataStream & operator >>(QDataStream& stream, blioParameters& c);

private:
    QStringList m_keys;
    QStringList m_values;
};

#endif // BLIOPARAMETERS_H
