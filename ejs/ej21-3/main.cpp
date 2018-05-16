#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
using namespace std;

long int random() {
    srand(getpid());
    long int result = rand() % 30;
    return result;
}

key_t getKey() {
  return ftok("/bin/bash", 1);
}

int crearMem(int nproc) {
    key_t key = getKey();
    return shmget(key, sizeof(int)*nproc, 0644 | IPC_CREAT | IPC_EXCL);

}

int main() {
    int nproc;
    cout << "ingrese número de procesos a crear." << endl;
    cin >> nproc;

    int id = crearMem(nproc);
    int * sleep_times = (int *) shmat(id, NULL, 0);

    for (int i = 0; i < nproc; ++i) {
        int pid = fork();
        if (pid == 0) {
            int wait_time = random();
            cout << "Soy el hijo de pid [" << getpid() <<"] y voy a esperar " << wait_time << " segundos" << endl;
            sleep_times[i] = wait_time;
            shmdt(sleep_times);
            sleep(wait_time);
            exit(i);
        }
    }

    int status;
    for (int i = 0; i < nproc; ++i) {
        pid_t id_child = waitpid(-1, &status, 0);
        if WIFEXITED(status) {
          cout << "Acaba de terminar el hijo de pid [" << id_child << "]. Terminó en " << sleep_times[WEXITSTATUS(status)] << " segundos." << endl;
        } else {
          cout << "Acaba de terminar el hijo de pid [" << id_child << "]. Terminó con error. " << endl;
        }
    }

    // Libero recursos.
    shmdt(sleep_times);
    shmctl(id, IPC_RMID, NULL);

    return 0;
}
