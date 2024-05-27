################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/custom_middleware/helper_functions/free_RTOS_functions.c 

OBJS += \
./Core/custom_middleware/helper_functions/free_RTOS_functions.o 

C_DEPS += \
./Core/custom_middleware/helper_functions/free_RTOS_functions.d 


# Each subdirectory must supply rules for building sources it contributes
Core/custom_middleware/helper_functions/%.o Core/custom_middleware/helper_functions/%.su Core/custom_middleware/helper_functions/%.cyclo: ../Core/custom_middleware/helper_functions/%.c Core/custom_middleware/helper_functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-custom_middleware-2f-helper_functions

clean-Core-2f-custom_middleware-2f-helper_functions:
	-$(RM) ./Core/custom_middleware/helper_functions/free_RTOS_functions.cyclo ./Core/custom_middleware/helper_functions/free_RTOS_functions.d ./Core/custom_middleware/helper_functions/free_RTOS_functions.o ./Core/custom_middleware/helper_functions/free_RTOS_functions.su

.PHONY: clean-Core-2f-custom_middleware-2f-helper_functions

