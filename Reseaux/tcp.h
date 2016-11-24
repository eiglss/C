/******************************************************************************/
/*        @TITRE : udp.h                                                      */
/*      @VERSION : 0                                                          */
/*     @CREATION : august 16, 2016                                            */
/* @MODIFICATION :                                                            */
/*      @AUTEURS : Enzo IGLESIS                                               */
/*    @COPYRIGHT : Copyright (c) 2016 Enzo IGLESIS                            */
/*      @LICENSE : MIT License (MIT)                                          */
/******************************************************************************/
#ifndef TCP_H_
#define TCP_H_

/*******************************    LIBRARYS    *******************************/
#include <netinet/in.h> /* constantes et structures propes au domaine INTERNET*/

/*******************************     TYPES      *******************************/
typedef struct
{
    unsigned short int port;
    int socket;
    struct sockaddr_in socket_addr;
}
tcp_in_t;

typedef struct
{
    char * host;
    unsigned short int port;
    int socket;
    struct sockaddr_in socket_addr;
}
tcp_out_t;


typedef struct
{
    tcp_in_t in;
    tcp_out_t out;
}
tcp_t;

/*******************************   FUNCTIONS    *******************************/
int init_input_tcp_connection(tcp_in_t * tcp_in, unsigned short int port);
int init_output_tcp_connection(tcp_out_t * tcp_out, unsigned short int port, char * host);
int init_tcp_connection(tcp_t * tcp, unsigned short int in_port, unsigned short int out_port, char * host);
int tcp_output_connection(tcp_out_t * tcp_out);
int tcp_input_connection(tcp_in_t * tcp_in);
ssize_t send_data_tcp(tcp_out_t  tcp_out, char * data, size_t data_length);
ssize_t receive_data_tcp(tcp_in_t tcp_in, char * data, size_t data_length);
int close_input_tcp_connection(tcp_in_t tcp_in);
int close_input_tcp_connection(tcp_out_t tcp_out);

#endif
