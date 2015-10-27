/// \file khToolInfo.h
/// \brief khToolInfo
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) Khimbio 2015

#pragma once

#include <QString>
#include <QStringList>
#include "blToolExport.h"

/// \class blToolIO
/// \brief Contains the informations of tool inputs/outputs
class BLTOOL_EXPORT blToolIO{

public:
    /// \fn blToolIO();
    /// \brief Constructor
    blToolIO();
    /// \fn ~blToolIO();
    /// \brief Destructor
    ~blToolIO();

public:
    // getters/setters
    void addInput(QString name, QString type);
    void addOutput(QString name, QString type);

    unsigned int inputsCount();
    unsigned int outputsCount();

    QString inputNameAt(unsigned int i);
    QString inputTypeAt(unsigned int i);

    QString outputNameAt(unsigned int i);
    QString outputTypeAt(unsigned int i);

    QStringList inputsNames();
    QStringList inputsTypes();
    QStringList outputsNames();
    QStringList outputsTypes();

    void print();

private:
    QStringList m_inputsNames;
    QStringList m_inputsTypes;
    QStringList m_outputsNames;
    QStringList m_outputsTypes;
};
