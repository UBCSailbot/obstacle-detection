################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../img_proc/HorizonFoundImg.cpp \
../img_proc/HorizonFoundImg_test.cpp \
../img_proc/HorizontalHorizon.cpp \
../img_proc/HorizontalHorizon_test.cpp \
../img_proc/VerticalHorizon.cpp \
../img_proc/VerticalHorizon_test.cpp \
../img_proc/horizon_finder.cpp \
../img_proc/hough_mod.cpp 

OBJS += \
./img_proc/HorizonFoundImg.o \
./img_proc/HorizonFoundImg_test.o \
./img_proc/HorizontalHorizon.o \
./img_proc/HorizontalHorizon_test.o \
./img_proc/VerticalHorizon.o \
./img_proc/VerticalHorizon_test.o \
./img_proc/horizon_finder.o \
./img_proc/hough_mod.o 

CPP_DEPS += \
./img_proc/HorizonFoundImg.d \
./img_proc/HorizonFoundImg_test.d \
./img_proc/HorizontalHorizon.d \
./img_proc/HorizontalHorizon_test.d \
./img_proc/VerticalHorizon.d \
./img_proc/VerticalHorizon_test.d \
./img_proc/horizon_finder.d \
./img_proc/hough_mod.d 


# Each subdirectory must supply rules for building sources it contributes
img_proc/%.o: ../img_proc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=gnu++11 -I/usr/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


