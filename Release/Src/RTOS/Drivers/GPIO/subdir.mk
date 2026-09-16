################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/RTOS/Drivers/GPIO/gpio_stm32f4.c 

OBJS += \
./Src/RTOS/Drivers/GPIO/gpio_stm32f4.o 

C_DEPS += \
./Src/RTOS/Drivers/GPIO/gpio_stm32f4.d 


# Each subdirectory must supply rules for building sources it contributes
Src/RTOS/Drivers/GPIO/%.o Src/RTOS/Drivers/GPIO/%.su Src/RTOS/Drivers/GPIO/%.cyclo: ../Src/RTOS/Drivers/GPIO/%.c Src/RTOS/Drivers/GPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F411xE -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-RTOS-2f-Drivers-2f-GPIO

clean-Src-2f-RTOS-2f-Drivers-2f-GPIO:
	-$(RM) ./Src/RTOS/Drivers/GPIO/gpio_stm32f4.cyclo ./Src/RTOS/Drivers/GPIO/gpio_stm32f4.d ./Src/RTOS/Drivers/GPIO/gpio_stm32f4.o ./Src/RTOS/Drivers/GPIO/gpio_stm32f4.su

.PHONY: clean-Src-2f-RTOS-2f-Drivers-2f-GPIO

