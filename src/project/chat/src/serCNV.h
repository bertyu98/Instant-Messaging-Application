#ifndef SERCNV_H
#define SERCNV_H
#include "Constants.h"
#include "SocketList.h"
#include "Database.h"
/*
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
*/
//
void RenameNode(char* newName, SocketSet* TotalSet, SocketSet* ActiveSet, int currClient);
char* ServerActive(char* newName, SocketSet* ActiveSet, int currClient);
int CommandCNV(char* strn, char* CurrentName, SocketSet* set, int currClient);
char *strnstr(char* hay, char* needle,int maxlen,int minlen);
#endif
