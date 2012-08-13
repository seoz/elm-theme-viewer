all:
	gcc main.c gui.c -o elm-theme-viwer `pkg-config --cflags --libs elementary`
