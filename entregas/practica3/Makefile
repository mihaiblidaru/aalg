#-----------------------
# Análisis de algoritmos 2017/2018
# Práctica 3
# 
# Alberto Ayala, Mihai Blidaru
#-----------------------

CC = gcc -g -std=gnu99 -pedantic
LIBS = -lm
CFLAGS = -Wall
EXE = ejercicio1 ejercicio2 

all : $(EXE)

.PHONY : clean clear
clean :
	rm -f *.o core $(EXE)
	
clear:
	rm -f *.o

$(EXE) : % : %.o busqueda.o tiempos.o permutaciones.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o busqueda.o tiempos.o permutaciones.o $(LIBS)

busqueda.o : busqueda.c busqueda.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

tiempos.o : tiempos.c tiempos.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

permutaciones.o : permutaciones.c permutaciones.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<
