#include <gtk/gtk.h> /*Declares variables functions need for GTK*/
#include <stdio.h>
#include <stdlib.h>

/*Image Loading and Manipulation*/
GdkPixbuf *load_pixbuf_from_file (const char *filename)
{
    GError *error = NULL;
    /*Load the image to GdkPixbuf or variant*/
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file (filename, &error);

    if (pixbuf == NULL)
    {
        g_print ("Error loading file: %d : %s\n", error->code, error->message);
        g_error_free (error);
        exit (1);
    }
    return pixbuf;
}

GdkPixbufAnimation *load_pixbuf_animation_from_file (const char *filename)
{
    GError *error = NULL;
    GdkPixbufAnimation *pixbuf = gdk_pixbuf_animation_new_from_file (filename, &error);

    if (pixbuf == NULL)
 	if (pixbuf == NULL)
    {
        g_print ("Error loading file: %d : %s\n", error->code, error->message);
        g_error_free (error);
        exit (1);   
    }
    return pixbuf;
}

static void open_dialog(GtkWidget *button,gpointer window)
{
   GtkWidget *dialog, *label;
   dialog = gtk_dialog_new_with_buttons("Dialog",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
   label= gtk_label_new("Please enter the correct username and password");
   gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,0,0,0); /*Vertical Box*/
   gtk_widget_show_all(dialog);
   /*G_SIGNAL to connect everything so GTK will respond on click*/
   gint response = gtk_dialog_run(GTK_DIALOG(dialog));
   if (response==GTK_RESPONSE_OK)
       g_print("OK is pressed \n");
   else
	g_print("Cancel is pressed \n");
        gtk_widget_destroy(dialog);
}

void username_password (GtkButton *button, GObject *context_object){
    GtkEntry *username = g_object_get_data(context_object,"Login");
    const  gchar *text;
    text= gtk_entry_get_text(username);
    g_print("%s \n",text);
   GtkEntry *password = g_object_get_data(context_object,"Login2");
    const  gchar *text2;

    text2= gtk_entry_get_text(password);
    g_print("%s \n",text2);
}


int main (int argc, char **argv)
{
    
    GtkWidget *window = NULL;
    GtkWidget *button, *button1,*fixed=NULL;
    GtkWidget *image1,*image2 = NULL;
    GtkWidget *username, *password =NULL;
    GdkPixbuf *image = NULL;
    GdkPixmap *background = NULL;
    GtkStyle *style = NULL; 
    PangoFontDescription *font_desc =NULL;

    gtk_init (&argc, &argv);
 
    /* Load a file and put that as a background */
    image = load_pixbuf_from_file ("/users/ugrad/2017/fall/adhikarb/project/chat/background.png");
    gdk_pixbuf_render_pixmap_and_mask (image, &background, NULL, 0);
    style = gtk_style_new ();
    style->bg_pixmap [0] = background;

     image2  =gtk_image_new_from_file("Signup.png");
     image1  =gtk_image_new_from_file("Login.png");
   
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
     g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
       /* Sets the border width of the window. */

    gtk_container_set_border_width (GTK_CONTAINER (window),0);	

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);



    /* Creates a new button with the label "LOGIN" and "SIGNUP". */
    
    button = gtk_button_new_with_label ("LOGIN");
    gtk_fixed_put(GTK_FIXED(fixed), button, 650, 300);
    gtk_widget_set_size_request(button,80,30);
    gtk_button_set_image (GTK_BUTTON (button), image1);

    button1= gtk_button_new_with_label("SIGNUP");
     gtk_fixed_put(GTK_FIXED(fixed), button1, 650,500);
    gtk_widget_set_size_request(button1,80,30);
    gtk_button_set_image (GTK_BUTTON (button1),image2);
 

     /*displaying box for username and password*/
     username= gtk_entry_new();
     gtk_fixed_put(GTK_FIXED(fixed),username,535,87);/*location*/
     gtk_widget_set_size_request(username,325,62); /*box width,box height*/

     password= gtk_entry_new();
     gtk_fixed_put(GTK_FIXED(fixed),password,535,178);/*location*/
     gtk_widget_set_size_request(password,325,62);/*box width  , box height*/

     font_desc= pango_font_description_from_string("Serif 30");
     gtk_widget_modify_font(username,font_desc);
     gtk_widget_modify_font(password,font_desc);
     pango_font_description_free(font_desc);     


     /* Dialogbox when user does not enter a correct password or username,Login       clicked without entering username or password*/
      g_signal_connect(button,"clicked", G_CALLBACK(open_dialog),window);
      
     /*Handling object*/
      g_object_set_data(G_OBJECT(button),"Login",username);
      g_object_set_data(G_OBJECT(button),"Login2",password);
      g_signal_connect(GTK_BUTTON(button),"clicked",G_CALLBACK(username_password),button);

      
  
     /* Handler for deleting event*/
    g_signal_connect(G_OBJECT(window), "destroy", 
      G_CALLBACK(gtk_main_quit), NULL);

    /* Always remember this step, this tells GTK that our preparation for
 *      * this button is complete, and it can now be displayed. */
    gtk_widget_show (button);
    gtk_widget_show(button1);
    
/*Set title*/	
    gtk_window_set_title (GTK_WINDOW(window), "Project 2");
	/*Size Window*/
    gtk_window_set_default_size (GTK_WINDOW (window),900 , 600);
	/*Put Background Image*/
    gtk_widget_set_style (GTK_WIDGET(window), GTK_STYLE (style));


       /*Set Positon of the window*/
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
   
    gtk_widget_show_all (window);
    gtk_main ();
    return 0;
}
	
