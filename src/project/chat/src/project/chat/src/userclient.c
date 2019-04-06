#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define NAME 12
#define MAXCMND 20
#define MAXSTRN 256
#define UNSAID "Unspecifed Output\n"
#define NOTSAID ""
#define FRIENDS " "
#define DEFAULTNAME "Anon"

#define h_addr h_addr_list[0]

void encrypt(char* strn);
int CommandCNV(char* strn);
void PrintMenu(int i);
void error(const char *msg);


void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int flop = 0;
    int loggedIn = 0;
    char username[NAME];
    char password[NAME];

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    char command[256];
    int option;
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
    n = write(sockfd, "connect", strlen(buffer));
    n = read(sockfd, buffer, 255);

    #ifndef DEBUG
    /*Enters a username to associate with the socket number*/
    printf("Please enter a username: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    strcpy(username,buffer);
    username[strlen(username)-1] = '\0';
    /*printf("%s\n",username);*/

    printf("Please enter a password: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    strcpy(password,buffer);
    password[strlen(password)-1] = '\0';
    encrypt(password);
    /*printf("%s\n",password);*/
    #endif

   /*Debug Username and Password*/
   #ifdef DEBUG
   strcpy(username, "DEBUG");
   username[strlen(username)-1] = '\0';

   strcpy(password, "DEBUGpassword");
   password[strlen(password)-1] = '\0';
   encrpyt(password);
   #endif

   /*beginning of the menu*/
   option = 0;
   strcpy(command,"");

    while(option != 10){
        PrintMenu(!loggedIn);

        scanf("%d", &option);
    
        /*printf("%d\n", loggedIn);*/
     

                switch(option){
                        /*Sign up */
                        case 1:
                                strcat(command, "SUser: /");
                                strcat(command, username);
                                strcat(command,"/Pwd: /");
                                strcat(command, password);
                                strcat(command, "/");
                                break;

                        /*Log in*/
			case 2:
                                flop = 1;
                                strcat(command, "LUser: /");
                                strcat(command, username);
                                strcat(command,"/Pwd: /");
                                strcat(command, password);
                                strcat(command, "/");                                                                                                                                                                        break;

                        case 3:
                                printf("Please enter a username: ");
                                bzero(buffer,256);
                                fgets(buffer,255,stdin);
                                strncpy(username,buffer,12);
                                username[strlen(username)-1] = '\0';
                                printf("Please enter a password: ");
                                bzero(buffer,256);
                                fgets(buffer,255,stdin);
                                password[strlen(password)-1] = '\0';
                                strncpy(password,buffer,12);
                                bzero(buffer, 256);
                                break;

                        /*Access contact lists*/
                        case 4:
                                strcat(command,"A: /");
                                break;
                       

       		        /*Send messages*/
                        case 5:
                                strcat(command,"M: /");
                                printf("Please enter the messages: ");
                                bzero(buffer,256);
                                scanf("%s", buffer);
                                buffer[strlen(buffer)-1] = '\0';
                                strcat(command, buffer);
                                strcat(command, "/F: /");
                                strcat(command, username);
                                strcat(command, "/T: /");
                                printf("Please enter the username of the recipient: ");
                                bzero(buffer,256);
				char recipient[12];
				scanf("%s", recipient);
                                scanf("%s", buffer);
                                strcat(command, recipient);
                                command[strlen(command)-1] = '\0';
                                strcat(command, "/");
                                break;
 
                       /*Receive messages*/
                        case 6:
                                if(!strcmp(command,"")){
                                        strcat(command,"R: /"); 
                                        strcat(command,username);
                                        strcat(command,"/");
                                }
                                break;

                        default:
                                option = 10;
                                printf("Invalid command");
                                break;
                }
                if(loggedIn){
                        strcat(command,"R: /");
                        strcat(command,username);
                        strcat(command,"/");
               }
                bzero(buffer, 256);
                strcpy(buffer,command);
                n = write(sockfd,buffer, strlen(buffer));
                if ( n < 0)
                        error("ERROR sending command to socket");
                bzero(buffer, 256);
                n = read(sockfd, buffer, 255);
                loggedIn = CommandCNV(buffer);
                if (n < 0)
                        error ("ERROR reading from socket");
                bzero(buffer, 256);
                printf("command input into server:\n%s\n",command);
                strcpy(command,buffer);
                printf("command output from server:\n%s\n",command);
                if(flop){
                        strcpy(buffer,"C: /");
                        strcat(buffer, username);
                        strcat(buffer,"/ /JOSE\nGUY\nAVIK\n/");
                        loggedIn = CommandCNV(buffer);
                        strcpy(command,buffer);
                        flop = 0;
                }
   }

   printf("Now closing...");
   close(sockfd);

return 0;
}

void PrintMenu(int i) {
        
                printf("1: Create Account\n");
                printf("2: Login to Account\n");
                printf("3: Change Login/SignUp Credentials(UNFINISHED)\n");
                /*printf("Other#: Quit\n");*/
              
        
      
                printf("4: Get Contacts\n");
                printf("5: Send Message\n");
                printf("6: Receive Message\n");
                printf("Other#: Quit\n");
        
        printf("Please make your choice: ");
}
void encrypt(char* strn){
        int i;
        for(i = 0;*(strn+i)!='\0';i++){
                *(strn+i)+=2;
        }
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
        /*char finalStrn[MAXSTRN] = "";*/
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
        

return loggedIn;}









