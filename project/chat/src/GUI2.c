
#define _SVID_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <assert.h>
#include "user.h"
#define MAXMSG 50
/*max contacts is squared*/
#define MAXCONTACTS 4
const char *Program
	= NULL;


const gchar *messaging(GtkButton *button, GObject *context_object){
	GtkWidget *chatview = g_object_get_data(context_object,"chat");
	const gchar *text = gtk_button_get_label(GTK_BUTTON(button));
	GtkTextIter start, end;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chatview));
	gtk_text_buffer_get_start_iter(buffer,&start);
	gtk_text_buffer_get_end_iter(buffer,&end);
	gchar text2[100];
	int c;
     
	/*g_object_set_data(G_OBJECT(chatview),"recipient",text); 
*/
	recipientpointer = text;
	c = sprintf(text2,"\nYou are now chatting with %s.",text);
	g_print("%s\n",text2);
	gtk_text_buffer_insert(buffer,&end,text2,-1);
	return text;	
}


/*GdkPixbuf *load_pixbuf_from_file(const char *filename)
{
	GError *error = NULL;
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	
	if (pixbuf == NULL)
	{
		g_print("Error loading file: %d : %s\n", error->code, error->message);
		g_error_free(error);
		exit(1);	

	}
	return pixbuf;

}
*/
const gchar *add_click(GtkButton *button,GObject *context_object){
	GtkEntry *searchbar = g_object_get_data(context_object,"searchbar");
	GtkWidget *window = g_object_get_data(context_object,"window3");
	GtkWidget *vbox = g_object_get_data(context_object,"vbox");
	const gchar *text = gtk_entry_get_text(searchbar);
	GList *children, *iter;
	GtkWidget* contacts[MAXCONTACTS][MAXCONTACTS];
	children = gtk_container_get_children(GTK_CONTAINER(vbox));
	int i =0;
	int j=0;
	for(iter = children; iter != NULL; iter = g_list_next(iter))	
	{
		contacts[i][j] = g_object_get_data(context_object,"contacts");
		j++;

	
	if(j== MAXCONTACTS){
				
		i++;
		j=0;
	}

}
g_list_free(children);	
	/*or if user does not exist*/
	if (strcmp(text,"")== 0){
		GtkWidget *dialog,*label;
		dialog = gtk_dialog_new_with_buttons("Dialog",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
		label = gtk_label_new("Invalid user");
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,0,0,0);
		gtk_widget_show_all(dialog);
		gint response = gtk_dialog_run(GTK_DIALOG(dialog));
		if(response == GTK_RESPONSE_OK)
			g_print("OK is pressed \n ");
		else
			g_print("Cancel is pressed \n");
		gtk_widget_destroy(dialog);

	}
	children = gtk_container_get_children(GTK_CONTAINER(vbox));
	int flag = 0;
	for(iter = children; iter != NULL; iter = g_list_next(iter))
	{
		if(strcmp(gtk_button_get_label(GTK_BUTTON(iter->data)),text)== 0){
			GtkWidget *dialog1,*label1;
			flag = 1;
			dialog1 = gtk_dialog_new_with_buttons("Dialog",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
			label1 = gtk_label_new("User is already added");
			gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog1)->vbox),label1,0,0,0);
			gtk_widget_show_all(dialog1);
			gint response = gtk_dialog_run(GTK_DIALOG(dialog1));
			if(response == GTK_RESPONSE_OK)
				g_print("OK is pressed \n ");
			else
				g_print("Cancel is pressed \n");
			gtk_widget_destroy(dialog1);
			return NULL;
		}
		
	}
	g_list_free(children);	
	i =0;
	j=0;
	children = gtk_container_get_children(GTK_CONTAINER(vbox));

	for(iter = children; iter != NULL; iter = g_list_next(iter))	
	{
		if(g_list_next(g_list_next(iter)) == NULL){
			if (j == MAXCONTACTS -1){
				j = 0;
				contacts[i+1][j] = gtk_button_new_with_label(text);
				gtk_box_pack_start(GTK_BOX(vbox),contacts[i+1][j],1,1,0);
				g_signal_connect(GTK_BUTTON(contacts[i+1][j]),"clicked",G_CALLBACK(messaging),contacts[i][j]);
				gtk_widget_show(contacts[i+1][j]);
				break;	
			}
			else if(j < MAXCONTACTS -1){
				contacts[i][j+1] = gtk_button_new_with_label(text);
				gtk_box_pack_start(GTK_BOX(vbox),contacts[i][j+1],1,1,0);
				g_signal_connect(GTK_BUTTON(contacts[i][j+1]),"clicked",G_CALLBACK(messaging),contacts[i][j]);
				gtk_widget_show(contacts[i][j+1]);
				break;
			}
	

		}
		j++;

	
	if(j== MAXCONTACTS){
				
		i++;
		j=0;
	}

	}
	g_list_free(children);		
	
	g_print("%s is added\n",text);	
	return text;
	
}
const gchar *delete_click(GtkButton *button,GObject *context_object){
	GtkEntry *searchbar = g_object_get_data(context_object,"searchbar2");
	GtkWidget *window = g_object_get_data(context_object,"window4");
	GtkWidget *vbox = g_object_get_data(context_object,"vbox1");

	const gchar *text = gtk_entry_get_text(searchbar);
	GList *children, *iter;
				

	/*if (strcmp(text,"")== 0){
		GtkWidget *dialog,*label;
		dialog = gtk_dialog_new_with_buttons("Dialog",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
		label = gtk_label_new("Invalid user");
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,0,0,0);
		gtk_widget_show_all(dialog);
		gint response = gtk_dialog_run(GTK_DIALOG(dialog));
		if(response == GTK_RESPONSE_OK)
			g_print("OK is pressed \n ");
		else
			g_print("Cancel is pressed \n");
		gtk_widget_destroy(dialog);
		return NULL

	}*/

	/*text contains the name of the friend to be deleted until freed*/
	/*g_free(text);*/
	children = gtk_container_get_children(GTK_CONTAINER(vbox));
	
	for(iter = children; iter != NULL; iter = g_list_next(iter))
	{
		if(strcmp(gtk_button_get_label(GTK_BUTTON(iter->data)),text)== 0){
			gtk_widget_destroy(GTK_WIDGET(iter->data));
			
		}
		/*if(strcmp(gtk_button_get_label(GTK_BUTTON(iter->data)),text) != 0){
			GtkWidget *dialog1,*label1;
			dialog1 = gtk_dialog_new_with_buttons("Dialog",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
			label1 = gtk_label_new("Invalid user");
			gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog1)->vbox),label1,0,0,0);
			gtk_widget_show_all(dialog1);
			gint response = gtk_dialog_run(GTK_DIALOG(dialog1));
			if(response == GTK_RESPONSE_OK)
				g_print("OK is pressed \n ");
			else
				g_print("Cancel is pressed \n");
			gtk_widget_destroy(dialog1);
			return NULL;
		}*/

	}
	g_list_free(children);		
	g_print("%s is removed.\n",text);
	return text;


}


