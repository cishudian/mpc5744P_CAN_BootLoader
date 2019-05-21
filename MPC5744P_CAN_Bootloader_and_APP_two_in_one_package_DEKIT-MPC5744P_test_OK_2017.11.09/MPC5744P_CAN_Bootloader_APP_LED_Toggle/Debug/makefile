################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 8
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Project_Settings/Linker_Files/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
MPC5744P_CAN_Bootloader_APP_LED_Toggle.elf \

EXECUTABLES_QUOTED += \
"MPC5744P_CAN_Bootloader_APP_LED_Toggle.elf" \

EXECUTABLES_OS_FORMAT += \
MPC5744P_CAN_Bootloader_APP_LED_Toggle.elf \

SECONDARY_FLASH += \
MPC5744P_CAN_Bootloader_APP_LED_Toggle.srec \

SECONDARY_FLASH_QUOTED += \
"MPC5744P_CAN_Bootloader_APP_LED_Toggle.srec" \

SECONDARY_FLASH_OS_FORMAT += \
MPC5744P_CAN_Bootloader_APP_LED_Toggle.srec \

SECONDARY_SIZE += \
MPC5744P_CAN_Bootloader_APP_LED_Toggle.siz \

SECONDARY_SIZE_QUOTED += \
"MPC5744P_CAN_Bootloader_APP_LED_Toggle.siz" \

SECONDARY_SIZE_OS_FORMAT += \
MPC5744P_CAN_Bootloader_APP_LED_Toggle.siz \


# All Target
all: warning-messages explicit-dependencies MPC5744P_CAN_Bootloader_APP_LED_Toggle.elf secondary-outputs

# Tool invocations
MPC5744P_CAN_Bootloader_APP_LED_Toggle.elf: $(OBJS) F:/work/workspaceS32DS.Power1.2/MPC5744P_CAN_Bootloader_APP_LED_Toggle/Project_Settings/Linker_Files/57xx_flash.ld F:/work/workspaceS32DS.Power1.2/MPC5744P_CAN_Bootloader_APP_LED_Toggle/Project_Settings/Linker_Files/libs.ld $(OSPT) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #9 $@'
	@echo 'Invoking: Standard S32DS C Linker'
	powerpc-eabivle-gcc -o "MPC5744P_CAN_Bootloader_APP_LED_Toggle.elf" "@MPC5744P_CAN_Bootloader_APP_LED_Toggle.args"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED) $(OSPT)
	@echo 'Finished building target: $@'
	@echo ' '

MPC5744P_CAN_Bootloader_APP_LED_Toggle.srec: $(EXECUTABLES)
	@echo 'Executing target #10 $@'
	@echo 'Invoking: Standard S32DS Create Flash Image'
	powerpc-eabivle-objcopy -O srec $(EXECUTABLES)  "MPC5744P_CAN_Bootloader_APP_LED_Toggle.srec"
	@echo 'Finished building: $@'
	@echo ' '

MPC5744P_CAN_Bootloader_APP_LED_Toggle.siz: $(EXECUTABLES)
	@echo 'Executing target #11 $@'
	@echo 'Invoking: Standard S32DS Print Size'
	powerpc-eabivle-size --format=berkeley $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_FLASH_QUOTED) ./*/*.d  ./*/*/*.o ./*/*.o  $(SECONDARY_SIZE_QUOTED) $(EXECUTABLES_QUOTED)
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

