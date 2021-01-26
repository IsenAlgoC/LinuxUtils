#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include "liste.h"

// #define VERSION 3.0
// #define SQUELET


// crée une nouvelle liste chainée unilataire vide et renvoie un pointeur sur cette liste
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
// crée un nouveau maillon qui contient la personne passée en paramètre
SingleLinkedListElem  *NewLinkedListElement(Enregistrement pers) {
	SingleLinkedListElem *tmp;
	tmp = (SingleLinkedListElem *)malloc(sizeof(SingleLinkedListElem));
	if (tmp != NULL) {	
	tmp->pers = pers;
	tmp->next = NULL;
	}
	return(tmp);
}
// renvoie un pointeur sur l'élément en ième position dans la liste
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

// Ajoute une nouvelle personne dans la liste chaînée en ième position
// Cette fonction fait appel à la fonction NewLinkedListElement(Enregistrement pers) pour créer un maillon
//
// FONCTION A COMPLETER AUX ENDROITS INDIQUES

int InsertElementAt(LinkedList *Liste, int i, Enregistrement pers) {
	SingleLinkedListElem *CurrentElement, *NewElement;
	if (Liste == NULL) return(0);
	// recherche de l'élément qui se trouve déjà en position i
	CurrentElement = GetElementAt(Liste, i);
	// s'il y en a un
	if (CurrentElement != NULL) {
		// on insère un nouvel élément
		NewElement = NewLinkedListElement(pers);
		// son suivant est alors l'élément courant
		NewElement->next = CurrentElement;

		if (i == 0) {
			// si l'insertion est en tête
			// le nouvel élément devient la tête
			Liste->head = NewElement;
		}
		else {
			// sinon il faut rétablir le chainage depuis l'élément précédent
			CurrentElement = GetElementAt(Liste, i - 1);
			// le successeur du précédent devient le nouvel élément
			CurrentElement->next = NewElement;
		}
		Liste->size++;
		return(1);
	}
	else {
		if (Liste->size == 0) { // insertion en tête de l'unique élément
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
// Suppression d'un élément de la liste chaînée
//
// FONCTION A COMPLETER
int DeleteLinkedListElem(LinkedList * list, SingleLinkedListElem * item) {
	if (list == NULL) return(0); // La liste n'existe pas
	if ((list->head == NULL) || (list->tail == NULL)) return(0); // liste vide ou anomalie
	if ((list->head == list->tail) && (list->size != 1)) return(0); // anomalie
	if ((list->size == 0) || (item == NULL)) return(0); // pas d'élément dans la liste ou item invalide

	//
	//
	// compléter code ici
	//
	//


	return(0);  // pas trouvé
}