const gchar *send_click(GtkButton *button, GObject *context_object){
	
	GtkWidget *window = g_object_get_data(context_object,"window2");
	GtkWidget *chatbox = g_object_get_data(context_object,"chatbox2");
	GtkWidget *chatview = g_object_get_data(context_object,"chat");

	int *temp1 = g_object_get_data(context_object,"sockfd");        
/*	char *usertemp = g_object_get_data(context_object,"username");
*/

        int a = *temp1;


	/*printf("\nHERE IS THE USER: %s", usertemp);
*/

	char *fakeptr;

	char *recptemp = recipientpointer;


	gtk_text_view_set_editable(GTK_TEXT_VIEW(chatview),TRUE);
	PangoFontDescription *font_desc = NULL;
	font_desc = pango_font_description_from_string("Serif 20");
	GtkTextIter start,end;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chatbox));	
	GtkTextBuffer *buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chatview));
	gtk_text_buffer_get_start_iter(buffer,&start);
	gtk_text_buffer_get_end_iter(buffer,&end);
	gtk_text_iter_forward_chars(&start,MAXMSG);
	gtk_text_buffer_delete(buffer,&start,&end);
/*prepend a sring*/	
	gchar *text;
	gchar *text_temp = "\nME:";
	gtk_text_buffer_get_bounds(buffer,&start,&end);
	text = gtk_text_buffer_get_text(buffer,&start,&end,FALSE);

  /*      printf("\nHere's the usernamepointer:");
        g_print(usernamepointer);
        printf("\nHere's the recipientpointer:");
        g_print(recipientpointer);
*/	if(recipientpointer == NULL){
	 	GtkWidget *dialog,*label;
		dialog = gtk_dialog_new_with_buttons("Dialog",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
		label = gtk_label_new("Please click on a contact before sending.");
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,0,0,0);
		gtk_widget_show_all(dialog);
		gint response = gtk_dialog_run(GTK_DIALOG(dialog));
		if(response == GTK_RESPONSE_OK)
			g_print("OK is pressed \n ");
		else
			g_print("Cancel is pressed \n");
		gtk_widget_destroy(dialog);
		return NULL;
		

	}
	
	printf("\nmessage about to be sent");

	sendmessage(fakeptr, recipientpointer, text, a);

