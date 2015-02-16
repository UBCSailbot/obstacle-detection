################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../img_proc/test/HorizonFinder_test.cpp 

OBJS += \
./img_proc/test/HorizonFinder_test.o 

CPP_DEPS += \
./img_proc/test/HorizonFinder_test.d 


# Each subdirectory must supply rules for building sources it contributes
img_proc/test/%.o: ../img_proc/test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=gnu++11 -DQT_SHARED -I/usr/include/opencv -I"/home/paul/workspace_cpp/OA/img_proc/src" -I/usr/include/qt4 -I/usr/include/qt4/QtTest -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


