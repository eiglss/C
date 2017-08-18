/******************************************************************************/
/*        @TITRE : tcp.c                                                      */
/*      @VERSION : 1                                                          */
/*     @CREATION : august 18, 2016                                            */
/* @MODIFICATION : august 18, 2017                                            */
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
static void tcp_initialize_struct(tcp_t * tcp)
{
    tcp->connect = tcp_connect;
    tcp->accept = tcp_accept;
    tcp->write = tcp_write;
    tcp->read = tcp_read;
    tcp->close = tcp_close;
}

int tcp_initialize_server(tcp_t * tcp, uint16_t port)
{
    tcp_initialize_struct(tcp);
    tcp->port = port;
    tcp->sockaddr.sin_family = AF_INET;
    tcp->sockaddr.sin_port = htons(port);
    tcp->sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(tcp->sockaddr.sin_zero, '\0', 8);
    if((tcp->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != -1)
    {
        return bind(tcp->socket, (struct sockaddr *)&tcp->sockaddr, sizeof(tcp->sockaddr));
    }
    return -1;
}

int tcp_initialize_client(tcp_t * tcp, uint16_t port, char * host)
{
    /* local declarations */
    struct hostent * hp;
    /* program statement */
    tcp_initialize_struct(tcp);
    tcp->port = port;
    tcp->host = host;
    tcp->sockaddr.sin_family = AF_INET; /* pour le domaine INTERNET */
    tcp->sockaddr.sin_port = htons(port); /* numero de port */
    if((hp = gethostbyname(host)) == NULL)
    {
        return -1;
    }
    memcpy((char *)&(tcp->sockaddr.sin_addr.s_addr), hp->h_addr, hp->h_length);
    memset(tcp->sockaddr.sin_zero, '\0', 8); /* mise a zero */
    tcp->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    return 0;
}

int tcp_connect(tcp_t * tcp)
{
    return connect(tcp->socket, (struct sockaddr * )&tcp->sockaddr, sizeof(tcp->sockaddr));
}

int tcp_accept(tcp_t * tcp)
{
    /* local declaration  */
    struct sockaddr_in padr_client;
    int lg = sizeof(padr_client);
    int temp;
    /* program statement */
    temp = tcp->socket;
    listen(tcp->socket, 1);
    if((tcp->socket = accept(tcp->socket, (struct sockaddr *)(&padr_client), (socklen_t *)(&lg))) == -1)
    {
        return -1;
    }
    close(temp);
    return 0;
}

ssize_t tcp_write(tcp_t * tcp, char * data, size_t length)
{
    return  write(tcp->socket, data, length);
}

ssize_t tcp_read(tcp_t * tcp, char * data, size_t length)
{
    return read(tcp->socket, data, length);
}

int tcp_close(tcp_t * tcp)
{
    if(shutdown(tcp->socket, SHUT_RDWR) != -1)
    {
        return close(tcp->socket);
    }
    return -1;
}
