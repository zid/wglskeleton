CC := gcc

SRC = game.c gfx.c gfx_geom.c shader.c model.c scene.c
OBJ = $(SRC:.c=.o)

CFLAGS  += -O2 -W -Wall -Iinclude/ -flto -march=native -mtune=native
LDFLAGS += -fwhole-program

ifeq ($(OS), Windows_NT)
	SRC += win-main.c win-gl-functions.c
	LDFLAGS += -lgdi32 -lopengl32
else
	SRC += linux-main.c
	LDFLAGS += -lGL -lX11
endif

game.exe: $(OBJ)
	$(CC) $(OBJ) -o game.exe $(LDFLAGS)

%.o : %.c
	$(CC) -c $^ $(CFLAGS)

clean:
	-rm game.exe
	-rm $(OBJ)
