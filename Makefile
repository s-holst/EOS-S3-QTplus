CC=arm-none-eabi-gcc
LD=$(CC)

FLAGS=-mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmerge-constants -fomit-frame-pointer -fcrossjumping -fexpensive-optimizations -ftoplevel-reorder -fmessage-length=0 -lm -fsigned-char -ffunction-sections -fdata-sections -gdwarf-4

CCFLAGS=$(FLAGS) -std=c99 
LDFLAGS=$(FLAGS) -T "main.ld" -Xlinker --gc-sections -Wall -Werror -Wl,--fatal-warnings --specs=nano.specs --specs=nosys.specs -Wl,--no-wchar-size-warning 

DEPS=regs/*.h

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CCFLAGS)

main.elf: startup.o main.o uart.o i2c.o
	$(LD) -o $@ $^ $(LDFLAGS)

main.bin: main.elf
	arm-none-eabi-objcopy -O binary main.elf main.bin


.PHONY: all run clean
all: main.bin

run: main.bin
	JLinkExe -Device Cortex-M4 -If SWD -Speed 4000 -autoconnect 1 -CommandFile scripts/load_and_run.jlink
	
clean:
	-rm -f *.o main.elf