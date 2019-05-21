################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS_QUOTED += \
"../src/intc_sw_handlers.S" \

C_SRCS_QUOTED += \
"../src/Flash_Driver_utils.c" \
"../src/FlexCAN_api.c" \
"../src/MPC574xP_SystemInit.c" \
"../src/MPC57xx__Interrupt_Init.c" \
"../src/Vector.c" \
"../src/block_mpc574xP.c" \
"../src/flashrchw.c" \
"../src/flexcan_init.c" \
"../src/intc_SW_mode_isr_vectors_MPC5744P.c" \
"../src/load.c" \
"../src/main.c" \

S_SRCS_QUOTED += \
"../src/IVORx_vle.s" \

S_UPPER_SRCS += \
../src/intc_sw_handlers.S \

S_SRCS += \
../src/IVORx_vle.s \

C_SRCS += \
../src/Flash_Driver_utils.c \
../src/FlexCAN_api.c \
../src/MPC574xP_SystemInit.c \
../src/MPC57xx__Interrupt_Init.c \
../src/Vector.c \
../src/block_mpc574xP.c \
../src/flashrchw.c \
../src/flexcan_init.c \
../src/intc_SW_mode_isr_vectors_MPC5744P.c \
../src/load.c \
../src/main.c \

C_DEPS_QUOTED += \
"./src/Flash_Driver_utils.d" \
"./src/FlexCAN_api.d" \
"./src/MPC574xP_SystemInit.d" \
"./src/MPC57xx__Interrupt_Init.d" \
"./src/Vector.d" \
"./src/block_mpc574xP.d" \
"./src/flashrchw.d" \
"./src/flexcan_init.d" \
"./src/intc_SW_mode_isr_vectors_MPC5744P.d" \
"./src/load.d" \
"./src/main.d" \

OBJS_QUOTED += \
"./src/Flash_Driver_utils.o" \
"./src/FlexCAN_api.o" \
"./src/IVORx_vle.o" \
"./src/MPC574xP_SystemInit.o" \
"./src/MPC57xx__Interrupt_Init.o" \
"./src/Vector.o" \
"./src/block_mpc574xP.o" \
"./src/flashrchw.o" \
"./src/flexcan_init.o" \
"./src/intc_SW_mode_isr_vectors_MPC5744P.o" \
"./src/intc_sw_handlers.o" \
"./src/load.o" \
"./src/main.o" \

C_DEPS += \
./src/Flash_Driver_utils.d \
./src/FlexCAN_api.d \
./src/MPC574xP_SystemInit.d \
./src/MPC57xx__Interrupt_Init.d \
./src/Vector.d \
./src/block_mpc574xP.d \
./src/flashrchw.d \
./src/flexcan_init.d \
./src/intc_SW_mode_isr_vectors_MPC5744P.d \
./src/load.d \
./src/main.d \

OBJS_OS_FORMAT += \
./src/Flash_Driver_utils.o \
./src/FlexCAN_api.o \
./src/IVORx_vle.o \
./src/MPC574xP_SystemInit.o \
./src/MPC57xx__Interrupt_Init.o \
./src/Vector.o \
./src/block_mpc574xP.o \
./src/flashrchw.o \
./src/flexcan_init.o \
./src/intc_SW_mode_isr_vectors_MPC5744P.o \
./src/intc_sw_handlers.o \
./src/load.o \
./src/main.o \

OBJS += \
./src/Flash_Driver_utils.o \
./src/FlexCAN_api.o \
./src/IVORx_vle.o \
./src/MPC574xP_SystemInit.o \
./src/MPC57xx__Interrupt_Init.o \
./src/Vector.o \
./src/block_mpc574xP.o \
./src/flashrchw.o \
./src/flexcan_init.o \
./src/intc_SW_mode_isr_vectors_MPC5744P.o \
./src/intc_sw_handlers.o \
./src/load.o \
./src/main.o \


# Each subdirectory must supply rules for building sources it contributes
src/Flash_Driver_utils.o: ../src/Flash_Driver_utils.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/Flash_Driver_utils.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/Flash_Driver_utils.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/FlexCAN_api.o: ../src/FlexCAN_api.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/FlexCAN_api.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/FlexCAN_api.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/IVORx_vle.o: ../src/IVORx_vle.s
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: Standard S32DS Assembler'
	powerpc-eabivle-gcc "@src/IVORx_vle.args" -c -o "src/IVORx_vle.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/MPC574xP_SystemInit.o: ../src/MPC574xP_SystemInit.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/MPC574xP_SystemInit.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/MPC574xP_SystemInit.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/MPC57xx__Interrupt_Init.o: ../src/MPC57xx__Interrupt_Init.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/MPC57xx__Interrupt_Init.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/MPC57xx__Interrupt_Init.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Vector.o: ../src/Vector.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/Vector.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/Vector.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/block_mpc574xP.o: ../src/block_mpc574xP.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/block_mpc574xP.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/block_mpc574xP.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/flashrchw.o: ../src/flashrchw.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/flashrchw.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/flashrchw.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/flexcan_init.o: ../src/flexcan_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/flexcan_init.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/flexcan_init.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/intc_SW_mode_isr_vectors_MPC5744P.o: ../src/intc_SW_mode_isr_vectors_MPC5744P.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/intc_SW_mode_isr_vectors_MPC5744P.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/intc_SW_mode_isr_vectors_MPC5744P.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/intc_sw_handlers.o: ../src/intc_sw_handlers.S
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: Standard S32DS Assembler'
	powerpc-eabivle-gcc "@src/intc_sw_handlers.args" -c -o "src/intc_sw_handlers.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/load.o: ../src/load.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/load.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/load.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.o: ../src/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/main.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


