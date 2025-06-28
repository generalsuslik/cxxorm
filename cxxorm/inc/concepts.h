//
// Created by generalsuslik on 14.06.25.
//

#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <cstdint>
#include <optional>
#include <string>

namespace cxxorm {

    template <typename DB>
    concept DataBase = requires(DB db,
                                std::string host,
                                std::string user,
                                std::string password,
                                std::string database,
                                std::optional<int> timeout,
                                std::uint16_t port) {
        { db.connect(host, user, password, database, timeout, port) } -> std::same_as<bool>;
    };

} // namespace cxxorm

#endif //CONCEPTS_H
