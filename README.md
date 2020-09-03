# TF_NCS_dev
This repo is a work in progress project where the goal is to run tenserflow lite microcontroller example code on the nrf9160 using Zephyr. 

___

**🚧** There is no guarantee that this repo will work **🚧**
___

##### Description
> Tensorflow examples in zephyr on nrf products:  
> Using the nrf9160dk or Thingy:91 some tensorflow lite micro examples shuld be able to run.  
> Some of the exmapels is also able to run on other nrf products like nrf52840dk, Thingy:52  
>  and nrf53840dk with some changes to the code.   


## info: before u start/good to know:
Currently no native Windows suport due to some tensorflow build dependecies. 

U need the following:  
pip3  
west  
ect..  

NCS repo and tenserflow repo,  
these two repositories should be included.      

Link to TF lite micro: https://www.tensorflow.org/lite/microcontrollers  
Link to TF lite micro Hello World! exampel: https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/hello_world  
Link to NCS install guide: https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/gs_installing.html  

### How to set up:
#### This is still undergoing testing and might not be complete or might not cover all aspects.
This is how I did it on linux:  
Operating system: linux based  

Note: make sure that you have the correct enviroment and tools available and installed on your operating system.
West, nRF commandline tools, python 3.X, git ect.. if you have the tools to work on sdk-nrf(https://github.com/nrfconnect/sdk-nrf) then the only additional requirement is including tensorflow(https://github.com/tensorflow/tensorflow)
### 1
Create folder called ncs(or something you like)  
clone this repo in that folder using git clone
use ``west init-l`` to initiate the repository
use ``west update`` to gett evertying (run this command twice to makes sure everything is up to date)  
### Alternativ step 1  
Use ``west init -m <this repo link>`` in the folder you want the project  


follow Zephyrs guide on how to set up comandline tools and enviroment variabels. 

### 2
Now locate the tensorflow folder and open a terminal, run the following command:  
``make -f tensorflow/lite/micro/tools/make/Makefile third_party_downloads``



### How to run an example 
make shure u have the flatbuffers/flatbufers.h file, this can be made doing the following,  
run make -f tensorflow/lite/micro/tools/make/Makefile third_party_downloads  
or if that does not work run this exampel to build the same files, u dont acualy need to use the genrated exameple but it wil include make shure that you have the correct files.  
run make -f tensorflow/lite/micro/tools/make/Makefile TARGET=esp generate_hello_world_esp_project  

Then you can do the following to build whit Cmake 
go to example >TF_hello_world_nrfXX 
run west build -b ``<your board of choice>`` 
run west flash

## How to use segger system view

moddify the file profiler_sysview.h file in path nrf>subsys>profiler> to include ``#include <SEGGER_SYSVIEW.h>``.
in the proj.conf file of your project add the following: 
```
CONFIG_PROFILER=y
CONFIG_USE_SEGGER_RTT=y
CONFIG_PROFILER_SYSVIEW=y
CONFIG_SEGGER_SYSTEMVIEW=y
CONFIG_TRACING=y
``` 

make shure the ``autoconf.h`` file in the build folder after building your project has the following configured coretly:
```
#define CONFIG_PROFILER_SYSVIEW 1
#define CONFIG_SEGGER_SYSTEMVIEW 1
#define CONFIG_PROFILER 1
```

Download the segger Sysview program to your operating system of choice:
 https://www.segger.com/downloads/systemview/ 
