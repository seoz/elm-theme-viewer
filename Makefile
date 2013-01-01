all:
	edje_cc data/layout.edc
	gcc src/main.c src/log.c src/gui.c src/theme.c src/widget.c -o elm_theme_viewer `pkg-config --cflags --libs elementary` -g -Wall

install:
	cp ./elm-theme-viewer /usr/local/bin
	mkdir -p /usr/local/share/elm-theme-viewer/images
	cp images/* /usr/local/share/elm-theme-viewer/images
