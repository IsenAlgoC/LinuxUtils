/**********************************************************************/
/*****                    R�pertoire t�l�phonique                   ***/
/**********************************************************************/
/*                                                                    */
/*       rep.c                                                        */
/*       VERSION 3.0                                                  */
/*                                                                    */
/*       SQUELET                                                   */
/*                                                                    */
/**********************************************************************/
/* REMARQUE: le fichier de donn�es est au format suivant :            */
/*      nom;prenom;no_de_telephone1                                   */
/*      nom2;prenom2;no_de_telephone2                                 */
/*      ...                                                           */
/* soit un enregistrement par ligne de 3 champs separ�s par ';'        */
/* Si on utilise un autre fichier de donnees que rep.txt, il faut     */
/* passer son nom en param�tre � l'appel du programme                 */
/**********************************************************************/

#include <stdio.h>   /* pour les entr�es-sorties */
#include <string.h>  /* pour les manipulations de cha�nes de caract�res */
#include "conio.h"
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <fcntl.h>
#include "rep.h"


/* flag de modification du r�pertoire : indique si le tableau de contacts �t� modifi�         */
/* Permet notamment de d�cider s'il faut sauvegarder le r�pertoire dans un fichier             */
bool modif = false;

/* fichier texte de sauvegarde des contacts */
char nom_fichier[MAX_NOM_FICHIER];

/* divers messages � l'intention de l'utilisateur  */

/* \x82 permet de forcer l'encodage du caract�re '�' � la valeur hexa 0x82 quand c'est n�cessaire */
/* et non � celle utilis�e pour l'encodage du fichier source  .c par visual studio */
/* c'est la valeur utilis�e par le  Western European (DOS) - Codepage 850 utilis� dans la console DOS */

char mess1[] = "\nn'existe pas dans le répertoire.\n";
char mess2[] = "\nPlus d'autre %s dans le répertoire\n";


/*****************************************************************************/
/*                        programme principal : main                         */
/*****************************************************************************/

void main(int argc, char *argv[])
{

	char choix;						/* caract�re de l'option choisie dans menu utilisateur */

	Repertoire repertoire;			/* variable qui d�clare et cr�e le r�pertoire en m�moire */

	if (argc == 1)
	{
		strcpy(nom_fichier, "rep.txt");	/* nom du fichier par defaut */
	}
	else
	{
		strcpy(nom_fichier, (char *)argv[1]);	/* nom du fichier utilisateur */
	}
	/* intialise le nombre d'�l�ments � z�ro, alloue la m�moire du r�pertoire, 
	charge le fichier et le trie */
	if (init_rep(&repertoire) <0) return;

	afficher_menu_principal();

	do								/* lecture menu principal */
	{							/* tant que pas demande pour Quitter */
		do
		{						/* lecture touche frappee au clavier */
			choix = (char)toupper(getch());
		} while ((choix != 'A') && (choix != 'X') && (choix != 'J') && (choix != 'R'));

		switch (choix)
		{
		case 'A':
			affichage_repertoire(&repertoire);
			break;
		case 'J':
			option_ajouter(&repertoire);
			break;
		case 'R':
			option_rechercher(&repertoire);
			break;
		}
		afficher_menu_principal();
	} while (choix != 'X');

	if (modif)					/* Si modification apportee au repertoire */
	{						/* on propose une sauvegarde */
		printf("\n Enregistrer modification ? O/N");
		do
		{
			choix = (char)toupper(getch());
		} while ((choix != 'O') && (choix != 'N'));

		if (choix == 'O')
		{
			printf("\n Enregistrer sous %s ? O/N", nom_fichier);
			do
			{
				choix = (char)toupper(getch());
			} while ((choix != 'O') && (choix != 'N'));

			if (choix == 'N') saisir_chemin("Nom du fichier: ?", nom_fichier);
			sauvegarder(&repertoire, nom_fichier);
		}
	}
	printf("\nBye !\n\n");


	return;
}
/*****************************FIN du programme principal*********************/


/********************************************************************************/
/* initialisation d'un r�pertoire                                               */
/* prend en param�tre un pointeur vers le r�pertoire � initialiser              */
/* intialise le nombre d'�l�ments � z�ro, charge le fichier et le trie          */
/********************************************************************************/

