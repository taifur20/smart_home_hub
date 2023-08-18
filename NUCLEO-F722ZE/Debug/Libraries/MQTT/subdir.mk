################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/MQTT/MQTTClient.c \
../Libraries/MQTT/mqtt_interface.c 

C_DEPS += \
./Libraries/MQTT/MQTTClient.d \
./Libraries/MQTT/mqtt_interface.d 

OBJS += \
./Libraries/MQTT/MQTTClient.o \
./Libraries/MQTT/mqtt_interface.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/MQTT/%.o Libraries/MQTT/%.su Libraries/MQTT/%.cyclo: ../Libraries/MQTT/%.c Libraries/MQTT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/khair/STM32CubeIDE/workspace_1.13.0/NUCLEO-F722ZE/Libraries/Ethernet" -I"C:/Users/khair/STM32CubeIDE/workspace_1.13.0/NUCLEO-F722ZE/Libraries/MQTT" -I"C:/Users/khair/STM32CubeIDE/workspace_1.13.0/NUCLEO-F722ZE/Libraries/timer" -I"C:/Users/khair/STM32CubeIDE/workspace_1.13.0/NUCLEO-F722ZE/Libraries/library_io_driver" -I"C:/Users/khair/STM32CubeIDE/workspace_1.13.0/NUCLEO-F722ZE/Libraries/httpServer" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-MQTT

clean-Libraries-2f-MQTT:
	-$(RM) ./Libraries/MQTT/MQTTClient.cyclo ./Libraries/MQTT/MQTTClient.d ./Libraries/MQTT/MQTTClient.o ./Libraries/MQTT/MQTTClient.su ./Libraries/MQTT/mqtt_interface.cyclo ./Libraries/MQTT/mqtt_interface.d ./Libraries/MQTT/mqtt_interface.o ./Libraries/MQTT/mqtt_interface.su

.PHONY: clean-Libraries-2f-MQTT

