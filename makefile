CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

abb: abb.c pruebas.c
	gcc abb.c pruebas.c $(CFLAGS) -o abb

ejecutar: abb
	clear
	./abb

debug: abb
	clear
	gdb ./abb

probar: abb
	clear
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb

minipruebas: abb.c abb_minipruebas.c
	gcc abb.c abb_minipruebas.c $(CFLAGS) -o minipruebas

ejecutar_minipruebas: minipruebas
	clear
	./minipruebas

debug_minipruebas: minipruebas
	clear
	gdb ./minipruebas

probar_minipruebas: minipruebas
	clear
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./minipruebas