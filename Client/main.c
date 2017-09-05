
#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define RCVBUFSIZE 198   /* Size of receive buffer */

void DieWithError(char *errorMessage);  /* Error handling function */

//extern struct table;

int main(int argc, char *argv[])
{
    int sock;                        /* Socket descriptor */
    struct sockaddr_in echoServAddr; /* Echo server address */
    unsigned short echoServPort;     /* Echo server port */
    char *servIP;                    /* Server IP address (dotted quad) */
    char *echoString;                /* String to send to echo server  --- string that contains device name*/
    char echoBuffer[RCVBUFSIZE];     /* Buffer for echo string */
    unsigned int echoStringLen;      /* Length of string to echo */
    int bytesRcvd, totalBytesRcvd;   /* Bytes read in single recv()
                                        and total bytes read */
    int value = 0, i,j, name_len, c;
    int count;
    char name [128];
    char readval[32];
    char writeval [32];
    char temp[192];

    echoString = (char *)malloc(sizeof(RCVBUFSIZE));

    servIP = argv[1];             /* First arg: server IP address (dotted quad) */
   // echoString = argv[2];         /* Second arg: string to echo */
    echoServPort = atoi(argv[2]); /*Second arg: given port*/

   // if (argc == 4)
   //    echoServPort = atoi(argv[3]); /* Use given port, if any */
    /* else
     echoServPort = 7;   7 is the well-known port for the echo service */



     while(1)
     {
         memset(&echoBuffer, 0, RCVBUFSIZE);

       /* Create a reliable, stream socket using TCP */
        if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
                DieWithError("socket() failed");


        /* Construct the server address structure */
        memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
        echoServAddr.sin_family      = AF_INET;             /* Internet address family */
        echoServAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
        echoServAddr.sin_port        = htons(echoServPort); /* Server port */

        /* Establish the connection to the echo server */
        if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
            DieWithError("connect() failed");

        printf("Client connected to server on port %d\n", echoServPort);




        printf("Here are your options:\n");


        printf("1. ADD\n");
        printf("2. REMOVE\n");
        printf("3. READ\n");
        printf("4. WRITE\n");
        printf("5. Quit\n");
        printf("Enter option: ");
        //fgets(value, sizeof(value), stdin);
        scanf("%d",&value);
        do{
                c = getchar();
        }while(c != EOF && c != '\n');

        switch(value)
        {

            case 1:     memset(echoString, 0, RCVBUFSIZE);
                        strcpy(name, "\0");
                        strcpy(readval, "\0");
                        strcpy(writeval, "\0");




                        printf("Enter device name to ADD: ");
                        fgets(name,sizeof(name),stdin);
                        name[strlen(name)-1] = '\0';
                        printf("name[i] = %s\n", name);

                        printf("Enter read value: ");
                        scanf("%s", &readval);
                        printf("readval = %s\n", readval);

                        printf("Enter write value: ");
                        scanf("%s", &writeval);
                        printf("writeval = %s\n", writeval);

                      //  *echoString = malloc(strlen(name) + strlen(readval) + strlen(writeval) + 3);


                        strcpy(echoString, "add");
                        strcat(echoString, ",");
                        strcat(echoString, name);
                        strcat(echoString, ",");
                        strcat(echoString, readval);
                        strcat(echoString, ",");
                        strcat(echoString, writeval);
                        strcat(echoString, "\0");

                        printf("echoString = %s\n", echoString);

                       echoStringLen = strlen(echoString);          /* Determine input length */

                        /* Send the string to the server */
                        if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
                                DieWithError("send() sent a different number of bytes than expected");

                        printf("Client sent message to server: ");
                        printf(echoString);
                        printf("\n");

                       // printf("echoString: %s\n", echoString);

                        bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0);

                        if (bytesRcvd  <= 0)
                            DieWithError("recv() failed or connection closed prematurely");

                        printf("Client Receives string '%s'\n", echoBuffer);


                        printf("\n");    /* Print a final linefeed */


                        sleep(1);
                        close(sock);

                     //   memset(name, 0, 128);
                        break;

            case 2:     memset(echoString, 0, RCVBUFSIZE);
                        strcpy(name, "\0");

                        printf("Enter device name to REMOVE: ");
                        fgets(name,sizeof(name),stdin);
                        name[strlen(name)-1] = '\0';
                        printf("name[i] = %s\n", name);

                        strcpy(echoString, "remove");
                        strcat(echoString, ",");
                        strcat(echoString, name);
                        strcat(echoString, "\0");

                        printf("echoString = %s\n", echoString);

                       echoStringLen = strlen(echoString);          /* Determine input length */
                        /* Send the string to the server */
                          if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
                                DieWithError("send() sent a different number of bytes than expected");

                        printf("Client sent message to server: ");
                        printf(" %s", echoString);
                       // printf("\033[01;37m");
                        printf("\n");

                       // printf("echoString: %s\n", echoString);

                        bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0);

                        if (bytesRcvd  <= 0)
                            DieWithError("recv() failed or connection closed prematurely");

                        printf("Client Receives string '%s'\n", echoBuffer);


                        printf("\n");    /* Print a final linefeed */


                        sleep(1);
                        close(sock);

                        break;


            case 3:     memset(echoString, 0, RCVBUFSIZE);
                        //memset(&name, 0, RCVBUFSIZE);
                        strcpy(name, "\0");
                        strcpy(readval, "\0");
                        strcpy(writeval, "\0");


                        printf("Enter device name to READ: ");
                        fgets(name,sizeof(name),stdin);
                        name[strlen(name)-1] = '\0';
                        printf("name[i] = %s\n", name);

                        strcpy(echoString, "read");
                        strcat(echoString, ",");
                        strcat(echoString, name);
                        strcat(echoString, "\0");
                        printf("echoString = %s\n", echoString);

                       echoStringLen = strlen(echoString);          /* Determine input length */

                       /* Send the string to the server */
                        if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
                                DieWithError("send() sent a different number of bytes than expected");

                        printf("Client sent message to server: ");
                        printf(echoString);
                        printf("\n");

                       // printf("echoString: %s\n", echoString);

                        bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0);

                        if (bytesRcvd  <= 0)
                            DieWithError("recv() failed or connection closed prematurely");

                        printf("Client Receives string '%s'\n", echoBuffer);



                        if(strcmp(echoBuffer, "No Match") != 0)
                        {
                            i=0;
                            while(echoBuffer[i] != ',')
                            {
                              readval[i] = echoBuffer[i];
                              i++;
                            }
                            readval[i] = '\0';
                            printf("read value= %s\n", readval);


                             i+=1;
                             j=0;
                            while(echoBuffer[i] != '\0')
                            {
                              writeval[j] = echoBuffer[i];
                              i++;
                              j++;
                            }
                            writeval[i] = '\0';


                            printf("write value= %s\n", writeval);
                        }


                            printf("\n");    /* Print a final linefeed */
                            sleep(1);
                            close(sock);
                            break;





            case 4:     memset(echoString, 0, RCVBUFSIZE);
                        strcpy(name, "\0");
                        strcpy(readval, "\0");
                        strcpy(writeval, "\0");


                        printf("Enter device name to WRITE: ");
                        fgets(name,sizeof(name),stdin);
                        name[strlen(name)-1] = '\0';
                        printf("name[i] = %s\n", name);

                        printf("Enter write value: ");
                        scanf("%s", &writeval);
                        printf("writeval = %s\n", writeval);

                        strcpy(echoString, "write");
                        strcat(echoString, ",");
                        strcat(echoString, name);
                        strcat(echoString, ",");
                        strcat(echoString, writeval);
                        strcat(echoString, "\0");

                        printf("echoString = %s\n", echoString);

                       echoStringLen = strlen(echoString);          /* Determine input length */


                         /* Send the string to the server */
                        if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
                                DieWithError("send() sent a different number of bytes than expected");

                        printf("Client sent message to server: ");
                        printf(echoString);
                        printf("\n");

                       // printf("echoString: %s\n", echoString);

                        bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0);

                        if (bytesRcvd  <= 0)
                            DieWithError("recv() failed or connection closed prematurely");

                        printf("Client Receives string '%s'\n", echoBuffer);


                        printf("\n");    /* Print a final linefeed */


                        sleep(1);
                        close(sock);
                        break;


            case 5:     sleep(1);
                        close(sock);

                        printf("exit program\n");

                        exit(0);


                        break;

            default:    break;
        }


     }

      // exit(0);
 printf("\n");    /* Print a final linefeed */


 return 0;
}



