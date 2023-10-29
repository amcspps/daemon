#include "daemon.h"
#include <sys/syslog.h>

auto main(int argc, char *argv[]) -> int {
	if(argc != 2) {
		//std::cout << "wrong argument count, please enter <cfg-path> only" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		const Daemon& d = Daemon::get_instance(argv[1]);
		d.run();
	}
    return 0;
}
