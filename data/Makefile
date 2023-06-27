SRC = $(wildcard *.s)
OBJ = $(SRC:.s=.bin)

all: $(OBJ)

%.o: %.s
	as $^ -o $@

%.bin: %.o
	objcopy --dump-section .model=$@ $^
