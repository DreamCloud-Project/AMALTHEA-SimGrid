# AMALTHEA-SimGrid

This repository contains the simulator used to simulate cloud applications described using the Amalthea application model on top of a cloud computing architecture. Once you have unzipped the archive provided in this repository, follow the steps below to run a simulation.

## Installing SimGrid ##

This simulator relies on SimGrid, so you must first install it to run a simulation.
Install the latest version of SimGrid (the latest stable version is 3.12 released in oct. 2015).

The source of the latest version can be found at : 
    	   - https://gforge.inria.fr/frs/download.php/file/35215/SimGrid-3.12.tar.gz
If this doesn't work, go to the SimGrid website http://simgrid.gforge.inria.fr/ -> "Get it!" (http://simgrid.gforge.inria.fr/download.html). It is not sure that "apt-get install simg
rid" gives the latest version. You may try 
   	   - apt-get install simgrid
You may also try to get the latest unstable version
    	   - git clone git://scm.gforge.inria.fr/simgrid/simgrid.git

If you have simgrid by its source files (i.e. if you used the first or the third options above), you have to build it. In that case, you will find an INSTALL file in the downloaded f
older. Read the INSTALL file and follow the steps. For the fist step ((1) configure SimGrid) you have many options. The option -DCMAKE_INSTALL_PREFIX=<path> allows you to specify whe
re to install simgrid on your system. You may as well specify no option.

## Run the simulation

This directory contains the following contents. Pay attention to the 5th point!

1. Parser contains the source code for AMALTHEA parser and the integration file (dcMain.cpp).
The integration file integrates the AMALTHEA parser  with SimGrid tool.

2. OUTPUT_FILES directory contains the simulation reports, generated after simulation.

3. storage_input directory contains the content of a storage.

4. User_Manual.pdf is the user manual, which explains, how to configure and simulate the framework.

5. Compile_and_Execute.sh is the scripts file, which compiles and executes the framework, after configuring the system according to the instruction, provided by user manual. After th
e simulations, simulation reports are generated as mentioned in 2nd point, and Vite visualization tool displays the temporal output of the framework. To properly compile and run the 
simulation, you will need to install the xerces library (http://xerces.apache.org/xerces-c/install-3.html).
Before launching Compile_and_Execute.sh, you will need to check the paths in the files : Makefile and Compile_and_Execute.sh. 
	* In the file "Makefile", set the following variables accordingly:
      XERCES_DIR = /usr/local/xercesc311 : set the location of the xerces according to your system
      INSTALL_PATH = /usr/local/simgrid_dev : set the location of simgrid according to your system
	* In the Compile_and_Ecxecute.sh, set the following variables accordingly:
     export LD_LIBRARY_PATH=/usr/local/simgrid_dev/lib/ : set the location of the simgrid library according to your system

## Details of the simulation

- The input applications to the simulator are specified in the ./Parser/dcConfiguration.h file
- The xml files describing the input applications are located in the ./Parser/ApplicationModels folder. TAKE CARE that the applications files contain dummy values for the memory size
s and the computation amounts.
- The xml files describing the platform are located in the ./Parser/DeploymentFiles folder. This folder consists of 
      	  		- msg_deployment_dev.xml specifying the number of hosts and who is the slave/master
			- msg_platform_dev.xml specifying the physical properties of the platform. TAKE CARE that the platform file contains some dummy values (for example regarding 
the memory red/write bandwith)
- To launch the application, move to the folder where this README file is located and type ./Compile_and_Execute.sh
- The output of the simulation is located in the folder ./OUTPUT_FILES. The output consists of the following files:
	      	     	- Energy.out 
			- Mapping_details.out  
			- Simmulation_summary.out
			- Execution_trace.out  
			- simgrid.trace is used by vite to visualise the temporal behaviour of the simulation

## Licence

This software is made available under the  GNU Lesser General Public License v3.0

Report bugs at: mcsim-support@lirmm.fr  

(C)2016 CNRS and Université de Montpellier

