#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include <iostream>
using namespace std;
// regitro handler de sigint.

bool terminar;

void handler_sigint(int signal) {
  cout << "soy el handler!" << endl;
  terminar = true;
}

int main() {
  terminar = false;

  // registro señal.
  struct sigaction sa; // acciones a ejecutar.
  sigemptyset (&sa.sa_mask); // Borra la máscara.
  sigaddset (&sa.sa_mask, SIGINT); // bloquea sigint.
  sa.sa_handler = handler_sigint; // asigno un handler.
  sigaction (SIGINT, &sa, 0);


  pid_t id_fork = fork();
  if (id_fork != 0) {
    // Padre.
    while (!terminar) {
      cout << "soy el padre! Mi pid es: " << getpid()  << " y mi padre es: " << getppid() << endl;
      sleep(3);
    }
  } else {
    execl("child", "child");
    // while (!terminar) {
    //   cout << "soy el hijo! Tengo pid: " << getpid() << endl;
    //   sleep(1);
    // }
    // Hijo.
  }
  return 0;
}
