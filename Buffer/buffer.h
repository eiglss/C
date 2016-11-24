/******************************************************************************/
/*        @TITRE : buffer.h                                                   */
/*      @VERSION : 0                                                          */
/*     @CREATION : may 28, 2016                                               */
/* @MODIFICATION :                                                            */
/*      @AUTEURS : Enzo IGLESIS                                               */
/*    @COPYRIGHT : Copyright (c) 2016 Enzo IGLESIS                            */
/*      @LICENSE : MIT License (MIT)                                          */
/******************************************************************************/
#ifndef BUFFER_H_
#define BUFFER_H_

/*******************************     MACROS     *******************************/
#ifndef FALSE
    #define FALSE   (0)
#endif
#ifndef TRUE
    #define TRUE    (!FALSE)
#endif

/**** TYPE ****/
#define FIFO    ('F')
#define LIFO    ('L')
#define STACK   (LIFO)


/*******************************     TYPES      *******************************/
typedef struct
{
    void ** data;
    unsigned int size;
    unsigned int w_index;
    unsigned int r_index;
    unsigned int nb_element;
    unsigned char type; /* FIFO, LIFO, STACk */
} t_buffer;

typedef t_buffer t_fifo;

typedef t_buffer t_lifo;

/*******************************   CONSTANTES   *******************************/

/*******************************    VARIABLES   *******************************/

/*******************************   FUNCTIONS    *******************************/
/* Initialisation */
char init_fifo(t_fifo * fifo, unsigned int size);
char init_lifo(t_lifo * lifo, unsigned int size);
/* resize */
char resize_fifo(t_fifo * fifo, unsigned int new_size);
char resize_lifo(t_lifo * lifo, unsigned int size);
/* write */
char write_buffer(t_buffer * buffer, void * data, unsigned char priority); /* Slowest*/
char write_fifo(t_fifo * fifo, void * data, unsigned char priority);
char write_lifo(t_lifo * lifo, void * data);
/* Read */
char read_buffer(t_buffer * buffer, void ** data); /* Slowest */
char read_fifo(t_fifo * fifo, void ** data);
char read_lifo(t_lifo * lifo, void ** data);
/* Peek */
char peek_buffer(t_buffer * buffer, void * data, int elem); /* Fastest */
char peek_fifo(t_fifo * fifo, void * data, int elem);
char peek_lifo(t_fifo * lifo, void * data, int elem);
/* free */
void free_buffer(t_buffer * buffer); /* Fastest */
void free_fifo(t_fifo * fifo);
void free_lifo(t_lifo * lifo);
/* Usefull function */
unsigned int elem2pos(t_fifo * fifo, int elem);
void buffer_exchange(t_buffer * buffer, int elem_x, int elem_y); /* Fastest */
void fifo_exchange(t_fifo * fifo, int elem_x, int elem_y);
void lifo_exchange(t_lifo * lifo, int elem_x, int elem_y);
char fifo_shift(t_fifo * fifo, int shift);

#endif
