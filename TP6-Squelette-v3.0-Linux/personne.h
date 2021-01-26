#pragma once
#define MAX_NOM 30     /* longueur maximale d'un nom */
#define MAX_TEL 20      /* longueur maximale d'un numéro de tél. */

/* Enregistrement : structure d'un contact dans le tableau de contacts */
/* le type enregistrement contient 3 champs :                          */
/*  - nom, prenom et tel qui sont tous les trois des chaînes de        */
/*  caractères (tableaux de char)                                      */
typedef struct enreg
{
	unsigned char nom[MAX_NOM];
	unsigned char prenom[MAX_NOM];
	unsigned char tel[MAX_TEL];
} Enregistrement;

