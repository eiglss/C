/******************************************************************************/
/*        @TITRE : buffer.c                                                   */
/*      @VERSION : 0                                                          */
/*     @CREATION : may 28, 2016                                               */
/* @MODIFICATION :                                                            */
/*      @AUTEURS : Enzo IGLESIS                                               */
/*    @COPYRIGHT : Copyright (c) 2016 Enzo IGLESIS                            */
/*      @LICENSE : MIT License (MIT)                                          */
/******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
/*******************************     MACROS     *******************************/

/*******************************     TYPES      *******************************/

/*******************************   CONSTANTES   *******************************/

/*******************************    VARIABLES   *******************************/

/*******************************   FUNCTIONS    *******************************/
/* Usefull function */
unsigned int elem2pos(t_fifo * fifo, int elem)
{
    elem = elem%((int)(fifo->size));
    if(((int)(fifo->r_index)+elem) > (int)(fifo->size))
    {
        elem = fifo->r_index+elem-fifo->size;
    }
    else if(((int)(fifo->r_index)+elem) < 0)
    {
         elem = fifo->r_index+elem+fifo->size;
    }
    else
    {
        elem = fifo->r_index+elem;
    }
    return elem;
}

void buffer_exchange(t_buffer * buffer, int elem_x, int elem_y)
{
    /* local declaration */
    void ** temp;
    /* action */
    if(buffer->type == FIFO)
    {
        elem_x = (int)elem2pos((t_fifo *)buffer, elem_x);
        elem_y = (int)elem2pos((t_fifo *)buffer, elem_y);
    }
    temp = buffer->data[elem_x];
    buffer->data[elem_x] = buffer->data[elem_y];
    buffer->data[elem_y] = temp;
}

void fifo_exchange(t_fifo * fifo, int elem_x, int elem_y)
{
    buffer_exchange((t_buffer *)fifo, elem_x, elem_y);
}

void lifo_exchange(t_lifo * lifo, int elem_x, int elem_y)
{
    buffer_exchange((t_buffer *)lifo, elem_x, elem_y);
}

char fifo_shift(t_fifo * fifo, int shift)
{
    /* local declaration */
    unsigned int i;
    /* action */
    if(fifo->size-fifo->nb_element < abs(shift))
    {
        return FALSE;
    }
    for(i = 0; i < fifo->nb_element; i++)
    {
        fifo_exchange(fifo, i, shift+i);
    }
    fifo->r_index = elem2pos(fifo, shift);
    fifo->w_index = elem2pos(fifo, fifo->nb_element);
    return TRUE;
}

/* Initialisation */
static char init_buffer(t_buffer * buffer, unsigned int size)
{
    if((buffer->data = malloc(size*sizeof(buffer->data))) == NULL)
    {
        return FALSE;
    }
    buffer->size = size;
    buffer->w_index = 0;
    buffer->r_index = 0;
    buffer->nb_element = 0;
    while(size--)
    {
        buffer->data[size] = NULL;
    }
    return TRUE;
}

char init_fifo(t_fifo * fifo, unsigned int size)
{
    if(!init_buffer((t_buffer*) fifo, size))
    {
        return FALSE;
    }
    fifo->type = FIFO;
    return TRUE;
}

char init_lifo(t_lifo * lifo, unsigned int size)
{
    if(!init_buffer((t_buffer*) lifo, size))
    {
        return FALSE;
    }
    lifo->type = LIFO;
    return TRUE;
}

/* resize */
static char resize_buffer(t_buffer * buffer, unsigned int new_size)
{
    /* local declaration */
    void ** p;
    /* programme statement */
    if((p = realloc(buffer->data, new_size*sizeof(buffer->data))) == NULL)
    {
        return FALSE;
    }
    else
    {
        if(buffer->type == FIFO)
        {
            fifo_shift((t_fifo *)buffer, -buffer->r_index);
        }
        buffer->data = p;
        buffer->size = new_size;
        if(buffer->nb_element > new_size)
        {
            buffer->nb_element = new_size;
        }
    }
    return TRUE;
}

