# TF_NCS_dev
This repo is a work in progress project where the goal is to run tenserflow lite microcontroller example code on the nrf9160 using Zephyr. 


There is no guarantee that this repo will work



##### Description
> Tensorflow examples in zephyr on nrf products:
> Using the  



## info: before u start/good to know:
> U need the following, probebaly more:
> Zephyr-sdk repo
> nsc repo
> tenserflow repo
> how u want to settup it u is up to u 

Link to TF lite micro : https://www.tensorflow.org/lite/microcontrollers  
Link to TF lite micro Hello World! exampel: https://github.com/tensorflow/tensorflow/tree/master/tensorflow/lite/micro/examples/hello_world  

### How to set up
This is how i did it:  
Operating system: linux based  


### 1


### 2


### How to run an example 
make shure u have the flatbuffers/flatbufers.h file, this can be made doing the following,  
run make -f tensorflow/lite/micro/tools/make/Makefile third_party_downloads  
or if that does not work run this exampel to build the same files, u dont acualy need to use the genrated exameple but it wil include make shure that you have the correct files.  
run make -f tensorflow/lite/micro/tools/make/Makefile TARGET=esp generate_hello_world_esp_project  

Then u kan do the following to build whut Cmake 
go to exampel >TF_hello_world_nrfXX 
run west build -b ``<your board of coise>`` 
run west flash

## How to use segger system view

moddify the file profiler_sysview.h file in path nrf>subsys>profiler> to include ``#include <SEGGER_SYSVIEW.h>``.
in the proj.conf file of your porject adde the following: 
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

Download the segger Sysview program to  yur operatisg system of choise:
 https://www.segger.com/downloads/systemview/ 



