################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Core/custom_middleware/99_tasks/wifi_task/subdir.mk
-include Core/custom_middleware/02_printf/subdir.mk
-include Core/custom_middleware/01_helper_functions/subdir.mk
-include Core/custom_middleware/00_uart_lib/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := EMBSY_RTOS_wifi_demo_AP
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
EMBSY_RTOS_wifi_demo_AP.elf \

MAP_FILES += \
EMBSY_RTOS_wifi_demo_AP.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
EMBSY_RTOS_wifi_demo_AP.list \


# All Target
all: main-build

# Main-build Target
main-build: EMBSY_RTOS_wifi_demo_AP.elf secondary-outputs

# Tool invocations
EMBSY_RTOS_wifi_demo_AP.elf EMBSY_RTOS_wifi_demo_AP.map: $(OBJS) $(USER_OBJS) /home/patrick/STM32CubeIDE/BIC24/EMBSY_RTOS_wifi_demo_AP/STM32L432KCUX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "EMBSY_RTOS_wifi_demo_AP.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/patrick/STM32CubeIDE/BIC24/EMBSY_RTOS_wifi_demo_AP/STM32L432KCUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="EMBSY_RTOS_wifi_demo_AP.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

EMBSY_RTOS_wifi_demo_AP.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "EMBSY_RTOS_wifi_demo_AP.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) EMBSY_RTOS_wifi_demo_AP.elf EMBSY_RTOS_wifi_demo_AP.list EMBSY_RTOS_wifi_demo_AP.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
