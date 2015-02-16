################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../img_proc/src/HorizonFoundImg.cpp \
../img_proc/src/HorizontalHorizon.cpp \
../img_proc/src/VerticalHorizon.cpp \
../img_proc/src/horizon_finder.cpp \
../img_proc/src/hough_mod.cpp 

OBJS += \
./img_proc/src/HorizonFoundImg.o \
./img_proc/src/HorizontalHorizon.o \
./img_proc/src/VerticalHorizon.o \
./img_proc/src/horizon_finder.o \
./img_proc/src/hough_mod.o 

CPP_DEPS += \
./img_proc/src/HorizonFoundImg.d \
./img_proc/src/HorizontalHorizon.d \
./img_proc/src/VerticalHorizon.d \
./img_proc/src/horizon_finder.d \
./img_proc/src/hough_mod.d 


# Each subdirectory must supply rules for building sources it contributes
img_proc/src/%.o: ../img_proc/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=gnu++11 -DQT_SHARED -I/usr/include/opencv -I"/home/paul/workspace_cpp/OA/img_proc/src" -I/usr/include/qt4 -I/usr/include/qt4/QtTest -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


