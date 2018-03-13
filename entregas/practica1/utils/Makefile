ALL: gen_hist

gen_hist: gen_hist.c ../permutaciones.h ../permutaciones.c
	gcc -ansi -pedantic -Wall gen_hist.c ../permutaciones.c -o gen_hist
	
clean: 
	rm -f gen_hist

