#-----------------------
# Análisis de algoritmos 2017/2018
# Práctica 1
# 
# Alberto Ayala, Mihai Blidaru
#-----------------------

CC = gcc -g -std=gnu99 -pedantic
LIBS = -lm
CFLAGS = -Wall 
EXE = ejercicio1 ejercicio2 ejercicio3 ejercicio4 ejercicio5

all : $(EXE)

.PHONY : clean clear
clean :
	rm -f *.o core $(EXE)
	
clear:
	rm -f *.o

$(EXE) : % : %.o ordenacion.o tiempos.o permutaciones.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o ordenacion.o tiempos.o permutaciones.o $(LIBS)

permutaciones.o : permutaciones.c permutaciones.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

 ordenacion.o : ordenacion.c ordenacion.h
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


ejercicio1_test:
	@echo Ejecutando ejercicio1
	@./ejercicio1 -limInf 0 -limSup 9 -numN 100

ejercicio2_test:
	@echo Ejecutando ejercicio2
	@./ejercicio2 -tamanio 10 -numP 20

ejercicio3_test:
	@echo Ejecutando ejercicio3
	@./ejercicio3 -tamanio 10 -numP 20

ejercicio4_test:
	@echo Ejecutando ejercicio4
	@./ejercicio4 -tamanio 10

ejercicio5_test:
	@echo Ejecutando ejercicio5
	@./ejercicio5 -num_min 100 -num_max 50000 -incr 100 -numP 20 -fichSalida ejercicio5.log

