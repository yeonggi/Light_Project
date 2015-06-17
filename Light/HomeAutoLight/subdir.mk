################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../HomeAutoLight/DateStrings.cpp \
../HomeAutoLight/HomeAutoLight.cpp \
../HomeAutoLight/Time.cpp 

OBJS += \
./HomeAutoLight/DateStrings.o \
./HomeAutoLight/HomeAutoLight.o \
./HomeAutoLight/Time.o 

CPP_DEPS += \
./HomeAutoLight/DateStrings.d \
./HomeAutoLight/HomeAutoLight.d \
./HomeAutoLight/Time.d 


# Each subdirectory must supply rules for building sources it contributes
HomeAutoLight/%.o: ../HomeAutoLight/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\Users\USER\Documents\Workspace\Light_Project\HomeAutoLight" -I"C:\Arduino\hardware\arduino\avr\libraries\RCSwitch" -I"C:\Users\USER\Documents\Workspace\ArduinoCore\src" -Wall -g1 -gstabs -O2 -ffunction-sections -fdata-sections -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