char resize_fifo(t_fifo * fifo, unsigned int new_size)
{
    if(resize_buffer((t_buffer *)fifo, new_size))
    {
        return FALSE;
    }
    fifo->type = FIFO;
    return TRUE;
}

char resize_lifo(t_lifo * lifo, unsigned int size)
{
    if(init_buffer((t_buffer*) lifo, size))
    {
        return FALSE;
    }
    lifo->type = LIFO;
    return TRUE;
}

/* write */
char write_fifo(t_fifo * fifo, void * data, unsigned char priority)
{
    if((fifo->nb_element) >= (fifo->size))
    {
        return FALSE;
    }
    fifo->data[fifo->w_index] = data;
    fifo->nb_element++;
    if(priority)
    {
        fifo->r_index = elem2pos(fifo, -1);
        fifo_exchange(fifo, fifo->nb_element, 0);
    }
    else
    {
        fifo->w_index++;
        if((fifo->w_index) >= (fifo->size))
        {
            fifo->w_index = 0;
        }
    }
    return TRUE;
}

char write_lifo(t_lifo * lifo, void * data)
{
    if((lifo->nb_element) >= (lifo->size))
    {
        return FALSE;
    }
    lifo->data[lifo->w_index] = data;
    lifo->nb_element++;
    lifo->r_index = lifo->w_index;
    if((lifo->w_index) < (lifo->size))
    {
        lifo->w_index++;
    }
    return TRUE;
}

char write_buffer(t_buffer * buffer, void * data, unsigned char priority)
{
    switch(buffer->type)
    {
        case FIFO:
            return write_fifo((t_fifo *)buffer, data, priority);
        break;
        case LIFO:
            return write_lifo((t_lifo *)buffer, data);
        break;
        default:
            ;
    }
    return FALSE;
}

/* Read */
char read_fifo(t_fifo * fifo, void ** data)
{
    if(fifo->nb_element == 0)
    {
        return FALSE;
    }
    *data = fifo->data[fifo->r_index];
    fifo->r_index++;
    if((fifo->r_index) >= (fifo->size))
    {
        fifo->r_index = 0;
    }
    fifo->nb_element--;
    return TRUE;
}

char read_lifo(t_lifo * lifo, void ** data)
{
    if(lifo->nb_element == 0)
    {
        return FALSE;
    }
    *data = lifo->data[lifo->r_index];
    lifo->w_index = lifo->r_index;
    if((lifo->r_index) > 0)
    {
        lifo->r_index--;
    }
    lifo->nb_element--;
    return TRUE;
}

char read_buffer(t_buffer * buffer, void ** data)
{
    switch(buffer->type)
    {
        case FIFO:
            return read_fifo((t_fifo *)buffer, data);
        break;
        case LIFO:
            return read_lifo((t_lifo *)buffer, data);
        break;
        default:
            ;
    }
    return FALSE;
}

/* Peek */
char peek_buffer(t_buffer * buffer, void * data, int elem)
{
    if((buffer->nb_element) == 0)
    {
        return FALSE;
    }
    if(buffer->type == FIFO)
    {
        elem = elem2pos((t_fifo *)buffer, elem);
    }
    else
    {
        elem = abs(elem);
    }
    data = buffer->data[buffer->r_index+elem];
    return TRUE;
}

char peek_fifo(t_fifo * fifo, void * data, int elem)
{
    return peek_buffer((t_buffer*)fifo, data, elem);
}

char peek_lifo(t_fifo * lifo, void * data, int elem)
{
    return peek_buffer((t_buffer*)lifo, data, elem);
}
/* free */
void free_buffer(t_buffer * buffer)
{
    free(buffer->data);
    buffer->data = NULL;
    buffer->size = 0;
    buffer->w_index = 0;
    buffer->r_index = 0;
    buffer->nb_element = 0;

}

void free_fifo(t_fifo * fifo)
{
    free_buffer((t_buffer *)fifo);
}

void free_lifo(t_lifo * lifo)
{
    free_buffer((t_buffer *)lifo);
}
