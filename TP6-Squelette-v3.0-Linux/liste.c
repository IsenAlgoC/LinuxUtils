#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include "liste.h"

// #define VERSION 3.0
// #define SQUELET


// cr�e une nouvelle liste chain�e unilataire vide et renvoie un pointeur sur cette liste
LinkedList *NewLinkedList() {
	LinkedList *tmp;
	tmp = (LinkedList*)malloc(sizeof(LinkedList));
	if (tmp != NULL) {
		tmp->head = NULL;
		tmp->tail = NULL;
		tmp->size = 0;
	}
	return tmp;
}
// cr�e un nouveau maillon qui contient la personne pass�e en param�tre
SingleLinkedListElem  *NewLinkedListElement(Enregistrement pers) {
	SingleLinkedListElem *tmp;
	tmp = (SingleLinkedListElem *)malloc(sizeof(SingleLinkedListElem));
	if (tmp != NULL) {	
	tmp->pers = pers;
	tmp->next = NULL;
	}
	return(tmp);
}
// renvoie un pointeur sur l'�l�ment en i�me position dans la liste
SingleLinkedListElem *GetElementAt(LinkedList *Liste, int i) {
	int CurrentIndex = 0;
	SingleLinkedListElem *Element;
	if ((Liste == NULL) || (i < 0) || (i >= Liste->size)) return(NULL);
	if (i == 0) return(Liste->head);
	if (i == Liste->size - 1) return(Liste->tail);
	Element = Liste->head;
	while (CurrentIndex != i  && Element != NULL) {
		Element = Element->next;
		CurrentIndex++;
	}
	return(Element);
}

// Ajoute une nouvelle personne dans la liste cha�n�e en i�me position
// Cette fonction fait appel � la fonction NewLinkedListElement(Enregistrement pers) pour cr�er un maillon
//
// FONCTION A COMPLETER AUX ENDROITS INDIQUES

int InsertElementAt(LinkedList *Liste, int i, Enregistrement pers) {
	SingleLinkedListElem *CurrentElement, *NewElement;
	if (Liste == NULL) return(0);
	// recherche de l'�l�ment qui se trouve d�j� en position i
	CurrentElement = GetElementAt(Liste, i);
	// s'il y en a un
	if (CurrentElement != NULL) {
		// on ins�re un nouvel �l�ment
		NewElement = NewLinkedListElement(pers);
		// son suivant est alors l'�l�ment courant
		NewElement->next = CurrentElement;

		if (i == 0) {
			// si l'insertion est en t�te
			// le nouvel �l�ment devient la t�te
			Liste->head = NewElement;
		}
		else {
			// sinon il faut r�tablir le chainage depuis l'�l�ment pr�c�dent
			CurrentElement = GetElementAt(Liste, i - 1);
			// le successeur du pr�c�dent devient le nouvel �l�ment
			CurrentElement->next = NewElement;
		}
		Liste->size++;
		return(1);
	}
	else {
		if (Liste->size == 0) { // insertion en t�te de l'unique �l�ment
			NewElement = NewLinkedListElement(pers);
			if (NewElement != NULL) {
			//
			//
			//   insertion code ici
			//
			//
			//
		}
			else {
				return(0);
			}
		}
		if (Liste->size <= i) { // insertion en queue
			NewElement = NewLinkedListElement(pers);
			if (NewElement != NULL) {
			//
			//
			//   insertion code ici
			//
			//
			//
			}
			else {
				return(0);
			}
		}

	}
	return(0);
}
//
// Suppression d'un �l�ment de la liste cha�n�e
//
// FONCTION A COMPLETER
int DeleteLinkedListElem(LinkedList * list, SingleLinkedListElem * item) {
	if (list == NULL) return(0); // La liste n'existe pas
	if ((list->head == NULL) || (list->tail == NULL)) return(0); // liste vide ou anomalie
	if ((list->head == list->tail) && (list->size != 1)) return(0); // anomalie
	if ((list->size == 0) || (item == NULL)) return(0); // pas d'�l�ment dans la liste ou item invalide

	//
	//
	// compl�ter code ici
	//
	//


	return(0);  // pas trouv�
}

