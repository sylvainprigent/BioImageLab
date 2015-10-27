#ifndef blioDataInfo_H
#define blioDataInfo_H

#include "blioDataList.h"
#include "blToolExport.h"

///
/// \brief The blInputDataList class stores the list of input data information
///
class BLTOOL_EXPORT blioDataInfo
{
public:
    // contructor
    blioDataInfo();

    // getters/setters
    unsigned int count();
    blioDataList at(unsigned int index);

    void add(blioDataList dataList);

    // load/save
    void saveAs(QString url);
    void save();
    void load(QString url);

public:
    void print();
    friend QDataStream & operator <<(QDataStream &s, const blioDataInfo &c);
    friend QDataStream & operator >>(QDataStream& stream, blioDataInfo& c);


private:
    QList<blioDataList> m_dataList;
    QString m_fileURL;

};

#endif // blioDataInfo_H
