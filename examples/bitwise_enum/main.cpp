// Copyright (c) 2026 TypeCombinator <typecombinator@foxmail.com>
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <kon/qi/enum.hpp>

// Bitwise enums may not be a good pattern, this example is only intended to demonstrate the
// extensibility of annotations. Of course, the following code can also be further simplified using
// X-macros.
enum class permission : unsigned char {
    read = 1 << 5,
    write = 1 << 6,
    execute = 1 << 7,
    all = execute | write | read,
};

namespace kon::qi {
template <>
struct addon_register<permission> {
    using addon_host_type = permission;
    // Specify the scan ranges.
    static constexpr int value_ranges[][2] = {
        KON_QI_ENUM_POINT_RANGE(addon_host_type::read),
        KON_QI_ENUM_POINT_RANGE(addon_host_type::write),
        KON_QI_ENUM_POINT_RANGE(addon_host_type::execute),
        KON_QI_ENUM_POINT_RANGE(addon_host_type::all),
    };
};
} // namespace kon::qi

using minfo = kon::qi::reflect_e<permission>;
using addon = minfo::addon_type;

static_assert(minfo::min() == permission::read);
static_assert(minfo::max() == permission::all);

static_assert(minfo::to_name(permission::read) == std::string_view{"read"});
static_assert(minfo::to_name(permission::write) == std::string_view{"write"});
static_assert(minfo::to_name(permission::execute) == std::string_view{"execute"});
static_assert(minfo::to_name(permission::all) == std::string_view{"all"});

int main(int argc, char *argv[]) {
    return 0;
}