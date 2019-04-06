
#define _SVID_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <assert.h>
#define MAXMSG 50
const char *Program
	= NULL;

GdkPixbuf *load_pixbuf_from_file(const char *filename)
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

const gchar *add_click(GtkButton *button,GObject *context_object){
	GtkEntry *searchbar = g_object_get_data(context_object,"searchbar");
	GtkWidget *window = g_object_get_data(context_object,"window3");
	
	const gchar *text = gtk_entry_get_text(searchbar);
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

	g_print("%s",text);	
	return text;
	/*text contains the name of the friend to be added until freed*/
	/*g_free(text);*/

	
}
const gchar *delete_click(GtkButton *button,GObject *context_object){
	GtkEntry *searchbar = g_object_get_data(context_object,"searchbar2");
	GtkWidget *window = g_object_get_data(context_object,"window4");

	const gchar *text = gtk_entry_get_text(searchbar);
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

	/*text contains the name of the friend to be deleted until freed*/
	/*g_free(text);*/
	g_print("%s",text);
	return text;


}


const gchar *send_click(GtkButton *button, GObject *context_object){
	GtkWidget *window = g_object_get_data(context_object,"window2");
	GtkWidget *chatbox = g_object_get_data(context_object,"chatbox2");
	GtkWidget *message4 = g_object_get_data(context_object,"label");
	GtkWidget *message3 = g_object_get_data(context_object,"label2");
	GtkWidget *message2 = g_object_get_data(context_object,"label3");
	GtkWidget *message1 = g_object_get_data(context_object,"label4");
	PangoFontDescription *font_desc = NULL;
	font_desc = pango_font_description_from_string("Serif 20");
	GtkTextIter start,end;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chatbox));
	gtk_text_buffer_get_start_iter(buffer,&start);
	gtk_text_buffer_get_end_iter(buffer,&end);
	gtk_text_iter_forward_chars(&start,MAXMSG);
	gtk_text_buffer_delete(buffer,&start,&end);
	const gchar *text;
	gtk_text_buffer_get_bounds(buffer,&start,&end);
	text = gtk_text_buffer_get_text(buffer,&start,&end,FALSE);
	
	if (strcmp(text,"")== 0){
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

	}
	g_print("%s",text);
	/*setting labels and setting fonts of messages*/
	const gchar *oldtext = gtk_label_get_text(GTK_LABEL(message1));
	
	/*const gchar *text2 = g_convert(oldtext,-1,"UTF-8","UTF-16BE",&bytes_read,&bytes_written,NULL);
	*/const gchar *oldtext2 = gtk_label_get_text(GTK_LABEL(message2));
	const gchar *oldtext3 = gtk_label_get_text(GTK_LABEL(message3));

	gtk_label_set_text(GTK_LABEL(message4),oldtext3);
	gtk_label_set_text(GTK_LABEL(message3),oldtext2);
	gtk_label_set_text(GTK_LABEL(message2),oldtext);
	gtk_label_set_text(GTK_LABEL(message1),text);
	gtk_widget_modify_font(message1, font_desc);
	gtk_widget_modify_font(message2, font_desc);
	gtk_widget_modify_font(message3, font_desc);
	gtk_widget_modify_font(message4, font_desc);
	gtk_text_buffer_delete(buffer,&start,&end);
	return text;
	
	/*g_free(text);*/
 	/*pango_font_description_free(font_desc);
	*/
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
	GtkWidget *message1 = g_object_get_data(context_object,"label");
	GtkWidget *message2 = g_object_get_data(context_object,"label2");
	GtkWidget *message3 = g_object_get_data(context_object,"label3");
	GtkWidget *message4 = g_object_get_data(context_object,"label4");
	GdkPixbuf *image;
	GdkPixmap *background;	
	GtkStyle *style;
	image = load_pixbuf_from_file("add-scrn.gif");
	gtk_widget_hide(addfriend);
	gtk_widget_show(add_button);
	gtk_widget_show(delete_button);
	gtk_widget_show(search);
	gtk_widget_show(back);
	gtk_widget_hide(send);
	gtk_widget_hide(chatbox);
	gtk_widget_hide(message1);
	gtk_widget_hide(message2);
	gtk_widget_hide(message3);
	gtk_widget_hide(message4);
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
	GtkWidget *message1 = g_object_get_data(context_object,"label");
	GtkWidget *message2 = g_object_get_data(context_object,"label2");
	GtkWidget *message3 = g_object_get_data(context_object,"label3");
	GtkWidget *message4 = g_object_get_data(context_object,"label4");
	/*GtkWidget *message5 = g_object_get_data(context_object,"label5");
	*/
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
	gtk_widget_show(message1);
	gtk_widget_show(message2);
	gtk_widget_show(message3);
	gtk_widget_show(message4);
	gdk_pixbuf_render_pixmap_and_mask(image,&background2,NULL,0);
	style2 = gtk_style_new();
	style2->bg_pixmap[0] = background2;