int init_rep(Repertoire *rep)
{
	/* fonction compl�te : ne pas modifier  */
	int errno;
	void * tmpPtr;
	rep->nb_elts = 0;
	rep->est_trie = true; /* un r�pertoire vide est tri� :-) */
#ifdef IMPL_TAB
						  // code pour tableau

	tmpPtr = (void *)malloc(MAX_ENREG * sizeof(Enregistrement));
	if (tmpPtr != NULL) {
		rep->tab = (Enregistrement *)tmpPtr;
	}
	else return(-1);
#else
#ifdef IMPL_LIST
						  // code pour Liste
	tmpPtr = (LinkedList*)NewLinkedList();
	if (tmpPtr != NULL) {
		rep->liste = (LinkedList*)tmpPtr;
	}
	else return(-1);
#endif
#endif
	errno = charger(rep, nom_fichier);

	if ((errno == OK) && (rep->nb_elts > 0))
	{
		rep->est_trie = false;
		trier(rep);
	}
	return(0);
} /* fin init_rep */

  /**************************************************************************/
  /*  Lecture d'une cha�ne de caract�res depuis le clavier.                 */
  /*  Elle est stock�e dans le tableau de char pass� en param�tre           */
  /*   La longueur max � lire est donn�e en second param�tre                */
  /*   Elle renvoie la longueur de la chaine et une longueur n�gative s'il  */
  /*   y a eu un probl�me                                                   */
  /**************************************************************************/
int saisie_chaine(unsigned char c[], int max)
{
	/* fonction compl�te : ne pas modifier */

	/* longueur de la cha�ne c */
	int l;

	/* saisie en rangeant dans tableau c */
	if (fgets(c, max, stdin) == NULL)          /* lecture des caract�res sur entr�e standard= clavier */
		return -1;	
						   /* s'il y a une erreur, on renvoie -1                  */
	
	l = strlen(c);							   /* calcul de la longueur de la chaine */

	if (c[l - 1] == '\n')					   /* suppression du retour chariot            */
	{									       /* en fin de cha�ne s'il est pr�sent        */
		c[l - 1] = '\0';                       /* �criture d'un caract�re de fin de chaine */
		l--;                                   /* � la place                               */
	}
	return l;								   /* on retourne la longueur de */
} /* fin saisie_chaine */

  /**************************************************************************/
  /* entr�e au clavier d'un enregistrement (contact)                        */
  /* l'�l�ment saisi est stock� dans l'enregistrement point� par le         */
  /* parametre enr                                                          */
  /* la fonction renvoie OK si l'�l�ment est correctement saisie et         */
  /* ERROR s'il y a eu un probl�me...                                       */
  /**************************************************************************/
int saisie_enreg(Enregistrement *enr)
{
	unsigned char tmp[MAX_SAISIE];
	int l;

	printf("Nom :");
	if ((l = saisie_chaine(tmp, MAX_SAISIE)) < 0)
		return ERROR;
	/* chaine vide ? */
	if (l == 0)
	{
		printf("nom vide...\n");
		return ERROR;
	}
	/* chaine trop longue ? */
	if (l >= MAX_NOM)
	{
		printf("nom tronqu�...\n");

	}
	/* on copie dans le champ nom... */
	strncpy(enr->nom, tmp, MAX_NOM);

	/* Entr�e clavier du pr�nom */
	printf("Prénom :");
	if ((l = saisie_chaine(tmp, MAX_SAISIE)) < 0)
		return ERROR;
	/* chaine vide ? */
	if (l == 0)
	{
		printf("prénom vide...\n");

	}
	/* chaine trop longue ? */
	if (l >= MAX_NOM)
	{
		printf("prénom trop long...\n");

	}
	/* on copie dans le champ prenom... */
	strncpy(enr->prenom, tmp, MAX_NOM);

	/* Entr�e clavier du num�ro de t�l�phone */
	printf("Téléphone :");
	if ((l = saisie_chaine(tmp, MAX_SAISIE)) < 0)
		return ERROR;
	/* chaine vide ? */
	if (l == 0)
	{
		printf("téléphone vide...\n");

	}
	/* chaine trop longue ? */
	if (l >= MAX_TEL)
	{
		printf("téléphone tronqu�...\n");

	}
	/* on copie dans le champ tel... */
	strncpy(enr->tel, tmp, MAX_TEL);

	return OK;
} /* fin saisie_enreg */


  /********************************************************************************/
  /*  Affichage pagin� du r�pertoire par fa�on commande DOS 'more'                */
  /********************************************************************************/
