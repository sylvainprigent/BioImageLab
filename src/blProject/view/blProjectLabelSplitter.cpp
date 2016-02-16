/// \file blProjectLabelSplitter.cpp
/// \brief blProjectLabelSplitter
/// \author Sylvain Prigent 
/// \version 0.1
/// \date 2014
///
/// Copyright (C) BioimageLab 2015

#include "blProjectLabelSplitter.h"

blProjectLabelSplitter::blProjectLabelSplitter(QObject *parent) : QObject(parent){

}

void blProjectLabelSplitter::setColumnName(QString columnName){
    m_columnName = columnName;
}

void blProjectLabelSplitter::setSubColumnName(QString subColumnName){
    m_subColumnName = subColumnName;
}

void blProjectLabelSplitter::setSeparator(QString separator){
    m_separator = separator;
}

void blProjectLabelSplitter::setNewSubColumnsNames(QString newSubColumnsNames){
    m_newSubColumnsNames = newSubColumnsNames;
}

void blProjectLabelSplitter::run(blProjectControler* project){

    // add the new sub columns
    QStringList subColumn = m_newSubColumnsNames.split(",");
    int splitCount = subColumn.count();
    for (int subc = 0 ; subc < subColumn.count() ; ++subc){
        project->addColumn(m_columnName, subColumn[subc], false, blProjectModelColumn::STRING);
    }

    // split the data
    blProjectModelMainColumn mainCol = project->model()->mainColumn(m_columnName);
    blProjectModelColumn col = mainCol.column(m_subColumnName);
    QMapIterator<unsigned int, QString> idata(col.data());
    unsigned int addSplitCount;
    while (idata.hasNext()) {
        idata.next();

        QStringList splitedData = idata.value().split(m_separator);

        addSplitCount = splitCount;
        if (splitedData.count() < splitCount){
            addSplitCount = splitedData.count();
        }
        for (unsigned int subc = 0 ; subc < addSplitCount ; subc++){
            project->columnAddData(m_columnName, subColumn[subc], idata.key(), splitedData[subc]);
        }
    }
}
