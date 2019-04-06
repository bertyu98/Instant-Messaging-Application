#ifndef DATABASE_H
#define DATABASE_H
/*#include "stdio.h"
#include "string.h"*/
/*Server Header Files*/
/*#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <strings.h>
#include <netdb.h>
#include <arpa/inet.h>
//#include "SocketList.h"
#include <assert.h>
#include <errno.h>
#include <dirent.h>
*/
#include "Constants.h"
char* ServerSignUp(char* username, char* password);
char* ServerAddFriend(char* username, char* friend); //

int SetDatabase(void); //create directories: Database, Usernames, File: Login.txt Called only once
char *GetConversation(char *username, char* friend); //Retrieves a conversation from username (sender) with his friend
int AppendMessage(char* user, char* friend, char* message); //This will be the "send" a message function, will append a new message to both, the user and friend with their respectively flaggs
char* GetContacts(char* username); //This will return the contacts  list as a pointer string
int FolderExists(char* folder); //Used only by database . checks if a folder exists
int CreateFolder(char* folder);// used only by databse
int FileExists(char* file);//used only by database
int CreateFile(char* file);//used only by database
int File2String(char** dest,char *file); //used only by database. Takes a file name (name should include path) and converts it to a string 
char* ServerDeleteFriend(char* username, char* friend);
char* StringRemove(char *str,char *word);
char* ServerLogin(char* username, char* password);



//Should check if the folder Fusername exists
//if it doesnt return username ERRUSER_DNE
//
//Should check in the folder usernames for Fusername_pnd.txt
//if it exists return username's friends list
//and change the name of Fusername_pnd.txt to Fusername.txt
//and add username.txt to the folder Fusername
//
//Should check in the folder Fusernames for username_pnd.txt
//if it exists return ERRREQ_SENT
//else add username_pnd.txt to thier folder
//
//*OPTIONAL*
//Should check in usernames folder for Fusername.txt
//if it exists return ERRUSER_AF
//should check in the folder usernames for Fusername.txt and Fusername_pnd.txt
//if any of these text files exist delete them
//
//should check in the folder Fusernames for username.txt and username_pnd.txt
//if any of these text files exist delete them
#endif
