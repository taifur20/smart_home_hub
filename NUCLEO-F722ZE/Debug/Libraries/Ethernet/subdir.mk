################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Ethernet/socket.c \
../Libraries/Ethernet/w5300.c \
../Libraries/Ethernet/wizchip_conf.c 

C_DEPS += \
./Libraries/Ethernet/socket.d \
./Libraries/Ethernet/w5300.d \
./Libraries/Ethernet/wizchip_conf.d 

OBJS += \
./Libraries/Ethernet/socket.o \
./Libraries/Ethernet/w5300.o \
./Libraries/Ethernet/wizchip_conf.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Ethernet/%.o Libraries/Ethernet/%.su Libraries/Ethernet/%.cyclo: ../Libraries/Ethernet/%.c Libraries/Ethernet/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/khair/STM32CubeIDE/workspace_1.13.0/NUCLEO-F722ZE/Libraries/Ethernet" -I"C:/Users/khair/STM32CubeIDE/workspace_1.13.0/NUCLEO-F722ZE/Libraries/MQTT" -I"C:/Users/khair/STM32CubeIDE/workspace_1.13.0/NUCLEO-F722ZE/Libraries/timer" -I"C:/Users/khair/STM32CubeIDE/workspace_1.13.0/NUCLEO-F722ZE/Libraries/library_io_driver" -I"C:/Users/khair/STM32CubeIDE/workspace_1.13.0/NUCLEO-F722ZE/Libraries/httpServer" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-Ethernet

clean-Libraries-2f-Ethernet:
	-$(RM) ./Libraries/Ethernet/socket.cyclo ./Libraries/Ethernet/socket.d ./Libraries/Ethernet/socket.o ./Libraries/Ethernet/socket.su ./Libraries/Ethernet/w5300.cyclo ./Libraries/Ethernet/w5300.d ./Libraries/Ethernet/w5300.o ./Libraries/Ethernet/w5300.su ./Libraries/Ethernet/wizchip_conf.cyclo ./Libraries/Ethernet/wizchip_conf.d ./Libraries/Ethernet/wizchip_conf.o ./Libraries/Ethernet/wizchip_conf.su

.PHONY: clean-Libraries-2f-Ethernet

