/*This sate of code is made solely to work with the GUI, it may not remain in this module but it will be here to work on in the meantime */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include <strings.h>
#include <fcntl.h>

#define NAME 12
#define MAXCMND 20
#define MAXSTRN 50
#define UNSAID "Unspecifed Output\n"
#define NOTSAID ""
#define FRIENDS " "
#define DEFAULTNAME "Anon"

#define h_addr h_addr_list[0]

/* variables used all throughout the code */
char buffer[MAXSTRN];
char message[MAXSTRN];
char username[NAME];
char password[NAME];
char result[NAME];
char recipient[NAME];


void encrypt(char* strn);
void sendmessage(char *result, char *username, char *recipient, char *message, int sockfd);
int login(char *username, char *password, int sockfd);
void signup(char *username, char *password, int sockfd);
void error(const char *message);
int CommandCNV(char* strn);
void nonblock(int sockfd);

void error(const char *message)
{
    perror(message);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n, loggedIn;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    nonblock(sockfd);
    nonblock(0);

    /*This is where login and sign up go
 * if login then run chat loop, if not then exit*/

    fgets(username, 11, stdin);
    fgets(password, 11, stdin);

    signup(username, password, sockfd);

    login(username, password, sockfd);

	if(loggedIn == 1)
	{

		fd_set client;

		while(true){
		
		/*Values and functions used to make select work*/
		FD_ZERO(&client);
		FD_SET(sockfd, &client);

		FD_SET(0, &client);
		if(select(FD_SETSIZE, &client, NULL, NULL, NULL) != -1)
		{
			for(int fd = 0;fd < FD_SETSIZE; fd++)
			{
				if(fd == sockfd)
				{
					int lastchar = read(sockfd, buffer, 255);
					buffer[lastchar] = '\0';
					/*send buffer to GUI*/
					memset(&buffer, 0, 256);
				
				}
				else if(fd == 0)
				{
					/*get the message from the GUI*/
					fgets(message,255, stdin); 
					sendmessage(buffer, username, recipient, message, sockfd);

				}						

			}
		}
		}


	}
	if(loggedIn < 1)
	{

		open_dialog(button, window);

	}   


}

void sendmessage(char *result, char *username, char *recipient, char *message, int sockfd)
{

     int n;
     memset(result, 0, MAXSTRN);

     strcat(result,"M: /");
     strcat(result, message );
     strcat(result, "/F: /");
     strcat(result, username);
     strcat(result, "/T: /");
     strcat(result, recipient);
     strcat(result, "/");
     
     bzero(buffer, MAXSTRN);
     strcpy(buffer, result);
     n = write(sockfd, buffer, strlen(buffer));
     if (n < 0)
		error("ERROR sending command to socket");
     bzero(buffer, 256);
     n = read(sockfd, buffer, 255);
     if (n < 0)
		error("ERROR reading from socket");
     printf("%s\n\n", buffer);
     memset(result, 0, MAXSTRN);

 

}

/*Login code*/
int login(char *username, char *password, int sockfd)
{

    int n;

    memset(result, 0, MAXSTRN);
    #ifndef DEBUG
    /*Enters a username to associate with the socket number*/
    username[strlen(username)-1] = '\0';
    password[strlen(password)-1] = '\0';

    encrypt(password);
    
    strcat(result, "LUser: /");
    strcat(result, username);
    strcat(result,"/Pwd: /");
    strcat(result, password);
    strcat(result, "/");

    #endif

    /*Debug Username and Password*/
    #ifdef DEBUG
    strcpy(username, "DEBUG");
    username[strlen(username)-1] = '\0';

    strcpy(password, "DEBUGpassword");
    password[strlen(password)-1] = '\0';
    encrpyt(password);
    #endif

    bzero(buffer, 256);
    strcpy(buffer, result); 
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
               error("ERROR sending command to socket");
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if (n < 0)
               error("ERROR reading from socket");

    n = CommandCNV(buffer);

    return n;

}


/*Sign up module, slightly different in that it calls login*/	
void signup(char *username, char *password, int sockfd)
{

    int n;

    memset(result, 0, MAXSTRN);
    #ifndef DEBUG
    /*Enters a username to associate with the socket number*/
    username[strlen(username)-1] = '\0';
    password[strlen(password)-1] = '\0';

    encrypt(password);

    strcat(result, "SUser: /");
    strcat(result, username);
    strcat(result,"/Pwd: /");
    strcat(result, password);
    strcat(result, "/");

    #endif

    /*Debug Username and Password*/
    #ifdef DEBUG
    strcpy(username, "DEBUG");
    username[strlen(username)-1] = '\0';

    strcpy(password, "DEBUGpassword");
    password[strlen(password)-1] = '\0';
    encrpyt(password);
    #endif

    bzero(buffer, 256);
    strcpy(buffer, result);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
               error("ERROR sending command to socket");
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if (n < 0)
               error("ERROR reading from socket");

    open_dialogSignUp(button, window);
   
}

