################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/RTOS/context.c \
../Src/RTOS/context_switch_logic.c \
../Src/RTOS/os_manager.c \
../Src/RTOS/supervisor_call.c \
../Src/RTOS/sys_timer.c 

S_UPPER_SRCS += \
../Src/RTOS/scheduler.S \
../Src/RTOS/supervisor_call_asm.S 

OBJS += \
./Src/RTOS/context.o \
./Src/RTOS/context_switch_logic.o \
./Src/RTOS/os_manager.o \
./Src/RTOS/scheduler.o \
./Src/RTOS/supervisor_call.o \
./Src/RTOS/supervisor_call_asm.o \
./Src/RTOS/sys_timer.o 

S_UPPER_DEPS += \
./Src/RTOS/scheduler.d \
./Src/RTOS/supervisor_call_asm.d 

C_DEPS += \
./Src/RTOS/context.d \
./Src/RTOS/context_switch_logic.d \
./Src/RTOS/os_manager.d \
./Src/RTOS/supervisor_call.d \
./Src/RTOS/sys_timer.d 


# Each subdirectory must supply rules for building sources it contributes
Src/RTOS/%.o Src/RTOS/%.su Src/RTOS/%.cyclo: ../Src/RTOS/%.c Src/RTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F411xE -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/RTOS/%.o: ../Src/RTOS/%.S Src/RTOS/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Src-2f-RTOS

clean-Src-2f-RTOS:
	-$(RM) ./Src/RTOS/context.cyclo ./Src/RTOS/context.d ./Src/RTOS/context.o ./Src/RTOS/context.su ./Src/RTOS/context_switch_logic.cyclo ./Src/RTOS/context_switch_logic.d ./Src/RTOS/context_switch_logic.o ./Src/RTOS/context_switch_logic.su ./Src/RTOS/os_manager.cyclo ./Src/RTOS/os_manager.d ./Src/RTOS/os_manager.o ./Src/RTOS/os_manager.su ./Src/RTOS/scheduler.d ./Src/RTOS/scheduler.o ./Src/RTOS/supervisor_call.cyclo ./Src/RTOS/supervisor_call.d ./Src/RTOS/supervisor_call.o ./Src/RTOS/supervisor_call.su ./Src/RTOS/supervisor_call_asm.d ./Src/RTOS/supervisor_call_asm.o ./Src/RTOS/sys_timer.cyclo ./Src/RTOS/sys_timer.d ./Src/RTOS/sys_timer.o ./Src/RTOS/sys_timer.su

.PHONY: clean-Src-2f-RTOS

