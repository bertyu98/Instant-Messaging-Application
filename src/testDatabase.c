#include <stdio.h>
#include <string.h>
#define NAME 12
#define MAXGROUPSIZE 5
#define MAXCMND 20
#define MAXSTRN 256
#define UNSAID "output not recieved"//replace with actual function outputs
#define NOTSAID "has no output"
#define INVALIDCOMM "No command matches target\n"
#define ENABLEOUTPUT 1
#define DEFAULTNAME "Anon"
#define ERRPWD "Wrong Password\n"
#define ERRUSER "Wrong Username\n"
#define ERR "\n"
#define ERRUSERAE "Username Already Exists\n"
/*Server Header Files*/
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <strings.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <assert.h>

char* ServerLogin(char* username, char* password);
char* ServerSignUp(char* username, char* password);
char* ServerAddFriend(char* username);
char* ServerDeleteFriend(char* username);



/*int main(int argc, char* argv[]){
 *         ServerLogin("hi", "hello");
 *
 *         }*/


void error(const char* msg);

int main(){
        char* Result;
	Result = ServerSignUp("hi", "hello");
	printf("%s\n", Result);
	//Result = ServerAddFriend("hi");
	//printf("%s\n", Result);
        Result = ServerLogin("hi", "hello");
        printf("%s\n", Result);
}

//char* ServerLogin(char* username, char* password){
//      char Data_uname[NAME] = "0"; /*Usernames from login file*/
//      //      char Data_pwd[NAME] = "0"; /*Passwords from login file*/
//      //      char usercopy[NAME] = "0"; /*copy of username to be manipulated*/
//      //      /*int c;//utility for fgetc*/
//      //      int Filelength = 0;
//      //      DIR *Chat; /*chat directory*/
//      //      DIR *Usernames; FILE *LoginData; /*directory and file in parallel: Different Usernames*/
//      //      DIR *User; /*folder with all user folders*/
//      //      FILE *UserData;/*data for each user*/
//      //      /*Chat = opendir(".");*/
//      //      LoginData = fopen("login.txt", "w+");
//      //      fprintf(LoginData,"hi\n");
//      //      fprintf(LoginData,"hello\n");
//      //      /*continuous loop to run through entire login.txt file until value is returned*/
//      //      /*while(strcmp(Data_uname,"")){*/
//      //      while(feof(LoginData)==0){
//      //              /*getline()*/
//      //              /*get each line in the login data for stored users*/
//      //              fgets(Data_uname, NAME-1, LoginData); /*gets first line for user which is the username*/
//      //              fgets(Data_pwd, NAME-1, LoginData); /*gets second line for user which is the password*/
//      //              if((strcmp(password, Data_pwd) == 0) && (strcmp(username, Data_uname) == 0)){ /*compares login data from text file to what is inputted by user to check for match*/
//      //                      strcpy(usercopy, username); /*copy input string to username copy utilized for concatonation*/
//      //                      UserData = fopen(strcat(usercopy,".txt"), "r"); /*concatonates username copy string to add txt extension to access specified user's files*/
//      //                      while(fgetc(UserData) !=EOF){ /*loop to increment Filelength until it has reached the length of the entire file's contents*/
//      //                              Filelength++;
//      //                      }
//      //                      char GuiInfo[Filelength]; /*give array size of file*/
//      //                      memset( GuiInfo, 0, Filelength*sizeof(char) );
//      //                      fgets(GuiInfo, Filelength, UserData); /*fill array with file data*/
//      //                      fclose(LoginData);
//      //                      fclose(UserData);
//      //                      return GuiInfo; /*return the newly filled array*/
//      //                      /*do{
//      //                              c = fgetc(UserData);
//      //                              if(feof(UserData)){
//      //                                      return b;
//      //                              }
//      //                              b = strcat(b, c);
//      //                      }while(1);*/
//      //              }
//      //      }
//      //      printf("error\n");
//      //      return "Error logging in";
//      //}
void error(const char* msg)
{
    perror(msg);
    exit(0);
}

