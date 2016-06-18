####################
# DEVICE LIBRARIES #
####################

set( DEVICE_LIBS )

# RTIMULib is compiled with the project
include_directories(RTIMULib2 STATIC
        lib/RTIMULib2/RTIMULib)
add_subdirectory(lib/RTIMULib2/RTIMULib)
list(APPEND DEVICE_LIBS RTIMULib)


# Lepton SDK is compiled with the project
include_directories(${CMAKE_SOURCE_DIR}/lib/LeptonModule/software/raspberrypi_libs/leptonSDKEmb32PUB)
set(LEPTONSDK_DIR ${CMAKE_SOURCE_DIR}/lib/LeptonModule/software/raspberrypi_libs/leptonSDKEmb32PUB)
# TODO: We run a custom build script for leptonSDK
#  because otherwise we get lots of annoying and useless output.
#  This is far from ideal - ideally we'd have a way to remove the -v and -fpermissive
#  flags from the COMPILE variable in the Makefile, as these are the flags that cause
#  the useless output. However, modifying the Makefile directly is not an option
#  as it belongs to the LeptonSDK submodule.
add_custom_command(
        OUTPUT ${LEPTONSDK_DIR}/Debug/libLEPTON_SDK.a
        COMMAND ${CMAKE_SOURCE_DIR}/scripts/build_scripts/build_leptonSDK.sh ${LEPTONSDK_DIR}
        COMMENT "Building Lepton SDK using scripts/build_leptonSDK.sh"
)
add_custom_target(leptonSDK DEPENDS ${LEPTONSDK_DIR}/Debug/libLEPTON_SDK.a)

list(APPEND DEVICE_LIBS ${LEPTONSDK_DIR}/Debug/libLEPTON_SDK.a)


# rpusbdisp is compiled with the project
set(RPUSBDISP_DIR ${CMAKE_SOURCE_DIR}/lib/rpusbdisp/usermode-sdk)
include_directories(${RPUSBDISP_DIR})
include_directories(${RPUSBDISP_DIR}/infra/include)
include_directories(${RPUSBDISP_DIR}/rpusbdisp-drv/include)
include_directories(${RPUSBDISP_DIR}/deps-wraps/libusbx_wrap/include)
if(NOT EXISTS ${RPUSBDISP_DIR}/Makefile OR NOT EXISTS ${RPUSBDISP_DIR}/Makefile.conf)
    execute_process(COMMAND ./configure
            WORKING_DIRECTORY ${RPUSBDISP_DIR}
            )
endif(NOT EXISTS ${RPUSBDISP_DIR}/Makefile OR NOT EXISTS ${RPUSBDISP_DIR}/Makefile.conf)
add_custom_target(
        rpusbdisp
        COMMAND make
        WORKING_DIRECTORY ${RPUSBDISP_DIR}
)

list(APPEND DEVICE_LIBS ${RPUSBDISP_DIR}/build/output/rpusbdisp-drv.a)
list(APPEND DEVICE_LIBS ${RPUSBDISP_DIR}/build/output/librpusbdisp-drv.so)


# Threads library must be independently preinstalled on the host machine
find_package (Threads REQUIRED)
list(APPEND CORE_LIBS ${CMAKE_THREAD_LIBS_INIT})
