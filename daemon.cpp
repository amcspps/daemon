#include "daemon.h"
#include <chrono>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include<fstream>
#include <ios>
#include <string>
//#include <format>
#include <ctime>
#include <sys/stat.h>
#include <cerrno>
#include <sys/syslog.h>
#include <unistd.h>

namespace fs = std::filesystem;

std::string Daemon::_cfg_path = "";
std::string Daemon::_f_dir_path = "";
std::string Daemon::_s_dir_path = "";


Daemon::Daemon(const std::string& cfg_path) {
	openlog("daemon", LOG_PID, LOG_USER);
	if(!fs::exists(fs::absolute(cfg_path).string())) {
		syslog(LOG_ERR, "config file does not exist");
		closelog();
		exit(EXIT_FAILURE);
	}
	else {
		_cfg_path = fs::absolute(cfg_path).string();
		syslog(LOG_INFO, "config path read successfully");
		_read_cfg(cfg_path);
	}
}

void Daemon::_init() const {
	if (fs::exists(_pid_path)) {
		std::ifstream pid_file(_pid_path);
		pid_t existing_pid;
		if (pid_file >> existing_pid) {
			if (fs::exists(_proc_path + "/" + std::to_string(existing_pid))) {
				syslog(LOG_WARNING, "another instance of daemon currently works");
				kill(existing_pid, SIGTERM);
				syslog(LOG_WARNING,"another instance of daemon killed successfully");
			}
		}
	}
	pid_t child = fork();
	if(child < 0) {
		syslog(LOG_ERR,"fork failed");
		closelog();
		exit(EXIT_FAILURE);
	}
	else if (child) {
		exit(EXIT_SUCCESS);
	}
	else {
		std::signal(SIGHUP, _h_sighup);
		std::signal(SIGTERM, _h_sigterm);

		std::ofstream pid_file(_pid_path, std::ios::out);
		if (pid_file.is_open()) {
			pid_file << getpid();
		}
		else {
			syslog(LOG_ERR,"error while writing pid");
			exit(EXIT_FAILURE);
		}
	}
	syslog(LOG_INFO, "initialization successful");
}

void Daemon::run() const {
	_init();
	while (true) {
		task();
		std::this_thread::sleep_for(std::chrono::seconds(_time));
	}
}

void Daemon::_h_sighup(int sig) {
	syslog(LOG_INFO, "SIGHUP received, re-reading config files");
	_read_cfg(_cfg_path);
}

void Daemon::_h_sigterm(int sig) {
	syslog(LOG_INFO, "SIGTERM received, terminating process...");
	closelog();
	exit(EXIT_SUCCESS);
}

void Daemon::task() const {
	std::ofstream logfile(fs::absolute(_s_dir_path).string() + "/" + "size.log", std::ios_base::app);
	if(fs::exists(_f_dir_path) && fs::is_directory(_f_dir_path)) {
		std::uintmax_t total_size = 0;
		for (const auto& entry : fs::recursive_directory_iterator(_f_dir_path)) {
			if (fs::is_regular_file(entry)) {
				total_size += fs::file_size(entry);
				fs::remove(entry);
			}
		}
		for (const auto& subdir : fs::directory_iterator(_f_dir_path)) {
			fs::remove_all(subdir);
		}
		time_t now = time(0);
		logfile << "dir size: " << total_size << "at time: " << std::string(ctime(&now)) << std::endl;
		// std::chrono::time_point<std::chrono::utc_clock> now = std::chrono::utc_clock::now();
		// std::string output = std::format("dir size: {}B at time {:%T}\n", total_size, now);
		//logfile << output;
	}
}

void Daemon::_read_cfg(const std::string& cfg_path) {
	std::ifstream cfg_file(cfg_path);
	std::string rel_f = "";
	std::string rel_s = "";
	std::getline(cfg_file, rel_f);
	std::getline(cfg_file, rel_s);
	_f_dir_path = fs::absolute(rel_f).string();
	_s_dir_path = fs::absolute(rel_s).string();
	if(!fs::exists(_f_dir_path)) {
		syslog(LOG_ERR, "task: first directory does not exist");
		closelog();
		exit(EXIT_FAILURE);
	}
	if(!fs::exists(_s_dir_path)) {
		syslog(LOG_ERR, "task: second directory does not exist");
		closelog();
		exit(EXIT_FAILURE);
	}
}
