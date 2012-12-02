all:
	gcc main.c log.c gui.c theme.c widget.c -o elm-theme-viewer `pkg-config --cflags --libs elementary` -g -Wall

install:
	cp ./elm-theme-viewer /usr/local/bin
	mkdir -p /usr/local/share/elm-theme-viewer/images
	cp images/* /usr/local/share/elm-theme-viewer/images
