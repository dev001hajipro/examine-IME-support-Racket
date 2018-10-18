//  gcc -o hello.exe hello.c `pkg-config --cflags --libs gtk+-3.0`

#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
        gtk_init(&argc, &argv);
        GtkWidget *dialog = gtk_message_dialog_new(
                        NULL,
                        GTK_DIALOG_DESTROY_WITH_PARENT,
                        GTK_MESSAGE_OTHER,
                        GTK_BUTTONS_OK,
                        "Hello GTK!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return 0;
}
