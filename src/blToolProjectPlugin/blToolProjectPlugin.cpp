#include "blToolProjectPlugin.h"
#include "blToolInputSelectorWidgetProject.h"

blToolProjectPlugin::blToolProjectPlugin()
    : blToolIOPluginInterface()
{

}

blToolProjectPlugin::~blToolProjectPlugin(){

}

QString blToolProjectPlugin::name(){
    return "Project";
}

blToolInputSelectorWidgetInterface* blToolProjectPlugin::selectorWidget(blToolIO toolIO, QWidget *parent){


    blToolInputSelectorWidgetProject * project = new blToolInputSelectorWidgetProject(toolIO, parent);
    return project;
}

Q_PLUGIN_METADATA(IID "blToolCore.blToolIOPluginInterface")
