#include <chrono>
#include <iostream>
#include <ostream>
#include <thread>
#include <unistd.h>
#include <signal.h>
#include "daemon.h"

auto main(int argc, char *argv[]) -> int {
	const Daemon& d = Daemon::getInstance();
	d.run();
	// parent
	//pid_t pid = fork();
	// parent and child
	//if (pid == 0) {
		// child only
		//while(true) {
			//std::cout << "done" << std::endl;
			//std::this_thread::sleep_for(std::chrono::seconds(1));
			//kill(getpid(), SIGKILL);
	//	}
	//}
	//while(true) {
	//}
	// parent and child
	//std::cout << getpid() << std::endl << pid << std::endl;
    return 0;
}
