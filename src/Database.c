#include "Database.h"
//int SignUpExists(char *username) //Returns 1 if username exists, 0 if not
//{
//	FILE *login;
//	login=fopen("/Database/Login.txt","r");
//	if(!login) //check to see if login.txt exists
//		return 0; //if file does not exists, then user also doesnt
//	int namelength=strlen(username);//Get the size of username
//	char *pointer;
//	fread(pointer,namelength,,login);
//	while(
//}
<<<<<<< Database.c
char* ServerSignUp(char* username, char* password){
        FILE *LoginData;
        FILE *UserData;
        char usercopy[NAME] = "0"; /*copy of username to be manipulated*/
        char usercopy2[NAME] = "0"; /*copy of username to be manipulated*/
        char pwdcopy[NAME] = "0"; /*copy of username to be manipulated*/
	char UserDataPath = USERSPATH;
	
//	char Data_uname[NAME] = "0";
        strcpy(usercopy,username);
        strcpy(usercopy2,username);
        strcpy(pwdcopy, password);
        LoginData = fopen("Database/Login.txt", "a");
        strcat(usercopy,"\n");
        strcat(pwdcopy,"\n");
	
        while(strcmp(Data_uname,"")){
        	fgets(Data_uname, NAME-1, LoginData); /*gets first line for user which is the username*/
        	if((strcmp(usercopy, Data_uname) == 0)){ /*compares login data from text file to what is inputted by user to check for match*/
			return ERRUSERAE;
		}
	}
        fprintf(LoginData,"%s\n", username);
        fprintf(LoginData,"%s\n", password);
        UserData = fopen(strcat(usercopy2,".txt"), "w"); /*concatonates username copy string to add txt extension to access specified user's files*/
        fprintf(UserData, "%s\n", username);
        fprintf(UserData, "sly");
        fclose(LoginData);
        fclose(UserData);
        return SUCCESSSIGNUP;

}

char* ServerLogin(char* username, char* password){
        char Data_uname[NAME] = "0"; /*Usernames from login file*/
        char Data_pwd[NAME] = "0"; /*Passwords from login file*/
        char usercopy[NAME] = "0"; /*copy of username to be manipulated*/
        char usercopy2[NAME] = "0"; /*copy of username to be manipulated*/
        char passcopy[NAME] = "0"; /*copy of username to be manipulated*/
	strcpy(usercopy, username); /*copy input string to username copy utilized for concatonation*/
        strcpy(passcopy, password); /*copy input string to password copy utilized for concatonation*/
        FILE *LoginData;

        /* To be impletmented in Beta Version*/
        int Filelength = 0;
        FILE *UserData;/*data for each user*/
        LoginData = fopen("login.txt", "r");
        /*continuous loop to run through entire login.txt file until value is returned*/
        while(strcmp(Data_uname,"")){


                /*get each line in the login data for stored users*/
                fgets(Data_uname, NAME-1, LoginData); /*gets first line for user which is the username*/
                fgets(Data_pwd, NAME-1, LoginData); /*gets second line for user which is the password*/
                if((strcmp(strcat(passcopy,"\n"), Data_pwd) == 0) && (strcmp(strcat(usercopy,"\n"), Data_uname) == 0)){ /*compares login data from text file to what is inputted by user to check for match*/

                	strcpy(usercopy2, username); /*copy input string to username copy utilized for concatonation*/
                	UserData = fopen(strcat(usercopy2,".txt"), "r"); /*concatonates username copy string to add txt extension to access specified user's files*/
			while(fgetc(UserData) !=EOF){ /*loop to increment Filelength until it has reached the length of the entire file's contents*/
                                Filelength++;
                        }
			fclose(UserData);
                	UserData = fopen(usercopy2, "r"); /*concatonates username copy string to add txt extension to access specified user's files*/
                        char GuiInfo[Filelength]; /*give array size of file*/
                        memset( GuiInfo, 0, Filelength*sizeof(char) );
			fread(GuiInfo, sizeof(char), Filelength, UserData);   
                        username = GuiInfo;
                        fclose(LoginData);
                	UserData = fopen(usercopy2, "r"); /*concatonates username copy string to add txt extension to access specified user's files*/
                        //char GuiInfo[Filelength]; /*give array size of file*/
                        memset( GuiInfo, 0, Filelength*sizeof(char) );	
			fread(GuiInfo, sizeof(char), Filelength, UserData);
                        username = GuiInfo;
                        fclose(LoginData);
                        fclose(UserData);
                        return username; /*return the newly filled array*/

                }else if((strcmp(passcopy,Data_pwd) == 0) && (strcmp(usercopy,Data_uname) !=0)){
                        strcpy(username, ERRUSER);
                        return username;
                }else if((strcmp(strcat(usercopy,"\n"),Data_uname) == 0) && (strcmp(strcat(passcopy,"\n"),Data_pwd) !=0)){
                        strcpy(username, ERRPWD);
                        return username;
                }else{

                }
        }
        return "Error Logging in";
}


