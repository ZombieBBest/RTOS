################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/RTOS/Port/hardfault.c \
../Src/RTOS/Port/port_mpu.c \
../Src/RTOS/Port/port_supervisor_call.c \
../Src/RTOS/Port/port_sys_timer.c 

S_UPPER_SRCS += \
../Src/RTOS/Port/port_mpu_asm.S \
../Src/RTOS/Port/scheduler.S \
../Src/RTOS/Port/supervisor_call_asm.S 

OBJS += \
./Src/RTOS/Port/hardfault.o \
./Src/RTOS/Port/port_mpu.o \
./Src/RTOS/Port/port_mpu_asm.o \
./Src/RTOS/Port/port_supervisor_call.o \
./Src/RTOS/Port/port_sys_timer.o \
./Src/RTOS/Port/scheduler.o \
./Src/RTOS/Port/supervisor_call_asm.o 

S_UPPER_DEPS += \
./Src/RTOS/Port/port_mpu_asm.d \
./Src/RTOS/Port/scheduler.d \
./Src/RTOS/Port/supervisor_call_asm.d 

C_DEPS += \
./Src/RTOS/Port/hardfault.d \
./Src/RTOS/Port/port_mpu.d \
./Src/RTOS/Port/port_supervisor_call.d \
./Src/RTOS/Port/port_sys_timer.d 


# Each subdirectory must supply rules for building sources it contributes
Src/RTOS/Port/%.o Src/RTOS/Port/%.su Src/RTOS/Port/%.cyclo: ../Src/RTOS/Port/%.c Src/RTOS/Port/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32 -DSTM32F411xE -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/RTOS/Port/%.o: ../Src/RTOS/Port/%.S Src/RTOS/Port/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Src-2f-RTOS-2f-Port

clean-Src-2f-RTOS-2f-Port:
	-$(RM) ./Src/RTOS/Port/hardfault.cyclo ./Src/RTOS/Port/hardfault.d ./Src/RTOS/Port/hardfault.o ./Src/RTOS/Port/hardfault.su ./Src/RTOS/Port/port_mpu.cyclo ./Src/RTOS/Port/port_mpu.d ./Src/RTOS/Port/port_mpu.o ./Src/RTOS/Port/port_mpu.su ./Src/RTOS/Port/port_mpu_asm.d ./Src/RTOS/Port/port_mpu_asm.o ./Src/RTOS/Port/port_supervisor_call.cyclo ./Src/RTOS/Port/port_supervisor_call.d ./Src/RTOS/Port/port_supervisor_call.o ./Src/RTOS/Port/port_supervisor_call.su ./Src/RTOS/Port/port_sys_timer.cyclo ./Src/RTOS/Port/port_sys_timer.d ./Src/RTOS/Port/port_sys_timer.o ./Src/RTOS/Port/port_sys_timer.su ./Src/RTOS/Port/scheduler.d ./Src/RTOS/Port/scheduler.o ./Src/RTOS/Port/supervisor_call_asm.d ./Src/RTOS/Port/supervisor_call_asm.o

.PHONY: clean-Src-2f-RTOS-2f-Port

