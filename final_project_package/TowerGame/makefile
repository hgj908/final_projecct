CC := g++
CFLAGS := -Wall -std=c++17 -O2 -v
ALLEGRO_LIBRARIES := allegro-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_dialog-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5
ALLEGRO_FLAGS := $(shell pkg-config --cflags --libs "$(ALLEGRO_LIBRARIES) <= 5.2.7") -lallegro -lallegro_main

OUT:= game
SOURCE = Main.cpp Attack.cpp Circle.cpp GameWindow.cpp global.cpp Level.cpp Menu.cpp Monster.cpp Slider.cpp Tower.cpp DataCenter.cpp ../algif5/src/algif.cpp ../algif5/src/bitmap.cpp ../algif5/src/gif.cpp ../algif5/src/lzw.cpp
OBJ = Main.o Attack.o Circle.o GameWindow.o global.o Level.o Menu.o Monster.o Slider.o Tower.o DataCenter.o algif.o bitmap.o gif.o lzw.o

all: 
	$(CC) -c -g $(CFLAGS) $(SOURCE) $(ALLEGRO_FLAGS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ) $(ALLEGRO_FLAGS)
	rm $(OBJ)

.PHONY:clean
clean:
	rm $(OUT)
