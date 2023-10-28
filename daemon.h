#include <iostream>
#include <thread>
#include <unistd.h>
#include <signal.h>
#include <chrono>
#ifndef DAEMON_H
#define DAEMON_H

class Daemon {
    Daemon(const Daemon&) = delete;
    Daemon(Daemon&&) = delete;
    Daemon& operator=(const Daemon&) = delete;
    Daemon& operator=(Daemon&&) = delete;
public:
    static Daemon& getInstance() {
        static Daemon instance = Daemon();
        return instance;
    }
    void run() const;
private:
    Daemon() {
        std::cout << "daemon instance created" << std::endl;
    };
    void _init();
    void _h_sighup();
    void _h_sigterm();
    const std::string _pid_path = "/var/run/daemon.pid";
};

#endif