void affichage_repertoire(Repertoire *rep)
{
	int idx = 0;							/* Index sur enregistrement courant */
	int cpt = LIGNES_PAR_PAGE;				/* Compteur de ligne affich�es */
	char key = 0;							/* Controle de l'affichage */

	trier(rep);								/* trie du r�pertoire avant affichage */
#ifdef IMPL_LIST
	// on place un pointeur sur la t�te de liste,
	// elle est peut-�tre vide
	SingleLinkedListElem *currentElement = rep->liste->head;
#endif
	// tant qu'il y a un �l�ment
	while ((idx < rep->nb_elts) && (key != 'X'))
	{
		if (cpt > 0)						/* S'il reste des lignes � afficher */
		{								/* dans la page */
#ifdef IMPL_TAB
			affichage_enreg_frmt(rep->tab[idx]);	/* Affichage enrg courant */

#else
#ifdef IMPL_LIST
			affichage_enreg_frmt(currentElement->pers);	/* Affichage enrg courant */
			currentElement = currentElement->next; /* on passe au suivant */
#endif
#endif

			idx++;							/* On passe au suivant */
			cpt--;							/* Une ligne de moins a afficher */
		}
		else
		{	/* si page compl�tement affich�e, on attend la suite */
			printf("\n\n_____________________________ entr�e/espace/x ___ :\n");

			do
			{
				key = (char)toupper(getch());
				cpt = (key == 13) ? 1 : LIGNES_PAR_PAGE;
			} while ((key != ' ') && (key != 13) && (key != 'X'));
		}

	}
} /* fin affichage_repertoire */



  /**********************************************************************/
  /* Recherche par no de t�l�phone avec compactage du no                */
  /**********************************************************************/
