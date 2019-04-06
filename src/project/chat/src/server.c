/*Converter header*/
#define _SVID_SOURCE
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
/*Server Header Files*/
#include "SocketList.h"
//#include "Database.h"
#include "serCNV.h"
//
#include "Database.h"
int professorP=4;
int teacherP=5;

char* Message=" ";
char* To=" ";
char* From= " ";
char* Username=" ";
char* Pwd=" ";
char **split_string(char *str,const char a_delim);
void GetGlobals(char* buffer);
char* GetText(char* buffer);
int command(char* buffer,SocketSet* set,int currClient);
void getuser(char *buffer);
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
int main(int argc, char *argv[])
{
	SetDatabase(); //create directories: Database, Usernames, File: Login.txt Called only once
	int serversocket, port;
	int charsN;
     	char cbuffer[MAXSTRN];
	char CurrName[NAME];
     	socklen_t ClientLen;
     	char buffer[256];
     	struct sockaddr_in serv_addr,ClientAddr;
	if(ENABLESetDatabase)
		SetDatabase();
     	if (argc < 2) {
         	fprintf(stderr,"ERROR, no port provided\n");
         	exit(1);
     	}
     	serversocket = socket(AF_INET, SOCK_STREAM, 0);
     	if (serversocket < 0) 
        	error("ERROR opening socket");
     	bzero((char *) &serv_addr, sizeof(serv_addr));
     	port = atoi(argv[1]);
     	serv_addr.sin_family = AF_INET;
     	serv_addr.sin_addr.s_addr = INADDR_ANY;
     	serv_addr.sin_port = htons(port);
    	 if (bind(serversocket, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
    	listen(serversocket,SOMAXCONN);//Select function
	fd_set waitlist, Cwaitlist; //This will hold the vector with all connected ports to server
	FD_ZERO(&waitlist);
	FD_SET(serversocket,&waitlist);  
	int running=1;
	SocketSet *SocketsVector=CreateSet();
	AppendSocket("server",serversocket,SocketsVector);
	printf("Server has been initialized, now listening to clients\n");
	//char *currUser;//Some temporal holder
        int Nsockets,A;
        SocketSet *ActiveList=CreateSet();
	Cwaitlist=waitlist;
	SocketSet *NotLoginList=CreateSet();
	while(running)
	{
		printf("Waiting connections\n");
		Nsockets=select(FD_SETSIZE,&Cwaitlist,NULL,NULL,NULL);
                A=0; //some counter
                //We will get a copy of the active users in the following lines
		ClearSet(ActiveList);
                for(int i=0;i<FD_SETSIZE;i++)
                {
                        if(FD_ISSET(i, &Cwaitlist)) //This will check if socket i is an active socket
                        {//In the case that it is, then
				AppendPort(i,ActiveList);
			}
		}//I dont need to know their usernames, only the ports
		//By now ActiveList should have all clients trying to connect to the server socket
		int i=0,currClient;
		while((currClient=IterateSet(i,ActiveList))!=-1)
		{
			if(currClient==serversocket)
			{
				ClientLen=sizeof(ClientAddr);
                                int client=accept(serversocket,(struct sockaddr*)&ClientAddr,&ClientLen);
                                if(client<0)
				{ 
					printf("Error creating socket for new client\n");
                                	continue; //If there was an eeror, continue with the next node active
				}
				FD_SET(client, &waitlist);//Add new client to vector list
                                AppendSocket("noname",client,NotLoginList); //Append to original socket
                                printf("New client in socket %d\n",client);
                                send(client,"Welcome to the server!\n",sizeof("Welcome to the server!\n")+1,1);
			}
			else //if it get into this area, that means that the active node (currClient) had already been added and is connected to the server
			{
		//Next step: get destination of message in order to send message between clients
				bzero(buffer,257);
				charsN = read(currClient,buffer,sizeof(buffer)-1);
				strcpy(cbuffer,buffer);
				if(!(strcmp(buffer,"exit")))
				{
					running=0;
				}
				if(charsN<=0)//The following block is in case that a user has disconnected from server
				{
					printf("Dropping client %d\n",currClient);
					close(currClient);
					RemoveSocketPort(currClient, SocketsVector);
					FD_CLR(currClient, &waitlist);
					i++;
					continue;
				}
				printf("Message: %s\n",buffer);
				char *copy=(char*)malloc(strlen(buffer));
				strcpy(copy,buffer);
				if(buffer[0]!='\n')
				{
					int result=command(copy,SocketsVector,currClient);
					printf("Result: %d\n",result);
					if(result==3)
					{
						AppendSocket(Username,currClient,SocketsVector);
						printf("Adding username: %s and port %d\n",Username,GetPort(Username,SocketsVector));
					}
				}
				//CommandCNV(cbuffer,CurrName,ActiveList,currClient);
			//	printf("Going out: %s\n",buffer);
			//	if(CurrName!='\0')
			//		AppendSocket(CurrName,currClient,SocketsVector);
			}
        		i++; //Go to the next active user
		}	
		FD_ZERO(&Cwaitlist);//Repopulate list
		Cwaitlist=waitlist;

	}
	printf("Closing server\n");
	FD_CLR(serversocket,&waitlist);
	close(serversocket);
}
int command(char* buffer,SocketSet* set,int currClient)
{
	char* substring=(char*) malloc(strlen(buffer));
	char* returnV;
	char* Msend=(char*)malloc(sizeof(char)*256);
	GetGlobals(buffer);
	//getuser(buffer);
	printf("1 %s\n",Message);
    printf("2 %s\n",To);
    printf("3 %s\n",From);
    printf("4 %s\n",Username);
    printf("5 %s\n",Pwd);
	//Call command converter
	if((substring=strstr(buffer,"M:")))
	{
		Msend=strcpy(Msend,"F:/");
		Msend=strcpy(Msend,From);
		Msend=strcpy(Msend,"/");
		Msend=strcpy(Msend,"M:/");
		Msend=strcpy(Msend,Message);
		Msend=strcpy(Msend,"/");
		printf("Printing To field\n");
		int i=0;
		while(To[i]!='\0')
		{
			printf("%d ",To[i]);
			i++;
		}
		printf("\n");
		int Destination=GetPort(To,set);
/*		if(!strcmp(To,"professor"))
		{
			printf("SEnding message to professor\n");
			Destination=professorP;
		}
		else if(!strcmp(To,"teacher"))
		{
			Destination=teacherP;
			printf("SEnding message to professor\n");
		}
*/		printf("Printing %s port: %d \n",To,Destination);
		if(Destination>0)
			write(Destination,Message,strlen(Message));
		else
			write(currClient,"M:/User is not connected/",strlen("M:/User is not connected/"));
		return 1;
	}
	else if((substring=strstr(buffer,"SUser:")))
	{
		returnV=ServerSignUp(Username,Pwd);
		write(currClient,returnV,strlen(returnV)+1);
		return 2;
	}
	else if((substring=strstr(buffer,"LUser:")))
	{
		assert(Username);
		assert(Pwd);
		returnV=ServerLogin(Username,Pwd);
		if(returnV[0]=='E')//If error logging in
		{
			write(currClient,returnV,strlen(returnV));
			return 0;
		}
		//But if not error loging in, then returV will have the contacts list
		Msend=strcpy(Msend,"C:/");
		strcat(Msend,returnV);
		strcat(Msend,"/");
		printf("Sending message: %s\n",Msend);
		write(currClient,Msend,strlen(Msend)+1);
	//	if(Msend) free(Msend);
	//	if(substring) free(substring);
		return 3;
	}
	else if((substring=strstr(buffer,"A:")))
	{
		return 4;
	}
	else if((substring=strstr(buffer,"D:")))
	{
		return 5;
	}
	else
	{
		return 6;
	}
}
void GetGlobals(char* buffer)
{
        Message=GetText(strstr(buffer,"M:"));
        To=GetText(strstr(buffer,"T:"));
        From=GetText(strstr(buffer,"F:"));
        if(!(Username=GetText(strstr(buffer,"LUser:")))) //Username will come from either LUser or SUser so if LUser returns null, then get SUser
                Username=GetText(strstr(buffer,"SUser:"));
        Pwd=GetText(strstr(buffer,"Pwd:"));
}
char* GetText(char* buffer)
{
        if(!buffer)
            return " ";
        char* text=(char*) malloc(strlen(buffer));
        char* start=strstr(buffer,"/");
        int a=1;//for the substring "start"
        int b=0;//for text
        while(start[a]!='/')
        {
                text[b]=start[a];
                a++;
                b++;
        }
	text[b]='\0';
        if(!text)
                text[0]=' ';
        return text;
}

