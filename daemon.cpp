#include "daemon.h"
#include <csignal>
#include <iostream>
#include <unistd.h>

void Daemon::run() const {
	// parent
	pid_t pid = fork();
	if(pid != 0) {
		kill(getpid(), SIGKILL);
	}
	if(pid == 0) {
		while (true) {
			std::cout << "child" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
	// parent and child
	//if (pid == 0) {
		// child only
		//while(true) {
			//std::cout << "done" << std::endl;

			//kill(getpid(), SIGKILL);
	//	}
	//}
	//while(true) {
	//}
	// parent and child
	//std::cout << getpid() << std::endl << pid << std::endl;

}
