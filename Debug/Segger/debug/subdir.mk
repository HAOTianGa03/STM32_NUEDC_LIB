################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Segger/debug/SEGGER_RTT.c \
../Segger/debug/SEGGER_SYSVIEW.c \
../Segger/debug/SEGGER_SYSVIEW_Config_NoOS.c 

C_DEPS += \
./Segger/debug/SEGGER_RTT.d \
./Segger/debug/SEGGER_SYSVIEW.d \
./Segger/debug/SEGGER_SYSVIEW_Config_NoOS.d 

OBJS += \
./Segger/debug/SEGGER_RTT.o \
./Segger/debug/SEGGER_SYSVIEW.o \
./Segger/debug/SEGGER_SYSVIEW_Config_NoOS.o 


# Each subdirectory must supply rules for building sources it contributes
Segger/debug/%.o Segger/debug/%.su Segger/debug/%.cyclo: ../Segger/debug/%.c Segger/debug/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Hardware/hal/Inc -I../Hardware/port/Inc -I../App/algorithim/Inc -I../App/filiter/Inc -I../Port/Inc -I../Segger/SystemView -I../Segger/debug -I../11 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Segger-2f-debug

clean-Segger-2f-debug:
	-$(RM) ./Segger/debug/SEGGER_RTT.cyclo ./Segger/debug/SEGGER_RTT.d ./Segger/debug/SEGGER_RTT.o ./Segger/debug/SEGGER_RTT.su ./Segger/debug/SEGGER_SYSVIEW.cyclo ./Segger/debug/SEGGER_SYSVIEW.d ./Segger/debug/SEGGER_SYSVIEW.o ./Segger/debug/SEGGER_SYSVIEW.su ./Segger/debug/SEGGER_SYSVIEW_Config_NoOS.cyclo ./Segger/debug/SEGGER_SYSVIEW_Config_NoOS.d ./Segger/debug/SEGGER_SYSVIEW_Config_NoOS.o ./Segger/debug/SEGGER_SYSVIEW_Config_NoOS.su

.PHONY: clean-Segger-2f-debug

