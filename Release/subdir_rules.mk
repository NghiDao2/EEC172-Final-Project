################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/daomi/TI/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=none -me -Ooff --include_path="C:/Users/daomi/TI/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --include_path="C:/Users/daomi/OneDrive - University of California, Davis/Spring 2025/EEC 172/lab/ccs_workspace/Project" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/driverlib" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/inc" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/example/common" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink/" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink/source" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink/include" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink_extlib/provisioninglib" --define=ccs --define=cc3200 -g --gcc --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

gpio_if.obj: C:/TI/CC3200SDK_1.5.0/cc3200-sdk/example/common/gpio_if.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/daomi/TI/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=none -me -Ooff --include_path="C:/Users/daomi/TI/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --include_path="C:/Users/daomi/OneDrive - University of California, Davis/Spring 2025/EEC 172/lab/ccs_workspace/Project" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/driverlib" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/inc" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/example/common" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink/" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink/source" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink/include" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink_extlib/provisioninglib" --define=ccs --define=cc3200 -g --gcc --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="gpio_if.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

i2c_if.obj: C:/TI/CC3200SDK_1.5.0/cc3200-sdk/example/common/i2c_if.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/daomi/TI/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=none -me -Ooff --include_path="C:/Users/daomi/TI/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --include_path="C:/Users/daomi/OneDrive - University of California, Davis/Spring 2025/EEC 172/lab/ccs_workspace/Project" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/driverlib" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/inc" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/example/common" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink/" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink/source" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink/include" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink_extlib/provisioninglib" --define=ccs --define=cc3200 -g --gcc --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="i2c_if.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

network_common.obj: C:/TI/CC3200SDK_1.5.0/cc3200-sdk/example/common/network_common.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/daomi/TI/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=none -me -Ooff --include_path="C:/Users/daomi/TI/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --include_path="C:/Users/daomi/OneDrive - University of California, Davis/Spring 2025/EEC 172/lab/ccs_workspace/Project" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/driverlib" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/inc" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/example/common" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink/" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink/source" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink/include" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink_extlib/provisioninglib" --define=ccs --define=cc3200 -g --gcc --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="network_common.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_ccs.obj: C:/TI/CC3200SDK_1.5.0/cc3200-sdk/example/common/startup_ccs.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/daomi/TI/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=none -me -Ooff --include_path="C:/Users/daomi/TI/ccs1250/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --include_path="C:/Users/daomi/OneDrive - University of California, Davis/Spring 2025/EEC 172/lab/ccs_workspace/Project" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/driverlib" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/inc" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/example/common" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink/" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink/source" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink/include" --include_path="C:/TI/CC3200SDK_1.5.0/cc3200-sdk/simplelink_extlib/provisioninglib" --define=ccs --define=cc3200 -g --gcc --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="startup_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


