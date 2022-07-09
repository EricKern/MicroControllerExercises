################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Device_Startup/ \
../Common \
../OCD/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../board_cortex7_init.c \
../Common/string.c \
../Common/syscalls.c \
../dbgu.c \
../Device_Startup/startup_same70q21.c \
../Device_Startup/system_same70q21.c \
../fifo.c \
../main.c \
../mpu.c \
../xdmac.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
board_cortex7_init.o \
Common/string.o \
Common/syscalls.o \
dbgu.o \
Device_Startup/startup_same70q21.o \
Device_Startup/system_same70q21.o \
fifo.o \
main.o \
mpu.o \
xdmac.o

OBJS_AS_ARGS +=  \
board_cortex7_init.o \
Common/string.o \
Common/syscalls.o \
dbgu.o \
Device_Startup/startup_same70q21.o \
Device_Startup/system_same70q21.o \
fifo.o \
main.o \
mpu.o \
xdmac.o

C_DEPS +=  \
board_cortex7_init.d \
Common/string.d \
Common/syscalls.d \
dbgu.d \
Device_Startup/startup_same70q21.d \
Device_Startup/system_same70q21.d \
fifo.d \
main.d \
mpu.d \
xdmac.d

C_DEPS_AS_ARGS +=  \
board_cortex7_init.d \
Common/string.d \
Common/syscalls.d \
dbgu.d \
Device_Startup/startup_same70q21.d \
Device_Startup/system_same70q21.d \
fifo.d \
main.d \
mpu.d \
xdmac.d

OUTPUT_FILE_PATH +=CORTEX_TEST.elf

OUTPUT_FILE_PATH_AS_ARGS +=CORTEX_TEST.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+=  \
../Device_Startup/same70q21_flash.ld \
../Device_Startup/same70q21_sram.ld


# AVR32/GNU C Compiler





















./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.2.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE)  -x c -mthumb -D__SAME70Q21__ -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\SAME70_DFP\2.1.82\include" -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\arm\CMSIS\4.2.0\CMSIS\Include"  -O0 -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m7 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

Common/%.o: ../Common/%.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.2.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE)  -x c -mthumb -D__SAME70Q21__ -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\SAME70_DFP\2.1.82\include" -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\arm\CMSIS\4.2.0\CMSIS\Include"  -O0 -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m7 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

Device_Startup/%.o: ../Device_Startup/%.c
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 6.2.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE)  -x c -mthumb -D__SAME70Q21__ -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\SAME70_DFP\2.1.82\include" -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\arm\CMSIS\4.2.0\CMSIS\Include"  -O0 -ffunction-sections -mlong-calls -g3 -Wall -mcpu=cortex-m7 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: ARM/GNU Linker : 6.2.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -mthumb -Wl,-Map="CORTEX_TEST.map" -Wl,--start-group -lm  -Wl,--end-group -L"..\\Device_Startup"  -Wl,--gc-sections -mcpu=cortex-m7 -Tsame70q21_flash.ld  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -O binary "CORTEX_TEST.elf" "CORTEX_TEST.bin"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "CORTEX_TEST.elf" "CORTEX_TEST.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O binary "CORTEX_TEST.elf" "CORTEX_TEST.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objdump.exe" -h -S "CORTEX_TEST.elf" > "CORTEX_TEST.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "CORTEX_TEST.elf" "CORTEX_TEST.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-size.exe" "CORTEX_TEST.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "CORTEX_TEST.elf" "CORTEX_TEST.a" "CORTEX_TEST.hex" "CORTEX_TEST.bin" "CORTEX_TEST.lss" "CORTEX_TEST.eep" "CORTEX_TEST.map" "CORTEX_TEST.srec"
	