void encrypt(char* strn){
        int i;
        for(i = 0;*(strn+i)!='\0';i++){
                *(strn+i)+=2;
        }
}

void nonblock(int fd)
{
    int flags = fcntl(fd, F_GETFL);
    if(flags < 0)
        perror("fcntl failed");

    flags |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flags);
}

int CommandCNV(char* strn){
        /*char *person[10];*/
        static int loggedIn = 0;
        int nonLog = 1;
        int strnLen = 0;
        int Com = -1;/*looks looks for a ':' then a ' ' then a '/'*/
        int ComLoc[MAXCMND] = {0};
        char ComEnd[MAXCMND];
        char newStrn[MAXSTRN] = "";
        char finalStrn[MAXSTRN] = "";
        static char userStrn[NAME] = DEFAULTNAME;
        char *ComRoot, *ComStart,*k;
        int ComUser, ComNext;
        int i;
        int j = 0;
        char from[NAME] = "N", to[NAME] = "N"/*, pwd[NAME] = "N"*/;
        for(i = 1;*(strn+i)!='\0';i++){/*saves the location within the string that a : indication of command appears. It does so for every instance in order inside ComLoc*/
                strnLen++;/*attains the size of the string*/
                if(Com>-1){/*if : has been found*/
                        if(Com>256){/*if : and ' ' have been found*/
                                if(Com>1256){/*if : / has been found*/
                                        ComLoc[j] = Com - 2000;/*stores pos of the ':' in ComLoc*/
                                        Com = -1;/*result stored so reset Com to begin looking for ':' again*/
                                        j++;
                                }
                                else if(*(strn+i) =='/'){ Com += 1000;  }/*indicate '/' has been found*/
                                else{ Com = -1; }/*no '/' was found so reset Com to begin looking for ':' again*/
                        }
                        else if(        *(strn+i) ==' '){ Com += 1000;  }/*indicate ' ' has been found*/
                        else{         Com = -1; }/*no ' ' was found so reset Com to begin looking for ':' again*/
                }
                else if(                *(strn+i) ==':'){ Com = i;      }/*indicate ':' has been found*/
        }
        j--;
        i = j;
        for(;j>=0;j--){
                ComRoot = strn + ComLoc[j] - 1;
                switch( *ComRoot ){
                        case 'F':/*F From*/
                                /*if(loggedIn){*/
                                        /*Should be passed as F: /USER/ */
                                        /*No Output*/
                                        ComEnd[j] = 4;
                                        ComLoc[j] -= 1;
                                        ComStart = strn + ComLoc[j] + ComEnd[j];
                                        if(i==j){/*Last, F Command*/
                                                ComNext = strnLen - (ComLoc[j] + ComEnd[j]);
                                        }
                                        else{/*F Command*/
                                                ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
                                        }
                                        strncpy(from, ComStart, ComNext);
                                        from[ComNext] = '\0';
                                /*}*/
                                break;
                        case 'T':/*T To*/
                                /*if(loggedIn){*/
                                /*Should be passed as T: /FRIENDUSER/ */
                                /*No Output*/
                                        ComEnd[j] = 4;
                                        ComLoc[j] -= 1;
                                        ComStart = strn + ComLoc[j] + ComEnd[j];
                                        if(i==j){/*Last, T Command*/
                                                ComNext = strnLen - (ComLoc[j] + ComEnd[j]);
                                        }
                                        else{/*T Command*/
                                                ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
                                        }
                                        strncpy(to, ComStart, ComNext);
                                        to[ComNext] = '\0';
                                
                                break;
                        case 'M':/*M Message*/
                                /*M*/
                                /*if(loggedIn){*/
                                /*Should be passed as M: /MESSAGE/ requires that F and T commands be placed after M command*/
                                /*No Output*/
                                /*Sent to Display*/
                                       ComEnd[j] = 4;
                                        ComLoc[j] -= 1;
                                        ComStart = strn + ComLoc[j] + ComEnd[j];
                                        if(i==j){/*Last, M Command*/
                                                ComNext = strnLen - (ComLoc[j] + ComEnd[j]);
                                        }
                                        else{/*M Command*/
                                                ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
                                        }
                                        strncpy(newStrn, ComStart, ComNext);
                                        newStrn[ComNext] = '\0';
                                        if(!strcmp(from,userStrn)){
                                                printf("Message Sent Successfuly\n");
                                        }
                                        else if(!strcmp(to,userStrn)){
                                                printf("Dearest %s,\n%s\nSincerly, %s\n",to,newStrn,from);
                                        }
                               
                                break;
                        case 'r':/*Err*/
                                if( ComLoc[j]>=3 && !strncmp(ComRoot-2,"Err",2) ){
                                        /*Err*/
                                        ComEnd[j] = 6;
                                        ComLoc[j] -= 3;
                                        ComStart = strn + ComLoc[j] + ComEnd[j];
                                        if(i==j){/*Last, Err Command*/
                                                ComNext = strnLen - (ComLoc[j] + ComEnd[j]);
                                        }
                                        else{/*Err Comman*/
                                                ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
                                        }
                                        strncpy(newStrn, ComStart, ComNext);
                                        newStrn[ComNext] = '\0';
                                        printf("Error: %s\n",newStrn);
                                }
                                else{
                                        printf("Found no target command\n");
                                        ComEnd[j] = 3;
                                }
                                break;
                        case 'A':/*A Active*/
                                /*A*/
                                if(loggedIn){
                                        /*input A: /USER\nUSER/ */
                                        /*Outputs active users*/
                                        ComEnd[j] = 4;
                                        ComLoc[j] -= 1;
                                        ComStart = strn + ComLoc[j] + ComEnd[j];
                                        if(i==j){/*Last, A Command*/
                                                ComNext = strnLen - (ComLoc[j] + ComEnd[j]);
                                        }
                                        else{/*A Command*/
                                                ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
                                        }
                                        strncpy(newStrn, ComStart, ComNext);
                                        newStrn[ComNext] = '\0';
                                        printf("These are the current active users:\n%s\n",newStrn);
                                }
                                break;
                        case 'C':/*C Contacts*/
                                /*C*/
                                ComEnd[j] = 4;
                                ComLoc[j] -= 1;
                                ComStart = strn + ComLoc[j] + ComEnd[j];
                                if(i==j){/*Last, C Command*/
                                        ComNext = strnLen - (ComLoc[j] + ComEnd[j]);
                                }
                                else{/*C Command*/
                                        ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
                                }
                                Com = 0;
                                for(k = ComStart;k!=ComStart+ComNext;k++){
                                        if(Com>0){/*if / has been found*/
                                                if(Com>1){/*if / and ' ' have been found*/
                                                        if(Com>2){/*if / / has been found*/
                                                                ComUser = k - ComStart - 3;
                                                                break;
                                                        }
                                                        else if(*k =='/'){ Com = 3;     }/*indicate '/' has been found*/
                                                        else{ Com = 0;  }/*no '/' was found so reset Com to begin looking for ':' again*/
                                                }
                                                else if(        *k ==' '){ Com = 2;     }/*indicate ' ' has been found*/
                                                else{         Com = 0;  }/*no ' ' was found so reset Com to begin looking for ':' again*/
                                        }
                                        else if(                *k =='/'){ Com = 1;     }/*indicate '/' has been found*/
                                        else{                 Com = 0; }
                                }
                                if(!loggedIn){
                                        nonLog = 1;
                                }
                                strncpy(userStrn, ComStart, ComUser);
                                strncpy(newStrn, ComStart + ComUser + 3, ComNext - ComUser - 3);
                                userStrn[ComUser] = '\0';
                                newStrn[ComNext] = '\0';
                                if(nonLog){
                                        if(!strcmp(userStrn,DEFAULTNAME)){
       						printf("Sign up successful, please Log in to access your account\n");
                                        }
                                        else{
                                                printf("Login successful\nWelcome %s\n",userStrn);
                                                loggedIn = 1;
                                        }
                                        nonLog = 0;
                                }
                                else{
                                        printf("Here is a list of all your current friends\n%s\n",newStrn);
                                }
                                break;
                        default:/*Empty Command*/
                                printf("Found no target command\n");
                                ComEnd[j] = 3;
                                break;
                }
        }
        /*strcpy(strn,finalStrn);Store return commands where input commands were stored*/
        /*if(loggedIn){
 *                 strcat(strn,"R: /");
 *                                 strcat(strn,userStrn);
 *                                                 strcat(strn,"/");
 *                                                         }*/
        /*printf("Cumulative output:\n\n%s\n\n",strn);*/
        return(loggedIn);
}



