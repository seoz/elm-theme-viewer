all:
	gcc main.c log.c gui.c theme.c -o elm-theme-viewer `pkg-config --cflags --libs elementary`
