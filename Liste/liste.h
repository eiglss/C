/******************************************************************************/
/*        @TITRE : liste.h                                                    */
/*      @VERSION : 0                                                          */
/*     @CREATION : october 21, 2015                                           */
/* @MODIFICATION : may 28, 2016                                               */
/*      @AUTEURS : Enzo IGLESIS                                               */
/*    @COPYRIGHT : Copyright (c) 2016 Enzo IGLESIS                            */
/*      @LICENSE : MIT License (MIT)                                          */
/******************************************************************************/
#ifndef LISTE_H
#define LISTE_H
/* liste.h gere de maniere generique les liste chainee, c'esst a dire quel que
soit le type object de la structure cell */

/*******************************     MACROS     *******************************/
#ifndef FALSE
    #define FALSE	(0)
#endif
#ifndef TRUE
    #define TRUE    (!FALSE)
#endif

/*******************************     TYPES      *******************************/
typedef struct cell
{
    void * object;
    struct cell * next;
}
t_cell;

typedef struct list
{
    t_cell * head;
    t_cell * tail;
    t_cell * current;
}
t_list;

/*******************************   CONSTANTES   *******************************/

/*******************************    VARIABLES   *******************************/

/*******************************   FUNCTIONS    *******************************/
void init_liste(t_list * liste);
unsigned char liste_vide(t_list * liste);
unsigned char fin(t_list * liste);
unsigned char debut(t_list * liste);
void aller_debut(t_list * liste);
unsigned char avancer(t_list * liste);
void echange_object_cell(t_cell * a, t_cell * b);
void * objet_courant(t_list * liste);
t_cell * allouer_cell(void);
t_cell * cell_precedent(t_list * liste);
char ajouter_cell(t_list * liste, void * object);
unsigned char effacer_cell(t_list * liste);
unsigned char effacer_liste(t_list * liste);

#endif
