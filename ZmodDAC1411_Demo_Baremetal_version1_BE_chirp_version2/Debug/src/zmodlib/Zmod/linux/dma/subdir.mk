################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/drexel/Eclypse-Z7-SW/zmodlib/Zmod/linux/dma/dma.c \
C:/drexel/Eclypse-Z7-SW/zmodlib/Zmod/linux/dma/libaxidma.c 

OBJS += \
./src/zmodlib/Zmod/linux/dma/dma.o \
./src/zmodlib/Zmod/linux/dma/libaxidma.o 

C_DEPS += \
./src/zmodlib/Zmod/linux/dma/dma.d \
./src/zmodlib/Zmod/linux/dma/libaxidma.d 


# Each subdirectory must supply rules for building sources it contributes
src/zmodlib/Zmod/linux/dma/dma.o: C:/drexel/Eclypse-Z7-SW/zmodlib/Zmod/linux/dma/dma.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O0 -g3 -I"C:\drexel\Eclypse-Z7-SW\ZmodDAC1411_Demo_Baremetal\Debug/../../zmodlib/Zmod" -I"C:\drexel\Eclypse-Z7-SW\ZmodDAC1411_Demo_Baremetal\Debug/../../zmodlib/ZmodDAC1411" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/drexel/Eclypse-Z7-SW/design_1_wrapper_platform_0_1/export/design_1_wrapper_platform_0_1/sw/design_1_wrapper_platform_0_1/ZmodDAC1411_Demo_Baremetal_bsp_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/zmodlib/Zmod/linux/dma/libaxidma.o: C:/drexel/Eclypse-Z7-SW/zmodlib/Zmod/linux/dma/libaxidma.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O0 -g3 -I"C:\drexel\Eclypse-Z7-SW\ZmodDAC1411_Demo_Baremetal\Debug/../../zmodlib/Zmod" -I"C:\drexel\Eclypse-Z7-SW\ZmodDAC1411_Demo_Baremetal\Debug/../../zmodlib/ZmodDAC1411" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IC:/drexel/Eclypse-Z7-SW/design_1_wrapper_platform_0_1/export/design_1_wrapper_platform_0_1/sw/design_1_wrapper_platform_0_1/ZmodDAC1411_Demo_Baremetal_bsp_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


