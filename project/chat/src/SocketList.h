#ifndef SOCKET_H
#define SOCKET_H
#include "Constants.h"
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <strings.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <assert.h>*/
SocketNode* CreateSocket(char *username,int Port);

void ClearSet(SocketSet *Set);

void DeleteSet(SocketSet *Set);

void RemoveSocket(SocketNode *node);

void RemoveSocketUser(char* username,SocketSet *Set);

SocketSet *CreateSet();

void AppendSocket(char *username, int port, SocketSet *Set);/*Appens some port to the list*/

int GetPort(char *username,SocketSet *Set); /*Returns some port of username, -1 if no match found*/

char *GetUsername(int Port, SocketSet *Set); //This return some username when given some port

int IterateSet(int number, SocketSet* Set);

SocketNode* CreatePort(int Port);// Used for AppendPort only

void AppendPort(int port, SocketSet *Set);//Appends some port to list, with no need of a username

void RemoveSocketPort(int port,SocketSet *Set);//Same as RemoveSocketUser, but this will require a socket number to remove a socket

#endif

