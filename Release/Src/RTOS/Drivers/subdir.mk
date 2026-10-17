################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/RTOS/Drivers/drivers_periphery_include.c 

OBJS += \
./Src/RTOS/Drivers/drivers_periphery_include.o 

C_DEPS += \
./Src/RTOS/Drivers/drivers_periphery_include.d 


# Each subdirectory must supply rules for building sources it contributes
Src/RTOS/Drivers/%.o Src/RTOS/Drivers/%.su Src/RTOS/Drivers/%.cyclo: ../Src/RTOS/Drivers/%.c Src/RTOS/Drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F411xE -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-RTOS-2f-Drivers

clean-Src-2f-RTOS-2f-Drivers:
	-$(RM) ./Src/RTOS/Drivers/drivers_periphery_include.cyclo ./Src/RTOS/Drivers/drivers_periphery_include.d ./Src/RTOS/Drivers/drivers_periphery_include.o ./Src/RTOS/Drivers/drivers_periphery_include.su

.PHONY: clean-Src-2f-RTOS-2f-Drivers

