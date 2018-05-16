#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main() {
  while (true) {
    cout << "soy el hijo. Mi pid es " << getpid() << " y mi padre es " << getppid() << endl;
    sleep(3);
  }
  return 0;
}
