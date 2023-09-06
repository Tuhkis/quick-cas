all: main.o microui.o str.o renderer.o util.o
	$(LINK)
	strip $(OUT)

main.o: src/main.c
	$(COMP)

microui.o: src/microui.c
	$(COMP)

str.o: src/str.c include/str.h
	$(COMP)

renderer.o: src/renderer.c
	$(COMP)

util.o: src/util.c include/util.h
	$(COMP)

