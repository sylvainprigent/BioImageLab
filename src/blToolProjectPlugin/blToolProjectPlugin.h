#ifndef blToolProjectPlugin_H
#define blToolProjectPlugin_H

#include "blTool/view/blToolIOPluginInterface.h"
#include "blTool/view/blToolInputSelectorWidgetInterface.h"
#include "blToolProjectPluginExport.h"

class BLTOOLPROJECTPLUGIN_EXPORT blToolProjectPlugin : public blToolIOPluginInterface
{
    Q_INTERFACES(blToolIOPluginInterface)
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "blToolCore.blToolIOPluginInterface" FILE "blToolProjectPlugin.json")


public:
    /// \fn blToolProjectPlugin()
    /// \brief Constructor
    blToolProjectPlugin();
    /// \fn ~blToolProjectPlugin()
    /// \brief Destructor
    ~blToolProjectPlugin();

    /// \fn virtual QString name() = 0;
    /// \return the name of the plugin (for the tab title)
    QString name();
    /// \fn virtual virtual QWidget* selectorWidget(blToolIO *toolIO)=0;
    /// \param[in] toolIO Container of the data description
    /// \return a pointer to the I/O selector widget
    blToolInputSelectorWidgetInterface* selectorWidget(blToolIO toolIO, QWidget *parent);
};

#endif // blToolProjectPlugin_H
