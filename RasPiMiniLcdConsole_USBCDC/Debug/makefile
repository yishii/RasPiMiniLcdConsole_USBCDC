################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: RasPiMiniLcdConsole_USBCDC.axf

dependents:
	-cd /Users/yishii/Dropbox/lpcXpresso/CMSISv2p00_LPC11Uxx/Release && $(MAKE) clean all
	-cd /Users/yishii/Dropbox/lpcXpresso/LPC11Uxx_Driver_Lib/Release && $(MAKE) clean all

# Tool invocations
RasPiMiniLcdConsole_USBCDC.axf: $(OBJS) $(USER_OBJS) /Users/yishii/Dropbox/lpcXpresso/CMSISv2p00_LPC11Uxx/Release/libCMSISv2p00_LPC11Uxx.a /Users/yishii/Dropbox/lpcXpresso/LPC11Uxx_Driver_Lib/Release/libLPC11Uxx_Driver_Lib.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/Users/yishii/Dropbox/lpcXpresso/LPC11Uxx_Driver_Lib/Release" -L"/Users/yishii/Dropbox/lpcXpresso/CMSISv2p00_LPC11Uxx/Release" -L"/Users/yishii/Dropbox/lpcXpresso/RasPiMiniLcdConsole_USBCDC/inc" -Xlinker -Map="RasPiMiniLcdConsole_USBCDC.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "RasPiMiniLcdConsole_USBCDC_Debug.ld" -o "RasPiMiniLcdConsole_USBCDC.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) RasPiMiniLcdConsole_USBCDC.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "RasPiMiniLcdConsole_USBCDC.axf"; arm-none-eabi-objcopy -O binary "RasPiMiniLcdConsole_USBCDC.axf" "RasPiMiniLcdConsole_USBCDC.bin" ; checksum -p LPC11U24_301 -d "RasPiMiniLcdConsole_USBCDC.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
/Users/yishii/Dropbox/lpcXpresso/CMSISv2p00_LPC11Uxx/Release/libCMSISv2p00_LPC11Uxx.a:
/Users/yishii/Dropbox/lpcXpresso/LPC11Uxx_Driver_Lib/Release/libLPC11Uxx_Driver_Lib.a:

-include ../makefile.targets
