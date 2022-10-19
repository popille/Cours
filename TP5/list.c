#include "list.h"

/* --------------Fonction de base---------------*/

Bool is_empty_list(List list)
{
	if(list == NULL) return true;
	return false;
}

List queue(List list)
{
	return list->next;
}

int head(List list)
{
	return list->value;
}

/* -------------Creation/Ajout----------------*/
List new_list(void)
{
	return NULL;
}

List createElement(int val){
	ListElement *element;
	
	element = malloc(sizeof(*element));
	
	if(element == NULL)
	{
		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}
	
	element->value = val;
	element->next = NULL;

	return element;

}

List insert(List  newList, List list)
{	
	if(is_empty_list(  list))  newList->next = NULL;
	else   newList->next = list;
	
	return  newList;
}

List successive_insert(int nbr_to_add, List list)
{
	int val = 0;
	int i = 0;
	List newList = new_list();

	printf("Pour arreter l'ajout, entrer -1.\n");
	while(val != -1 && i < nbr_to_add)
	{
		printf("Valeur à ajouter : ");
		scanf("%d", &val);
		if(val != -1){ 			
			newList = createElement(val);
			list = insert(newList, list);
		}
		print_list(list);
		i++;
	}
	return list;
}

/*------------------Suppresion------------------*/
List delete_first_element(List   list)
{
	if(is_empty_list(list)) return new_list();
	
	if(queue(list) == NULL)				//Si un seul element, on supprime l'element et retourne  liste vide
	{
	 	free(list);
	 	list = NULL;
	 	
	 	return new_list();
	}									//Sinon on crée un pointeur sur l'element suivant de la  liste et on retourne la  liste a partir de cet element
	
	ListElement *element;
	
	element = malloc(sizeof(*element));
	
	if(element == NULL)
	{
		fprintf(stderr, "Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}
	
	element = list->next;
	
	free(list);
	list = NULL;
	
	return element;
	
}


List clear_list(List list)
{
	if(is_empty_list(list)) return NULL;
	while(!is_empty_list(list))
	{
		  list = delete_first_element(list);
	}
	printf("\nListe effacee\n");
	return list;
}


void print_list(List list)
{
	if(is_empty_list(list))
	{
		printf("Rien a afficher. La  liste est vide \n");
		return;
	}
	
	while(!is_empty_list(list))
	{
		printf("[%d]", head(list));
		list = queue(list);
	}
	printf("\n");
}
















