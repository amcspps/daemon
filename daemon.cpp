#include "daemon.h"
#include <chrono>
#include <cstring>
#include <filesystem>
#include<fstream>
#include <string>
#include <format>
#include <sys/stat.h>
#include <cerrno>
namespace fs = std::filesystem;

void Daemon::_init() const {
	std::cout << "daemon started" <<std::endl;
	//clear workspace for another daemon process
	if (fs::exists(_pid_path)) {
		std::ifstream pid_file(_pid_path);
		pid_t existing_pid;
		if (pid_file >> existing_pid) {
			if (fs::exists(_proc_path + "/" + std::to_string(existing_pid))) {
				kill(existing_pid, SIGTERM);
			}
		}
	}
	if(fork()) {
		exit(0);
	} else {
		std::ofstream pid_file(_pid_path,std::ios::out);
		if (pid_file.is_open()) {
			pid_file << getpid();
		} else {
			std::cerr << strerror(errno) << std::endl;
		}
	}
}

void Daemon::run() const {
	_init();
  while (true) {
	task();
	std::this_thread::sleep_for(std::chrono::seconds(_time));
  }
}

void Daemon::_h_sighup(int sig) {

}

void Daemon::_h_sigterm(int sig) {

}

void Daemon::task() const {
	std::ofstream logfile("size.log");
	if(fs::exists(_f_dir_path) && fs::is_directory(_f_dir_path)) {
		std::uintmax_t total_size = 0;
		for (const auto& entry : fs::recursive_directory_iterator(_f_dir_path)) {
            if (fs::is_regular_file(entry)) {
                total_size += fs::file_size(entry);
            }
		}
		std::chrono::time_point<std::chrono::utc_clock> now = std::chrono::utc_clock::now();
		std::string output = std::format("{} {:%T}", total_size,now);
		std::cout << output << std::endl;
        }
}
