################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include HomeAutoLight/subdir.mk
-include Debug/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
FLASH_IMAGE += \
Light_Project.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Light_Project.elf secondary-outputs

# Tool invocations
Light_Project.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -s -Os  -o"Light_Project.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lm -Wl,-Map,Light_Project.map,--cref -mrelax -Wl,--gc-sections -L"C:\Users\USER\Documents\Workspace\Light_Project\HomeAutoLight" -L"C:\Users\USER\Documents\Workspace\ArduinoCore\328P_16MHz" -L"C:\Arduino\hardware\arduino\avr\libraries\RCSwitch" -L"C:\Arduino\hardware\arduino\avr\libraries\Time" -mmcu=atmega328p
	@echo 'Finished building target: $@'
	@echo ' '

Light_Project.hex: Light_Project.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Light_Project.elf  "Light_Project.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Light_Project.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p Light_Project.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(S_DEPS)$(C_DEPS)$(FLASH_IMAGE)$(CC_DEPS)$(ELFS)$(C++_DEPS)$(OBJS)$(CXX_DEPS)$(ASM_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(CPP_DEPS) Light_Project.elf
	-@echo ' '

secondary-outputs: $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
