################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/Program Files/CCS/ccsv6/tools/compiler/c2000_6.2.5

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./source/DSP2833x_usDelay.obj" \
"./source/DSP2833x_Xintf.obj" \
"./source/DSP2833x_SysCtrl.obj" \
"./source/DSP2833x_PieVect.obj" \
"./source/DSP2833x_PieCtrl.obj" \
"./source/DSP2833x_GlobalVariableDefs.obj" \
"./source/DSP2833x_DefaultIsr.obj" \
"./source/DSP2833x_CpuTimers.obj" \
"./source/DSP2833x_CodeStartBranch.obj" \
"./source/DSP2833x_ADC_cal.obj" \
"./yssources/ysSPI.obj" \
"./yssources/ysSCI.obj" \
"./yssources/ysPWM.obj" \
"./yssources/ysPORT.obj" \
"./yssources/ysECAP.obj" \
"./yssources/ysDAC.obj" \
"./yssources/ysCAN.obj" \
"./yssources/ysADC.obj" \
"./yssources/main.obj" \
"./yssources/DABcontrol.obj" \
"../cmd/DSP2833x_Headers_nonBIOS.cmd" \
"../cmd/F28335_RAM_lnk.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include yssources/subdir_vars.mk
-include source/subdir_vars.mk
-include cmd/subdir_vars.mk
-include yssources/subdir_rules.mk
-include source/subdir_rules.mk
-include cmd/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
DAB_V2G_MPC.out \

EXE_OUTPUTS__QUOTED += \
"DAB_V2G_MPC.out" \

BIN_OUTPUTS += \
DAB_V2G_MPC.hex \

BIN_OUTPUTS__QUOTED += \
"DAB_V2G_MPC.hex" \


# All Target
all: DAB_V2G_MPC.out

# Tool invocations
DAB_V2G_MPC.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/Program Files/CCS/ccsv6/tools/compiler/c2000_6.2.5/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --diag_warning=225 --display_error_number --diag_wrap=off -z -m"DAB_V2G_MPC.map" --stack_size=0x300 --warn_sections -i"C:/Program Files/CCS/ccsv6/tools/compiler/c2000_6.2.5/lib" -i"C:/Program Files/CCS/ccsv6/tools/compiler/c2000_6.2.5/include" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="DAB_V2G_MPC_linkInfo.xml" --rom_model -o "DAB_V2G_MPC.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

DAB_V2G_MPC.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"C:/Program Files/CCS/ccsv6/tools/compiler/c2000_6.2.5/bin/hex2000"  -o "DAB_V2G_MPC.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "yssources\DABcontrol.pp" "yssources\main.pp" "yssources\ysADC.pp" "yssources\ysCAN.pp" "yssources\ysDAC.pp" "yssources\ysECAP.pp" "yssources\ysPORT.pp" "yssources\ysPWM.pp" "yssources\ysSCI.pp" "yssources\ysSPI.pp" "source\DSP2833x_CpuTimers.pp" "source\DSP2833x_DefaultIsr.pp" "source\DSP2833x_GlobalVariableDefs.pp" "source\DSP2833x_PieCtrl.pp" "source\DSP2833x_PieVect.pp" "source\DSP2833x_SysCtrl.pp" "source\DSP2833x_Xintf.pp" 
	-$(RM) "yssources\DABcontrol.obj" "yssources\main.obj" "yssources\ysADC.obj" "yssources\ysCAN.obj" "yssources\ysDAC.obj" "yssources\ysECAP.obj" "yssources\ysPORT.obj" "yssources\ysPWM.obj" "yssources\ysSCI.obj" "yssources\ysSPI.obj" "source\DSP2833x_ADC_cal.obj" "source\DSP2833x_CodeStartBranch.obj" "source\DSP2833x_CpuTimers.obj" "source\DSP2833x_DefaultIsr.obj" "source\DSP2833x_GlobalVariableDefs.obj" "source\DSP2833x_PieCtrl.obj" "source\DSP2833x_PieVect.obj" "source\DSP2833x_SysCtrl.obj" "source\DSP2833x_Xintf.obj" "source\DSP2833x_usDelay.obj" 
	-$(RM) "source\DSP2833x_ADC_cal.pp" "source\DSP2833x_CodeStartBranch.pp" "source\DSP2833x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

