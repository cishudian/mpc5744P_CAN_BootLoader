################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Flash_Driver/Demo/block_mpc57xx.c" \
"../Flash_Driver/Demo/demo.c" \
"../Flash_Driver/Demo/demo_utils.c" \

C_SRCS += \
../Flash_Driver/Demo/block_mpc57xx.c \
../Flash_Driver/Demo/demo.c \
../Flash_Driver/Demo/demo_utils.c \

C_DEPS_QUOTED += \
"./Flash_Driver/Demo/block_mpc57xx.d" \
"./Flash_Driver/Demo/demo.d" \
"./Flash_Driver/Demo/demo_utils.d" \

OBJS_QUOTED += \
"./Flash_Driver/Demo/block_mpc57xx.o" \
"./Flash_Driver/Demo/demo.o" \
"./Flash_Driver/Demo/demo_utils.o" \

C_DEPS += \
./Flash_Driver/Demo/block_mpc57xx.d \
./Flash_Driver/Demo/demo.d \
./Flash_Driver/Demo/demo_utils.d \

OBJS_OS_FORMAT += \
./Flash_Driver/Demo/block_mpc57xx.o \
./Flash_Driver/Demo/demo.o \
./Flash_Driver/Demo/demo_utils.o \

OBJS += \
./Flash_Driver/Demo/block_mpc57xx.o \
./Flash_Driver/Demo/demo.o \
./Flash_Driver/Demo/demo_utils.o \


# Each subdirectory must supply rules for building sources it contributes
Flash_Driver/Demo/block_mpc57xx.o: ../Flash_Driver/Demo/block_mpc57xx.c
	@echo 'Building file: $<'
	@echo 'Executing target #34 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@Flash_Driver/Demo/block_mpc57xx.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "Flash_Driver/Demo/block_mpc57xx.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Flash_Driver/Demo/demo.o: ../Flash_Driver/Demo/demo.c
	@echo 'Building file: $<'
	@echo 'Executing target #35 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@Flash_Driver/Demo/demo.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "Flash_Driver/Demo/demo.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Flash_Driver/Demo/demo_utils.o: ../Flash_Driver/Demo/demo_utils.c
	@echo 'Building file: $<'
	@echo 'Executing target #36 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@Flash_Driver/Demo/demo_utils.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "Flash_Driver/Demo/demo_utils.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


