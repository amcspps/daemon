class Daemon {
    Daemon() = delete;
    Daemon(const Deleter&) = delete;
    Daemon(Deleter&&) = delete;
    
    Daemon& operator=(const Deleter&) = delete;
    Daemon& operator=(Deleter&&) = delete;

    static Daemon& getInstance() {
        static Daemon instance;
        return instance
    }

}