/*	gtk_widget_set_style(GTK_WIDGET(window),GTK_STYLE(background2));
*/	gtk_widget_set_style(GTK_WIDGET(window),NULL);
	gtk_widget_set_style(GTK_WIDGET(window),GTK_STYLE(style2));

}
char **split_string(char *str,const char a_delim){
	/*char str[1000] = "HIM\nnia\nadsfng\n-\ngan";
	i is  number of strings and 15 is max length of strings
	int i = 1;
	max length of name
	int j = 15;
	char names[1000][1000];
	gets first substring
	const char s[2] = "\n";
	char *substring = NULL;
	substring = strtok(str,s);
	while(substring !=NULL){
		printf("%s\n",substring);
		names[i][j] = substring; 
		i++;
		substring = strtok(NULL,s);

	}
	
	
	return names;

*/
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


void callback(GtkWidget *parent,gpointer *data){

	g_print("Addfriend was pressed");
}



int main(int argc, char *argv[]){

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
GtkWidget *label = NULL;
GtkWidget *label2 = NULL;
GtkWidget *label3 = NULL;
GtkWidget *label4 = NULL;
GtkWidget *label5 = NULL;
GtkWidget *back = NULL;
GtkWidget *notebook = NULL;
 
 
/*initialize libraries*/
gtk_init(&argc, &argv);

char **tokens;
char names[] = "John Doe\nKanye West\nJane Doe\nBert Yu\n";
tokens = split_string(names,'\n');
if(tokens)
{
int i;
for(i=0;*(tokens +i);i++){
	printf("names=[%s]\n",*(tokens+i));
	free(*(tokens +i));


}
printf("\n");
free(tokens);


}

/*to split strings*/


/*loading in background for widgets*/
image = load_pixbuf_from_file ("messaging-scrn.gif");
gdk_pixbuf_render_pixmap_and_mask(image,&background, NULL,0);
style = gtk_style_new();
style->bg_pixmap[0] = background;

image6 = load_pixbuf_from_file("add-scrn.gif");
gdk_pixbuf_render_pixmap_and_mask(image6,&background2,NULL,0);
style2 = gtk_style_new();
style2->bg_pixmap[0] = background2;
/*image2 = load_pixbuf_from_file("send.gif");
gdk_pixbuf_render_pixmap_and_mask(image2,&background2,NULL,0);
style2 = gtk_style_new();
style2->bg_pixmap[0] = background2;
*/
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

/*displaying window*/
/*gtk_window_set_default_size(GTK_WINDOW(Window), 900,600 );
 * */
/*gtk_window_fullscreen(GTK_WINDOW(Window));*/

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

/*layout = gtk_layout_new(NULL,NULL);
igtk_fixed_put(GTK_FIXED(fixed),layout,780,200);
gtk_widget_show(layout);*/

/*loading in send button*/
/*image2 = gtk_image_new_from_file ("send.gif");
gtk_layout_put(GTK_LAYOUT(layout),image2,0,0);*/

/*making addfriend button*/
Addfriend = gtk_button_new ();
gtk_fixed_put(GTK_FIXED(fixed),Addfriend,-5,520);
gtk_widget_set_size_request(Addfriend,225,59);
gtk_button_set_image(GTK_BUTTON(Addfriend),image3);

label = gtk_label_new("");
gtk_fixed_put(GTK_FIXED(fixed),label,600,100);

/*gtk_widget_set_size_request(label,300,100);
*/
label2 = gtk_label_new("");
gtk_fixed_put(GTK_FIXED(fixed),label2,600,200);
/*gtk_widget_set_size_request(label2,300,100);
*/
label3 = gtk_label_new("");
gtk_fixed_put(GTK_FIXED(fixed),label3,600,300);
/*gtk_widget_set_size_request(label3,300,100);
*/
label4 = gtk_label_new("");
gtk_fixed_put(GTK_FIXED(fixed),label4,600,400);

gtk_label_set_use_markup(GTK_LABEL(label4),TRUE);
gtk_label_set_use_markup(GTK_LABEL(label3),TRUE);	
gtk_label_set_use_markup(GTK_LABEL(label2),TRUE);
gtk_label_set_use_markup(GTK_LABEL(label),TRUE);
gtk_label_set_line_wrap(GTK_LABEL(label4),TRUE);
gtk_label_set_line_wrap(GTK_LABEL(label3),TRUE);
gtk_label_set_line_wrap(GTK_LABEL(label2),TRUE);
gtk_label_set_line_wrap(GTK_LABEL(label),TRUE);
gtk_label_set_max_width_chars(GTK_LABEL(label4),25);
gtk_label_set_max_width_chars(GTK_LABEL(label3),25);
gtk_label_set_max_width_chars(GTK_LABEL(label2),25);
gtk_label_set_max_width_chars(GTK_LABEL(label),25);
/*gtk_widget_set_size_request(label4,300,100);
*/
/*
label5 = gtk_label_new("");
gtk_fixed_put(GTK_FIXED(fixed),label5,600,480);
*/
/*add_delete = AddFriend(Window);
gtk_fixed_put(GTK_FIXED(fixed),add_delete,100,100);*/

/*label = gtk_label_new("HI");
gtk_fixed_put(GTK_FIXED(fixed),label,700,400);
*/
/*making chatbox button*/
Chatbox = gtk_text_view_new();
gtk_fixed_put(GTK_FIXED(fixed),Chatbox,227,510);
gtk_widget_set_size_request(Chatbox,545,75);

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

GtkWidget *message1,*message2;
notebook = gtk_notebook_new();
gtk_fixed_put(GTK_FIXED(fixed),notebook,300,300);
gtk_widget_set_size_request(notebook,400,400);
/*gtk_widget_set_style(GTK_WIDGET(Send),GTK_STYLE(style2));*/


/*gtk_widget_set_style(GTK_WIDGET(Send),GTK_STYLE(style2));*/

/*hbox = gtk_hbox_new(0,0);
gtk_box_pack_start(GTK_BOX(hbox),Addfriend,1,1,0);
gtk_box_pack_start(GTK_BOX(hbox),Chatbox,1,1,0);
gtk_box_pack_start(GTK_BOX(hbox),Send,1,1,0);
gtk_container_add(GTK_CONTAINER(Window),hbox);*/

/*changing font in text widgets*/
font_desc = pango_font_description_from_string("Serif 30");
font_desc2 = pango_font_description_from_string("Serif 40");
gtk_widget_modify_font(Chatbox, font_desc);
gtk_widget_modify_font(searchbar,font_desc2);
pango_font_description_free(font_desc);



/*gtk_entry_set_max_length(GTK_TEXT_VIEW(Chatbox),50);*/
/*getting contents of text widgets as a string with max 50 char*/
buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Chatbox));
/*gtk_text_buffer_set_text(buffer, "Type your message here", -1);
*/
/*gtk_text_buffer_get_bounds(buffer,&range_start,&range_end);
*/
/*set text*/
/*text = gtk_text_iter_get_text(&range_start,&range_end);
g_free(text);
*/
/*modifying text color in chatbox widget*/
gdk_color_parse( "black", &color);
gtk_widget_modify_text(Chatbox, GTK_STATE_NORMAL, &color);