char* ServerSignUp(char* username, char* password){
	FILE *LoginData;
	FILE *UserData;
//        char Data_uname[NAME] = "0"; /*Usernames from login file*/
        char usercopy[NAME] = "0"; /*copy of username to be manipulated*/
        char usercopy2[NAME] = "0"; /*copy of username to be manipulated*/
        char pwdcopy[NAME] = "0"; /*copy of username to be manipulated*/
	strcpy(usercopy,username);
	strcpy(usercopy2,username);
	strcpy(pwdcopy, password);	

	LoginData = fopen("testlogin.txt", "a");
	strcat(usercopy,"\n");
	strcat(pwdcopy,"\n");
//        while(strcmp(Data_uname,"")){
//        	fgets(Data_uname, NAME-1, LoginData); /*gets first line for user which is the username*/
//        	if((strcmp(usercopy, Data_uname) == 0)){ /*compares login data from text file to what is inputted by user to check for match*/
//			return ERRUSERAE;
//		}
//	}
 
	fprintf(LoginData,"%s\n", username);
	fprintf(LoginData,"%s\n", password);
	UserData = fopen(strcat(usercopy2,".txt"), "w"); /*concatonates username copy string to add txt extension to access specified user's files*/
	fprintf(UserData, "%s\n", username);
	fprintf(UserData, "sly");
	fclose(LoginData);
	fclose(UserData);		
	return "You have signed up!";	

}

char* ServerDeleteFriend(char* username){
	FILE *UserData;
	FILE *LoginData;
        char Data_uname[NAME] = "0"; /*Usernames from login file*/
        char usercopy[NAME] = "0"; /*copy of username to be manipulated*/
	int Filelength = 0;
	strcpy(usercopy,username);
	LoginData = fopen("testlogin.txt", "r");
	        while(strcmp(Data_uname,"")){

        /*while(feof(LoginData)==0){*/
                /*getline()*/

                /*get each line in the login data for stored users*/
                	fgets(Data_uname, NAME-1, LoginData); /*gets first line for user which is the username*/

                	if((strcmp(strcat(usercopy,"\n"), Data_uname) == 0)){ /*compares login data from text file to what is inputted by user to check for match*/
				UserData = fopen(strcat(usercopy,".txt"), "a"); /*concatonates username copy string to add txt extension to access specified user's files*/
				fprintf(UserData,"%s\n", username);
                        	while(fgetc(UserData) !=EOF){ /*loop to increment Filelength until it has reached the length of the entire file's contents*/
                                	Filelength++;
                        	}
                        	printf("%d\n",Filelength);
                        	char GuiInfo[Filelength]; /*give array size of file*/
                        	memset( GuiInfo, 0, Filelength*sizeof(char) );
                        	fgets(GuiInfo, Filelength, UserData); /*fill array with file data*/
                        	printf("%s\n", GuiInfo);
                        	fclose(LoginData);
                        	fclose(UserData);
                        	strcpy(username,GuiInfo);
                        	free(GuiInfo);
                        	return username; /*return the newly filled array*/
				

		}
	}
	return "user does not exist\n";
}
char* ServerAddFriend(char* username){
	FILE *UserData;
	FILE *LoginData;
        char Data_uname[NAME] = "0"; /*Usernames from login file*/
        char Data_pwd[NAME] = "0"; /*Usernames from login file*/
        char usercopy[NAME] = "0"; /*copy of username to be manipulated*/
        char usercopy2[NAME] = "0"; /*copy of username to be manipulated*/
	int Filelength = 0;
	strcpy(usercopy,username);
	strcpy(usercopy2, username);
	LoginData = fopen("testlogin.txt", "r");
	        while(strcmp(Data_uname,"")){

        /*while(feof(LoginData)==0){*/
                /*getline()*/
              
                /*get each line in the login data for stored users*/
                	fgets(Data_uname, NAME-1, LoginData); /*gets first line for user which is the username*/
			printf("%s\n",Data_uname);
			fgets(Data_pwd, NAME-1, LoginData);
                	if((strcmp(strcat(usercopy,"\n"), Data_uname) == 0)){ /*compares login data from text file to what is inputted by user to check for match*/
				UserData = fopen(strcat(usercopy2,".txt"), "a+"); /*concatonates username copy string to add txt extension to access specified user's files*/
				fprintf(UserData,"\n%s", username);
				fclose(UserData);
                		UserData = fopen(usercopy2, "r"); /*concatonates username copy string to add txt extension to access specified user's files*/
                        	while(fgetc(UserData) !=EOF){ /*loop to increment Filelength until it has reached the length of the entire file's contents*/
                                	Filelength++;
                        	}
                        	fclose(UserData);
                        	printf("%d\n",Filelength);
				printf("%s\n", usercopy2);
                		UserData = fopen(usercopy2, "r"); /*concatonates username copy string to add txt extension to access specified user's files*/
                        	char GuiInfo[Filelength]; /*give array size of file*/
                        	memset( GuiInfo, 0, Filelength*sizeof(char) );
                        	printf("%s\n", GuiInfo);
				fread(GuiInfo, sizeof(char), Filelength, UserData);
				username = GuiInfo;
                        	fclose(LoginData);
                        	fclose(UserData);
                        	return username; /*return the newly filled array*/
				

		}
	}
	return "user does not exist\n";
}

