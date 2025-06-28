//
// Created by generalsuslik on 13.06.25.
//

#ifndef CONNECTION_H
#define CONNECTION_H

#include <concepts.h>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <optional>

namespace cxxorm {

    /**
     * @brief Class represents db connection to specific dbms
     * Singleton
     *
     * @tparam DB
     */
    template <DataBase DB>
    class Connection {
    private:
        explicit Connection(const std::string& host = "",
                            const std::string& user = "",
                            const std::string& password = "",
                            const std::string& database = "",
                            const std::optional<int> timeout = {},
                            const std::uint16_t port = 0)
            : args_(host, user, password, database, timeout, port)
        {
            std::call_once(flag_, &Connection::init, this);
        }

    public:
        Connection(const Connection&) = delete;

        Connection& operator=(const Connection&) = delete;

        Connection(Connection&&) noexcept = default;

        Connection& operator=(Connection&&) noexcept = default;

        ~Connection() = default;

        Connection& get() {
            std::unique_lock lock(mutex_);

            if (conn_ == nullptr) {
                if (cv_.wait_for(lock, std::chrono::seconds(3)) == std::cv_status::timeout) {
                    return nullptr;
                }

                conn_ = std::make_unique<DB>();
            }

            return *conn_;
        }

    private:
        void init() {
            const auto conn = std::make_shared<DB>();
            if (!conn->connect(args_)) {
                throw std::invalid_argument("Connection initialization failed");
            }
        }

    private:
        static inline std::unique_ptr<Connection> conn_ = nullptr;

        std::mutex mutex_;
        std::condition_variable cv_;

        std::once_flag flag_;

        std::tuple<std::string, std::string, std::string, std::string, std::optional<int>, std::uint16_t> args_;
    };


} // namespace cxxorm

#endif //CONNECTION_H