/*	char massage[256];

	int n = read(a, massage, 255);

                if (n < 0)
                        error("ERROR reading from socket");


	printf("\nmessage %s sent!", massage);
*/
/*	USERPOINTER = usertemp;
*/	recipientpointer = recptemp;
/*
        printf("\nHere's the usernamepointer2:");
	g_print(usernamepointer);
	printf("\nHere's the recipientpointer2:");
	g_print(recipientpointer);
*/
	size_t len = strlen(text_temp);
	size_t i;
	memmove(text+len,text,strlen(text)+1);
	for(i=0;i<len;++i){
		text[i] = text_temp[i];
	}
	/*strcat(text,"\n");
	*/	if (strcmp(text,"\nME:")== 0){
		GtkWidget *dialog,*label;
		dialog = gtk_dialog_new_with_buttons("Dialog",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
		label = gtk_label_new("Please enter a message before sending.");
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,0,0,0);
		gtk_widget_show_all(dialog);
		gint response = gtk_dialog_run(GTK_DIALOG(dialog));
		if(response == GTK_RESPONSE_OK)
			g_print("OK is pressed \n ");
		else
			g_print("Cancel is pressed \n");
		gtk_widget_destroy(dialog);
		return NULL;

	}
	g_print("%s\n",text);
	gtk_text_buffer_delete(buffer,&start,&end);
	GtkTextIter start2, end2;
	gtk_text_buffer_get_start_iter(buffer2,&start2);
	gtk_text_buffer_get_end_iter(buffer2,&end2);
	gtk_text_buffer_insert(buffer2,&end2,text,-1);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(chatview),FALSE);

	return text;
	
}




