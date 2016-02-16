/// \file blToolIOPluginInterface.h.h
/// \brief blToolIOPluginInterface.h
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2015
///
/// Copyright (C) BioImageLab 2015

#pragma once

#include <QObject>
#include "blToolCore/model/blToolIO.h"
#include "blToolInputSelectorWidgetInterface.h"
#include "blToolExport.h"

/// \class blToolIOPluginInterface.h
/// \brief Define the interface for a plugin.
/// A plugin is a Input selector for the tool run widget
class BLTOOL_EXPORT blToolIOPluginInterface : public QObject
{
    Q_OBJECT
public:
    /// \fn blToolIOPluginInterface()
    /// \brief Constructor
    blToolIOPluginInterface(){}
    /// \fn ~blToolIOPluginInterface()
    /// \brief Destructor
    virtual ~blToolIOPluginInterface(){}

    /// \fn virtual QString name() = 0;
    /// \return the name of the plugin (for the tab title)
    virtual QString name() = 0;
    /// \fn virtual virtual QWidget* selectorWidget(blToolIO *toolIO)=0;
    /// \param[in] toolIO Container of the data description
    /// \return a pointer to the I/O selector widget
    virtual blToolInputSelectorWidgetInterface* selectorWidget(blToolIO toolIO, QWidget *parent)=0;

};
Q_DECLARE_INTERFACE(blToolIOPluginInterface, "blToolCore.blToolIOPluginInterface")
