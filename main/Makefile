# Binaries will be generated with this name (.elf, .bin, .hex, etc)
PROJ_NAME=PMPS

# Put your STM32F4 library code directory here
STM_COMMON=../sdk
STM32CUBEPROG:=../stmcubeprog/bin/STM32_Programmer.sh -vb 1 -q -c port=SWD 

# Put your source files here (or *.c, etc)
SRCS = main.c 
SRCS += system_stm32f4xx.c stm32f4xx_it.c
SRCS += usart.c misc.c
SRCS += delay.c
SRCS += adc.c
SRCS += pwm.c

# HAL Driver
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_usart.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c 
SRCS += $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_timebase_tim_template.c

# Normally you shouldn't need to change anything below this line!
#######################################################################################
GNUGCC = $(STM_COMMON)/gcc-arm-none-eabi/bin
CC = $(GNUGCC)/arm-none-eabi-gcc
OBJCOPY = $(GNUGCC)/arm-none-eabi-objcopy
SIZE =  $(GNUGCC)/arm-none-eabi-size

CFLAGS  = -g -O2 -Wall -Tstm32_flash.ld 
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
# important flag is -fsingle-precision-constant which prevents the double precision emulation
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant
CFLAGS += -I.

# Include files from STM libraries
CFLAGS += -I $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Inc
CFLAGS += -I $(STM_COMMON)/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
CFLAGS += -I $(STM_COMMON)/Drivers/CMSIS/Include 
CFLAGS += -I $(STM_COMMON)/Drivers/CMSIS/Device/ST/STM32F4xx/Include
#CFLAGS += -I$(STM_COMMON)/Utilities/STM32F4-Discovery
#CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/Include 
#CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/ST/STM32F4xx/Include
#CFLAGS += -I$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/inc

# add startup file to build
SRCS += $(STM_COMMON)/Drivers/startup_stm32f4xx.s
OBJS = $(SRCS:.c=.o)


.PHONY: proj

all: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -lm -lc -lnosys -o $@ 
	$(CC) $(CFLAGS) -S $< $^
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin
	$(SIZE) -B  $(PROJ_NAME).elf
	rm -rf *.o *.s
	ls -l $(PROJ_NAME).bin



clean:
	rm -rf *.o $(PROJ_NAME).elf $(PROJ_NAME).hex $(PROJ_NAME).bin *.s
	ls

# Flash the STM32F4
upload: proj
	@$(STM32CUBEPROG) -w $(PROJ_NAME).bin  0x08000000 
	@sleep 1
	@$(STM32CUBEPROG) -hardRst 

