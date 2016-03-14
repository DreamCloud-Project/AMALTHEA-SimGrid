#!/bin/bash

# Clean everything
echo 'Cleaning ...'
rm OUTPUT_FILES/* > /dev/null 2>&1
rm Buffer/* > /dev/null 2>&1
make clean > /dev/null 2>&1
make -f Makefile_post_process clean > /dev/null 2>&1
echo 'cleaning done'

export LD_LIBRARY_PATH=/usr/local/simgrid_dev/lib/

# Compile everything
echo 'Compiling ...'
make > /dev/null 2>&1
make -f Makefile_post_process > /dev/null 2>&1
echo 'compilation done'

# Launch the simulation of the application on the platform
#./main --cfg=tracing:1 --cfg=tracing/msg/process:1 > OUTPUT_FILES/OUTPUT_Execution_Energy_Repport.txt 2>&1   # Redirect stdout and stderr towards the same output file

echo 'Running simulation ...'
./main > Buffer/Output.out 2>&1
./Post_process
cp Template/simgrid_template.trace OUTPUT_FILES/simgrid.trace
./Paje_process
rm *.o
echo 'simulation done'

#rm Buffer/Output.out Buffer/Buffer.out


# Launch Paje
vite OUTPUT_FILES/simgrid.trace  > /dev/null 2>&1 &