void addfriend_click(GtkButton *button, GObject *context_object){
	GtkWidget *window = g_object_get_data(context_object,"window");
	GtkWidget *add_button = g_object_get_data(context_object,"add");
	GtkWidget *delete_button = g_object_get_data(context_object,"delete");
	GtkWidget *search = g_object_get_data(context_object,"search");
	GtkWidget *send = g_object_get_data(context_object,"send");
	GtkWidget *chatbox = g_object_get_data(context_object,"chatbox");
	GtkWidget *back = g_object_get_data(context_object,"back");
	GtkWidget *addfriend = g_object_get_data(context_object,"addfriend");
	GtkWidget *chat = g_object_get_data(context_object,"chat");
	GdkPixbuf *image;
	GdkPixmap *background;	
	GtkStyle *style;
	image = load_pixbuf_from_file("add-scrn.gif");
	gtk_widget_hide(GTK_WIDGET(chat));
	gtk_widget_hide(GTK_WIDGET(addfriend));
	gtk_widget_show(GTK_WIDGET(add_button));
	gtk_widget_show(GTK_WIDGET(delete_button));
	gtk_widget_show(GTK_WIDGET(search));
	gtk_widget_show(GTK_WIDGET(back));
	gtk_widget_hide(GTK_WIDGET(send));
	gtk_widget_hide(GTK_WIDGET(chatbox));
	gdk_pixbuf_render_pixmap_and_mask(image,&background,NULL,0);
	style = gtk_style_new();
	style->bg_pixmap[0] = background;

	gtk_widget_set_style(GTK_WIDGET(window),NULL);
	gtk_widget_set_style(GTK_WIDGET(window),GTK_STYLE(style));
		
}
void back_click(GtkButton *button, GObject *context_object){
	GtkWidget *window = g_object_get_data(context_object,"window5");
	GtkWidget *add_button = g_object_get_data(context_object,"add2");
	GtkWidget *delete_button = g_object_get_data(context_object,"delete2");
	GtkWidget *search = g_object_get_data(context_object,"search2");
	GtkWidget *send = g_object_get_data(context_object,"send2");
	GtkWidget *chatbox = g_object_get_data(context_object,"chatbox2");
	GtkWidget *back = g_object_get_data(context_object,"back");	
	GtkWidget *addfriend = g_object_get_data(context_object,"addfriend2");
	GtkWidget *chat = g_object_get_data(context_object,"chat");
	GdkPixbuf *image;
	GdkPixmap *background2;	
	GtkStyle *style2;
	image = load_pixbuf_from_file("messaging-scrn.gif");
	gtk_widget_hide(add_button);
	gtk_widget_hide(delete_button);
	gtk_widget_hide(search);
	gtk_widget_hide(back);
	gtk_widget_show(send);
	gtk_widget_show(chatbox);
	gtk_widget_show(addfriend);
	gtk_widget_show(chat);
	gdk_pixbuf_render_pixmap_and_mask(image,&background2,NULL,0);
	style2 = gtk_style_new();
	style2->bg_pixmap[0] = background2;

/*	gtk_widget_set_style(GTK_WIDGET(window),GTK_STYLE(background2));
*/	gtk_widget_set_style(GTK_WIDGET(window),NULL);
	gtk_widget_set_style(GTK_WIDGET(window),GTK_STYLE(style2));

}
char **split_string(char *str,const char a_delim){
	char **result = 0;
	size_t count = 0;
	char *tmp = str;
	char *last_newline = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;
	while(*tmp){
		if(a_delim == *tmp){

			count++;
			last_newline = tmp;
		}

		tmp++;

	}
	/*space for trail token*/
	count +=last_newline < (str + strlen(str)-1);
	count ++;
	
	result = malloc(sizeof(char*) *count);
	if(result){
		size_t idx = 0;
		char *token = strtok(str,delim);
		
		while(token){
			*(result +idx++) = strdup(token);
			token = strtok(0,delim);

		}
		*(result +idx) = 0;
	
	}
	
	return result;	


}


int CHAT(int argc, char **argv, int sockfd, char *us){

GtkWidget *Window = NULL;
GtkWidget *Addfriend = NULL;
GtkWidget *Chatbox = NULL;
GtkWidget *Send = NULL;
GtkWidget *add = NULL;
GtkWidget *delete = NULL;
GtkWidget *searchbar = NULL;
GdkPixmap *background = NULL;
GdkPixmap *background2 = NULL;
GdkPixbuf *image = NULL;
GtkWidget *image2 = NULL;
GtkWidget *image3 = NULL;
GtkWidget *image4 = NULL;
GtkWidget *image5 = NULL;
GdkPixbuf *image6 = NULL;
GtkTextBuffer *buffer = NULL;
GtkTextIter start,end;
PangoFontDescription *font_desc = NULL;
PangoFontDescription *font_desc2 = NULL;
GdkColor color;
GtkTextTag *tag = NULL;
GtkStyle *style = NULL;
GtkStyle *style2 = NULL;
char *text;
GtkWidget *fixed = NULL;
GtkWidget *back = NULL;
 
 
/*initialize libraries*/
gtk_init(&argc, &argv);


/*loading in background for widgets*/
image = load_pixbuf_from_file ("messaging-scrn.gif");
gdk_pixbuf_render_pixmap_and_mask(image,&background, NULL,0);
style = gtk_style_new();
style->bg_pixmap[0] = background;

image6 = load_pixbuf_from_file("add-scrn.gif");
gdk_pixbuf_render_pixmap_and_mask(image6,&background2,NULL,0);
style2 = gtk_style_new();
style2->bg_pixmap[0] = background2;

image2 = gtk_image_new_from_file("send.png");

image3 = gtk_image_new_from_file("AddFriend.png");

image4 = gtk_image_new_from_file("Add.png");

image5 = gtk_image_new_from_file("Delete.png");

/*create, top level window*/
Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

/*give title to the program*/
gtk_window_set_title(GTK_WINDOW(Window), Program);

/*center window*/
gtk_window_set_position(GTK_WINDOW(Window), GTK_WIN_POS_CENTER);

/*user unable to resize window*/
gtk_window_set_resizable(GTK_WINDOW(Window),FALSE);

gtk_widget_set_size_request(Window,900,600);
/*border width of window*/
gtk_container_set_border_width (GTK_CONTAINER(Window), 5);
/*setting the background for the gui*/
gtk_widget_set_style(GTK_WIDGET(Window),GTK_STYLE(style));
/*gtk_window_set_transient_for(GTK_WINDOW(Window),NULL);*/

/*fixed container*/
fixed = gtk_fixed_new();
gtk_container_add(GTK_CONTAINER(Window),fixed);

/*making addfriend button*/
Addfriend = gtk_button_new ();
gtk_fixed_put(GTK_FIXED(fixed),Addfriend,-5,520);
gtk_widget_set_size_request(Addfriend,225,59);
gtk_button_set_image(GTK_BUTTON(Addfriend),image3);

/*making chatbox button*/
Chatbox = gtk_text_view_new();
gtk_fixed_put(GTK_FIXED(fixed),Chatbox,227,510);
gtk_widget_set_size_request(Chatbox,545,75);

GtkWidget *chat = gtk_text_view_new();
gtk_text_view_set_editable(GTK_TEXT_VIEW(chat),FALSE);
gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(chat),FALSE);
GtkWidget *vbox2 = gtk_vbox_new(FALSE,2);
gtk_fixed_put(GTK_FIXED(fixed),vbox2,231,71);
gtk_widget_set_size_request(vbox2,660,425);

