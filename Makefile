all:
	gcc main.c -o elm-theme-viwer `pkg-config --cflags --libs elementary`
