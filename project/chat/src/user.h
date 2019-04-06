#ifndef USER_H
#define USER_H
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
#include <gtk/gtk.h>
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
int loggedIn;
const char *recipientpointer;
const char *usernamepointer;
char MyFriends[NAME*10];
char ActiveFriends[NAME*10];
char LastSender[NAME];
char LastReciever[NAME];
char ServerErrMSG[MAXSTRN];
char *CONTACTLIST;
char contacts;


char *MESSAGEPOINTER;
char *FROMPOINTER;
char *TOPOINTER;
char *USERPOINTER;
char *PASSWORDPOINTER;
char messagevalue;
char fromvalue;
char tovalue;
char uservalue;
char passwordvalue;






void encrypt(char* strn);
void sendmessage(char  *username, char *recipient, char *message, int sockfd);
int login(char  *username, char  *password, int sockfd);
void signup(char *username, char  *password, int sockfd);
void error(const char *message);
int CommandCNV();
/*void nonblock(int sockfd);*/
GdkPixbuf *load_pixbuf_from_file (const char *filename);
GdkPixbufAnimation *load_pixbuf_animation_from_file (const char *filename);
void open_dialog(GtkWidget *button,gpointer window);
void open_dialogSignUp(GtkWidget *button,gpointer window);
int login_button (GtkButton *button, GObject *context_object);
int signup_button (GtkButton *button, GObject *context_object);
char LOGIN_SCREEN(int sockfd, int argc, char **argv);
const gchar *messaging (GtkButton *button,GObject *context_object);
const gchar *add_click(GtkButton *button,GObject *context_object);
const gchar *delete_click (GtkButton *button, GObject *context_object);
const gchar *send_click(GtkButton *button, GObject *context_object);
void addfriend_click(GtkButton *button,GObject *context_object);
void back_click(GtkButton *button, GObject *context_object);
char **split_string(char *str, const char a_delim);
int CHAT(int argc, char **argv, int sockfd, char *us);
void UpdateWindow(void);
void FatalError(const char *ErrorMsg);
void getuser(char *buffer);
void getmessage(char *buffer);

#endif

