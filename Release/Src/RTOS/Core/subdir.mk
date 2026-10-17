################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/RTOS/Core/core_context.c \
../Src/RTOS/Core/core_context_switch_logic.c \
../Src/RTOS/Core/core_drivers_table.c \
../Src/RTOS/Core/core_handlers.c \
../Src/RTOS/Core/core_manager.c \
../Src/RTOS/Core/core_supervisor_dispatcher.c 

OBJS += \
./Src/RTOS/Core/core_context.o \
./Src/RTOS/Core/core_context_switch_logic.o \
./Src/RTOS/Core/core_drivers_table.o \
./Src/RTOS/Core/core_handlers.o \
./Src/RTOS/Core/core_manager.o \
./Src/RTOS/Core/core_supervisor_dispatcher.o 

C_DEPS += \
./Src/RTOS/Core/core_context.d \
./Src/RTOS/Core/core_context_switch_logic.d \
./Src/RTOS/Core/core_drivers_table.d \
./Src/RTOS/Core/core_handlers.d \
./Src/RTOS/Core/core_manager.d \
./Src/RTOS/Core/core_supervisor_dispatcher.d 


# Each subdirectory must supply rules for building sources it contributes
Src/RTOS/Core/%.o Src/RTOS/Core/%.su Src/RTOS/Core/%.cyclo: ../Src/RTOS/Core/%.c Src/RTOS/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F411xE -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-RTOS-2f-Core

clean-Src-2f-RTOS-2f-Core:
	-$(RM) ./Src/RTOS/Core/core_context.cyclo ./Src/RTOS/Core/core_context.d ./Src/RTOS/Core/core_context.o ./Src/RTOS/Core/core_context.su ./Src/RTOS/Core/core_context_switch_logic.cyclo ./Src/RTOS/Core/core_context_switch_logic.d ./Src/RTOS/Core/core_context_switch_logic.o ./Src/RTOS/Core/core_context_switch_logic.su ./Src/RTOS/Core/core_drivers_table.cyclo ./Src/RTOS/Core/core_drivers_table.d ./Src/RTOS/Core/core_drivers_table.o ./Src/RTOS/Core/core_drivers_table.su ./Src/RTOS/Core/core_handlers.cyclo ./Src/RTOS/Core/core_handlers.d ./Src/RTOS/Core/core_handlers.o ./Src/RTOS/Core/core_handlers.su ./Src/RTOS/Core/core_manager.cyclo ./Src/RTOS/Core/core_manager.d ./Src/RTOS/Core/core_manager.o ./Src/RTOS/Core/core_manager.su ./Src/RTOS/Core/core_supervisor_dispatcher.cyclo ./Src/RTOS/Core/core_supervisor_dispatcher.d ./Src/RTOS/Core/core_supervisor_dispatcher.o ./Src/RTOS/Core/core_supervisor_dispatcher.su

.PHONY: clean-Src-2f-RTOS-2f-Core

