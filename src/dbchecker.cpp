#include "dbchecker.h"

auto DBChecker::checkDBthread() -> void {
    while (!this->closing) {
        std::this_thread::sleep_for(std::chrono::seconds(900));
        try {
            std::thread iter(&DBChecker::checkDBiter, this);
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
    }
}

auto DBChecker::checkDBiter() -> void {
    std::mutex mtx;
    mtx.lock();
    int res = notify_check(*(this->_db),
            this->_db->_notify_by_email, this->_db->_notify_by_notify);
    if (res)
        emit this->checkDBepoch();
    mtx.unlock();
}
