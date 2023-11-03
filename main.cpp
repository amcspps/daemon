#include "daemon.h"
#include <cstdlib>

auto main(int argc, char *argv[]) -> int {
  if(argc != 2) {
    exit(EXIT_FAILURE);
  }
  else {
    uid_t euid = geteuid();
    if (euid == -1) {
      std::cout << "attempt to check if daemon was run with sudo failed" << std ::endl;
      exit(EXIT_FAILURE);
    }
    else if (euid == 0) {
      const Daemon &d = Daemon::get_instance(argv[1]);
      d.run();
    }
    else {
      std::cout << "start daemon only with root privileges" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}