//char* ServerDeleteFriend(char* username){
//	FILE *UserData;
//	FILE *LoginData;
//        char Data_uname[NAME] = "0"; /*Usernames from login file*/
//        char Data_pwd[NAME] = "0"; /*Usernames from login file*/
//        char usercopy[NAME] = "0"; /*copy of username to be manipulated*/
//        char usercopy2[NAME] = "0"; /*copy of username to be manipulated*/
//	int Filelength = 0;
//	strcpy(usercopy,username);
//	strcpy(usercopy2, username);
//	LoginData = fopen("testlogin.txt", "r");
//	        while(strcmp(Data_uname,"")){
//
//        /*while(feof(LoginData)==0){*/
//                /*getline()*/
//              
//                /*get each line in the login data for stored users*/
//                	fgets(Data_uname, NAME-1, LoginData); /*gets first line for user which is the username*/
//			printf("%s\n",Data_uname);
//			fgets(Data_pwd, NAME-1, LoginData);
//                	if((strcmp(strcat(usercopy,"\n"), Data_uname) == 0)){ /*compares login data from text file to what is inputted by user to check for match*/
//				UserData = fopen(strcat(usercopy2,".txt"), "a+"); /*concatonates username copy string to add txt extension to access specified user's files*/
//				//need to search through file and find specific username. Then set pointer right on the username and overwrite with 12 blank spaces "            "
//				//fread
//				fseek(UserData,-13,SEEK_END);				
//				fclose(UserData);
//                		UserData = fopen(usercopy2, "r"); /*concatonates username copy string to add txt extension to access specified user's files*/
//                        	while(fgetc(UserData) !=EOF){ /*loop to increment Filelength until it has reached the length of the entire file's contents*/
//                                	Filelength++;
//                        	}
//                        	fclose(UserData);
//                        	printf("%d\n",Filelength);
//				printf("%s\n", usercopy2);
//                		UserData = fopen(usercopy2, "r"); /*concatonates username copy string to add txt extension to access specified user's files*/
//                        	char GuiInfo[Filelength]; /*give array size of file*/
//                        	memset( GuiInfo, 0, Filelength*sizeof(char) );
//                        	printf("%s\n", GuiInfo);
//				fread(GuiInfo, sizeof(char), Filelength, UserData);
//				username = GuiInfo;
//                        	fclose(LoginData);
//                        	fclose(UserData);
//                        	return username; /*return the newly filled array*/
//				
//
//		}
//	}
//	return "user does not exist\n";
//}
//
char* ServerLogin(char* username, char* password){
        char Data_uname[NAME] = "0"; /*Usernames from login file*/
        char Data_pwd[NAME] = "0"; /*Passwords from login file*/
        char usercopy[NAME] = "0"; /*copy of username to be manipulated*/
        char usercopy2[NAME] = "0"; /*copy of username to be manipulated*/
        char passcopy[NAME] = "0"; /*copy of username to be manipulated*/
	//char GuiInfo[3000] = "0";
	strcpy(usercopy, username); /*copy input string to username copy utilized for concatonation*/
        strcpy(passcopy, password); /*copy input string to password copy utilized for concatonation*/
        FILE *LoginData;

        /* To be impletmented in Beta Version*/
        /*int c;//utility for fgetc* */
        int Filelength = 0;
        /*DIR *Chat;*/ /*chat directory*/
        /*DIR *Usernames;       FILE *LoginData;*/ /*directory and file in parallel: Different Usernames*/
        /*DIR *User;*/ /*folder with all user folders*/
        FILE *UserData;/*data for each user*/
        /*Chat = opendir(".");*/
        LoginData = fopen("testlogin.txt", "r");
        /*continuous loop to run through entire login.txt file until value is returned*/
        while(strcmp(Data_uname,"")){

        /*while(feof(LoginData)==0){*/
                /*getline()*/

                /*get each line in the login data for stored users*/
                        	//}
                        	fclose(UserData);
                        	printf("%d\n",Filelength);
				printf("%s\n", usercopy2);
                		UserData = fopen(usercopy2, "r"); /*concatonates username copy string to add txt extension to access specified user's files*/
                        	char GuiInfo[Filelength]; /*give array size of file*/
                        	memset( GuiInfo, 0, Filelength*sizeof(char) );
                        	printf("%s\n", GuiInfo);
				fread(GuiInfo, sizeof(char), Filelength, UserData);
				username = GuiInfo;
                        	fclose(LoginData);
                        	fclose(UserData);
                        	return username; /*return the newly filled array*/
				

		}
	}
	return "user does not exist\n";
}

