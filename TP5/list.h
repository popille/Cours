#ifndef __LIST__H__
#define __LIST__H__

	#include <stdio.h>
	#include <stdlib.h>

	typedef enum
	{
		false, //0
		true //1
	}Bool;
	
	
	typedef struct ListElement
	{
		int value;
		struct ListElement *next;	
	}ListElement, *List;
	
	/*-----Fonction de base--------*/
	Bool is_empty_list(List  list);
	List queue(List  list);
	int head(List  list);
	
	/*-------Creation/Ajout--------*/
	List new_list(void);
	List createElement(int val);
	List insert(List newList, List   list);
	List successive_insert(int nbr_to_add, List list);
	/*--------Suppression----------*/
	List delete_first_element(List   list);
	List clear_list(List   list);	
	/*------------------------------*/	
	void print_list(List  list);
	
	
	

#endif
