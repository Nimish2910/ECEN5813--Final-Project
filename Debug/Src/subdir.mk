################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/command_processor.c \
../Src/dht11.c \
../Src/init.c \
../Src/main.c \
../Src/statemachine.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/test_statemachine.c 

OBJS += \
./Src/command_processor.o \
./Src/dht11.o \
./Src/init.o \
./Src/main.o \
./Src/statemachine.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/test_statemachine.o 

C_DEPS += \
./Src/command_processor.d \
./Src/dht11.d \
./Src/init.d \
./Src/main.d \
./Src/statemachine.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/test_statemachine.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F0 -DNUCLEO_F091RC -DSTM32F091RCTx -DSTM32F091xC -c -I../Inc -I../CMSIS -O0 -ffunction-sections -fdata-sections -Wall -Werror -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/command_processor.cyclo ./Src/command_processor.d ./Src/command_processor.o ./Src/command_processor.su ./Src/dht11.cyclo ./Src/dht11.d ./Src/dht11.o ./Src/dht11.su ./Src/init.cyclo ./Src/init.d ./Src/init.o ./Src/init.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/statemachine.cyclo ./Src/statemachine.d ./Src/statemachine.o ./Src/statemachine.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/test_statemachine.cyclo ./Src/test_statemachine.d ./Src/test_statemachine.o ./Src/test_statemachine.su

.PHONY: clean-Src

