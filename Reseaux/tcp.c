/******************************************************************************/
/*        @TITRE : tcp.c                                                      */
/*      @VERSION : 0                                                          */
/*     @CREATION : august 18, 2016                                            */
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
#include <sys/un.h>
#include <netinet/in.h> /* constantes et structures propes au domaine INTERNET*/
#include <netdb.h> /* structures retournéespar les fonctions de gestio de la
base de données du reseau */
#include "tcp.h"

/*******************************     MACROS     *******************************/

/*******************************     TYPES      *******************************/

/*******************************   CONSTANTES   *******************************/

/*******************************    VARIABLES   *******************************/

/*******************************   FUNCTIONS    *******************************/
int init_input_tcp_connection(tcp_in_t * tcp_in, unsigned short int port)
{
    tcp_in->port = port;
    tcp_in->socket_addr.sin_family = AF_INET; /* pour le domaine INTERNET */
    tcp_in->socket_addr.sin_port = tcp_in->port; /* numero de port */
    memset(tcp_in->socket_addr.sin_zero, '\0', 8); /* mise a zero */
    if((tcp_in->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != -1)
    {
        return bind(tcp_in->socket, (struct sockaddr * )&tcp_in->socket_addr, sizeof(tcp_in->socket_addr));
    }
    return -1;
}

int init_output_tcp_connection(tcp_out_t * tcp_out, unsigned short int port, char * host)
{
    /* local declarations */
    struct hostent * hp;
    /* program statement */
    tcp_out->port = port;
    tcp_out->host = host;
    tcp_out->socket_addr.sin_family = AF_INET; /* pour le domaine INTERNET */
    tcp_out->socket_addr.sin_port = tcp_out->port; /* numero de port */
    if((hp = gethostbyname(tcp_out->host)) == NULL)
    {
        return -1;
    }
    memcpy((char *)&(tcp_out->socket_addr.sin_addr.s_addr), hp->h_addr, hp->h_length);
    memset(tcp_out->socket_addr.sin_zero, '\0', 8); /* mise a zero */
    tcp_out->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    return tcp_out->socket;
}

int init_tcp_connection(tcp_t * tcp, unsigned short int in_port, unsigned short int out_port, char * host)
{
    if(init_input_tcp_connection(&tcp->tcp_in, in_port) != -1)
    {
        return init_output_tcp_connection(&tcp->tcp_out, out_port, host);
    }
    return -1;
}

int tcp_output_connection(tcp_out_t * tcp_out)
{
    return connect(tcp_out->socket, (struct sockaddr * )&tcp_out->socket_addr, sizeof(tcp_out->socket_addr));
}

int tcp_input_connection(tcp_in_t * tcp_in)
{
    /* local declaration  */
    int new_socket;
    struct sockaddr_in padr_client;
    int lg = sizeof(padr_client);
    /* program statement */
    if((new_socket = accept(tcp_in->socket, (struct sockaddr *)(&padr_client), (socklen_t *)(&lg))) == -1)
    {
        return -1;
    }
    close(tcp_in->socket);
    listen(new_socket, 1);
    return tcp_in->socket = new_socket;
}

ssize_t send_data_tcp(tcp_out_t  tcp_out, char * data, size_t data_length)
{
    return  write(tcp_out.socket, data, data_length);
}

ssize_t receive_data_tcp(tcp_in_t tcp_in, char * data, size_t data_length)
{
    return read(tcp_in.socket, data, data_length);
}

int close_input_tcp_connection(tcp_in_t tcp_in)
{
    if(shutdown(tcp_in.socket, SHUT_RDWR) != -1)
    {
        return close(tcp_in.socket);
    }
    return -1;
}

int close_input_tcp_connection(tcp_out_t tcp_out)
{
    if(shutdown(tcp_out.socket, SHUT_RDWR) != -1)
    {
        return close(tcp_out.socket);
    }
    return -1;
}
