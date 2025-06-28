//
// Created by generalsuslik on 15.06.25.
//

#ifndef UTIL_H
#define UTIL_H

#include <sstream>
#include <string>

namespace cxxorm {

    enum class OperationType {
        INSERT,
        UPDATE,
        REPLACE,
        DELETE,
    };

    enum class DBType {
        POSTGRESQL,
        MYSQL,
        SQLITE,
        UNKNOWN,
    };

    template <typename T, typename... Args>
    std::string generate_sql(const bool insert, Args&&... args) {
        std::stringstream sql;
        sql << "INSERT INTO ";

        return {};
    }

} // namespace cxxorm

#endif //UTIL_H
