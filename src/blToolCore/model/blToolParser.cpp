/// \file blToolParser.cpp
/// \brief blToolParser
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2015
///
/// Copyright (C) BioImageLab 2015

#include "blToolParser.h"
#include <QtXml>

blToolParser::blToolParser(){

}

blToolParser::~blToolParser(){

}

blToolInfo* blToolParser::getToolInfo(QString xmlURL){

    blToolInfo *toolInfo = new blToolInfo();
    toolInfo->setXmlUrl(xmlURL);
    blToolIO toolIO;
    blToolParameters toolParameters;

    QFileInfo fileInfo(xmlURL);
    QString xmlDir = fileInfo.absolutePath();

    QDomDocument dom("parameterXML");
        QFile xml_doc(xmlURL);
        if(!xml_doc.open(QIODevice::ReadOnly))
        {
            qDebug() << "The XML" + xmlURL + " file cannot be read";
            //QMessageBox::warning(this, "Error openning XML file", "The XML" + xmlFileURL + " file cannot be read");
            return toolInfo;
        }
        if (!dom.setContent(&xml_doc))
        {
            xml_doc.close();
            qDebug() << "The XML" + xmlURL + "cannot be read as a QDomDocument.";
            //QMessageBox::warning(this, "Error openning XML file", "The XML" + xmlFileURL + "cannot be read as a QDomDocument.");
            return toolInfo;
        }

        QDomElement dom_element = dom.documentElement();
        QDomNode node = dom_element.firstChild(); // tool child
        if (!node.isNull()){
            QDomElement e = node.toElement();    
            toolInfo->setName(e.attribute("id"));
            toolInfo->setTitle(e.attribute("name"));
            toolInfo->setVersion(e.attribute("version"));
            toolInfo->setDatatype(e.attribute("datatype"));
            toolInfo->setToolbox("");

            QDomNodeList nodeList = node.childNodes();
            for(int n = 0 ; n < nodeList.count() ; ++n){
                QDomNode nodeN = nodeList.at(n);
                if(nodeN.nodeName() == "description"){
                    toolInfo->setDescription(nodeN.toElement().text());
                }
                else if(nodeN.nodeName() == "command"){
                    toolInfo->setInterpreter(nodeN.toElement().attribute("interpreter"));
                    toolInfo->setCommand(nodeN.toElement().text().simplified());
                }
                else if(nodeN.nodeName() == "inputs"){
                    QDomNodeList inputsNodes = nodeN.childNodes();
                    for (int c = 0 ; c < inputsNodes.count() ; ++c){
                        QDomNode nodeio = inputsNodes.at(c);
                        //qDebug() << "load input = " << nodeio.toElement().attribute("name") << "-------";
                        if(nodeio.nodeName() == "param"){
                            if (nodeio.toElement().attribute("type") == "data"){
                                toolIO.addInput(nodeio.toElement().attribute("name"),
                                                nodeio.toElement().attribute("format"));
                            }
                            else{
                                //qDebug() << "parse normal parameter";
                                blToolParameter toolparameter = parseParameter(nodeio, xmlDir);
                                toolParameters.add(toolparameter);
                            }
                        }
                        else if(nodeio.nodeName() == "conditional"){
                            //qDebug() << "parse conditional parameter";
                            QDomNodeList conditionalNodes = nodeio.childNodes();
                            QString contitionName = nodeio.toElement().attribute("name");
                            //qDebug() << "conditional name = " << contitionName;
                            for (int cond = 0 ; cond < conditionalNodes.count() ; ++cond){
                                QDomNode nodeCond = conditionalNodes.at(cond);
                                // get the condion param
                                if(nodeCond.nodeName() == "param"){
                                    //qDebug() << "conditional add param = " << nodeCond.toElement().attribute("name");
                                    blToolParameter toolparameter = parseParameter(nodeCond, xmlDir);
                                    contitionName = toolparameter.name();
                                    toolParameters.add(toolparameter);
                                }
                                // add the condional params
                                else if (nodeCond.nodeName() == "when"){
                                    //qDebug() << "conditional add when = " << nodeCond.toElement().attribute("value");
                                    QString conditionValue = nodeCond.toElement().attribute("value");
                                    QDomNodeList whenNodes = nodeCond.childNodes();
                                    for (int wh = 0 ; wh < whenNodes.count() ; ++wh){
                                        QDomNode nodeWhen = whenNodes.at(wh);
                                        //qDebug() << "conditional add when param = " << nodeWhen.toElement().attribute("name");
                                        // add the param
                                        blToolParameter toolparameter = parseParameter(nodeWhen, xmlDir);
                                        toolParameters.add(toolparameter);
                                        // add the condition
                                        blToolParameterCondition paramCondition;
                                        paramCondition.setConditionName(contitionName);
                                        paramCondition.setConditionValue(conditionValue);
                                        paramCondition.setConditionalName(toolparameter.name());
                                        toolParameters.addCondition(paramCondition);
                                    }
                                }
                            }
                        }
                    }
                }
                else if(nodeN.nodeName() == "outputs"){
                    QDomNodeList outputsNodes = nodeN.childNodes();
                    for (int c = 0 ; c < outputsNodes.count() ; ++c){
                        QDomNode nodeio = outputsNodes.at(c);
                        toolIO.addOutput(nodeio.toElement().attribute("name"),
                                        nodeio.toElement().attribute("format"));
                    }
                }
                else if(nodeN.nodeName() == "help"){
                    toolInfo->setDoc(xmlDir + QDir::separator() + nodeN.toElement().attribute("url"));
                    //toolInfo->setDoc(nodeN.toElement().text().simplified());
                }
            }
            toolInfo->setIO(toolIO);
            toolInfo->setParameters(toolParameters);
            //toolParameters.print();
        }
        else{
            //qDebug() << "Error openning XML file", "The XML" + xmlURL + "has a syntax error";
            //QMessageBox::warning(this, "Error openning XML file", "The XML" + xmlFileURL + "has a syntax error");
        }
        //qDebug() << "parse done";
        //toolInfo->parameters().print();
        //toolInfo->print();
        return toolInfo;
}

blToolParameter blToolParser::parseParameter(QDomNode node, QString xmlDir){

    blToolParameter toolparameter;
    QString typeAttr = node.toElement().attribute("type");
    toolparameter.setName(node.toElement().attribute("name"));
    toolparameter.setType(typeAttr);
    toolparameter.setLabel(node.toElement().attribute("label"));
    toolparameter.setValue(node.toElement().attribute("value"));
    if (node.toElement().attribute("advanced") == "true"){
        toolparameter.setAdvanced(true);
    }
    else{
        toolparameter.setAdvanced(false);
    }
    toolparameter.setHelp(xmlDir + QDir::separator() + node.toElement().attribute("helpurl"));

    if(typeAttr == "select"){
        QString value = "";
        QDomNodeList optNodes = node.childNodes();
        for (int opt = 0 ; opt < optNodes.count() ; ++opt){
            QDomNode nodeopt = optNodes.at(opt);
            value += nodeopt.toElement().attribute("value") + ";";
        }
        toolparameter.setValue(value);
    }
    return toolparameter;
}

QList<blToolInfo*> blToolParser::getToolsInfo(QString dirUrl){

    QList<blToolInfo*> toolsInfo;
    QDirIterator dirIt(dirUrl,QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile()){
            if (QFileInfo(dirIt.filePath()).suffix() == "xml"){
                toolsInfo.append(this->getToolInfo(dirIt.filePath()));
            }
        }
    }
    return toolsInfo;
}
