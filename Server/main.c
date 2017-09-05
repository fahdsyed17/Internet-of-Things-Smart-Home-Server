
#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <//psf/Home/Documents/NetBeansProjects/server/build/Debug/Cygwin_4.x_1-Windows/_ext/503961646/define.h>



#define MAXPENDING 5    /* Maximum outstanding connection requests */

void DieWithError(char *errorMessage);  /* Error handling function */
void Handle_TCP_Client(int clntSocket);   /* TCP client handling function */
//void init_database(void);

//extern struct table;

int main(int argc, char *argv[])
{
    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
    struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
    unsigned short echoServPort;     /* Server port */
    unsigned int clntLen;            /* Length of client address data structure */
    int i=0;

    //int *size = malloc (sizeof(int));

    // struct table *pointer = malloc(sizeof(struct table));

    if (argc != 2)     /* Test for correct number of arguments */
    {
        fprintf(stderr, "Usage:  %s <Server Port>  (Missing server port!)\n", argv[0]);
        exit(1);
    }

    echoServPort = atoi(argv[1]);  /* First arg:  local port */

    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    printf("Server has created socket using port %d\n", echoServPort);


    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(echoServPort);      /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed");

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");

        /* add the table fir the DNS server */


//   init_database();

    for(i=0;i<64;i++)
    {
        strcpy(table[i].string, "\0");
        strcpy(table[i].read, "\0");
        strcpy(table[i].write, "\0");
    }
    table_s.size = 0;
    /* initialize the lookup table with one IP address  */
    strcpy(table[0].string, "Thermostat-Main");
    strcpy(table[0].read, "19");
    strcpy(table[0].write, "23");
    table_s.size++;

    strcpy(table[1].string, "Thermostat-2nd floor");
    strcpy(table[1].read, "15");
    strcpy(table[1].write, "29");
    table_s.size++;

    strcpy(table[2].string, "Thermostat-third floor");
    strcpy(table[2].read, "11");
    strcpy(table[2].write, "26");
    table_s.size++;


    for (;;) /* Run forever */
    {
        /* Set the size of the in-out parameter */
        clntLen = sizeof(echoClntAddr);

        printf("\nServer calling blocking Accept() \n");

        /* Wait for a client to connect */
        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr,
                               &clntLen)) < 0)
            DieWithError("accept() failed");

        /* clntSock is connected to a client! */

        printf("Server Handling client \n");
        printf("Server Handling client with IP address %s\n", inet_ntoa(echoClntAddr.sin_addr));

        HandleTCPClient(clntSock);

        printf("size = %d\n", table_s.size);
         for(i=0;i<table_s.size;i++)
           printf("Device = %d - %s %s %s\n", i+1, table[i].string, table[i].read, table[i].write);

    }
    /* NOT REACHED */
}
