CC=arm-none-eabi-gcc
LD=$(CC)

FLAGS=-mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmerge-constants -fomit-frame-pointer -fcrossjumping -fexpensive-optimizations -ftoplevel-reorder -fmessage-length=0 -lm -fsigned-char -ffunction-sections -fdata-sections -gdwarf-4

CCFLAGS=$(FLAGS) -std=c99 
LDFLAGS=$(FLAGS) -T "main.ld" -Xlinker --gc-sections -Wall -Werror -Wl,--fatal-warnings --specs=nano.specs --specs=nosys.specs -Wl,--no-wchar-size-warning 

DEPS=*.h

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CCFLAGS)

main.elf: startup.o main.o
	$(LD) -o $@ $^ $(LDFLAGS)


.PHONY: all clean
all: main.elf

clean:
	-rm -f *.o main.elf