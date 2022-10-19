#include <stdio.h>
#include "list.h"

int main(void)
{
	int nbr_to_add = 0;

	List myList = new_list();
	printf("Combien de valeur voulez-vous ajouter ? ");
	scanf("%d", &nbr_to_add);
	myList = successive_insert(nbr_to_add,myList);

	clear_list(myList);

	return 0;
}
