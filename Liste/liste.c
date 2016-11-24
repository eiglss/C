/******************************************************************************/
/*        @TITRE : liste.c                                                    */
/*      @VERSION : 0                                                           */
/*     @CREATION : october 21, 2015                                           */
/* @MODIFICATION : may 28, 2016                                               */
/*      @AUTEURS : Enzo IGLESIS                                               */
/*    @COPYRIGHT : Copyright (c) 2016 Enzo IGLESIS                            */
/*      @LICENSE : MIT License (MIT)                                          */
/******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

/*******************************     MACROS     *******************************/

/*******************************     TYPES      *******************************/

/*******************************   CONSTANTES   *******************************/

/*******************************    VARIABLES   *******************************/

/*******************************   FUNCTIONS    *******************************/

/* init_liste: initialise une liste avec tous les pointeurs egale a NULL */
void init_liste(t_list * liste)
{
    liste->head = NULL;
    liste->tail = NULL;
    liste->current = NULL;
}

/* liste_vide: retourne vrai si la liste est vide */
unsigned char liste_vide(t_list * liste)
{
    return (liste->head == NULL);
}

/* fin: retourne vrai si le pointeur courant pointe sur la derniere cellule de
la liste */
unsigned char fin(t_list * liste)
{
    return (liste->current == liste->tail);
}

/* debut: retourne vrai si le pointeur courrent pointe sur la premiere cellule
de la liste */
unsigned char debut(t_list * liste)
{
    return (liste->current == liste->head);
}

/* aller_debut: remet le pointeur courrent au debut de la liste */
void aller_debut(t_list * liste)
{
    liste->current = liste->head;
}

/* avancer: place le pointeur courrent sur la cellule suivante et retourne TRUE
si l'action r�ussi ou FALSE si il n'y a pas d'element suivant */
unsigned char avancer(t_list * liste)
{
    if(!fin(liste))
    {
        liste->current = liste->current->next;
        return TRUE;
    }
    return FALSE;
}

/* echange_object_cell: echange le contenu object de deux cellule 'a' et 'b' */
void echange_object_cell(t_cell * a, t_cell * b)
{
    /*declaration locale*/
    t_cell buffer;
    /*action*/
    buffer.object = a->object;
    a->object = b->object;
    b->object = buffer.object;
}

/* objet_courant: retourne un pointeur sur object pointe par le pointeur current
*/
void * objet_courant(t_list * liste)
{
    return liste->current->object;
}

/* allouer_cell: alloue un espace memoire de taille t_cell et retourne un
pointeur sur cet espace memoire */
t_cell * allouer_cell(void)
{
    return (t_cell *)malloc(sizeof(t_cell));
}

/* cell_precedent: retourne un pointeur sur la cellule precedent celle pointe
par le current */
t_cell * cell_precedent(t_list * liste)
{
    /*declaration locale*/
    t_cell * cell_prec;
    t_cell * cell_actu;
    /*action*/
    cell_prec = liste->head;
    cell_actu = liste->head->next;
    while(cell_actu != NULL && cell_actu != liste->current)
    {
        cell_prec = cell_actu;
        cell_actu = cell_actu->next;
    }
    return cell_prec;
}

/* ajouter_cell: ajoute une cell 'object' a la fin de la liste chainee return
FALSE si il y a eu un echech d'allocation de la memoire, ou TRUE si la cellul a
ou etre ajoutee */
char ajouter_cell(t_list * liste, void * object)
{
    /*declaration locale*/
    t_cell * cell;
    /*action*/
    if(liste->tail == NULL || liste->tail->next == NULL)
    {
        if((cell = allouer_cell()) != NULL)
        {
            if(liste->tail == NULL)
            {
                liste->tail = cell;
                liste->head = cell;
                liste->current = cell;
            }
            else
            {
                liste->tail = liste->tail->next = cell;
            }
            liste->tail->object = object;
            liste->tail->next = NULL;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        liste->tail = liste->tail->next;
        ajouter_cell(liste, object);
    }
    return TRUE;
}

/* effacer_cell: libere l'espace memoire allouer pour la cellule pointe par
curent et la cellule precedent pointe maintenant sur la suivante, retourne TRUE
si l'action reussi false si la liste est vide */
unsigned char effacer_cell(t_list * liste)
{
    /*declaration locale*/
    t_cell * p;
    /*action*/
    if(!liste_vide(liste))
    {
        if(debut(liste))
        {
            if(fin(liste))
            {
                liste->tail = NULL;
            }
            liste->head = liste->head->next;
            free(liste->current);
            liste->current = liste->head;
        }
        else
        {
            p = cell_precedent(liste);
            p->next = liste->current->next;
            free(liste->current);
            liste->current = p;
        }
        if(!liste_vide(liste) && liste->current->next == NULL)
        {
            liste->tail = liste->current;
        }
        return TRUE;
    }
    return FALSE;
}

/* effacer_liste: libere tout l'espace memoire alloue pour toutes les cellules
de la liste retourne TRUE si l'action reussi, FALSE si la liste est vide */
unsigned char effacer_liste(t_list * liste)
{
    /*declaraion locale*/
    t_cell * p;
    t_cell * q;
    /*action*/
    if(!liste_vide(liste))
    {
        for(p = liste->head; p != NULL; p = q)
        {
            q = p->next;
            free(p);
        }
        init_liste(liste);
        return TRUE;
    }
    return FALSE;
}
