TARGET = instructions
CFLAGS = -O0 -Wall -fno-exceptions

.phony: objdump all default clean
default: all

main.o: main.s
	psp-gcc -I. -I/usr/local/pspdev/psp/include -I/usr/local/pspdev/psp/sdk/include -G0 $(CFLAGS) -D_PSP_FW_VERSION=150 -c -o main.o main.s

$(TARGET): main.o
	cp main.o $(TARGET) &&\
	chmod +x $(TARGET)

all: $(TARGET)

objdump: $(TARGET)
	psp-objdump -d $(TARGET)

clean:
	rm $(TARGET) main.o
