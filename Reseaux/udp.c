/******************************************************************************/
/*        @TITRE : udp.c                                                      */
/*      @VERSION : 0                                                          */
/*     @CREATION : august 16, 2016                                            */
/* @MODIFICATION :                                                            */
/*      @AUTEURS : Enzo IGLESIS                                               */
/*    @COPYRIGHT : Copyright (c) 2016 Enzo IGLESIS                            */
/*      @LICENSE : MIT License (MIT)                                          */
/******************************************************************************/

/*******************************    LIBRARYS    *******************************/
#include <stdio.h> /* entrees/sorties standards */
#include <stdlib.h> /* bibliotheque standard */
#include <unistd.h>
#include <string.h> /* manipulation d'objet en tant que tableaux de carateres */
#include <sys/types.h> /* declaration des types de base */
#include <sys/socket.h> /* constantes liee aux domaines, types et protocoles */
#include <netinet/in.h> /* constantes et structures propes au domaine INTERNET*/
#include <netdb.h> /* structures retournéespar les fonctions de gestio de la
base de données du reseau */
#include "udp.h"

/*******************************     MACROS     *******************************/

/*******************************     TYPES      *******************************/

/*******************************   CONSTANTES   *******************************/

/*******************************    VARIABLES   *******************************/

/*******************************   FUNCTIONS    *******************************/
int open_input_udp_connection(udp_in_t * udp_in, unsigned short int port)
{
    udp_in->port = port;
    udp_in->socket_addr.sin_family = AF_INET; /* pour le domaine INTERNET */
    udp_in->socket_addr.sin_port = udp_in->port; /* numero de port */
    memset(udp_in->socket_addr.sin_zero, '\0', 8); /* mise a zero */
    if((udp_in->socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) != -1)
    {
        return bind(udp_in->socket, (struct sockaddr * )&udp_in->socket_addr, sizeof(udp_in->socket_addr));
    }
    return -1;
}

int open_output_udp_connection(udp_out_t * udp_out, unsigned short int port, char * host)
{
    /* Local declarations */
    struct hostent * hp;
    /* Program statement */
    udp_out->port = port;
    udp_out->host = host;
    udp_out->socket_addr.sin_family = AF_INET; /* pour le domaine INTERNET */
    udp_out->socket_addr.sin_port = udp_out->port; /* numero de port */
    if((hp = gethostbyname(udp_out->host)) == NULL)
    {
        return -1;
    }
    memcpy((char *)&(udp_out->socket_addr.sin_addr.s_addr), hp->h_addr, hp->h_length);
    memset(udp_out->socket_addr.sin_zero, '\0', 8); /* mise a zero */
    return socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}

int open_udp_connection(udp_t * udp, unsigned short int in_port, unsigned short int out_port, char * host)
{
    if(open_input_udp_connection(&udp->in, in_port) != -1)
    {
        return open_output_udp_connection(&udp->out, out_port, host);
    }
    return -1;
}

ssize_t send_data_udp(udp_out_t udp_out, char * data, size_t data_length)
{
    return sendto(udp_out.socket, data, data_length, 0, (struct sockaddr *)&udp_out.socket_addr, sizeof(udp_out.socket_addr));
}

ssize_t receive_data_udp(udp_in_t udp_in, char * data, size_t data_length)
{
    /* declarationb local */
    struct sockaddr_in padr_em;
    int lg = sizeof(padr_em);
    /* action */
    return recvfrom(udp_in.socket, data, data_length, 0, (struct sockaddr *)(&padr_em), (socklen_t *)&lg);
}

int close_input_udp_connection(udp_in_t udp_in)
{
    return close(udp_in.socket);
}

int close_output_udp_connection(udp_out_t udp_out)
{
    return close(udp_out.socket);
}

int close_udp(udp_t * udp)
{
    if(close_input_udp_connection(udp->in) != -1)
    {
        return close_output_udp_connection(udp->out);
    }
    return -1;
}
