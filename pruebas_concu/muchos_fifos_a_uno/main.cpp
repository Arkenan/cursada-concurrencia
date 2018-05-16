#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


#define PATH "./fifo"
/* El padre leerá lo que escriben dos hijos distintos y lo escribirá */

int main() {
  // Creación de fifo.
  mkfifo(PATH, 0666);
  int child_id = fork();

  if (child_id == 0) {
    int fd_fifo = open(PATH, O_WRONLY);

    for (int i = 0; i < 10; ++i) {
      write(fd_fifo, "10101010", 100);
    }
    close(fd_fifo);
    // hijo.
  } else {
    // padre.
    int child_id_2 = fork();

    if (child_id_2 == 0) {
      // hijo 2.
      int fd_fifo = open(PATH, O_WRONLY);
      for (int i = 0; i < 10; ++i) {
        write(fd_fifo, "29292929", 100);
      }
      close(fd_fifo);

    } else {
      // padre.
      bool hayCosas = true;
      int fd_fifo = open(PATH, O_RDONLY);
      const char buf[1000]  = "";
      int bytes_read;
      while (hayCosas) {
        bytes_read = read(fd_fifo, (void *) buf, 1000);
        if (bytes_read == 0) {
          // Todos cerraron.
          hayCosas = false;
        } else {
          cout << "Lectura (" << bytes_read << " bytes): " << buf << endl;
        }
      }
      close(fd_fifo);
    }
  }
  return 0;
}