GtkWidget *scrolled = gtk_scrolled_window_new(NULL,NULL);
gtk_container_add(GTK_CONTAINER(scrolled),chat);
gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);
gtk_box_pack_start(GTK_BOX(vbox2),scrolled,TRUE,TRUE,1);

/*making send button*/
Send = gtk_button_new();
gtk_fixed_put(GTK_FIXED(fixed),Send,773,515);
gtk_widget_set_size_request(Send,108,72);
gtk_button_set_image(GTK_BUTTON(Send),image2);

/*making add and delete buttons*/
add = gtk_button_new();
gtk_fixed_put(GTK_FIXED(fixed),add,640,315);
gtk_widget_set_size_request(add,220,50);
gtk_button_set_image(GTK_BUTTON(add),image4);

delete = gtk_button_new();
gtk_fixed_put(GTK_FIXED(fixed),delete,640,380);
gtk_widget_set_size_request(delete,220,50);
gtk_button_set_image(GTK_BUTTON(delete),image5);

/*making search bar to search for friends*/
searchbar = gtk_entry_new();
gtk_fixed_put(GTK_FIXED(fixed),searchbar,251,346);
gtk_widget_set_size_request(searchbar,295,65);

/*making back button*/
back = gtk_button_new_with_label("Back");
gtk_fixed_put(GTK_FIXED(fixed),back,-5,520);
gtk_widget_set_size_request(back,225,59);

GtkWidget *vbox;
GtkWidget *contacts[MAXCONTACTS][MAXCONTACTS];
vbox = gtk_vbox_new(TRUE,0);
gtk_fixed_put(GTK_FIXED(fixed),vbox,45,65);
gtk_widget_set_size_request(vbox,180,450);

char **tokens;
char names[] = "TO CHAT TO OTHER USERS, ADD THEIR USERNAMES, AND THEN CLICK ON THEIR, NAME TO BEGIN CHATTING";
tokens = split_string(names,',');
if(tokens)
{
int i;
int j=0;
int k=0;
for(i=0;*(tokens +i);i++){
	contacts[j][k] = gtk_button_new_with_label(*(tokens+i));
	gtk_box_pack_start(GTK_BOX(vbox),contacts[j][k],1,1,0);
	k++;
	printf("names=[%s]\n",*(tokens+i));

	
	if(k== MAXCONTACTS){
				
		j++;
		k=0;
	}
}
}
printf("\n");
free(tokens);

