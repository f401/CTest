#include <gtk-3.0/gtk/gtk.h>

static void destroy() { gtk_main_quit(); }

extern char _binary_my_png_start[], _binary_my_png_size[];

int main(int argc, char *argv[]) {
  GtkWidget *window, *image;
  gtk_init(&argc, &argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  // image = gtk_image_new_from_file("../my.png");
  // GCancellable* cancellable = g_cancellable_new();

  GInputStream *stream = g_memory_input_stream_new_from_data(
      _binary_my_png_start, (gsize)_binary_my_png_size, NULL);
  image =
      gtk_image_new_from_pixbuf(gdk_pixbuf_new_from_stream(stream, NULL, NULL));
  g_signal_connect(GTK_WINDOW(window), "destroy", destroy, NULL);

  g_input_stream_close(stream, NULL, NULL);
  gtk_container_add(GTK_CONTAINER(window), image);
  gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
  gtk_widget_set_size_request(window, 800, 600);
  gtk_widget_show_all(window);
  gtk_main();
  return 0;
}
