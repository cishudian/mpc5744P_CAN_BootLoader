################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS_QUOTED += \
"../Project_Settings/Startup_Code/startup.S" \

S_UPPER_SRCS += \
../Project_Settings/Startup_Code/startup.S \

OBJS_QUOTED += \
"./Project_Settings/Startup_Code/startup.o" \

OBJS_OS_FORMAT += \
./Project_Settings/Startup_Code/startup.o \

OBJS += \
./Project_Settings/Startup_Code/startup.o \


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/startup.o: ../Project_Settings/Startup_Code/startup.S
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: Standard S32DS Assembler'
	powerpc-eabivle-gcc "@Project_Settings/Startup_Code/startup.args" -c -o "Project_Settings/Startup_Code/startup.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


