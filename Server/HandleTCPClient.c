/*
 *  HandleTCPClient.h  for DNS server
 *
 *  Created by Prof. TS for 4DN4 on Sunday, Jan. 19, 2014
 *
 */

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <string.h>


#include <//psf/Home/Documents/NetBeansProjects/server/build/Debug/Cygwin_4.x_1-Windows/_ext/503961646/define.h>
#define RCVBUFSIZE 198   /* Size of receive buffer */

void DieWithError(char *errorMessage);  /* Error handling function */

//extern struct table;

void HandleTCPClient(int clntSocket)
{
//    int size;
    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */    int recvMsgSize1;                    /* Size of 1st received message */
    int count = 0;
   // int i=0;
    char command [6] = "";
    char name_buf [128] = "";
    char read_buf [32] = "";
    char write_buf [32] = "";
    int  i,j,k, strlength;


    
    memset(&echoBuffer, 0, sizeof(echoBuffer));   /* Zero out structure */
    
    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");
   
   /* to get here, we received a message from client */
   /*  search lookup table, looking for the same string */

   printf("server receives this string: '%s'\n", echoBuffer);

    strlength = strlen(echoBuffer);
    //count =0;

        i=0;
        while(echoBuffer[i] != ',')
        {
          command[i] = echoBuffer[i];
          i++;                
        }
        command[i] = '\0';
        
        printf("Command= %s\n", command);
        
    ///////////////////////////////////////  
    ///////////////////////////////////////    

        if(strcmp(command, "add") == 0)
        {//Add command
 
            i+=1;
            j=0;
            while(echoBuffer[i] != ',')
            {
              name_buf[j] = echoBuffer[i];
              i++;       
              j++;
            }
            name_buf[i] = '\0';



            printf("Device name= %s\n", name_buf);

            i += 1;
            j = 0;
            while(echoBuffer[i] != ',')
            {
                read_buf[j] = echoBuffer[i];
                i++;    
                j++;
            }
            read_buf[i] = '\0';
            printf("read value= %s\n", read_buf);

            i += 1;
            j = 0;
            while(echoBuffer[i] != '\0')
            {
                write_buf[j] = echoBuffer[i];
                i++;              
                j++;
            }
            write_buf[i] = '\0';

            printf("write value= %s\n", write_buf);


            for (j=0; j<64; j++) 
            {
                if(strcmp("\0",table[j].string) == 0)
                {
                    strcpy(table[j].string, name_buf);
                    strcpy(table[j].read, read_buf);
                    strcpy(table[j].write, write_buf);
                    table_s.size++;

                    printf("Device = %d - %s %s %s\n", j+1, table[j].string, table[j].read, table[j].write);
                    strcpy(echoBuffer, "Success: Device added");
                    break;
                }
            }

            if (j == 64) {
                printf("Database is full\n");
                strcpy(echoBuffer, "URL Not Found");
                strlength = strlen(echoBuffer);
                sleep(1);
            }

        }
        
            ///////////////////////////////////////  
            ///////////////////////////////////////    
        
        
         if(strcmp(command, "remove") == 0)
        {
            i+=1;
            j=0;
            while(echoBuffer[i] != '\0')
            {
                name_buf[j] = echoBuffer[i];
                i++;       
                j++;
            }
            name_buf[i] = '\0';
            for(i=0;i<table_s.size;i++)
            {
               // printf("size = %d\n", table_s.size);
               // printf("name_buf = %s, table[%d].string  = %s ", name_buf, i, table[i].string);
                if(strcmp(name_buf, table[i].string)==0)
                {
                    for(j=i;j<table_s.size-1;j++)
                    {
                        strcpy(table[j].string,table[j+1].string);
                        strcpy(table[j].read, table[j+1].read);
                        strcpy(table[j].write, table[j+1].write);
                    }
                    strcpy(table[table_s.size-1].string, "\0");
                    strcpy(table[table_s.size-1].read, "\0");
                    strcpy(table[table_s.size-1].write, "\0");
                    table_s.size--;
                    strcpy(echoBuffer, "Success: Device removed");
                    break;
                }
                else
                    strcpy(echoBuffer, "No match");
            }
         }
        
         ///////////////////////////////////////  
         ///////////////////////////////////////   
        
         if(strcmp(command, "read") == 0)
        {
            i+=1;
            j=0;
            while(echoBuffer[i] != '\0')
            {
              name_buf[j] = echoBuffer[i];
              i++;       
              j++;
            }
            name_buf[i] = '\0';
             

             for(i=0;i<table_s.size;i++)
             {
                 if(strcmp(name_buf, table[i].string)==0)
                 {
                     strcpy(echoBuffer, table[i].read);
                     strcat(echoBuffer, ",");
                     strcat(echoBuffer, table[i].write);
                     strcat(echoBuffer, "\0");
                     break;
                 }
                 else
                     strcpy(echoBuffer, "No Match");
             }
         }
        
         ///////////////////////////////////////  
         /////////////////////////////////////// 
        
          if(strcmp(command, "write") == 0)
        {
            i+=1;
            j=0;
            while(echoBuffer[i] != ',')
            {
              name_buf[j] = echoBuffer[i];
              i++;       
              j++;
            }
            name_buf[i] = '\0';
             
            i += 1;
            j = 0;
            while(echoBuffer[i] != '\0')
            {
                write_buf[j] = echoBuffer[i];
                i++;              
                j++;
            }
            write_buf[i] = '\0';

           // printf("write value= %s\n", write_buf);

             for(i=0;i<64;i++)
                 if(strcmp(name_buf, table[i].string)==0)
                 {
                     strcpy(table[i].write,write_buf);
                     strcpy(echoBuffer, "Success: copied new write value");
                     break;
                 }
                 else
                     strcpy(echoBuffer, "No Match");
         }
        
        strlength = strlen(echoBuffer);
        
    /* Echo the string in 'echobuffer' back to client */
    if (send(clntSocket, echoBuffer, strlength, 0) != strlength)
        DieWithError("send() failed");
 

    printf("server sent string '%s' to client\n", echoBuffer);

    sleep(1);
    close(clntSocket);    /* Close client socket */
   
}
