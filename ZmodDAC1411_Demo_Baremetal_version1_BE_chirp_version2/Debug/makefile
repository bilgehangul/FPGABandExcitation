################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/zmodlib/ZmodDAC1411/subdir.mk
-include src/zmodlib/ZmodADC1410/subdir.mk
-include src/zmodlib/Zmod/linux/reg/subdir.mk
-include src/zmodlib/Zmod/linux/flash/subdir.mk
-include src/zmodlib/Zmod/linux/dma/subdir.mk
-include src/zmodlib/Zmod/linux/subdir.mk
-include src/zmodlib/Zmod/baremetal/reg/subdir.mk
-include src/zmodlib/Zmod/baremetal/intc/subdir.mk
-include src/zmodlib/Zmod/baremetal/flash/subdir.mk
-include src/zmodlib/Zmod/baremetal/dma/subdir.mk
-include src/zmodlib/Zmod/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
ZmodDAC1411_Demo_Baremetal.elf.size \


# All Target
all:
	$(MAKE) --no-print-directory pre-build
	$(MAKE) --no-print-directory main-build

# Main-build Target
main-build: ZmodDAC1411_Demo_Baremetal.elf secondary-outputs

# Tool invocations
ZmodDAC1411_Demo_Baremetal.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM v7 g++ linker'
	arm-none-eabi-g++ -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -Wl,-build-id=none -specs=Xilinx.spec -Wl,-T -Wl,../src/lscript.ld -LC:/drexel/Eclypse-Z7-SW/design_1_wrapper_platform_0_1/export/design_1_wrapper_platform_0_1/sw/design_1_wrapper_platform_0_1/ZmodDAC1411_Demo_Baremetal_bsp_domain/bsplib/lib -o "ZmodDAC1411_Demo_Baremetal.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ZmodDAC1411_Demo_Baremetal.elf.size: ZmodDAC1411_Demo_Baremetal.elf
	@echo 'Invoking: ARM v7 Print Size'
	arm-none-eabi-size ZmodDAC1411_Demo_Baremetal.elf  |tee "ZmodDAC1411_Demo_Baremetal.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(CPP_DEPS)$(ELFSIZE) ZmodDAC1411_Demo_Baremetal.elf
	-@echo ' '

pre-build:
	-a9-linaro-pre-build-step
	-@echo ' '

secondary-outputs: $(ELFSIZE)

.PHONY: all clean dependents main-build pre-build

-include ../makefile.targets
