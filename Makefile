CC := gcc

SRC = main.c game.c gl-functions.c gfx.c gfx_geom.c shader.c model.c scene.c
OBJ = $(SRC:.c=.o)

CFLAGS  += -O2 -W -Wall -Iinclude/ -flto -march=native -mtune=native
LDFLAGS += -lgdi32 -lopengl32 -fwhole-program

game.exe: $(OBJ)
	$(CC) $(OBJ) -o game.exe $(LDFLAGS)

%.o : %.c
	$(CC) -c $^ $(CFLAGS)

clean:
	-rm game.exe
	-rm $(OBJ)