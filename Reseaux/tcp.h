/******************************************************************************/
/*        @TITRE : tcp.h                                                      */
/*      @VERSION : 1                                                          */
/*     @CREATION : august 16, 2016                                            */
/* @MODIFICATION : august 18, 2017                                            */
/*      @AUTEURS : Enzo IGLESIS                                               */
/*    @COPYRIGHT : Copyright (c) 2016 Enzo IGLESIS                            */
/*      @LICENSE : MIT License (MIT)                                          */
/******************************************************************************/
#ifndef TCP_H_
#define TCP_H_

/*******************************    LIBRARYS    *******************************/
#include <netinet/in.h> /* constantes et structures propes au domaine INTERNET*/
#include <stdint.h>

/*******************************     TYPES      *******************************/
typedef struct tcp_t
{
    /* variables */
    char * host;
    uint16_t port;
    int socket;
    struct sockaddr_in sockaddr;
    /* functions */
    int (* connect)(struct tcp_t * tcp);
    int (* accept)(struct tcp_t * tcp);
    ssize_t (* write)(struct tcp_t * tcp, char * data, size_t length);
    ssize_t (* read)(struct tcp_t * tcp, char * data, size_t length);
    int (* close)(struct tcp_t * tcp);
}
tcp_t;

/*******************************   FUNCTIONS    *******************************/
int tcp_initialize_server(tcp_t * tcp, uint16_t port);
int tcp_initialize_client(tcp_t * tcp, uint16_t port, char * host);
int tcp_connect(tcp_t * tcp);
int tcp_accept(tcp_t * tcp);
ssize_t tcp_write(tcp_t * tcp, char * data, size_t length);
ssize_t tcp_read(tcp_t * tcp, char * data, size_t length);
int tcp_close(tcp_t * tcp);

#endif
