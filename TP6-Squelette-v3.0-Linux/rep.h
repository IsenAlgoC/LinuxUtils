#pragma once
#include <stdbool.h>
#include "liste.h"


// #define VERSION 3.0
// #define SQUELET


#define IMPL_TAB  // si d�fini, on compile pour une impl�mentation tableau du r�pertoire
//#define IMPL_LIST // si d�fini, on compile pour un impl�mentation Liste Cha�n�e du r�pertoire

#ifdef IMPL_LIST
#undef IMPL_TAB
#endif

#define MAX_ENREG 1000  /* nbre max d'enregistrements */
#define MAX_SAISIE 1024 /* longueur max pour la saisie d'une cha�ne
/* ATTENTION, il faut que MAX_SAISIE > MAX_NOM et
MAX_SAISIE > MAX_TEL */

#define OK    1
#define ERROR 0

#define SEPARATEUR ';'
#define LIGNES_PAR_PAGE 5
#define MAX_NOM_FICHIER 80


/**********************************************************************/
/*** D�clarations des types                                         ***/
/***                                                                ***/
/**********************************************************************/



/* Repertoire : structure qui contient :                         */
/* le nombre de contacts                                         */
/* le tableau de contacts,                                       */
/* est_trie : qui vaut VRAI si le tableau est tri� et FAUX sinon */
typedef struct rept
{
	int nb_elts;
#ifdef IMPL_TAB
	Enregistrement *tab;
#else
#ifdef IMPL_LIST
	LinkedList *liste;
#endif
#endif
	bool est_trie;
} Repertoire;

// initialise le r�pertoire pass� en param�tre et fait appel � charger() pour charger le fichier de contacts
int init_rep(Repertoire *rep);

// lit les lignes dans le fichier de contacts et les analyse avec la fonction lire_champ_suivant()
int charger(Repertoire *rep, char nom_fichier[]);

// Affiche le menu utilisateur principal
void afficher_menu_principal();

void option_ajouter(Repertoire *rep); // Traitement de l'option ajout d'un contact depuis le menu principal

// Ajout d'un contact dans le r�pertoire stock� en m�moire
int ajouter_un_contact_dans_rep(Repertoire *rep, Enregistrement enr); 

// Suppression d'un contact, utilis� notamment par traiter_recherche() afin de supprimer un contact recherch� et trouv�
void supprimer_un_contact_dans_rep(Repertoire *rep, int indice); 


// Suppression d'un contact pour impl�mentation avec une liste cha�n�e
int supprimer_un_contact_dans_rep_liste(Repertoire *rep, SingleLinkedListElem *elem);

void trier(Repertoire *rep); // tri du r�pertoire en m�moire

int saisie_chaine(unsigned char c[], int max);  // entree d'une chaine de caract�res quelconque au clavier, un nom par exemple
int saisie_enreg(Enregistrement *enr); // fait appel � saisie_chaine pour l'entree d'un nouveau contact
void affichage_enreg(Enregistrement enr); // affiche un seul enregistrement sur une ligne
void affichage_enreg_frmt(Enregistrement enr); // affiche un seul enregistrement avec des largeurs de colonnes fixes
void affichage_repertoire(Repertoire *rep); // affichage de tout le r�pertoire en paginant les lignes � la fa�on de la commande 'MORE'
bool est_sup(Enregistrement enr1, Enregistrement enr2); // test si un contact se trouve apr�s dans l'ordre alphab�tique par rapport � un autre contact
void trier(Repertoire *rep);  // tri des contacts du r�pertoire en m�moire

void compact(char *s); // suppression de tous les carat�res non num�riques dans une chaine (0..9) afin de faciliter la recherche par no de tel par ex.
int lire_champ_suivant(char *ligne, int *idx, char *champ, int taille_champ, char separateur); // analyse d'une ligne lue dans le fichier et stock�e dans le buffer 'ligne' 

void option_rechercher(Repertoire *rep); //traitement de l'option de recherche du menu principal
void afficher_menu_recherche();  //affiche un menu afin de proposer une recherche par nom ou par no tel ou, d'abandonner la recherche
int rechercher_nom(Repertoire *rep, char nom[], int ind); // recherche l'existance d'un contact et renvoie l'indice de sa position si trouv� ou -1 sinon
int rechercher_tel(Repertoire *rep, char tel[], int ind); // recherche l'existance d'un contact par no tel et renvoie l'indice de sa position si trouv� ou -1 sinon
bool traiter_recherche(Repertoire *rep, int pos); // menu qui propose de supprimer le contact trouv�, de poursuivre la recherche ou de s'arreter 

int saisir_chemin(char *message, char *buffer); // demande de saisie au clavier d'un chemin pour un fichier de sauvegarde, fait appel � saisie_chaine()
int sauvegarder(Repertoire *rep, char nom_fichier[]); // sauvegarde tout le r�pertoire en m�moire vers un fichier en rempla�ant l'ancien fichier



