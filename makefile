CC = gcc

SLD_DIR = ./librairies/SDL2-2.0.6
SDL_LIB = ${SLD_DIR}/lib/Win32
SDL_INC = ${SLD_DIR}/include

ifeq ($(OS),Windows_NT)
	LIBS = -lmingw32 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2
	clr = del /s *.o
	propre = del /s *.exe
else
	LIBS = `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -lSDL2
	clr = rm -rf *.o
	propre = find . -type f -executable -delete
endif

LIBS += -L${SDL_LIB} -I${SDL_INC}

Lights_out: main.o SDL_local.o
	${CC} $^ -o $@ ${LIBS}

%.o: %.c
	${CC} $< -c -o $@ ${LIBS}

clean:
	${clr}

mrproper: clean
	${propre}