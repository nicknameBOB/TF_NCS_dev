# TF_NCS_dev
Tensorflow examples in zephyr on nrf products


some exampel code from tensorflow lite microcontrollers ported to zephyr and runing on nrf products:WIP


# info: before u start/good to know:

# How to set up


# 1


# 2


# How to run an example 


# How to use segger system view

moddify the file profiler_sysview.h file in path nrf>subsys>profiler> to include "#include <SEGGER_SYSVIEW.h>".
in the proj.conf file adde the following: 
 
CONFIG_PROFILER=y
CONFIG_USE_SEGGER_RTT=y
CONFIG_PROFILER_SYSVIEW=y
CONFIG_SEGGER_SYSTEMVIEW=y
CONFIG_TRACING=y

make shure the autoconf.h file in the build folder after building your project has the following configured coretly:
"#define CONFIG_PROFILER_SYSVIEW 1"
"#define CONFIG_SEGGER_SYSTEMVIEW 1"
"#define CONFIG_PROFILER 1"



