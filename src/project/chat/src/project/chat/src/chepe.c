#define USERSPATH "Database/Usernames/"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <assert.h>
int SetDatabase(void); //create directories: Database, Usernames, File: Login.txt
int AppendMessage(char* user, char* friend, char* message);
char* GetContacts(char* username);
int FolderExists(char* folder);
int CreateFolder(char* folder);
int FileExists(char* file);//don't put in txt as it will be appended
int CreateFile(char* file);
int File2String(char** dest,char *file); //Takes a file and converts it to a string 
char *GetConversation(char *username, char* friend);


void main ()
{
	SetDatabase();
	int b;
	char *a;
	//b=FileExists("hey");
	b=AppendMessage("Kay","A","Nothing, nvm lol");
	printf("%d\n",b);
	a=GetContacts("Kay");
	printf("%s\n",a);
	a=GetConversation("Kay","A");
	printf("%s\n",a);
	
}
char *GetConversation(char *username, char* friend)
{
	char* fname=(char*)malloc(1+strlen(USERSPATH)+strlen(username)+strlen("/")+strlen(friend));
	fname=strcpy(fname,USERSPATH);//This should have the full path + username of sender
	fname=strcat(fname,username);//This should have the full path + username of sender
	if(!FolderExists(fname)) //If the sender's folder doesn't exist then don't get contacts
	{
		free(fname);
		return "Err:/User Doesn't exist/";
	}
	fname=strcat(fname,"/");//Add slash to indicate that we're getting into a directory
	fname=strcat(fname,friend);
	if(!FileExists(fname))//Check to make sure that conversation exists and that we're not reading something else
		return "Err:/Error conversation doesn't exist/";
	fname=strcat(fname,".txt");
	char *conversation="test";
	File2String(&conversation,fname);
	free(fname);
	return conversation;
}
int SetDatabase(void) //create directories: Database, Usernames, File: Login.txt
{
	int result=-2;
	result= result + CreateFolder("Database");
	result= result + CreateFolder("Database/Usernames");
	result= result + CreateFile("Database/Login");
	return result; //Result will be 1 if it successfully created all 3 elements
}
int AppendOneMessage(char* user, char* friend, char* message, char* flag) //This will be called to append some message
{
	FILE *chat;//This will hold the chat history
	char* fname=(char*) malloc(strlen(USERSPATH)+strlen(user)+strlen(friend)+strlen(".txt")+2);//This should have the full path + username of sender
	fname=strcpy(fname,USERSPATH);
	fname=strcat(fname,user);//This should have the full path + username of sender
	if(!FolderExists(fname)) //If the sender's folder doesn't exist then don't append
	{
		free(fname);
		return 0;
	}
	fname=strcat(fname,"/");
	fname=strcat(fname,friend);// This will add the path to the friend's file
	if(!FileExists(fname))//If file doesn't exist, then that means that such friend was never added
	{
		free(fname);
		return 0;
	}
	fname=strcat(fname,".txt");//Now it has full path + username(sender) + friendname + .txt
	chat=fopen(fname,"a"); //This will create file if it doesn't exist
	if(!chat)
	{
		free(fname);
		return 0; //this is in case that file did not opem.
	}
	char* fmessage=(char*)malloc(strlen(flag)+strlen(message)+strlen("/"));
	fmessage=strcpy(fmessage,flag);
	fmessage=strcat(fmessage,"/");
	fmessage= strcat(fmessage,message);
	fmessage=strcat(fmessage,"/");
	fprintf(chat,fmessage);
	fclose(chat);
	free(fname);
	free(fmessage);
	return 1;
}
int AppendMessage(char* sender, char* friend,char* message)
{
	int a=-1;
	a= a+ AppendOneMessage(sender,friend,message,"U:"); //Append to the sender file first with flag U
	a= a+AppendOneMessage(friend,sender,message,"F:");	//Append to the recipient file with flag F (the recipient's friend's message)
	return a;
}
int File2String(char** dest,char *fname) //Takes a file and converts it to a string 
{
	FILE *file;
	file=fopen(fname,"r");
	assert(file); //contacts file should have been created when the user (sender) was SignedUp
	char* fileAsString;
	int counter=0;
	while((fgetc(file))!=EOF) //Get the number of character in file
	{
		counter++;
	}
	counter++;//Add one more that is missing
	fileAsString=(char*) malloc(counter*sizeof(char));
	fseek(file,0,SEEK_SET);
	fgets(fileAsString,counter*(sizeof(char)),file);
//	if(*dest==0) // in case it hasnt been initialized
//	{
		*dest=fileAsString; //pass the pointer to the char given as argument
		fclose(file);
//		return 1;
//	}
/*	else //if dest had already been initialized, we will assume it is the right size to hold the file
	{
		for(int i=0;i<counter;i++) //pass all chars in the FileAsString
		{
			*dest[i]=fileAsString[i];
		}
		free(fileAsString);//get rid of pointer as we wont need it
		fclose(file);
		return 1;
	}
*/	return 1;
}
char* GetContacts(char* username)
{
	char* fname=(char*)malloc(1+strlen(USERSPATH)+strlen(username)+strlen("/Contacts.txt"));//This should have the full path + username of sender
//	fname=strcpy(fname,"./");
	fname=strcpy(fname,USERSPATH);//This should have the full path + username of sender
	fname=strcat(fname,username);//This should have the full path + username of sender
	if(!FolderExists(fname)) //If the sender's folder doesn't exist then don't get contacts
	{
		free(fname);
		return "Err:/User Doesn't exist/";
	}
	fname=strcat(fname,"/Contacts");//Add slash to indicate that we're getting into a directory
	if(!FileExists(fname))//Check to make sure that Contacts.txt exists and that we're not reading something else
		return "Err:/Error when signing up/";
	fname=strcat(fname,".txt");
	char *contacts="hi";
	File2String(&contacts,fname);
	free(fname);
	return contacts;
}
int FolderExists(char* folder)
{
	struct stat st={0};
	if(stat(folder,&st)==-1)
		return 0; //it does not exist
	else
		return 1; //it exists
}
int CreateFolder(char* folder)
{
	struct stat st={0};
	if(stat(folder,&st)==-1)
	{
		mkdir(folder,0700);
		return 1; //Successfully created a new folder
	}
	else
		return 0; //did not create because it already existed
}
int FileExists(char* file)
{
	char *fname=(char*)malloc(strlen(file)+strlen(".txt")+10);
	assert(fname);
	fname=strcpy(fname,file);
	fname=strcat(fname,".txt");
	FILE *somefile=fopen(fname,"r+");
	free(fname);
	if(!somefile)
		return 0; //It doesn't exist
	else
	{
		fclose(somefile);
		return 1;//It exists!
	}
}

int CreateFile(char* file)
{
	if(FileExists(file))
		return 0; //Don't create because it already exists
	char *fname;
	fname=(char*)malloc(strlen(file)+strlen(".txt")+1); //Allocate so we can do string manipulation
	assert(fname);
	fname=strcpy(fname,file);
	fname=strcat(fname,".txt");
	FILE *newFile=fopen(fname,"w");
	assert(newFile);
	fclose(newFile);//Create a new file and return 1;
	free(fname);
	return 1;
}
