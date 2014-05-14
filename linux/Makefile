# Makefile pour arkanapong
# @author Oblet Alexis, Biteau Armand

CC=gcc
CFLAGS=-Wall -g
LDFLAGS= -lSDLmain -lSDL -lSDL_image -lGL -lGLU -lSDL_mixer -lSDL_ttf -lm

SRC_PATH=../src
OBJ_PATH=../obj
BIN_PATH=../bin
INCLUDE_PATH=-I../include

SRC_FILES = $(shell find $(SRC_PATH) -type f -name '*.c')

OBJ_FILES = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o, $(SRC_FILES))

EXEC=arkanopong

all: $(EXEC)
	@echo 'All compiled'
	rm -rf ../obj
	$(BIN_PATH)/$(EXEC)


$(EXEC): $(OBJ_FILES)
	@mkdir -p $(BIN_PATH)
	@$(CC) -o $(BIN_PATH)/$(EXEC) $(OBJ_FILES) $(LDFLAGS)

#les dépendances pour les .h n'y sont pas => make clean avant chaque compil

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	@mkdir -p "$(@D)"
	@$(CC) -o $@ -c $< $(INCLUDE_PATH) $(CFLAGS)

.PHONY: clean

clean:
	rm -rf ../obj
	rm -rf ../bin