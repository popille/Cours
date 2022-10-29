#Pour le premier lancement (sans newfile) executer "make" puis "./prog" ou "make all"

VERIF = newfile.csv
TEST = $(wildcard newfile.csv)


prog : main.o
	gcc -o prog  main.o -lm

#####cibles pour execution du programme######
all : 
	make clean
	./prog
	libreoffice newfile.csv


test_console : 
	make clean
	./prog
#############################################

main.o : main.c
	gcc -o main.o -c main.c 
	
clean :
	rm -rf *.o

ifeq ($(TEST),$(VERIF))	
		rm newfile.csv
else
	@echo pas de newfile à supprimer
endif

clean_all :
	make clean
	rm prog

