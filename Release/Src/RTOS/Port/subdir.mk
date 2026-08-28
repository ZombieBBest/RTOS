################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../Src/RTOS/Port/scheduler.S \
../Src/RTOS/Port/supervisor_call_asm.S 

OBJS += \
./Src/RTOS/Port/scheduler.o \
./Src/RTOS/Port/supervisor_call_asm.o 

S_UPPER_DEPS += \
./Src/RTOS/Port/scheduler.d \
./Src/RTOS/Port/supervisor_call_asm.d 


# Each subdirectory must supply rules for building sources it contributes
Src/RTOS/Port/%.o: ../Src/RTOS/Port/%.S Src/RTOS/Port/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Src-2f-RTOS-2f-Port

clean-Src-2f-RTOS-2f-Port:
	-$(RM) ./Src/RTOS/Port/scheduler.d ./Src/RTOS/Port/scheduler.o ./Src/RTOS/Port/supervisor_call_asm.d ./Src/RTOS/Port/supervisor_call_asm.o

.PHONY: clean-Src-2f-RTOS-2f-Port

