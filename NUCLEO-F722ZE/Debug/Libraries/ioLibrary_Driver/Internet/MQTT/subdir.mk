################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/ioLibrary_Driver/Internet/MQTT/MQTTClient.c \
../Libraries/ioLibrary_Driver/Internet/MQTT/mqtt_interface.c 

OBJS += \
./Libraries/ioLibrary_Driver/Internet/MQTT/MQTTClient.o \
./Libraries/ioLibrary_Driver/Internet/MQTT/mqtt_interface.o 

C_DEPS += \
./Libraries/ioLibrary_Driver/Internet/MQTT/MQTTClient.d \
./Libraries/ioLibrary_Driver/Internet/MQTT/mqtt_interface.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/ioLibrary_Driver/Internet/MQTT/%.o Libraries/ioLibrary_Driver/Internet/MQTT/%.su Libraries/ioLibrary_Driver/Internet/MQTT/%.cyclo: ../Libraries/ioLibrary_Driver/Internet/MQTT/%.c Libraries/ioLibrary_Driver/Internet/MQTT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/khair/STM32CubeIDE/workspace_1.13.0/NUCLEO-F722ZE/Libraries/ioLibrary_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-ioLibrary_Driver-2f-Internet-2f-MQTT

clean-Libraries-2f-ioLibrary_Driver-2f-Internet-2f-MQTT:
	-$(RM) ./Libraries/ioLibrary_Driver/Internet/MQTT/MQTTClient.cyclo ./Libraries/ioLibrary_Driver/Internet/MQTT/MQTTClient.d ./Libraries/ioLibrary_Driver/Internet/MQTT/MQTTClient.o ./Libraries/ioLibrary_Driver/Internet/MQTT/MQTTClient.su ./Libraries/ioLibrary_Driver/Internet/MQTT/mqtt_interface.cyclo ./Libraries/ioLibrary_Driver/Internet/MQTT/mqtt_interface.d ./Libraries/ioLibrary_Driver/Internet/MQTT/mqtt_interface.o ./Libraries/ioLibrary_Driver/Internet/MQTT/mqtt_interface.su

.PHONY: clean-Libraries-2f-ioLibrary_Driver-2f-Internet-2f-MQTT

