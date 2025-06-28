//
// Created by generalsuslik on 13.06.25.
//

#ifndef POSTGRESQL_H
#define POSTGRESQL_H

#include <pqxx/pqxx>

#include "util.h"

namespace cxxorm::psql {

    class Postgresql {
    public:
        using ConnectionArgs = std::tuple<
                                            std::string,
                                            std::string,
                                            std::string,
                                            std::string,
                                            std::optional<int>,
                                            std::uint16_t
                                        >;
    public:
        Postgresql() = default;

        Postgresql(const Postgresql&) = delete;
        Postgresql& operator=(const Postgresql&) = delete;

        Postgresql(Postgresql&& other) noexcept;
        Postgresql& operator=(Postgresql&& other) noexcept;

        bool operator==(const Postgresql& other) const;
        bool operator!=(const Postgresql& other) const;

        explicit Postgresql(const ConnectionArgs& args);

        ~Postgresql();

        bool connect(const ConnectionArgs& args);

        void disconnect();

        template <typename T, typename... Args>
        int insert(const T& t, Args&&... args);

        template <typename T, typename... Args>
        int replace(const T& t, Args&&... args);

        template <typename T, typename... Args>
        int insert_impl(OperationType type, const T& t, Args&&... args);

    private:
        static std::string generate_conn_string(const ConnectionArgs& args);

        ConnectionArgs get_conn_args() const;

    private:
        pqxx::connection conn_;

         ConnectionArgs args_;
    };

} // namespace cxxorm::psql

#endif //POSTGRESQL_H
