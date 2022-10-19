CC = gcc
EXEC = listeTD4
#liste l'ensemble des fichier source
SRC = $(wildcard *.c)
#liste l'ensemble des fichier objet
OBJ = $(SRC:.c =.o)

all: $(EXEC) 

$(EXEC) : $(OBJ)
	$(CC) -o $(EXEC) $(OBJ)

#Joker qui prendre pour cible tous les fichier avec extention .o et en dependance tous les fichiers avec extention .c
%.o : %.c
#Creer l'ensemble des fichiers objet à partir de l'ensemble des fichier source
	%(CC) -o $(OBJ) -c $(SRC)

