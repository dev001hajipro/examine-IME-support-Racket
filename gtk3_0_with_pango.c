#include <stdio.h>
#include <gtk/gtk.h>

// http://www.nslabs.jp/pango.rhtml

// gcc -Wall main.c -o main `pkg-config --cflags --libs gtk+-3.0`

static int on_destroy(GtkWidget* w, GdkEvent* e, void* d) {
        gtk_main_quit();
        return 0;
}

int main(int argc, char *argv[]) {
        const char *str = "<span size='40000'><u>日本語</u> "
                          "<span font_family='Microsoft Sans Serif'>&#x0E19;&#x0E49;&#x0E33;</span></span>";

        char *text = NULL;
        PangoAttrList *attrs = NULL;
        GError *error = NULL;

        gtk_init(&argc, &argv);
        if (!pango_parse_markup(str, -1, 0, &attrs, &text, NULL, &error)) {
                printf("error:%s\n", error->message);
                return 1;
        }


        GtkWidget* label = gtk_label_new(text);
        gtk_label_set_attributes(GTK_LABEL(label), attrs);

        GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_container_add(GTK_CONTAINER(window), label);
        gtk_container_set_border_width(GTK_CONTAINER(window), 30);
        gtk_widget_show_all(window);

        g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(on_destroy), NULL);

        gtk_main();
        return 0;
}