char* ServerAddFriend(char* username, char* friend){
	FILE *UserData;
	FILE *FriendData;
	FILE *PendingData;
	char PendingFriendPath[256] = USERSPATH; // Database/Usernames/
	strcat(PendingFriendPath, friend); // Database/Usernames/friend
	char FriendDataPath[256] = PendingFriendPath; // Database/Usernames/friend
	char UserDataPath[256] = USERSPATH; // Database/Usernames/
	strcat(UserDataPath, username); // Database/Usernames/username
	char UserDataPath2[256] = UserDataPath; // Database/Usernames/username
	strcat(UserDataPath, "/"); // Database/Usernames/username/
	strcat(PendingFriendPath, "/"); // Database/Usernames/friend/
        char Data_uname[NAME] = "0"; /*Usernames from login file*/
        char Data_uname2[NAME] = "0"; /*Usernames from login file*/
        char Data_pwd[NAME] = "0"; /*Usernames from login file*/
        char usercopy[NAME] = "0"; /*copy of username to be manipulated*/
        char usercopy2[NAME] = "0"; /*copy of username to be manipulated*/
        char useGUI.o GUI2.o  -Wall -ansi -O2 `pkg-config --libs gtk+-2.0` -g -o GUI
gcc GUI2.o -Wall -ansi -O2 `pkg-config --libs gtk+-2.0` -c -o GUI2
gcc: GUI2.o: linker input file unused because linking not done
gcc -Wall -std=c99 -c -g server.c -o server.o
server.c: In function ‘main’:
server.c:143: warning: passing argument 3 of ‘CommandCNV’ from incompatible pointer type
serCNV.h:22: note: expected ‘struct SocketSet *’ but argument is of type ‘char *’
server.c:143: warning: passing argument 4 of ‘CommandCNV’ makes integer from pointer without a cast
serCNV.h:22: note: expected ‘int’ but argument is of type ‘struct SocketSet *’
server.c:143: error: too many arguments to function ‘CommandCNV’
server.c:144: warning: the address of ‘CurrName’ will never be NULL
make: *** [server.o] Error 1
[yubb@zuma src]$ ./GUI bondi 8989
Welcome to the server!
HERE IS THE INITIAL SOCKET NUMBER: 3
hulk
piiop
wcopy3[NAME] = "0"; /*copy of username to be manipulated*/
        char friendcopy[NAME] = "0"; /*copy of iusername to be manipulated*/
        char friendcopy2[NAME] = "0"; /*copy of iusername to be manipulated*/
	int Filelength = 0;
	strcpy(friendcopy, friend); //friend
	strcpy(friendcopy2, friend); //friend
	strcpy(friendcopy3, friend); //friend
	strcat(friendcopy2, "_pnd"); //friend_pnd	
	
	if(FileExists(strcat(UserDataPath, friendcopy2)) == 1){
		remove(strcat(UserDataPath, ".txt"));
		FriendData = fopen(strcat(FriendDataPath,".txt"),"a");
		UserData = fopen(strcat(UserDataPath2,".txt"),"a");
		fprintf(FriendData,",%s",username);  
		fprintf(UserData,",%s",friend);
		fclose(FriendData);
		fclose(UserData);
		return GetContacts(username);  
	}
	LoginData = fopen("Database/login.txt", "r")
	while(strcmp(Data_uname,"")){
		fgets(Data_uname, NAME-1, LoginData);
		fgets(Data_pwd, NAME-1, LoginData);
		if(strcmp(strcat(friendcopy3,"\n"),Data_uname ) == 0){
			UserData = fopen(strcat(FriendData
			while(strcmp(Data_uname2,"")){
				fgets(Data_uname2, NAME-1, UserData);
			
		else if(EOF){
			return ERRUSER_DNE;
		}
			PendingData = fopen(PendingFriendPath,"a");
			fprintf(PendingData, ",%s", username);
			return SUCCESSFRIEND;
		}else if( ) {
			return ERRUSER_AF;
		}else if( ==EOF{
			return ERRUSER_DNE;		
		}else{
			continue;	
		}		

}
char* ServerDeleteFriend(char* username, char* friend){
	return username;
}
=======
//
//char* ServerSignUp(char* username, char* password){
//        FILE *LoginData;
//        FILE *UserData;
//        char usercopy[NAME] = "0"; /*copy of username to be manipulated*/
//        char usercopy2[NAME] = "0"; /*copy of username to be manipulated*/
//        char pwdcopy[NAME] = "0"; /*copy of username to be manipulated*/
//	char UserDataPath = USERSPATH;
//	
////	char Data_uname[NAME] = "0";
//        strcpy(usercopy,username);
//        strcpy(usercopy2,username);
//        strcpy(pwdcopy, password);
//        LoginData = fopen("Database/Login.txt", "a");
//        strcat(usercopy,"\n");
//        strcat(pwdcopy,"\n");
//	
//        while(strcmp(Data_uname,"")){
//        	fgets(Data_uname, NAME-1, LoginData); /*gets first line for user which is the username*/
//        	if((strcmp(usercopy, Data_uname) == 0)){ /*compares login data from text file to what is inputted by user to check for match*/
//			return ERRUSERAE;
//		}
//	}
//        fprintf(LoginData,"%s\n", username);
//        fprintf(LoginData,"%s\n", password);
//        UserData = fopen(strcat(usercopy2,".txt"), "w"); /*concatonates username copy string to add txt extension to access specified user's files*/
//        fprintf(UserData, "%s\n", username);
//        fprintf(UserData, "sly");
//        fclose(LoginData);
//        fclose(UserData);
//        return SUCCESSSIGNUP;
//
//}
//
//char* ServerLogin(char* username, char* password){
//        char Data_uname[NAME] = "0"; /*Usernames from login file*/
//        char Data_pwd[NAME] = "0"; /*Passwords from login file*/
//        char usercopy[NAME] = "0"; /*copy of username to be manipulated*/
//        char usercopy2[NAME] = "0"; /*copy of username to be manipulated*/
//        char passcopy[NAME] = "0"; /*copy of username to be manipulated*/
//	strcpy(usercopy, username); /*copy input string to username copy utilized for concatonation*/
//        strcpy(passcopy, password); /*copy input string to password copy utilized for concatonation*/
//        FILE *LoginData;
//
//        /* To be impletmented in Beta Version*/
//        int Filelength = 0;
//        FILE *UserData;/*data for each user*/
//        LoginData = fopen("login.txt", "r");
//        /*continuous loop to run through entire login.txt file until value is returned*/
//        while(strcmp(Data_uname,"")){
//
//
//                /*get each line in the login data for stored users*/
//                fgets(Data_uname, NAME-1, LoginData); /*gets first line for user which is the username*/
//                fgets(Data_pwd, NAME-1, LoginData); /*gets second line for user which is the password*/
//                if((strcmp(strcat(passcopy,"\n"), Data_pwd) == 0) && (strcmp(strcat(usercopy,"\n"), Data_uname) == 0)){ /*compares login data from text file to what is inputted by user to check for match*/
//
//                	strcpy(usercopy2, username); /*copy input string to username copy utilized for concatonation*/
//                	UserData = fopen(strcat(usercopy2,".txt"), "r"); /*concatonates username copy string to add txt extension to access specified user's files*/
//			while(fgetc(UserData) !=EOF){ /*loop to increment Filelength until it has reached the length of the entire file's contents*/
//                                Filelength++;
//                        }
//			fclose(UserData);
//                	UserData = fopen(usercopy2, "r"); /*concatonates username copy string to add txt extension to access specified user's files*/
//                        char GuiInfo[Filelength]; /*give array size of file*/
//                        memset( GuiInfo, 0, Filelength*sizeof(char) );
//			fread(GuiInfo, sizeof(char), Filelength, UserData);   
//                        username = GuiInfo;
//                        fclose(LoginData);
//                	UserData = fopen(usercopy2, "r"); /*concatonates username copy string to add txt extension to access specified user's files*/
//                        //char GuiInfo[Filelength]; /*give array size of file*/
//                        memset( GuiInfo, 0, Filelength*sizeof(char) );	
//			fread(GuiInfo, sizeof(char), Filelength, UserData);
//                        username = GuiInfo;
//                        fclose(LoginData);
//                        fclose(UserData);
//                        return username; /*return the newly filled array*/
//
//                }else if((strcmp(passcopy,Data_pwd) == 0) && (strcmp(usercopy,Data_uname) !=0)){
//                        strcpy(username, ERRUSER);
//                        return username;
//                }else if((strcmp(strcat(usercopy,"\n"),Data_uname) == 0) && (strcmp(strcat(passcopy,"\n"),Data_pwd) !=0)){
//                        strcpy(username, ERRPWD);
//                        return username;
//                }else{
//
//                }
//        }
//        return "Error Logging in";
//}
//
//
//char* ServerAddFriend(char* username, char* friend){
//	FILE *UserData;
//	FILE *FriendData;
//	FILE *PendingData;
//	char PendingFriendPath[256] = USERSPATH; // Database/Usernames/
//	strcat(PendingFriendPath, friend); // Database/Usernames/friend
//	char FriendDataPath[256] = PendingFriendPath; // Database/Usernames/friend
//	char UserDataPath[256] = USERSPATH; // Database/Usernames/
//	strcat(UserDataPath, username); // Database/Usernames/username
//	char UserDataPath2[256] = UserDataPath; // Database/Usernames/username
//	strcat(UserDataPath, "/"); // Database/Usernames/username/
//	strcat(PendingFriendPath, "/"); // Database/Usernames/friend/
//        char Data_uname[NAME] = "0"; /*Usernames from login file*/
//        char Data_uname2[NAME] = "0"; /*Usernames from login file*/
//        char Data_pwd[NAME] = "0"; /*Usernames from login file*/
//        char usercopy[NAME] = "0"; /*copy of username to be manipulated*/
//        char usercopy2[NAME] = "0"; /*copy of username to be manipulated*/
//        char usercopy3[NAME] = "0"; /*copy of username to be manipulated*/
//        char friendcopy[NAME] = "0"; /*copy of iusername to be manipulated*/
//        char friendcopy2[NAME] = "0"; //copy of iusername to be manipulated
//	int Filelength = 0;
//	strcpy(friendcopy, friend); //friend
//	strcpy(friendcopy2, friend); //friend
//	strcpy(friendcopy3, friend); //friend
//	strcat(friendcopy2, "_pnd"); //friend_pnd	
//	
//	if(FileExists(strcat(UserDataPath, friendcopy2)) == 1){
//		remove(strcat(UserDataPath, ".txt"));
//		FriendData = fopen(strcat(FriendDataPath,".txt"),"a");
//		UserData = fopen(strcat(UserDataPath2,".txt"),"a");
//		fprintf(FriendData,",%s",username);  
//		fprintf(UserData,",%s",friend);
//		fclose(FriendData);
//		fclose(UserData);
//		return GetContacts(username);  
//	}
//	LoginData = fopen("Database/login.txt", "r")
//	while(strcmp(Data_uname,"")){
//		fgets(Data_uname, NAME-1, LoginData);
//		fgets(Data_pwd, NAME-1, LoginData);
//		if(strcmp(strcat(friendcopy3,"\n"),Data_uname ) == 0){
//			UserData = fopen(strcat(FriendData
//			while(strcmp(Data_uname2,"")){
//				fgets(Data_uname2, NAME-1, UserData);
//			
//		else if(EOF){
//			return ERRUSER_DNE;
//		}
//			PendingData = fopen(PendingFriendPath,"a");
//			fprintf(PendingData, ",%s", username);
//			return SUCCESSFRIEND;
//		}else if( ) {
//			return ERRUSER_AF;
//		}else if( ==EOF{
//			return ERRUSER_DNE;		
//		}else{
//			continue;	
//		}		
//
//}
//char* ServerDeleteFriend(char* username, char* friend){
//	return username;
//}
>>>>>>> 1.11


//char* ServerLogin(char* username, char* password){
//	char Data_uname[NAME] = "0"; /*Usernames from login file*/
//	char Data_pwd[NAME] = "0"; /*Passwords from login file*/
//	char usercopy[NAME] = "0"; /*copy of username to be manipulated*/
//	char usercopy2[NAME] = "0"; /*copy of username to be manipulated*/
//	char passcopy[NAME] = "0"; /*copy of username to be manipulated*/
//	
//	strcpy(usercopy, username); /*copy input string to username copy utilized for concatonation*/
//	strcpy(passcopy, password); /*copy input string to password copy utilized for concatonation*/
//	FILE *LoginData; 
//	
//	/* To be impletmented in Beta Version*/
//	/*int c;//utility for fgetc* */
//	int Filelength = 0;
//	/*DIR *Chat;*/ /*chat directory*/
//	/*DIR *Usernames;	FILE *LoginData;*/ /*directory and file in parallel: Different Usernames*/ 
//	/*DIR *User;*/ /*folder with all user folders*/
//	FILE *UserData;/*data for each user*/
//	/*Chat = opendir(".");*/
//	LoginData = fopen("login.txt", "r");
//	/*continuous loop to run through entire login.txt file until value is returned*/
//	while(strcmp(Data_uname,"")){
//	
//	/*while(feof(LoginData)==0){*/
//		/*getline()*/
//		
//		/*get each line in the login data for stored users*/
//		fgets(Data_uname, NAME-1, LoginData); /*gets first line for user which is the username*/
//
//		fgets(Data_pwd, NAME-1, LoginData); /*gets second line for user which is the password*/
//		if((strcmp(strcat(passcopy,"\n"), Data_pwd) == 0) && (strcmp(strcat(usercopy,"\n"), Data_uname) == 0)){ /*compares login data from text file to what is inputted by user to check for match*/
//			
//			strcpy(usercopy2, username); /*copy input string to username copy utilized for concatonation*/
//			UserData = fopen(strcat(usercopy2,".txt"), "r"); /*concatonates username copy string to add txt extension to access specified user's files*/
//			while(fgetc(UserData) !=EOF){ /*loop to increment Filelength until it has reached the length of the entire file's contents*/
//				Filelength++;			
//			}
//			printf("%d\n",Filelength);
//			char GuiInfo[Filelength]; /*give array size of file*/ 
//			memset( GuiInfo, 0, Filelength*sizeof(char) );
//			fgets(GuiInfo, Filelength, UserData); /*fill array with file data*/
//			printf("%s\n", GuiInfo);
//			fclose(LoginData);			fclose(UserData);
//			return GuiInfo; /*return the newly filled array*/ 
//		
//		}else if((strcmp(passcopy,Data_pwd) == 0) && (strcmp(usercopy,Data_uname) !=0)){
//			strcpy(username, ERRUSER);
//			return username;
//		}else if((strcmp(strcat(usercopy,"\n"),Data_uname) == 0) && (strcmp(strcat(passcopy,"\n"),Data_pwd) !=0)){
//			strcpy(username, ERRPWD);
//			return username;
//			
//
///* code to be implemented in Beta*/
//
//			/*strcpy(usercopy2, username);*/ /*copy input string to username copy utilized for concatonation*/
//			/*UserData = fopen(strcat(usercopy2,".txt"), "r");*/ /*concatonates username copy string to add txt extension to access specified user's files*/
//			/*while(fgetc(UserData) !=EOF){*/ /*loop to increment Filelength until it has reached the length of the entire file's contents*/
//			/*	Filelength++;			
//			}
//			printf("%d\n",Filelength);
//			char GuiInfo[Filelength];*/ /*give array size of file*/ 
//			/*memset( GuiInfo, 0, Filelength*sizeof(char) );*/
//			/*fgets(GuiInfo, Filelength, UserData);*/ /*fill array with file data*/
//			/*printf("%s\n", GuiInfo);
//			fclose(LoginData);			fclose(UserData);
//			return GuiInfo;*/ /*return the newly filled array*/ 
//			/*do{
//				c = fgetc(UserData); 
//				if(feof(UserData)){
//					return b;
//				}
//				b = strcat(b, c);
//			}while(1);*/	
//		}else{
//			
//		}			
//	}
//	return "Error Logging in";			
//}


//HERE THEY START

char* ServerLogin(char* username, char* password)
{
	char* fname=(char*)malloc(sizeof(char)*100);
	fname=strcpy(fname,"Database/");
	fname=strcat(fname,"Login.txt");
	char* login;
	File2String(&login,fname);
	if(!strstr(login,username))
		return "Err:/Username incorrect/";
	char* tmp;
	tmp=strstr(login,username);
	if(!strstr(tmp,password))
		return "Err:/Password incorrect/";
	return "Err:/Successful login/";
}
char* ServerDeleteFriend(char* username, char* friend) //This will delete "Friend" from the username as a friend
{
	char* usernameD=(char*) malloc(sizeof(char)*50);
	usernameD=strcpy(usernameD,USERSPATH);
	usernameD=strcat(usernameD,username);//This should contain the PathtoUsers+username (path to username directory)
	if(!FolderExists(usernameD))
	{
		free(usernameD);
		return "Err:/User Doesn't exist/";
	}
	usernameD=strcat(usernameD,"/Contacts");
	if(!FileExists(usernameD))
	{
		free(usernameD);
		return "Err:/Database Contacts.txt doesn't exist/";
	}
	usernameD=strcat(usernameD,".txt");
	///Delete from sender first
	char *tmp=(char*)malloc(sizeof(char)*100);
	assert(tmp);
	tmp=strcpy(tmp,",");
	tmp=strcat(tmp,friend);
	char* contacts;
	char* newContacts;
	File2String(&contacts,usernameD);
	if(!strstr(contacts,friend))//If the user doesnt have friend as in contacts
	{
		free(usernameD);
		free(tmp);
		return "Err:/Contact doesn't exist/";
	}
	newContacts=StringRemove(contacts,tmp);
	fopen(usernameD,"w");//Delete the content of contacts
	FILE* fileC=fopen(usernameD,"r+");
	fprintf(fileC,newContacts);
	fclose(fileC);
	//Delete from friend next
	usernameD=strcpy(usernameD,USERSPATH);
	usernameD=strcat(usernameD,friend);//This should contain the PathtoUsers+username (path to username directory)
	if(!FolderExists(usernameD))
	{
		free(tmp);
		free(usernameD);
		return "Err:/User Doesn't exist/";
	}
	usernameD=strcat(usernameD,"/Contacts");
	if(!FileExists(usernameD))
	{
		free(tmp);
		free(usernameD);
		return "Err:/Database Contacts.txt doesn't exist/";
	}
	usernameD=strcat(usernameD,".txt");
	tmp=strcpy(tmp,",");
	tmp=strcat(tmp,username);
	File2String(&contacts,usernameD);
	newContacts=StringRemove(contacts,tmp);
	fopen(usernameD,"w");//Delete the content of contacts
	fileC=fopen(usernameD,"r+");
	fprintf(fileC,newContacts);
	fclose(fileC);
	free(tmp);
	free(usernameD);
	return GetContacts(username);
}
char* StringRemove(char *str,char *word)
{
    int i, j = 0, k = 0,n = 0;
    int flag = 0;
   /* char str[100]*/ 
   char* new=(char*) malloc(strlen(str));
    for(i = 0 ; str[i] != '\0' ; i++)
    {
        k = i;
        while(str[i] == word[j])
        {
            i++,j++;
            if(j == strlen(word))
            {
                flag = 1;
                break;
            }
        }
    j = 0;
    if(flag == 0)
        i = k;      
    else
        flag = 0;
    new[n++] = str[i];
    }
    new[n] = '\0';
    return new;
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
