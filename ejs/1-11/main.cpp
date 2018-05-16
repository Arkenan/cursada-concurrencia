#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

long int random() {
    srand(getpid());
    long int result = rand() % 30;
    return result;
}

int main() {
    int nproc;
    cout << "ingrese número de procesos a crear." << endl;
    cin >> nproc;

    for (int i = 0; i < nproc; ++i) {
        if (fork() == 0) {
            int wait_time = random();
            cout << "Soy el hijo de pid [" << getpid() <<"] y voy a esperar " << wait_time << " segundos" << endl;
            sleep(wait_time);
            exit(wait_time);
        }
    }

    int status;
    for (int i = 0; i < nproc; ++i) {
        pid_t id_child = waitpid(-1, &status, 0);
        if WIFEXITED(status) {
          cout << "Acaba de terminar el hijo de pid [" << id_child << "]. Terminó en " << WEXITSTATUS(status) << " segundos." << endl;
        } else {
          cout << "Acaba de terminar el hijo de pid [" << id_child << "]. Terminó con error." << endl;
        }
    }
    exit(0);

    return 0;
}
