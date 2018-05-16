#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/file.h>

using namespace std;

const char * path = "salida.txt";

void sumar() {
  int fd = open(path, O_RDONLY | O_CREAT, 0777);
  flock(fd, LOCK_EX);
  leer(fd);
  escribir(fd, n);
  flock(fd, LOCK_UN);
}
int leer(fd) {
  char buf[100];
  int fd = open(path, O_RDONLY | O_CREAT, 0777);
  read(fd, buf, 100);
  int ret = atoi(buf);
  close(fd);
  cout << "Leí " << ret << endl;
  return ret;
}

void escribir(fd, int n) {
  int fd = open(path, O_WRONLY | O_CREAT, 0777);
  char buf[100];
  cout << "Escribo " << n << endl;
  sprintf(buf, "%d\n", n);
  write(fd, buf, 100);
  close(fd);
}

int main() {

  pid_t fork_id = fork();

  if (fork_id == 0) {
    // Soy el hijo.
    int n;
    for (int i = 0; i < 20; ++i) {
      n = leer();

      escribir(n-1000);

    }
  } else {
    // Soy el padre.
    int n;
    for (int i = 0; i < 20; ++i) {
      n = leer();

      escribir(n+1000);

    }
  }
  return 0;
}
