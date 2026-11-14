
CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -pedantic

LDLIBS = -lm

OBJETOS = main.o simulador.o validaciones.o interfaz.o

PROGRAMA = artemis

$(PROGRAMA): $(OBJETOS)
	$(CC) $(CFLAGS) -o $(PROGRAMA) $(OBJETOS) $(LDLIBS)

main.o: main.c simulador.h validaciones.h interfaz.h

simulador.o: simulador.c simulador.h

validaciones.o: validaciones.c validaciones.h

interfaz.o: interfaz.c interfaz.h simulador.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJETOS) $(PROGRAMA)

.PHONY: clean
