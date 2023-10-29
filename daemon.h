#include <fstream>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <csignal>
#include <chrono>
#include <string>
#ifndef DAEMON_H
#define DAEMON_H

class Daemon {
    Daemon(const Daemon&) = delete;
    Daemon(Daemon&&) = delete;
    Daemon& operator=(const Daemon&) = delete;
    Daemon& operator=(Daemon&&) = delete;
public:
    static Daemon& get_instance(const std::string& cfg_path) {
        static Daemon instance = Daemon(cfg_path);
        return instance;
    }
    void run() const;
private:
    Daemon(const std::string& cfg_path);
    void _init() const;
    static void _h_sighup(int sig);
    static void _h_sigterm(int sig);
    static void _read_cfg(const std::string& cfg_path);
    void task() const;
    const std::string _pid_path = "/home/pavel/dev/daemon/daemon.pid";
    const std::string _proc_path = "/proc";
    static std::string _f_dir_path;
    static std::string _s_dir_path;
    static std::string _cfg_path;
    const unsigned int _time = 2;
};

#endif
