/// \file blToolInfo.h
/// \brief blToolInfo
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2014
///
/// Copyright (C) blimbio 2015

#pragma once

#include <QString>
#include "blToolIO.h"
#include "blToolParameters.h"
#include "blToolCoreExport.h"

/// \class blToolInfo
/// \brief Contains the informations of a Tool
class BLTOOLCORE_EXPORT blToolInfo{

public:
    /// \fn blToolInfo();
    /// \brief Constructor
    blToolInfo();
    /// \fn ~blToolInfo();
    /// \brief Destructor
    ~blToolInfo();

public:
    // setters
    /// \fn void setId(unsigned int id);
    /// \param[in] id Id of the tool in the database
    void setId(int id);
    /// \fn void setName(QString name);
    /// \param[in] name Name of the tool
    void setName(QString name);
    /// \fn void setTitle(QString title);
    /// \param[in] name Title of the tool
    void setTitle(QString title);
    /// \fn void setVersion(QString version);
    /// \param[in] version Version number of the tool
    void setVersion(QString version);
    /// \fn void setToolbox(QString toolbox);
    /// \param[in] toolbox toolbox of the tool
    void setToolbox(QString toolbox);
    /// \fn void setInterpreter(QString interpreter);
    /// \param[in] interpreter Interpreter needed to run the tool (shell, python, native...)
    void setInterpreter(QString interpreter);
    /// \fn void setDatatype(QString type);
    /// \param[in] type Type of data processed by the tool (usefull for the viewers only)
    void setDatatype(QString type);
    /// \fn void setDescription(QString description);
    /// \param[in] description A short description of the tool functionalities
    void setDescription(QString description);
    /// \fn void setDoc(QString doc);
    /// \param[in] doc Documentation of the plugin documentation
    void setDoc(QString doc);
    /// \fn void setCommand(QString url);
    /// \param[in] url URL of the tool if native, command line if external
    void setCommand(QString url);
    /// \fn void setXmlUrl(QString url);
    /// \param[in] url URL of the xml file
    void setXmlUrl(QString url);
    /// \fn void setKeywords(QStringList &keywords);
    /// \param[in] keywords Keywords describing the tool
    void setKeywords(QStringList &keywords);
    /// \fn void setIO(blToolIO &io);
    ///  \param[in] io Object containing the inputs/outpus descriptions
    void setIO(blToolIO &io);
    /// \fn void setParameters(blToolParameters parameters);
    /// \param[in] parameters Tool parameters
    void setParameters(blToolParameters parameters);
    /// \fn void setIdInWorkflow();
    /// \param[in] id The id of the tool in the workflow
    void setIdInWorkflow(QString id);

public:
    // getters
    /// \fn int id();
    /// \return the Id of the project in the database
    int id();
    /// \fn QString name();
    /// \return the name of the project
    QString name();
    /// \fn QString title();
    /// \return the type of the tool
    QString title();
    /// \fn QString version();
    /// \return the version of the tool
    QString version();
    /// \fn QString toolbox();
    /// \return the toolbox of the tool
    QString toolbox();
    /// \fn QString interpreter();
    /// \return the interpreter needed to run the tool
    QString interpreter();
    /// \fn QString type();
    /// \return the type of the inptu data (for viewers only)
    QString datatype();
    /// \fn QString description();
    /// \return A short description of the plugin functionalities
    QString description();
    /// \fn QString urlDoc();
    /// \return the URL of the plugin documentation
    QString doc();
    /// \fn QString command();
    /// \return commande line
    QString command();
    /// \fn QString xmlurl();
    /// \return URL of the xml file
    QString xmlurl();
    /// \fn QStringList keywords();
    /// \return the keywords list
    QStringList keywords();
    /// \fn blToolIO io();
    /// \return the IO info object
    blToolIO getIO();
    /// \fn blToolParameters parameters();
    /// \return the tool parameters
    blToolParameters parameters();

    /// \fn void print();
    /// \brief print the content to consol
    void print();

public:
    friend QDataStream & operator <<(QDataStream &s, const blToolInfo &c);
    friend QDataStream & operator >>(QDataStream& stream, blToolInfo& c);

private:
    unsigned int m_id; ///< id of the project in the database
    QString m_name; ///< name
    QString m_title; ///< title
    QString m_version; ///<version
    QString m_toolbox; ///< toolbox
    QString m_interpreter; ///< interpreter to run the tool
    QString m_datatype; ///< datatype for viewer
    QString m_description; ///< A short description of the tool functionalities
    QString m_doc; ///< the tool documentation
    QString m_command; ///< command line
    QString m_xmlurl; ///< xml url
    QStringList m_keywords; ///< keywords list
    blToolIO m_io;///< IO container
    QString m_idInWorkflow; ///< id of the tool in the workflow
    blToolParameters m_parameters;
};
