################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../HomeAutoLight/HomeAutoLight.cpp 

OBJS += \
./HomeAutoLight/HomeAutoLight.o 

CPP_DEPS += \
./HomeAutoLight/HomeAutoLight.d 


# Each subdirectory must supply rules for building sources it contributes
HomeAutoLight/%.o: ../HomeAutoLight/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"C:\Users\USER\Documents\Workspace\ArduinoCore\src" -I"C:\Users\USER\Documents\Workspace\Light_Project\HomeAutoLight" -Wall -g1 -gstabs -O2 -ffunction-sections -fdata-sections -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


