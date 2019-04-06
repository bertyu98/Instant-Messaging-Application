#ifndef CONSTANTS_H
#define CONSTANTS_H

#define NAME 12
#define MAXGROUPSIZE 5
#define MAXCMND 20
#define MAXSTRN 256
#define NOTSAID ""
#define INVALIDCOMM "No command matches target"
#define ENABLEOUTPUT 1
#define DEFAULTNAME "Anon"
#define FRIENDS " "
#define MAXMSG 50
#define USERSPATH "Database/Usernames/"

#define SUCCESSFRIEND "Friend request was sent successfully"
#define SUCCESSSIGNUP "Sign up was successful" 
//#define _SVID_SOURCE

#define h_addr h_addr_list[0]

#define ERRCOMM "Err: /No command matches target/"
#define ERRSENDER "Err: /Oops you tried to read someone elses message/"
#define ERRPWD "Err: /Wrong Password/"
#define ERRUSER "Err: /Wrong Username/"
#define ERRREQ_SENT "Err: /Request Already Sent/"
#define ERRREQ_SUCC "Err: /Request Sent Successfuly/"
#define ERRBUSY "Err: /Server Busy Resend Message/"
#define ERRMISMATCH "Err: /User from name mismatch with sender name/"
#define ERRUSER_AE "Err: /Username Already Exists/"
#define ERRUSER_AF "Err: /User is already a friend/"
#define ERRUSER_DNE "Err: /Username Does Not Exists/"

//TESTING FUNCTIONS FOR Database in serCNV
//toggle to 0 for function to disable that field of output
//toggle to 1 for function to send outputs as normal
#define ENABLEGetContacts 1
//^TOP PRIORITY MUST WORK^ b/c used in most other functions
#define ENABLEAppendMessage 1//controls how messages are saved
#define ENABLEServerLogin 1//controls login dirs
#define ENABLEServerSignUp 0//controls sign up dirs
#define ENABLEServerDeleteFriend 1//controls delete friend dirs
#define ENABLEServerAddFriend 0//Controlls mirrored outputs to user
#define ENABLESetDatabase 1//trigger once at start of server.c
#define ENABLEServerActive 1//Hold active contacts if get contacts is also enabled ti will only output active users on friends list
//DEFAULT TESTING OUTPUT
#define UNSAID "OUTPUT DISABLED"

#include <errno.h>
#include <dirent.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <assert.h>

typedef struct SocketNodes SocketNode;
typedef struct SocketSets SocketSet;
struct SocketNodes  /*This will be a socket node*/
{
        int Port;
        char *username;
        SocketNode *next;
        SocketNode *prev;
};
struct SocketSets  /*This will be the head of sockets*/
{
        int NSockets; /*This will hold the number of sockets*/
        SocketNode *First; /*This will be the fisr socket in the list*/
};
#endif