//char* ServerLogin(char* username, char* password){
//        char Data_uname[NAME] = "0"; /*Usernames from login file*/
//        char Data_pwd[NAME] = "0"; /*Passwords from login file*/
//        char usercopy[NAME] = "0"; /*copy of username to be manipulated*/
//        char usercopy2[NAME] = "0"; /*copy of username to be manipulated*/
//        char passcopy[NAME] = "0"; /*copy of username to be manipulated*/
//	//char GuiInfo[3000] = "0";
//	strcpy(usercopy, username); /*copy input string to username copy utilized for concatonation*/
//        strcpy(passcopy, password); /*copy input string to password copy utilized for concatonation*/
//        FILE *LoginData;
//
//        /* To be impletmented in Beta Version*/
//        /*int c;//utility for fgetc* */
//        int Filelength = 0;
//        /*DIR *Chat;*/ /*chat directory*/
//        /*DIR *Usernames;       FILE *LoginData;*/ /*directory and file in parallel: Different Usernames*/
//        /*DIR *User;*/ /*folder with all user folders*/
//        FILE *UserData;/*data for each user*/
//        /*Chat = opendir(".");*/
//        LoginData = fopen("testlogin.txt", "r");
//        /*continuous loop to run through entire login.txt file until value is returned*/
//        while(strcmp(Data_uname,"")){
//
//        /*while(feof(LoginData)==0){*/
//                /*getline()*/
//
//                /*get each line in the login data for stored users*/
//                fgets(Data_uname, NAME-1, LoginData); /*gets first line for user which is the username*/
//                fgets(Data_pwd, NAME-1, LoginData); /*gets second line for user which is the password*/
//                if((strcmp(strcat(passcopy,"\n"), Data_pwd) == 0) && (strcmp(strcat(usercopy,"\n"), Data_uname) == 0)){ /*compares login data from text file to what is inputted by user to check for match*/
//
//                	strcpy(usercopy2, username); /*copy input string to username copy utilized for concatonation*/
// *     *                                                                                                                                         }
// *      *                                                                                                                                                                         b = strcat(b, c);
// *       *                                                                                                                                                                                                 }while(1);*/
//                }else{
//
//                }
//        }
//        return "Error Logging in";
//}
//
