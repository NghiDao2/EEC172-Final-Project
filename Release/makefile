################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/Users/daomi/TI/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./AWSIoT.obj" \
"./Adafruit_GFX.obj" \
"./Adafruit_OLED.obj" \
"./Clock.obj" \
"./gpio_if.obj" \
"./i2c_if.obj" \
"./main.obj" \
"./network_common.obj" \
"./pin_mux_config.obj" \
"./startup_ccs.obj" \
"./timer_if.obj" \
"./uart_if.obj" \
"./Scanner/IRSensor.obj" \
"./Scanner/Machine.obj" \
"./Scanner/StepperMotor.obj" \
"./UserInterface/AdjustmentUI.obj" \
"./UserInterface/Button.obj" \
"./UserInterface/MainOptions.obj" \
"./UserInterface/MainScreen.obj" \
"./UserInterface/MoveOptions.obj" \
"./UserInterface/OLED.obj" \
"./UserInterface/OptionsUI.obj" \
"./UserInterface/SettingsOptions.obj" \
"./UserInterface/UserInput.obj" \
"./UserInterface/Utils.obj" \
"./utils/network_utils.obj" \
"../cc3200v1p32.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"C:/TI/CC3200SDK_1.5.0/cc3200-sdk/driverlib/ccs/Release/driverlib.a" \
-l"C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink/ccs/NON_OS/simplelink.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Scanner/subdir_vars.mk
-include UserInterface/subdir_vars.mk
-include utils/subdir_vars.mk
-include subdir_rules.mk
-include Scanner/subdir_rules.mk
-include UserInterface/subdir_rules.mk
-include utils/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Project.out \

EXE_OUTPUTS__QUOTED += \
"Project.out" \


# All Target
all: Project.out

# Tool invocations
Project.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"C:/Users/daomi/TI/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=none -me -Ooff --define=ccs --define=cc3200 -g --gcc --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"Project.map" --heap_size=0x00008000 --stack_size=0x00001000 -i"C:/Users/daomi/TI/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/lib" -i"C:/Users/daomi/TI/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="Project_linkInfo.xml" --rom_model -o "Project.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "AWSIoT.obj" "Adafruit_GFX.obj" "Adafruit_OLED.obj" "Clock.obj" "gpio_if.obj" "i2c_if.obj" "main.obj" "network_common.obj" "pin_mux_config.obj" "startup_ccs.obj" "timer_if.obj" "uart_if.obj" "Scanner\IRSensor.obj" "Scanner\Machine.obj" "Scanner\StepperMotor.obj" "UserInterface\AdjustmentUI.obj" "UserInterface\Button.obj" "UserInterface\MainOptions.obj" "UserInterface\MainScreen.obj" "UserInterface\MoveOptions.obj" "UserInterface\OLED.obj" "UserInterface\OptionsUI.obj" "UserInterface\SettingsOptions.obj" "UserInterface\UserInput.obj" "UserInterface\Utils.obj" "utils\network_utils.obj" 
	-$(RM) "AWSIoT.d" "Adafruit_GFX.d" "Adafruit_OLED.d" "Clock.d" "gpio_if.d" "i2c_if.d" "main.d" "network_common.d" "pin_mux_config.d" "startup_ccs.d" "timer_if.d" "uart_if.d" "Scanner\IRSensor.d" "Scanner\Machine.d" "Scanner\StepperMotor.d" "UserInterface\AdjustmentUI.d" "UserInterface\Button.d" "UserInterface\MainOptions.d" "UserInterface\MainScreen.d" "UserInterface\MoveOptions.d" "UserInterface\OLED.d" "UserInterface\OptionsUI.d" "UserInterface\SettingsOptions.d" "UserInterface\UserInput.d" "UserInterface\Utils.d" "utils\network_utils.d" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-@echo 'Bin Generation'
	-"C:/Users/daomi/TI/ccs1250/ccs/utils/tiobj2bin/tiobj2bin" "Project.out" "Project.bin" "C:/Users/daomi/TI/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armofd" "C:/Users/daomi/TI/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armhex" "C:/Users/daomi/TI/ccs1250/ccs/utils/tiobj2bin/mkhex4bin"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

