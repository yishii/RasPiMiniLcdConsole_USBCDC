################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cdc_desc.c \
../src/cr_startup_lpc11u.c \
../src/main.c 

OBJS += \
./src/cdc_desc.o \
./src/cr_startup_lpc11u.o \
./src/main.o 

C_DEPS += \
./src/cdc_desc.d \
./src/cr_startup_lpc11u.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC11Uxx -I"/Users/yishii/Dropbox/lpcXpresso/LPC11Uxx_Driver_Lib" -I"/Users/yishii/Dropbox/lpcXpresso/CMSISv2p00_LPC11Uxx" -I"/Users/yishii/Dropbox/lpcXpresso/CMSISv2p00_LPC11Uxx/inc" -I"/Users/yishii/Dropbox/lpcXpresso/USB_ROM_CDC/inc" -I"/Users/yishii/Dropbox/lpcXpresso/LPC11Uxx_Driver_Lib/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_startup_lpc11u.o: ../src/cr_startup_lpc11u.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC11Uxx -I"/Users/yishii/Dropbox/lpcXpresso/LPC11Uxx_Driver_Lib" -I"/Users/yishii/Dropbox/lpcXpresso/CMSISv2p00_LPC11Uxx" -I"/Users/yishii/Dropbox/lpcXpresso/CMSISv2p00_LPC11Uxx/inc" -I"/Users/yishii/Dropbox/lpcXpresso/USB_ROM_CDC/inc" -I"/Users/yishii/Dropbox/lpcXpresso/LPC11Uxx_Driver_Lib/inc" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc11u.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