int rechercher_tel(Repertoire *rep, char tel[], int ind)
{
	int i = ind; // indice de d�but de recherche
	int ind_fin;

	char tmp_tel[MAX_TEL];
	char tmp_tel2[MAX_TEL];
	bool trouve = false;

	ind_fin = rep->nb_elts - 1; // indice de fin � ne pas d�passer
	strncpy(tmp_tel, tel, MAX_TEL);
	compact(tmp_tel); // nettoyage du num�ro

#ifdef IMPL_LIST
					  // on se place sur l'�l�ment en i�me position s'il existe
	SingleLinkedListElem *currentElement = GetElementAt(rep->liste, i);
	while ((currentElement != NULL) && (!trouve)) {
		strncpy(tmp_tel2, _countof(tmp_tel2) , currentElement->pers.tel,_TRUNCATE);
		compact(tmp_tel2);
		if (strcmp(tmp_tel, tmp_tel2) == 0)
			trouve = true;
		else {
			// si pas trouv�, on passe au suivant
			currentElement = currentElement->next;
			i++;
		}
	}
#else
#ifdef IMPL_TAB
	while ((i <= ind_fin) && (!trouve))
	{
		strncpy(tmp_tel2, rep->tab[i].tel, MAX_TEL);

		compact(tmp_tel2);
		if (strcmp(tmp_tel, tmp_tel2) == 0)
			trouve = true;
		else
			i++;
	}
#endif // IMPL_TAB
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_tel */


  /***********************************************************************************************************/
  /*                                                                                                         */
  /*  Lecture de champs contenus dans les lignes du fichier                                                  */
  /*  - ligne: pointeur sur un buffer qui contient la ligne lue dans le fichier et termin�e par un z�ro     */
  /*  - idx: pointeur sur un entier qui indique la position courante de la recherche dans la ligne           */
  /*  - champ: pointeur sur la variable � renseigner avec les informations trouv�es entre deux s�parateurs   */
  /*  - taille_champ : la taille du champ � ne pas d�passer                                                  */
  /*  - separateur : le caract�re utilis� comme s�parateur                                                   */
  /***********************************************************************************************************/

int lire_champ_suivant(char *ligne, int *idx, char *champ, int taille_champ,
	char separateur)
{

	int idx2 = 0;

	while ((idx2 < (taille_champ - 2)) && (ligne[*idx] != separateur)
		&& (ligne[*idx] != '\0'))
	{
		champ[idx2] = ligne[*idx];
		idx2 += 1;
		*idx += 1;
	}
	if ((ligne[*idx] == separateur) || (ligne[*idx] == '\0'))
	{
		champ[idx2] = 0;	/* fin de chaine sur caractere suivant */
		return(OK);
	}
	else return(ERROR);		/* fin de ligne ou s�parateur non atteints */

} /* fin lire_champuivant() */


  /**********************************************************************/
  /*    Affichage du sous menu rechercher                               */
  /**********************************************************************/

void afficher_menu_recherche()
{
	printf("\n\n Recherche :\n\n");
	printf("\n\t par (N)om");
	printf("\n\t par (T)éléphone");
	printf("\n\t\te(X)it\n");
	return;
}
/**********************************************************************/
/*                                                                    */
/* traiter_rechercher proposer de supprimer l element trouve          */
/* et demande s'il faut poursuivre ou  non la recherche               */
/**********************************************************************/

bool traiter_recherche(Repertoire *rep, int pos)
{
	char key = 0;
#ifdef IMPL_LIST
	// on r�cup�re l'�l�ment en i�me position
	SingleLinkedListElem *currentElement = GetElementAt(rep->liste, pos);
	if (currentElement != NULL)
		affichage_enreg(currentElement->pers);
#else
#ifdef IMPL_TAB
	affichage_enreg(rep->tab[pos]);
#endif
#endif
	printf("\n\n_____________________________ /espace/(D)elete/e(X)it ___ :\n");
	do
	{
		key = (char)toupper(getch());
	} while ((key != ' ') && (key != 'D') && (key != 'X'));

	switch (key)
	{
	case ' ':
		return(true);
		break;
	case 'X':
		return(false);
		break;
	case 'D':
#ifdef IMPL_TAB
		supprimer_un_contact_dans_rep(rep, pos);
#else
#ifdef IMPL_LIST
		supprimer_un_contact_dans_rep_liste(rep, currentElement);
#endif
#endif
		break;
	}
	return(false);

}
/**********************************************************************/
/*  Traite l'option rechercher du menu principal                      */
/**********************************************************************/


void option_rechercher(Repertoire *rep)
{
	char choix;

	int ind;			/* Indice de debut de la recherche ds tableau */
	int pos;			/* Position ds le tableau ou l'element a ete trouve */
	char nom[MAX_NOM];	/* Les chaines recherchees */
	char tel[MAX_TEL];
	bool suite = false;			/* true si recherche du suivant, false si on arrete*/

	if (rep->nb_elts <= 0)
	{
		printf("\nRépertoire vide ...\n");
		return;
	}
	afficher_menu_recherche();
	do
	{

		ind = 0;						/* la recherche reprend depuis le debut du tableau */
		suite = false;				/**/
		do
		{						/* lecture touche frappee au clavier */
			choix = (char)toupper(getch());
		} while ((choix != 'N') && (choix != 'T') && (choix != 'X'));

		switch (choix)
		{
		case 'N':
			printf("\nNom ? :");
			saisie_chaine(nom, MAX_NOM);


			do
			{
				pos = rechercher_nom(rep, nom, ind);

				if (pos >= 0)
				{
					ind = pos + 1;
					suite = traiter_recherche(rep, pos);
				}
				else
				{
					if (suite == true) printf(mess2, nom);	/* Plus de nouvelle occurence */
					else printf(mess1);						/* Pas d'occurence trouvee la premiere fois*/
					suite = false;								/* On arrete la recherche */
				}

			} while (suite);
			break;
		case 'T':
			printf("\nTel ? :");
			saisie_chaine(tel, MAX_TEL);

			do
			{
				pos = rechercher_tel(rep, tel, ind);

				if (pos >= 0)
				{
					ind = pos + 1;
					suite = traiter_recherche(rep, pos);
				}
				else
				{
					if (suite == true) printf(mess2, tel);	/* Plus de nouvelle occurence */
					else printf(mess1);						/* Pas d'occurence trouvee la premiere fois*/
					suite = false;								/* On arrete la recherche */
				}
			} while (suite);
			break;
		}
		afficher_menu_recherche();
	} while (choix != 'X');

	return;
}

/**********************************************************************/
/* ajoute  un contact au r�pertoire                                   */
/**********************************************************************/

void option_ajouter(Repertoire *rep)
{
	Enregistrement tmpenr;
	if (saisie_enreg(&tmpenr))
		if (!ajouter_un_contact_dans_rep(rep, tmpenr))
			printf("\nAjout impossible !! \n");

	return;
}
/**********************************************************************/
/*  Demande de saisie d'un chemin de fichier						  */
/**********************************************************************/

int saisir_chemin(char *message, char *buffer)
{
	printf("\n%s\n", message);
	saisie_chaine(buffer, MAX_NOM_FICHIER);
	printf("\n");
	return(OK);
}



/**********************************************************************/
/* Affichage du menu principal                                        */
/**********************************************************************/

void afficher_menu_principal()
{
	printf("\n\n Répertoire :");
	printf("\n\n\t(A)fficher tout");
	printf("\n\ta(J)outer une personne");
	printf("\n\trecherche(R) une personne");
	printf("\n\n\t\te(X)it\n");
}

/**********************************************************************/


