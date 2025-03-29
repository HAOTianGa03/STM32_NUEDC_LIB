################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Segger/SystemView/SEGGER_RTT.c \
../Segger/SystemView/SEGGER_RTT_printf.c \
../Segger/SystemView/SEGGER_SYSVIEW.c \
../Segger/SystemView/SEGGER_SYSVIEW_Config_NoOS.c 

C_DEPS += \
./Segger/SystemView/SEGGER_RTT.d \
./Segger/SystemView/SEGGER_RTT_printf.d \
./Segger/SystemView/SEGGER_SYSVIEW.d \
./Segger/SystemView/SEGGER_SYSVIEW_Config_NoOS.d 

OBJS += \
./Segger/SystemView/SEGGER_RTT.o \
./Segger/SystemView/SEGGER_RTT_printf.o \
./Segger/SystemView/SEGGER_SYSVIEW.o \
./Segger/SystemView/SEGGER_SYSVIEW_Config_NoOS.o 


# Each subdirectory must supply rules for building sources it contributes
Segger/SystemView/%.o Segger/SystemView/%.su Segger/SystemView/%.cyclo: ../Segger/SystemView/%.c Segger/SystemView/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Hardware/hal/Inc -I../Hardware/port/Inc -I../App/algorithim/Inc -I../App/filiter/Inc -I../Port/Inc -I../Segger/SystemView -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Segger-2f-SystemView

clean-Segger-2f-SystemView:
	-$(RM) ./Segger/SystemView/SEGGER_RTT.cyclo ./Segger/SystemView/SEGGER_RTT.d ./Segger/SystemView/SEGGER_RTT.o ./Segger/SystemView/SEGGER_RTT.su ./Segger/SystemView/SEGGER_RTT_printf.cyclo ./Segger/SystemView/SEGGER_RTT_printf.d ./Segger/SystemView/SEGGER_RTT_printf.o ./Segger/SystemView/SEGGER_RTT_printf.su ./Segger/SystemView/SEGGER_SYSVIEW.cyclo ./Segger/SystemView/SEGGER_SYSVIEW.d ./Segger/SystemView/SEGGER_SYSVIEW.o ./Segger/SystemView/SEGGER_SYSVIEW.su ./Segger/SystemView/SEGGER_SYSVIEW_Config_NoOS.cyclo ./Segger/SystemView/SEGGER_SYSVIEW_Config_NoOS.d ./Segger/SystemView/SEGGER_SYSVIEW_Config_NoOS.o ./Segger/SystemView/SEGGER_SYSVIEW_Config_NoOS.su

.PHONY: clean-Segger-2f-SystemView

