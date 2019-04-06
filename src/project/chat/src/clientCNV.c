#include "user.h" 

int CommandCNV(){
        /*char *person[10];*/
        /*static int loggedIn = 0;*/
/*
 * GLOBALS
//SET&U input	char buffer[MAXSTRN];
//SET	M: /	char message[MAXSTRN];
//SET&U C: /Log	char username[NAME];
//UNTOUCHED//	char password[NAME];
//IDK//		char result[NAME];
//IDK//		char recipient[NAME];
//SET&U	C: /Log	int loggedIn;
//UNTOUCHED//	const char *recipientpointer;
//UNTOUCHED//	const char *usernamepointer;
//SET	C: /	char MyFriends[NAME*10];
//SET	A: /	char ActiveFriends[NAME*10];
//SET	M: /	char LastSender[NAME];
//SET	M: /	char LastReciever[NAME];
//SET	Err: /	char ServerErrMSG[MAXSTRN];

*/	
	MyFriends[0] = '\0';
	ActiveFriends[0] = '\0';
	LastSender[0] = '\0';
	LastReciever[0] = '\0';
	ServerErrMSG[0] = '\0';
	message[0] = '\0';
	
	
		
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
        ComUser = 0;
        int i;
        int j = 0;
        char from[NAME] = "N", to[NAME] = "N"/*, pwd[NAME] = "N"*/;
        for(i = 1;*(buffer+i)!='\0';i++){/*saves the location within the string that a : indication of command appears. It does so for every instance in order inside ComLoc*/
                strnLen++;/*attains the size of the string*/
                if(Com>-1){/*if : has been found*/
                        if(Com>256){/*if : and ' ' have been found*/
                                if(Com>1256){/*if : / has been found*/
                                        ComLoc[j] = Com - 2000;/*stores pos of the ':' in ComLoc*/
                                        Com = -1;/*result stored so reset Com to begin looking for ':' again*/
                                        j++;
                                }
                                else if(*(buffer+i) =='/'){ Com += 1000;  }/*indicate '/' has been found*/
                                else{ Com = -1; }/*no '/' was found so reset Com to begin looking for ':' again*/
                        }
                        else if(        *(buffer+i) ==' '){ Com += 1000;  }/*indicate ' ' has been found*/
                        else{         Com = -1; }/*no ' ' was found so reset Com to begin looking for ':' again*/
                }
                else if(                *(buffer+i) ==':'){ Com = i;      }/*indicate ':' has been found*/
        }
        j--;
        i = j;
        for(;j>=0;j--){
                ComRoot = buffer + ComLoc[j] - 1;
                switch( *ComRoot ){
                        case 'F':/*F From*/
                                /*if(loggedIn){*/
                                        /*Should be passed as F: /USER/ */
                                        /*No Output*/
 ComEnd[j] = 4;
                                        ComLoc[j] -= 1;
                                        ComStart = buffer + ComLoc[j] + ComEnd[j];
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
                                        ComStart = buffer + ComLoc[j] + ComEnd[j];
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
                                        ComStart = buffer + ComLoc[j] + ComEnd[j];
                                        if(i==j){/*Last, M Command*/
                                                ComNext = strnLen - (ComLoc[j] + ComEnd[j]);
                                        }
                                        else{/*M Command*/
                                                ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
                                        }
                                        strncpy(newStrn, ComStart, ComNext);
                                        newStrn[ComNext] = '\0';
                                        if(!strcmp(from,username)){
						strcpy(LastSender,username);
						strcpy(LastReciever,to);
                                                printf("Message Sent Successfuly\n");
                                        }
                                        else if(!strcmp(to,username)){
                                                printf("You, %s , got thisa message:\n%s from: %s",to,newStrn,from);
						strcpy(LastSender,from);
						strcpy(LastReciever,username);
                                        	strcpy(message,newStrn);
					}

                                break;
                        case 'r':/*Err*/
                                if( ComLoc[j]>=3 && !strncmp(ComRoot-2,"Err",2) ){
                                        /*Err*/
                                        ComEnd[j] = 6;
                                        ComLoc[j] -= 3;
                                        ComStart = buffer + ComLoc[j] + ComEnd[j];
                                        if(i==j){/*Last, Err Command*/
                                                ComNext = strnLen - (ComLoc[j] + ComEnd[j]);
                                        }
                                        else{/*Err Comman*/
                                                ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
                                        }
                                        strncpy(newStrn, ComStart, ComNext);
                                        newStrn[ComNext] = '\0';
                                        printf("Error: %s\n",newStrn);
					strcpy(ServerErrMSG,newStrn);
				}
                                else{
                                        printf("Found no target command\n");
                                        ComEnd[j] = 3;
                                }
                                break;
                        case 'A':/*A Active*/
                                /*A*/
                                /*input A: /USER\nUSER/ */
                                /*Outputs active users*/
                                ComEnd[j] = 4;
                                ComLoc[j] -= 1;
                                ComStart = buffer + ComLoc[j] + ComEnd[j];
                                if(i==j){/*Last, A Command*/
                                        ComNext = strnLen - (ComLoc[j] + ComEnd[j]);
                                }
                                else{/*A Command*/
                                        ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
                                }
                                strncpy(newStrn, ComStart, ComNext);
                                newStrn[ComNext] = '\0';
                                printf("These are the current active users:\n%s\n",newStrn);
				strcpy(ActiveFriends,newStrn);
                                break;
                        case 'C':/*C Contacts*/
                                /*C*/
                                ComEnd[j] = 4;
                                ComLoc[j] -= 1;
                                ComStart = buffer + ComLoc[j] + ComEnd[j];
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
						strcpy(username,userStrn);
                                               	printf("Login successful\nWelcome %s\n",username);
                                               	loggedIn = 1;
                                        }
                                        nonLog = 0;
                                }
                                else{
                                        printf("Here is a list of all your current friends\n%s\n",newStrn);
                                	strcpy(MyFriends,newStrn);
				}
                                break;
                        default:/*Empty Command*/
                                printf("Found no target command\n");
                                ComEnd[j] = 3;
                                break;
                }
	}
	return loggedIn;
}




	
