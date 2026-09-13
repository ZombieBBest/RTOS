################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/RTOS/Core/context.c \
../Src/RTOS/Core/context_switch_logic.c \
../Src/RTOS/Core/isr_core_functions.c \
../Src/RTOS/Core/os_manager.c \
../Src/RTOS/Core/supervisor_call.c 

OBJS += \
./Src/RTOS/Core/context.o \
./Src/RTOS/Core/context_switch_logic.o \
./Src/RTOS/Core/isr_core_functions.o \
./Src/RTOS/Core/os_manager.o \
./Src/RTOS/Core/supervisor_call.o 

C_DEPS += \
./Src/RTOS/Core/context.d \
./Src/RTOS/Core/context_switch_logic.d \
./Src/RTOS/Core/isr_core_functions.d \
./Src/RTOS/Core/os_manager.d \
./Src/RTOS/Core/supervisor_call.d 


# Each subdirectory must supply rules for building sources it contributes
Src/RTOS/Core/%.o Src/RTOS/Core/%.su Src/RTOS/Core/%.cyclo: ../Src/RTOS/Core/%.c Src/RTOS/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F411xE -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-RTOS-2f-Core

clean-Src-2f-RTOS-2f-Core:
	-$(RM) ./Src/RTOS/Core/context.cyclo ./Src/RTOS/Core/context.d ./Src/RTOS/Core/context.o ./Src/RTOS/Core/context.su ./Src/RTOS/Core/context_switch_logic.cyclo ./Src/RTOS/Core/context_switch_logic.d ./Src/RTOS/Core/context_switch_logic.o ./Src/RTOS/Core/context_switch_logic.su ./Src/RTOS/Core/isr_core_functions.cyclo ./Src/RTOS/Core/isr_core_functions.d ./Src/RTOS/Core/isr_core_functions.o ./Src/RTOS/Core/isr_core_functions.su ./Src/RTOS/Core/os_manager.cyclo ./Src/RTOS/Core/os_manager.d ./Src/RTOS/Core/os_manager.o ./Src/RTOS/Core/os_manager.su ./Src/RTOS/Core/supervisor_call.cyclo ./Src/RTOS/Core/supervisor_call.d ./Src/RTOS/Core/supervisor_call.o ./Src/RTOS/Core/supervisor_call.su

.PHONY: clean-Src-2f-RTOS-2f-Core

