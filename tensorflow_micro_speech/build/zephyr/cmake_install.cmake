# Install script for directory: /home/jolu/ncs/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/jolu/ncs/tensorflow_micro_speech/build/zephyr/arch/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/zephyr/lib/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/zephyr/soc/arm/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/zephyr/boards/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/zephyr/subsys/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/zephyr/drivers/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/nrf/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/mcuboot/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/mcumgr/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/nrfxlib/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/cmsis/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/canopennode/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/civetweb/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/fatfs/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/nordic/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/st/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/libmetal/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/lvgl/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/mbedtls/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/open-amp/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/loramac-node/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/openthread/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/segger/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/tinycbor/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/tinycrypt/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/littlefs/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/mipi-sys-t/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/modules/nrf_hw_models/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/zephyr/kernel/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/zephyr/cmake/flash/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/zephyr/cmake/usage/cmake_install.cmake")
  include("/home/jolu/ncs/tensorflow_micro_speech/build/zephyr/cmake/reports/cmake_install.cmake")

endif()

