#pragma once
#include "personne.h"
// LISTES UNILATERES **************************************************
// #define VERSION 3.0
// #define SQUELET

#define UP 0
#define DOWN 1


typedef struct SingleLinkedListElem {
	Enregistrement pers;
	struct SingleLinkedListElem *next;
} SingleLinkedListElem;

typedef struct LinkedList {
	SingleLinkedListElem *head;
	int size;
	SingleLinkedListElem *tail;
} LinkedList;
// Crée une liste chaînée unilatère vide et renvoie un pointeur sur celle-ci
LinkedList *NewLinkedList();

// Crée un nouveau maillon qui contient une nouvelle personne et renvoie un pointeur sur ce maillon
SingleLinkedListElem  *NewLinkedListElement(Enregistrement pers);

// Renvoie un pointeur sur le maillon qui se trouve en ième position à partir de 1
SingleLinkedListElem *GetElementAt(LinkedList *liste, int i);

// Ajoute une nouvelle personne dans la liste chaînée en ième position
// Cette fonction fait appel à la fonction NewLinkedListElement(Enregistrement pers) pour créer un maillon

int InsertElementAt(LinkedList *liste, int i, Enregistrement pers);

// Suppression et destruction d'un élément de liste chainée
int DeleteLinkedListElem(LinkedList *list, SingleLinkedListElem *Elem);

