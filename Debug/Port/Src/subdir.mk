################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Port/Src/stm32_callback.cpp 

OBJS += \
./Port/Src/stm32_callback.o 

CPP_DEPS += \
./Port/Src/stm32_callback.d 


# Each subdirectory must supply rules for building sources it contributes
Port/Src/%.o Port/Src/%.su Port/Src/%.cyclo: ../Port/Src/%.cpp Port/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=c++20 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Hardware/hal/Inc -I../Hardware/port/Inc -I../App/algorithim/Inc -I../App/filiter/Inc -I../Port/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Port-2f-Src

clean-Port-2f-Src:
	-$(RM) ./Port/Src/stm32_callback.cyclo ./Port/Src/stm32_callback.d ./Port/Src/stm32_callback.o ./Port/Src/stm32_callback.su

.PHONY: clean-Port-2f-Src

