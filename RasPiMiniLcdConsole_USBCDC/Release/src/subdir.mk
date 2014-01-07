################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/7x5fonts.c \
../src/cdc_desc.c \
../src/console.c \
../src/cr_startup_lpc11u.c \
../src/fifo.c \
../src/gpio.c \
../src/iohandler.c \
../src/lcd_control.c \
../src/main.c \
../src/systick.c 

OBJS += \
./src/7x5fonts.o \
./src/cdc_desc.o \
./src/console.o \
./src/cr_startup_lpc11u.o \
./src/fifo.o \
./src/gpio.o \
./src/iohandler.o \
./src/lcd_control.o \
./src/main.o \
./src/systick.o 

C_DEPS += \
./src/7x5fonts.d \
./src/cdc_desc.d \
./src/console.d \
./src/cr_startup_lpc11u.d \
./src/fifo.d \
./src/gpio.d \
./src/iohandler.d \
./src/lcd_control.d \
./src/main.d \
./src/systick.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DNDEBUG -D__CODE_RED -D__USE_CMSIS=CMSISv2p00_LPC11Uxx -I"/Users/yishii/Dropbox/lpcXpresso/CMSISv2p00_LPC11Uxx/inc" -I"/Users/yishii/Dropbox/lpcXpresso/RasPiMiniLcdConsole_USBCDC/inc" -I"/Users/yishii/Dropbox/lpcXpresso/LPC11Uxx_Driver_Lib/inc" -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


