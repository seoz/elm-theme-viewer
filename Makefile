all:
	gcc main.c gui.c theme.c -o elm-theme-viwer `pkg-config --cflags --libs elementary`
