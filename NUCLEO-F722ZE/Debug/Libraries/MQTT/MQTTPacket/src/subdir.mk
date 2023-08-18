################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/MQTT/MQTTPacket/src/MQTTConnectClient.c \
../Libraries/MQTT/MQTTPacket/src/MQTTConnectServer.c \
../Libraries/MQTT/MQTTPacket/src/MQTTDeserializePublish.c \
../Libraries/MQTT/MQTTPacket/src/MQTTFormat.c \
../Libraries/MQTT/MQTTPacket/src/MQTTPacket.c \
../Libraries/MQTT/MQTTPacket/src/MQTTSerializePublish.c \
../Libraries/MQTT/MQTTPacket/src/MQTTSubscribeClient.c \
../Libraries/MQTT/MQTTPacket/src/MQTTSubscribeServer.c \
../Libraries/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.c \
../Libraries/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.c 

C_DEPS += \
./Libraries/MQTT/MQTTPacket/src/MQTTConnectClient.d \
./Libraries/MQTT/MQTTPacket/src/MQTTConnectServer.d \
./Libraries/MQTT/MQTTPacket/src/MQTTDeserializePublish.d \
./Libraries/MQTT/MQTTPacket/src/MQTTFormat.d \
./Libraries/MQTT/MQTTPacket/src/MQTTPacket.d \
./Libraries/MQTT/MQTTPacket/src/MQTTSerializePublish.d \
./Libraries/MQTT/MQTTPacket/src/MQTTSubscribeClient.d \
./Libraries/MQTT/MQTTPacket/src/MQTTSubscribeServer.d \
./Libraries/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.d \
./Libraries/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.d 

OBJS += \
./Libraries/MQTT/MQTTPacket/src/MQTTConnectClient.o \
./Libraries/MQTT/MQTTPacket/src/MQTTConnectServer.o \
./Libraries/MQTT/MQTTPacket/src/MQTTDeserializePublish.o \
./Libraries/MQTT/MQTTPacket/src/MQTTFormat.o \
./Libraries/MQTT/MQTTPacket/src/MQTTPacket.o \
./Libraries/MQTT/MQTTPacket/src/MQTTSerializePublish.o \
./Libraries/MQTT/MQTTPacket/src/MQTTSubscribeClient.o \
./Libraries/MQTT/MQTTPacket/src/MQTTSubscribeServer.o \
./Libraries/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.o \
./Libraries/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/MQTT/MQTTPacket/src/%.o Libraries/MQTT/MQTTPacket/src/%.su Libraries/MQTT/MQTTPacket/src/%.cyclo: ../Libraries/MQTT/MQTTPacket/src/%.c Libraries/MQTT/MQTTPacket/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F722xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/khair/STM32CubeIDE/workspace_1.13.0/NUCLEO-F722ZE/Libraries/Ethernet" -I"C:/Users/khair/STM32CubeIDE/workspace_1.13.0/NUCLEO-F722ZE/Libraries/MQTT" -I"C:/Users/khair/STM32CubeIDE/workspace_1.13.0/NUCLEO-F722ZE/Libraries/timer" -I"C:/Users/khair/STM32CubeIDE/workspace_1.13.0/NUCLEO-F722ZE/Libraries/library_io_driver" -I"C:/Users/khair/STM32CubeIDE/workspace_1.13.0/NUCLEO-F722ZE/Libraries/httpServer" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-MQTT-2f-MQTTPacket-2f-src

clean-Libraries-2f-MQTT-2f-MQTTPacket-2f-src:
	-$(RM) ./Libraries/MQTT/MQTTPacket/src/MQTTConnectClient.cyclo ./Libraries/MQTT/MQTTPacket/src/MQTTConnectClient.d ./Libraries/MQTT/MQTTPacket/src/MQTTConnectClient.o ./Libraries/MQTT/MQTTPacket/src/MQTTConnectClient.su ./Libraries/MQTT/MQTTPacket/src/MQTTConnectServer.cyclo ./Libraries/MQTT/MQTTPacket/src/MQTTConnectServer.d ./Libraries/MQTT/MQTTPacket/src/MQTTConnectServer.o ./Libraries/MQTT/MQTTPacket/src/MQTTConnectServer.su ./Libraries/MQTT/MQTTPacket/src/MQTTDeserializePublish.cyclo ./Libraries/MQTT/MQTTPacket/src/MQTTDeserializePublish.d ./Libraries/MQTT/MQTTPacket/src/MQTTDeserializePublish.o ./Libraries/MQTT/MQTTPacket/src/MQTTDeserializePublish.su ./Libraries/MQTT/MQTTPacket/src/MQTTFormat.cyclo ./Libraries/MQTT/MQTTPacket/src/MQTTFormat.d ./Libraries/MQTT/MQTTPacket/src/MQTTFormat.o ./Libraries/MQTT/MQTTPacket/src/MQTTFormat.su ./Libraries/MQTT/MQTTPacket/src/MQTTPacket.cyclo ./Libraries/MQTT/MQTTPacket/src/MQTTPacket.d ./Libraries/MQTT/MQTTPacket/src/MQTTPacket.o ./Libraries/MQTT/MQTTPacket/src/MQTTPacket.su ./Libraries/MQTT/MQTTPacket/src/MQTTSerializePublish.cyclo ./Libraries/MQTT/MQTTPacket/src/MQTTSerializePublish.d ./Libraries/MQTT/MQTTPacket/src/MQTTSerializePublish.o ./Libraries/MQTT/MQTTPacket/src/MQTTSerializePublish.su ./Libraries/MQTT/MQTTPacket/src/MQTTSubscribeClient.cyclo ./Libraries/MQTT/MQTTPacket/src/MQTTSubscribeClient.d ./Libraries/MQTT/MQTTPacket/src/MQTTSubscribeClient.o ./Libraries/MQTT/MQTTPacket/src/MQTTSubscribeClient.su ./Libraries/MQTT/MQTTPacket/src/MQTTSubscribeServer.cyclo ./Libraries/MQTT/MQTTPacket/src/MQTTSubscribeServer.d ./Libraries/MQTT/MQTTPacket/src/MQTTSubscribeServer.o ./Libraries/MQTT/MQTTPacket/src/MQTTSubscribeServer.su ./Libraries/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.cyclo ./Libraries/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.d ./Libraries/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.o ./Libraries/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.su ./Libraries/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.cyclo ./Libraries/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.d ./Libraries/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.o ./Libraries/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.su

.PHONY: clean-Libraries-2f-MQTT-2f-MQTTPacket-2f-src