gtk_text_view_set_left_margin(GTK_TEXT_VIEW(Chatbox),10);

tag = gtk_text_buffer_create_tag(buffer,"blue_foreground","foreground","gray",NULL);
gtk_text_buffer_get_iter_at_offset(buffer,&start,0);
gtk_text_buffer_get_iter_at_offset(buffer, &end,22);
gtk_text_buffer_apply_tag(buffer,tag,&start,&end);
text = gtk_text_iter_get_text(&start,&end);


/*free text*/
/*g_free(text);*/

/*GTKWidget *Window;
 * GTKWidget *Window;
 *
   * map the destroy signal of the window to gtk_main_quit;
 *      * when the window is about to be destroyed, we get a notification and
 *           * stop the main GTK+ loop by returning 0 */
g_signal_connect(Window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

/* overall vertical arrangement in the window */
/*VBox = gtk_vbox_new(TRUE, 10);		*/
/*gtk_container_add(GTK_CONTAINER(Window), VBox); */


/* on the bottom, two buttons to quit client and shutdown server */
/*HButtons = gtk_hbutton_box_new();
gtk_container_add(GTK_CONTAINER(VBox), HButtons);*/
/*
QuitButton = gtk_button_new_with_label("Quit Client");
gtk_container_add(GTK_CONTAINER(HButtons), QuitButton);
ShutdownButton = gtk_button_new_with_label("Shutdown Server");
gtk_container_add(GTK_CONTAINER(HButtons), ShutdownButton);
*/
/* make sure that everything becomes visible at the right times */
gtk_widget_show_all(Window);
gtk_widget_hide(add);
gtk_widget_hide(delete);
gtk_widget_hide(searchbar);
gtk_widget_hide(back);

/*disable minimization and maximization*/

/*first set data to strings and link button*/
/*triggering events for add friend button*/
g_object_set_data(G_OBJECT(Addfriend),"addfriend",Addfriend);
g_object_set_data(G_OBJECT(Addfriend),"window",Window);
g_object_set_data(G_OBJECT(Addfriend),"add",add);
g_object_set_data(G_OBJECT(Addfriend),"delete",delete);
g_object_set_data(G_OBJECT(Addfriend),"search",searchbar);
g_object_set_data(G_OBJECT(Addfriend),"chatbox",Chatbox);
g_object_set_data(G_OBJECT(Addfriend),"send",Send);
g_object_set_data(G_OBJECT(Addfriend),"back",back);
g_object_set_data(G_OBJECT(Addfriend),"label",label);
g_object_set_data(G_OBJECT(Addfriend),"label2",label2);
g_object_set_data(G_OBJECT(Addfriend),"label3",label3);
g_object_set_data(G_OBJECT(Addfriend),"label4",label4);
g_object_set_data(G_OBJECT(Addfriend),"label5",label5);

g_signal_connect(GTK_BUTTON(Addfriend),"clicked",G_CALLBACK(addfriend_click),Addfriend);

/*triggering events for send button*/
g_object_set_data(G_OBJECT(Send),"window2",Window);
g_object_set_data(G_OBJECT(Send),"chatbox2",Chatbox);
g_object_set_data(G_OBJECT(Send),"fixed",fixed);
g_object_set_data(G_OBJECT(Send),"label",label);
g_object_set_data(G_OBJECT(Send),"label2",label2);
g_object_set_data(G_OBJECT(Send),"label3",label3);
g_object_set_data(G_OBJECT(Send),"label4",label4);
/*g_object_set_data(G_OBJECT(Send),"label5",label5);
*/

g_signal_connect(GTK_BUTTON(Send),"clicked",G_CALLBACK(send_click),Send);

/*triggering events for add button */
g_object_set_data(G_OBJECT(add),"searchbar",searchbar);
g_object_set_data(G_OBJECT(add),"window3",Window);
g_signal_connect(GTK_BUTTON(add),"clicked",G_CALLBACK(add_click),add);


/*triggering events for delete button*/
g_object_set_data(G_OBJECT(delete),"searchbar2",searchbar);
g_object_set_data(G_OBJECT(delete),"window4",Window);
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
g_object_set_data(G_OBJECT(back),"label",label);
g_object_set_data(G_OBJECT(back),"label2",label2);
g_object_set_data(G_OBJECT(back),"label3",label3);
g_object_set_data(G_OBJECT(back),"label4",label4);
/*g_object_set_data(G_OBJECT(back),"label5",label5);
*/
g_signal_connect(GTK_BUTTON(back),"clicked",G_CALLBACK(back_click),back);

/* connect quit button with function terminating this client */
/* (note the 'swapped' call; try without to see the effect) */
/*g_signal_connect_swapped(QuitButton, "clicked", 
	G_CALLBACK(gtk_widget_destroy), Window);*/

gtk_main();

return 0;



}
