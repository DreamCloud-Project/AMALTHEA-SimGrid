Apart from source code, this directory contains two sub-directories.

1. ApplicationModels
This directory contains the AMALTHEA application models. The input application model can be decided by dcConfigurations.h file, located in current (Parser) disrectoy.   

2. DeploymentFiles
This directory contains two xml files.
	i. msg_platform_dev.xml: The cloud infrastructure, which defines the detailed cloud infrastructure model.
	ii. msg_deployment_dev.xml: Contains the list of resource from msg_platform_dev.xml file, which are available to execute the input application model.