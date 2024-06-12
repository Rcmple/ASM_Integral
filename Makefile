CFLAGS ?= -O2 -g

CFLAGS += -std=gnu99

CFLAGS += -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self \
	-Wswitch-default -Wpointer-arith -Wtype-limits -Wempty-body \
	-Wstrict-prototypes -Wold-style-declaration -Wold-style-definition \
	-Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs \
	-Wstack-usage=4096 -Wmissing-prototypes -Wfloat-equal -Wabsolute-value

CFLAGS += -fsanitize=undefined -fsanitize-undefined-trap-on-error

CC += -m32 -no-pie -fno-pie

LDLIBS = -lm

.PHONY: all

all: integral

integral: f1_calc.o f2_calc.o f3_calc.o integral.o
	$(CC) $(CFLAGS) f1_calc.o f2_calc.o f3_calc.o integral.o -o start
f1_calc.o:
	nasm -f elf f1_calc.asm
f2_calc.o:
	nasm -f elf f2_calc.asm
f3_calc.o:
	nasm -f elf f3_calc.asm
integral.o:
	$(CC) $(CFLAGS) -c integral.c
clean:
	rm -rf *.o integral
	rm -rf *.obj integral
	rm start