/*changing font in text widgets*/
font_desc = pango_font_description_from_string("Serif 30");
font_desc2 = pango_font_description_from_string("Serif 40");
gtk_widget_modify_font(Chatbox, font_desc);
gtk_widget_modify_font(searchbar,font_desc2);
pango_font_description_free(font_desc);

/*gtk_entry_set_max_length(GTK_TEXT_VIEW(Chatbox),50);*/
/*getting contents of text widgets as a string with max 50 char*/
buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Chatbox));

/*modifying text color in chatbox widget*/
gdk_color_parse( "black", &color);
gtk_widget_modify_text(Chatbox, GTK_STATE_NORMAL, &color);

gtk_text_view_set_left_margin(GTK_TEXT_VIEW(Chatbox),10);

tag = gtk_text_buffer_create_tag(buffer,"blue_foreground","foreground","gray",NULL);
gtk_text_buffer_get_iter_at_offset(buffer,&start,0);
gtk_text_buffer_get_iter_at_offset(buffer, &end,22);
gtk_text_buffer_apply_tag(buffer,tag,&start,&end);
text = gtk_text_iter_get_text(&start,&end);

g_signal_connect(Window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

/* make sure that everything becomes visible at the right times */
gtk_widget_show_all(Window);
gtk_widget_hide(add);
gtk_widget_hide(delete);
gtk_widget_hide(searchbar);
gtk_widget_hide(back);

GList *children, *iter;
children = gtk_container_get_children(GTK_CONTAINER(vbox));
int i =0;
int j=0;
for(iter = children; iter != NULL; iter = g_list_next(iter))	
{
	contacts[i][j] = iter->data;
	g_object_set_data(G_OBJECT(add),"contacts",contacts[i][j]);
	g_object_set_data(G_OBJECT(delete),"contacts",contacts[i][j]);
	g_signal_connect(GTK_BUTTON(contacts[i][j]),"clicked",G_CALLBACK(messaging),contacts[i][j]);
	g_object_set_data(G_OBJECT(contacts[i][j]),"contacts",contacts[i][j]);
	g_object_set_data(G_OBJECT(contacts[i][j]),"chat",chat);
	j++;

	
	if(j== MAXCONTACTS){
				
		i++;
		j=0;
	}

}
g_list_free(children);	
/*

first set data to strings and link button*/
/*triggering events for add friend button*/
g_object_set_data(G_OBJECT(Addfriend),"addfriend",Addfriend);
g_object_set_data(G_OBJECT(Addfriend),"window",Window);
g_object_set_data(G_OBJECT(Addfriend),"add",add);
g_object_set_data(G_OBJECT(Addfriend),"delete",delete);
g_object_set_data(G_OBJECT(Addfriend),"search",searchbar);
g_object_set_data(G_OBJECT(Addfriend),"chatbox",Chatbox);
g_object_set_data(G_OBJECT(Addfriend),"send",Send);
g_object_set_data(G_OBJECT(Addfriend),"back",back);
g_object_set_data(G_OBJECT(Addfriend),"chat",vbox2);
g_signal_connect(GTK_BUTTON(Addfriend),"clicked",G_CALLBACK(addfriend_click),Addfriend);

/*triggering events for send button*/
g_object_set_data(G_OBJECT(Send),"window2",Window);
g_object_set_data(G_OBJECT(Send),"chatbox2",Chatbox);
g_object_set_data(G_OBJECT(Send),"fixed",fixed);
g_object_set_data(G_OBJECT(Send),"chat",chat);
int *p = &sockfd;
g_object_set_data(G_OBJECT(Send),"sockfd", p);
char *q = us;
g_object_set_data(G_OBJECT(Send),"username",q);

g_signal_connect(GTK_BUTTON(Send),"clicked",G_CALLBACK(send_click),Send);

/*triggering events for add button */
g_object_set_data(G_OBJECT(add),"searchbar",searchbar);
g_object_set_data(G_OBJECT(add),"window3",Window);
g_object_set_data(G_OBJECT(add),"vbox",vbox);
g_signal_connect(GTK_BUTTON(add),"clicked",G_CALLBACK(add_click),add);

/*triggering events for delete button*/
g_object_set_data(G_OBJECT(delete),"searchbar2",searchbar);
g_object_set_data(G_OBJECT(delete),"window4",Window);
g_object_set_data(G_OBJECT(delete),"vbox1",vbox);
g_signal_connect(GTK_BUTTON(delete),"clicked",G_CALLBACK(delete_click),delete);

/*triggering events for back button*/
g_object_set_data(G_OBJECT(back),"back",back);
g_object_set_data(G_OBJECT(back),"window5",Window);
g_object_set_data(G_OBJECT(back),"add2",add);
g_object_set_data(G_OBJECT(back),"delete2",delete);
g_object_set_data(G_OBJECT(back),"search2",searchbar);
g_object_set_data(G_OBJECT(back),"chatbox2",Chatbox);
g_object_set_data(G_OBJECT(back),"send2",Send);
g_object_set_data(G_OBJECT(back),"addfriend2",Addfriend);
g_object_set_data(G_OBJECT(back),"chat",vbox2);
g_signal_connect(GTK_BUTTON(back),"clicked",G_CALLBACK(back_click),back);
/*triggering events for clicking on contacts*/
g_object_set_data(G_OBJECT(vbox),"vbox3",vbox);

   /* simple server main loop */
        
                          


    int Timeout = 250000;

    int DataSocketFD;   /* socket for a new client */
    socklen_t ClientLen;
    struct sockaddr_in
    ClientAddress;  /* client address we connect with */
    fd_set ActiveFDs;   /* socket file descriptors to select from */
    fd_set ReadFDs;     /* socket file descriptors ready to read from */
    struct timeval TimeVal;
    int res;

    FD_ZERO(&ActiveFDs);                /* set of active sockets */
    FD_SET(sockfd, &ActiveFDs);   /* server socket is active */

while(true)
    {
        UpdateWindow(); 
   	 ReadFDs = ActiveFDs;
        TimeVal.tv_sec  = Timeout / 1000000;
        TimeVal.tv_usec = Timeout % 1000000;
        res = select(FD_SETSIZE, &ReadFDs, NULL, NULL, &TimeVal);
        if (res < 0)
        {   FatalError("wait for input or timeout (select) failed");
        }
        if (res == 0)  
        {
           UpdateWindow();
        }
        else            
        {
		/*GtkTextIter end3;
		gchar *newline = '\n';
	*/
		/*gtk_text_buffer_get_end_iter(bufferchat,&end3);
		gtk_text_buffer_insert(bufferchat,&end3,newline,-1);	
		*/char massage[256];
		bzero(massage, 256);
	
		int n;
		n = read(sockfd, massage, 255);
	

	

    		if (n < 0)
        	        error("ERROR reading from socket");
	

/*		 if(strstr(massage, "M:/") == NULL){
			printf("Null");
		}
		else{
*/			

	/*	getmessage(massage);
*/
		

		GtkTextIter start,end;
		GtkTextIter start2,end2;
		GtkTextBuffer *bufferchat = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chat));
		gchar *buffer_from_server = massage;
	
		/*gtk_text_buffer_get_start_iter(buffer_from_server, &start);
		gtk_text_buffer_get_end_iter(buffer_from_server,&end);
		
		gtk_text_buffer_get_bounds(buffer_from_server,&start,&end);
		
		gchar *text_from_server = gtk_text_buffer_get_text(buffer_from_server,&start,&end,FALSE);
		*/gtk_text_buffer_get_end_iter(bufferchat,&end2);
	
		gtk_text_buffer_insert(bufferchat,&end2,buffer_from_server,-1);
			 	

		bzero(massage,256);	
	
              
                      
        	if (DataSocketFD < 0)
        		{   FatalError("data socket creation (accept) failed");
        		}	
		printf("\nHappiness");
	/*	}*/
	}
    }




return 0;
}


void UpdateWindow(void)         /* render the window on screen */
{
   /* this server has it's own main loop for handling client connections;
 *     * as such, it can't have the usual GUI main loop (gtk_main);
 *         * instead, we call this UpdateWindow function on regular basis
 *             */
        gtk_main_iteration();
    
} /* end of UpdateWindow */

void FatalError(const char *ErrorMsg)
{
    fputs(Program, stderr);
    fputs(": ", stderr);
    perror(ErrorMsg);
    fputs(Program, stderr);
    fputs(": Exiting!\n", stderr);
    exit(20);
} /* end of FatalError */


