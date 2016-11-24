/******************************************************************************/
/*        @TITRE : udp.h                                                      */
/*      @VERSION : 0                                                          */
/*     @CREATION : august 18, 2016                                            */
/* @MODIFICATION :                                                            */
/*      @AUTEURS : Enzo IGLESIS                                               */
/*    @COPYRIGHT : Copyright (c) 2016 Enzo IGLESIS                            */
/*      @LICENSE : MIT License (MIT)                                          */
/******************************************************************************/
#ifndef UDP_H_
#define UDP_H_

/*******************************    LIBRARYS    *******************************/
#include <netinet/in.h> /* constantes et structures propes au domaine INTERNET*/

/*******************************     TYPES      *******************************/
typedef struct
{
    unsigned short int port;
    int socket;
    struct sockaddr_in socket_addr;
}
udp_in_t;

typedef struct
{
    char * host;
    unsigned short int port;
    int socket;
    struct sockaddr_in socket_addr;
}
udp_out_t;


typedef struct
{
    udp_in_t in;
    udp_out_t out;
}
udp_t;

/*******************************     MACROS     *******************************/

/*******************************   FUNCTIONS    *******************************/
int open_input_udp_connection(udp_in_t * udp_in, unsigned short int port);
int open_output_udp_connection(udp_out_t * udp_out, unsigned short int port, char * host);
int open_udp_connection(udp_t * udp, unsigned short int in_port, unsigned short int out_port, char * host);
ssize_t send_data_udp(udp_out_t udp_out, char * data, size_t data_length);
ssize_t receive_data_udp(udp_in_t udp_in, char * data, size_t data_length);
int close_input_udp_connection(udp_in_t udp_in);
int close_output_udp_connection(udp_out_t udp_out);
int close_udp(udp_t * udp);

#endif
