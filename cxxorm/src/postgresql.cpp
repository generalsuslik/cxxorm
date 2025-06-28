//
// Created by generalsuslik on 13.06.25.
//

#include "postgresql.h"

#include "util.h"

#include <pqxx/pqxx>

#include <utility>

namespace cxxorm::psql {

    Postgresql::Postgresql(const ConnectionArgs& args) {
        connect(args);
    }

    Postgresql::Postgresql(Postgresql&& other) {
        other.disconnect();

        const auto& args = other.get_conn_args();
        connect(args);
    }

    Postgresql& Postgresql::operator=(Postgresql&& other) {
        if (*this != other) {
            disconnect();
            other.disconnect();

            const auto& args = other.get_conn_args();
            connect(args);
        }

        return *this;
    }

    bool Postgresql::operator==(const Postgresql& other) const {
        const auto& conn_str = generate_conn_string(args_);
        const auto& other_conn_str = generate_conn_string(other.get_conn_args());
        return conn_str == other_conn_str;
    }

    bool Postgresql::operator!=(const Postgresql& other) const {
        return !(*this == other);
    }

    Postgresql::~Postgresql() {

    }

    bool Postgresql::connect(const ConnectionArgs& args) {
        const std::string conn_str = generate_conn_string(args);
        conn_ = pqxx::connection(conn_str);

        if (!conn_.is_open()) {
            return false;
        }

        return true;
    }

    void Postgresql::disconnect() {
        if (conn_.is_open()) {
            conn_.close();
        }
    }

    template<typename T, typename... Args>
    int Postgresql::insert(const T& t, Args&&... args) {
        return insert_impl(OperationType::INSERT, t, std::forward<Args>(args)...);
    }

    template<typename T, typename... Args>
    int Postgresql::replace(const T& t, Args&&... args) {
        return insert_impl(OperationType::REPLACE, t, std::forward<Args>(args)...);
    }

    template<typename T, typename... Args>
    int Postgresql::insert_impl(OperationType type, const T& t, Args&&... args) {

    }

    std::string Postgresql::generate_conn_string(const ConnectionArgs& args) {
        const std::string host = std::get<0>(args);
        const std::string user = std::get<1>(args);
        const std::string password = std::get<2>(args);
        const std::string database = std::get<3>(args);
        const std::optional<int> timeout = std::get<4>(args);
        const std::uint16_t port = std::get<5>(args);

        std::stringstream ss;
        ss << "host=" << host << " port=" << port
            << " dbname=" << database <<" user=" << user << " password=" << password;

        if (timeout.has_value()) {
            ss << " connect_timeout=" << timeout.value();
        }

        return ss.str();
    }

    Postgresql::ConnectionArgs Postgresql::get_conn_args() const {
        return args_;
    }

} // namespace cxxorm::psql
