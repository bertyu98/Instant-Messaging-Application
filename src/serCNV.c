#include "serCNV.h"
char *strnstr(char* hay, char* needle,int maxlen,int minlen){	
	maxlen -= minlen - 1;
	while(maxlen > 0 && *hay){
		if(!strncmp(hay, needle, minlen)){
			return hay;
		}
		hay++;
		maxlen--;
	}
	return NULL;
}
char* ServerActive(char* newName, SocketSet* ActiveSet, int currClient){
	SocketNode* node;
	SocketNode* nextnode = ActiveSet->First;
	char newStrn[MAXSTRN] = "A: /";
	char contacts[MAXSTRN];
	char* STRING;
	if(ENABLEGetContacts){
		STRING = GetContacts(contacts);
		strncpy(contacts,STRING,strlen(STRING));
	}
	int first = 1;
	while(nextnode!=NULL){
		node = nextnode;
		nextnode = node->next;
		if(ENABLEGetContacts||
		strnstr(contacts,
		node->username,
		strlen(contacts),
		strlen(node->username))){
			if(first){
				strcat(newStrn," ");
				first = 0;
			}
			strcat(newStrn, node->username);
		}
	}
	strcat(newStrn,"/");
	return newName;
}
void RenameNode(char* newName, SocketSet* TotalSet, SocketSet* ActiveSet, int currClient){
/*	SocketNode* node;
	SocketNode* endnode;
	int newPort = GetPort("noname",ActiveSet);
	if(newPort != -1){
		node = ActiveSet->First;
		for(endnode = node;node->username==newName||NULL!=endnode;){
			endnode = node->next;
			if(!endnode)
				node = endnode;
			}
		node->username = newName;
	}
*/
}
int CommandCNV(char* strn, char* CurrentName, SocketSet* set, int currClient)
{
	//GetPort(currClient,set);
	/*strn is the main input and output of string which will hold the commands from the buffer*/
	printf("COMM INPUT : %s\n",strn);
	/*SocketNode* node;
	SocketNode* endnode;
*/	int port;
	/*
	int newPort = -1;
	if(CurrentName[0]!='\0')
		port = GetPort(CurrentName,set);
	if(port == -1)
		newPort = GetPort("noname",set);*/
	char* STRING;
	char newName[MAXSTRN] = DEFAULTNAME;
	int strnLen = 0;/*length of command string length*/
	int Com = -1;/*looks looks for a ':' then a ' ' then a '/'*/
	int ComLoc[MAXCMND] = {0};/*location with respect to strn of start of command*/
	char ComEnd[MAXCMND];/*location with respect to comLoc of end of command*/
	char newStrn[MAXSTRN] = "";/*string that the contents of commands or the return from a serverFunction*/
	char tmpStrn[MAXSTRN+4];/*string that temporarily holds command processes*/
	char finalStrn[MAXSTRN] = "";/*ending output command intended for client*/
	char *start,/* *middle, *midend,*/ *end;/*pointers to start and end of a T: / command called by the R: / command*/
	char *ComRoot;/*pointer to last letter of command name*/
	char *ComStart;/*pointer to first character of command contents*/
	int ComNext;/*number of characters between current command and the one that follows*/
	int i;
	int j = 0;/*holds the array position of which command to operate on*/
	"
	static char messStor[MAXSTRN] = "";/*pending messages are stored here*/
	
	char from[NAME] = "N", to[NAME] = "N", pwd[NAME] = "N";/*temporarily stored values for the F: / T: / and Pwd: / commands*/
	for(i = 1;*(strn+i)!='\0';i++)
	{/*saves the location within the string that a : indication of command appears. It does so for every instance in order inside ComLoc*/
		strnLen++;/*attains the size of the string*/
		if(Com>-1)
		{/*if : has been found*/
			if(Com>256)
			{/*if : and ' ' have been found*/
				if(Com>1256)
				{/*if : / has been found*/
					ComLoc[j] = Com - 2000;/*stores pos of the ':' in ComLoc*/
					Com = -1;/*result stored so reset Com to begin looking for ':' again*/
					j++;
				}
				else if(*(strn+i) =='/'){ Com += 1000;	}/*indicate '/' has been found*/
				else{ Com = -1;	}/*no '/' was found so reset Com to begin looking for ':' again*/
			}
			else if(	*(strn+i) ==' '){ Com += 1000;	}/*indicate ' ' has been found*/
			else{	      Com = -1;	}/*no ' ' was found so reset Com to begin looking for ':' again*/
		}
		else if(		*(strn+i) ==':'){ Com = i;	}/*indicate ':' has been found*/
	}
	j--;
	i = j;
	for(;j>=0;j--)
	{
		ComRoot = strn + ComLoc[j] - 1;
		switch( *ComRoot )
		{
			case 'F'://F From
				//Should be passed as F: /USER/
				//No Output
				ComEnd[j] = 4;
				ComLoc[j] -= 1;
				ComStart = strn + ComLoc[j] + ComEnd[j];
				if(i==j)
				{//Last, F Command
					ComNext = strnLen - (ComLoc[j] + ComEnd[j]); 
				}
				else
				{//F Command
					ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
				}
				strncpy(from, ComStart, ComNext);
				from[ComNext] = '\0';/*at this point newStrn holds the contents of the command*/		
				break;
			case 'T'://T To
				//Should be passed as T: /FRIENDUSER/
				//OR ONCE GROUP MESSAGING IMPLIMENTED:
				//	T: /FRIENDUSER\nOTHERFRIENDUSER/
				//No Output
				ComEnd[j] = 4;
				ComLoc[j] -= 1;
				ComStart = strn + ComLoc[j] + ComEnd[j];
				if(i==j)
				{//Last, T Command
					ComNext = strnLen - (ComLoc[j] + ComEnd[j]); 
				}
				else
				{//T Command
					ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
				}
				strncpy(to, ComStart, ComNext);
				to[ComNext] = '\0';/*at this point newStrn holds the contents of the command*/
						
				break;
			case 'M'://M Message
				//M
				//Should be passed as M: /MESSAGE/ requires that F and T commands be placed after M command
				//Output as M: /MESSAGE/ requires that F and T commands be placed after M command
				ComEnd[j] = 4;
				ComLoc[j] -= 1;
				ComStart = strn + ComLoc[j] + ComEnd[j];
				if(i==j)
				{//Last, M Command
					ComNext = strnLen - (ComLoc[j] + ComEnd[j]); 
				}
				else
				{//M Command
					ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
				}
				strncpy(newStrn, ComStart, ComNext);
				newStrn[ComNext] = '\0';/*at this point newStrn holds the contents of the command*/
				
				printf("Message--> %s\tFrom: %s\tTo: %s\n",newStrn,from,to);
				//MODIFY newStrn

				if(!strcmp(messStor,""))
				{
					
					strcpy(messStor,"M: /");//rebuilding message
					strcat(messStor,newStrn);
					strcat(messStor,"/T: /");
					strcat(messStor,to);
					strcat(messStor,"/F: /");
					strcat(messStor,from);
					strcat(messStor,"/");
					
					strcat(finalStrn,messStor);//Command to add command to list of commands
					printf("Message<-- %s\n",messStor);
					
					port = GetPort(to,set);
					if(port==-1){
						printf("User is not online message will not be printed\n");
					}
					else{
						write(port,messStor,strlen(messStor));
					}
					if(ENABLEAppendMessage){
						//Storing data
						strcpy(tmpStrn,"F: ");
						strcat(tmpStrn,newStrn);
						/////////////////////
						AppendMessage(to,from,tmpStrn);
						/////////////////////
						strcpy(tmpStrn,"U: ");
						strcat(tmpStrn,newStrn);
						/////////////////////
						AppendMessage(from,to,tmpStrn);
						/////////////////////
						bzero(messStor,MAXSTRN);
						//messStor[0] = '\0';
					}
				}
				else
				{
					strcat(finalStrn,ERRBUSY);
				}
				break;
			case 'R'://R Recieve
				//R
				//Should be passed as R: //
				//Allow USER to recieve commands
				//Output as M: /MESSAGE/ requires that F and T commands be placed after M command
				ComEnd[j] = 4;
				ComLoc[j] -= 1;
				strcpy(newStrn, CurrentName);
							
				printf("Read--%s--> \n",newStrn);
				if(strcmp(messStor,""))
				{
					start =	strstr(messStor,"/T: /") + 5;
					end =	strstr(start,"/F: /");
					if(!strnstr(start,",",end - start,strlen(newStrn))){/*if not group message*/
						if(!strncmp(newStrn, start, end - start))
						{
							/////////
							/////////
							printf("Message<-- %s\n",messStor);
							strcat(finalStrn,messStor);//Command to add command to list of commands
							messStor[0] = '\0';/*clear static message buffer*/
						}
						else
						{
							strcat(finalStrn,ERRSENDER);//Error Message not meant for you
							newStrn[0] = '\0';//not my message dont modify message
						}
					}
					else{//GROUP MESSAGING COMMENT OUT IF NOT IN CLIENT
					printf("group message\n");
				//		middle = strnstr(start,newStrn,end - start,strlen(newStrn));//middle is the location of the newStrn in mess stor
				//		if(middle!=NULL){
				//			strcpy(newStrn,messStor);
				//			midend = strnstr(middle,",",end - middle,1);/*find if there is a ',' after the name and where it is*/
				//			strncpy(tmpStrn,messStor,middle - messStor);
				//			if(midend!=NULL){/*are there any names after this one*/
				//				midend++;
				//				strcat(tmpStrn,midend);/*if there are skip this name and its ',' character and copy the rest of the command*/
				//			}
				//			else{/*if not skip the name and opy the rest of the string*/
				//				strcat(tmpStrn,end);
				//			}
				//			strcpy(messStor,tmpStrn);
				//			/*recalculate start midend and end*/
				//			start = strstr(messStor,"/T: /") + 5;
				//			midend = strnstr(start,",",end - start,1);//middle is the location of the newStrn in mess stor
				//			if(midend == NULL){
				//				end =	strstr(start,"/F: /");
				//			}
				//			else{
				//				end = midend;
				//			}
				//			strncpy(NextName,start,end - start);//specify a person who the message can be sent to
				//		}
				//		else{
				//			newStrn[0] = '\0';//not my message dont modify message
				//		}
						//UNTESTED ATTEMPT AT GROUP MESSEGEING
					}
				}
				else
				{
					//printf("No message for you\n");
					newStrn[0] = '\0';/*no message dont modify message*/
				}	
				break;
			case 'r'://LUser//SUser//Err
				if(ComLoc[j]>=5 && !strncmp(ComRoot-3,"User",3) )
				{
					if( *(ComRoot-4) == 'L' )
					{
						//LUser
						//Should be passed as LUser: /USERNAME/ Be sure to pass Pwd after
						//Should return Contacts in C: /USERNAME/ /USERNAME\nUSERNAME\nUSERNAME/
						ComEnd[j] = 8;
						ComLoc[j] -= 5;
						ComStart = strn + ComLoc[j] + ComEnd[j];
						if(i==j)
						{//Last, LUser Command
							ComNext = strnLen - (ComLoc[j] + ComEnd[j]); 
						}
						else
						{//LUser Command
							ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
						}
						strncpy(newStrn, ComStart, ComNext);
						newStrn[ComNext] = '\0';/*at this point newStrn holds the contents of the command*/
						
						strcpy(newName,newStrn);
						/////////////////
						if(ENABLEServerLogin){
							STRING = ServerLogin(newStrn,pwd);
							strncpy(tmpStrn,STRING,strlen(STRING));
							if(!strcmp(tmpStrn,"Err:/Successful login/")){
								STRING = GetContacts(newStrn);
								strncpy(newStrn,STRING,strlen(STRING));
							}
							else{
								strcpy(newStrn,tmpStrn);
							}//strcpy(newStrn,STRING);	
							//endr = -1;
							//do{
							//	endr++;
							//	newStrn[endr] = *STRING + endr;
							//}while(STRING!='\0');
							//printf("******* %s *******",STRING);
						}
						else
							strcpy(newStrn,UNSAID);//Delete When ServerLogin Implimented
						/////////////////
						if(strcmp(newStrn,ERRPWD)&&strcmp(newStrn,ERRUSER))
						{
							//if nonode is the name of the port change it to newName
							/*if(newPort != -1){
								node = set->First;
								for(endnode = node;node->username==newName||NULL!=endnode;){
									endnode = node->next;
									if(!node)
										node = endnode;
								}
								node->username = newName;
							}
							*/
							strcpy(tmpStrn,"C: /");
							strcat(tmpStrn,newName);
							strcat(tmpStrn,"/ /");
							strcat(tmpStrn,newStrn);//***********DEPENDANT on ServerLogin
							strcat(tmpStrn,"/");
							strcat(finalStrn,tmpStrn);//Command to add command to list of commands
							printf("%s\n",tmpStrn);//Modify newStrn
						}
						else
						{
							strcat(finalStrn,newStrn);
							printf("%s\n",newStrn);//Modify newStrn
						}
					}
					else if( *(ComRoot-4) == 'S' )
					{
						//SUser
						//Should be passed as SUser: /USERNAME/ Be sure to pass Pwd after
						//Should return Contacts in C: /USERNAME/ /USERNAME\nUSERNAME\nUSERNAME/
						ComEnd[j] = 8;
						ComLoc[j] -= 5;
						ComStart = strn + ComLoc[j] + ComEnd[j];
						if(i==j)
						{//Last, SUser Command
							ComNext = strnLen - (ComLoc[j] + ComEnd[j]); 
						}
						else
						{//SUser Command
							ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
						}
						strncpy(newStrn, ComStart, ComNext);
						newStrn[ComNext] = '\0';/*at this point newStrn holds the contents of the command*/

						strcpy(newName,newStrn);

						printf("SUser--> %s\tPwd %s\n",newStrn,pwd);
						
						strcpy(tmpStrn,newStrn);
						/////////////
						if(ENABLEServerSignUp){
							STRING = ServerSignUp(tmpStrn,pwd);
							//STRING = GetContacts(newStrn);
							strncpy(tmpStrn,STRING,strlen(STRING));
						}
						else
							strcpy(tmpStrn,UNSAID);//Delete this string when SignUp impimented
						/////////////
						if(strcmp(tmpStrn,ERRUSER_AE))
						{
							strcpy(newStrn,"C: /");
							strcat(newStrn,DEFAULTNAME);
							strcat(newStrn,"/ /");
							strcat(newStrn,tmpStrn);//***********DEPENDANT on server function
							strcat(newStrn,"/");
							strcat(finalStrn,newStrn);//Command to add command to list of commands
							printf("%s\n",newStrn);//Modify newStrn
						}
						else
						{
							strcat(finalStrn,tmpStrn);
							printf("%s\n",tmpStrn);//Modify newStrn
						}
					}
					else
					{
						strcat(finalStrn,ERRCOMM);
						printf("%s\n",ERRCOMM);
						ComEnd[j] = 3;
					}
				}
			case 'l'://Del
				if( ComLoc[j]>=3 && !strncmp(ComRoot-2,"Del",2) )
				{
					//Del
					//Should be passed as Del: /USERNAME/
					//Output C: /USERNAME/ /FUSERNAME\nFUSERNAME\n.../
					ComEnd[j] = 6;
					ComLoc[j] -= 3;
					ComStart = strn + ComLoc[j] + ComEnd[j];
					if(i==j)
					{//Last, Del Command
						ComNext = strnLen - (ComLoc[j] + ComEnd[j]); 
					}
					else
					{//Del Command
						ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
					}
					strncpy(newStrn, ComStart, ComNext);
					newStrn[ComNext] = '\0';/*at this point newStrn holds the contents of the command*/

					printf("Del--%s--> %s\n",CurrentName,newStrn);//Where to delete st
					//***********Del
					if(ENABLEServerDeleteFriend){
						STRING = ServerDeleteFriend(tmpStrn,newStrn);
						//STRING = GetContacts(newStrn);
						strncpy(tmpStrn,STRING,strlen(STRING));
					}
					else
						strcpy(tmpStrn,UNSAID);
					/////////////////
					strcpy(newStrn,"C: /");
					strcat(newStrn,CurrentName);
					strcat(newStrn,"/ /");
					strcat(newStrn,tmpStrn);/*commant this line out once server command is working*/
					strcat(newStrn,"/");
					strcat(finalStrn,newStrn);//Command to add command to list of commands
					printf("%s\n",newStrn);
				}
				break;
			case 'd'://Add//Pwd
				if( ComLoc[j]>=3 )
				{
					if( !strncmp(ComRoot-2,"Add",2) )
					{
						//Add
						//Should be passed as Add: /USERNAME/
						//Output C: /USERNAME/ /FUSERNAME\nFUSERNAME\n.../
						ComEnd[j] = 6;
						ComLoc[j] -= 3;
						ComStart = strn + ComLoc[j] + ComEnd[j];
						if(i==j)		
						{//Last, Add Command
							ComNext = strnLen - (ComLoc[j] + ComEnd[j]); 
						}
						else
						{//Add Command
							ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
						}
						strncpy(newStrn, ComStart, ComNext);
						newStrn[ComNext] = '\0';/*at this point newStrn holds the contents of the command*/
						
						printf("Add--%s--> %s\n",CurrentName,newStrn);
						strcpy(tmpStrn,CurrentName);
						//************Add
						if(ENABLEServerAddFriend){
							STRING = ServerAddFriend(tmpStrn,newStrn);
							//STRING = GetContacts(newStrn);
							strncpy(tmpStrn,STRING,strlen(STRING));
						}
						else
							strcpy(tmpStrn,UNSAID);/*commant this line out once server command is working*/
						/////////////////
						if(!strcmp(tmpStrn, ERRUSER_DNE)
						|| !strcmp(tmpStrn, ERRREQ_SENT)
						|| !strcmp(tmpStrn, ERRUSER_AF)
						|| !strcmp(tmpStrn, ERRREQ_SUCC) ){
							strcat(finalStrn,tmpStrn);
							printf("%s\n",tmpStrn);
						}
						else{
							
							strcpy(newStrn,"C: /");
							strcat(newStrn,CurrentName);
							strcat(newStrn,"/ /");
							strcat(newStrn,tmpStrn);
							strcat(newStrn,"/");
							port = GetPort(newStrn,set);
							///////////////
							if(ENABLEGetContacts)
							{
								STRING = GetContacts(newStrn);
								strncpy(newStrn,STRING,strlen(STRING));
							}
							else
								strcpy(newStrn,UNSAID);
							//////////////
							write(port,newStrn,strlen(newStrn));
						}
						strcat(finalStrn,newStrn);//Command to add command to list of commands
						printf("%s\n",newStrn);//Modify newStrn
					}
					else if( !strncmp(ComRoot-2,"Pwd",2) )
					{
						//Pwd
						//Should be passed as Pwd: /PASSWORD/
						//No Output
						ComEnd[j] = 6;
						ComLoc[j] -= 3;
						ComStart = strn + ComLoc[j] + ComEnd[j];
						if(i==j)
						{//Last, Pwd Command
							ComNext = strnLen - (ComLoc[j] + ComEnd[j]); 
						}
						else
						{//Pwd Command
							ComNext = ComLoc[j+1] - 1 - (ComLoc[j] + ComEnd[j]);
						}
						strncpy(pwd, ComStart, ComNext);
						pwd[ComNext] = '\0';/*at this point pwd holds the contents of the command*/
					}
				}
				else{
					strcat(finalStrn,ERRCOMM);
					printf("%s\n",ERRCOMM);
					ComEnd[j] = 3;	
				}
				break;
			case 'A'://A Active, Different from Client Active
				//Should be passed as A: //
				//Should be recieved as A: /ActiveClients,ActiveClient\n.../
				//A
				strcpy(tmpStrn,CurrentName);
				printf("A--%s-->\n",CurrentName);
				//********Active
				if(ENABLEServerActive){
					STRING = ServerActive(tmpStrn,set,currClient);
					//STRING = GetContacts(newStrn);
					strncpy(tmpStrn,STRING,strlen(STRING));
				}
				else
					strcpy(tmpStrn,UNSAID);//REPLACE when serverActive finished
				////////////////
				strcpy(newStrn,"A: /");
				strcat(newStrn,tmpStrn);/*commant this line out once server command is working*/
				strcat(newStrn,"/");
				strcat(finalStrn,newStrn);//Command to add command to list of commands
				printf("A<-- %s\n",newStrn);
				break;
			default://Empty Command
				strcat(finalStrn,ERRCOMM);
				printf("%s\n",ERRCOMM);	
				ComEnd[j] = 3;
				break;
		}
	}
	int slen;
//	if(currClient==-1){
//		printf("user was not assigned to port during action");
//	}
	if(ENABLEOUTPUT){
		bzero(strn,257);
		strcpy(strn,finalStrn);//Store return commands where input commands were stored
		for(slen = 0;*(strn+slen)!='\0';slen++){}//Get len of strn
		printf("Port: %d\nStrn: %s\nStringlen: %d\n",currClient,strn,slen);
		write(currClient,strn,slen);
	}
	else
		strn[0] = '\0';
	
	printf("COMM OUTPUT: %s\n",strn);
	
	if(strcmp(newName,DEFAULTNAME))
		strcpy(CurrentName,newName);
	else
		CurrentName[0] = '\0';
/*
	if(strn[0] != '\0')
		printf("COMM OUTPUT: %s\n",strn);
	if(CurrentName[0] != '\0')
	//if(CurrentName != NULL)
		printf("USER OUTPUT: %s\n",CurrentName);
	if(Destination[0] != '\0')
	//if(Destination != NULL)
		printf("DEST OUTPUT: %s\n",Destination);
*/
	int ret = (strcmp(messStor,"")?(1):(0));/*return of function 0 indicates there is no message waiting to be sent 1 indicates that there is a message to be sent*/
	printf("FUNC RETURN: %d\n\n",ret);
	return ret;
}

