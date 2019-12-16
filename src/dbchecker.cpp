#include "dbchecker.h"

auto DBChecker::checkDBthread() -> void {
    std::mutex mtx;
    while (!this->closing) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        mtx.lock();
        try {
            int res = notify_check(this->_db, 
                    this->_db._notify_by_email, this->_db._notify_by_notify);
            if (res)
                emit this->checkDBepoch();
        } catch (std::exception e) {
            std::cout << e.what() << std::endl;
        }
        mtx.unlock();
    }
}
