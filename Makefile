all:
	gcc main.c gui.c theme.c -o elm-theme-viewer `pkg-config --cflags --libs elementary`
