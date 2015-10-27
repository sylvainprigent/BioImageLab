/// \file blToolParser.h
/// \brief blToolParser
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2015
///
/// Copyright (C) BioImageLab 2015

#pragma once

#include "blToolInfo.h"
#include <QtXml/QDomNode>
#include "blToolExport.h"

/// \class blToolParser
/// \brief Load tools from xml files, and store information into
/// the tools database
class BLTOOL_EXPORT blToolParser{

public:
    /// \fn blToolParser();
    /// \brief Constructor
    blToolParser();
    /// \fn ~khToolIO();
    /// \brief Destructor
    ~blToolParser();

public:
    void loadTools(QString dir);
    blToolInfo* getToolInfo(QString xmlURL);
    QList<blToolInfo*> getToolsInfo(QString dirUrl);

private:
    blToolParameter parseParameter(QDomNode node, QString xmlDir);
};
