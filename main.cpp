#include <cstdlib>
#include <iostream>
#include <ostream>
#include "daemon.h"

auto main(int argc, char *argv[]) -> int {
	if(argc != 2) {
		exit(EXIT_FAILURE);
	}
	else {
		const Daemon& d = Daemon::get_instance(argv[1]);
		d.run();
	}
    return 0;
}
