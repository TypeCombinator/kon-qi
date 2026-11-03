// Copyright (c) 2026 TypeCombinator <typecombinator@foxmail.com>
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <kon/qi/enum.hpp>

namespace kq_addon_enum_test {
enum class foo : int {
    a,
    b,
    c,
    d
};
enum class foo_sparse : int {
    a,
    b,
    c = 1000,
    d
};
} // namespace kq_addon_enum_test

namespace kon::qi {
template <>
struct addon_register<kq_addon_enum_test::foo> {
    using addon_host_type = kq_addon_enum_test::foo;
    static constexpr int value_ranges[][2] = {
        {0, 10},
    };
    KON_QI_ADDON_E(a, 100, nullptr);
    KON_QI_ADDON_E(b, 'X');
    KON_QI_ADDON_E(c);

    KON_QI_ADDON_INIT();
};

template <>
struct addon_register<kq_addon_enum_test::foo_sparse> {
    using addon_host_type = kq_addon_enum_test::foo_sparse;
    static constexpr int value_ranges[][2] = {
        {   0,   10},
        {1000, 1010},
    };
    KON_QI_ADDON_E(a, 100, nullptr);
    KON_QI_ADDON_E(b, 'X');
    KON_QI_ADDON_E(c);

    KON_QI_ADDON_INIT();
};
} // namespace kon::qi

namespace kq_addon_enum_test {
static_assert(kon::qi::default_enum_value_ranges<char>[0][0] < 0);
static_assert(kon::qi::default_enum_value_ranges<short>[0][0] < 0);
static_assert(kon::qi::default_enum_value_ranges<int>[0][0] < 0);
static_assert(kon::qi::default_enum_value_ranges<long>[0][0] < 0);
static_assert(kon::qi::default_enum_value_ranges<long long>[0][0] < 0);

static_assert(kon::qi::default_enum_value_ranges<unsigned char>[0][0] == 0);
static_assert(kon::qi::default_enum_value_ranges<unsigned short>[0][0] == 0);
static_assert(kon::qi::default_enum_value_ranges<unsigned>[0][0] == 0);
static_assert(kon::qi::default_enum_value_ranges<unsigned long>[0][0] == 0);
static_assert(kon::qi::default_enum_value_ranges<unsigned long long>[0][0] == 0);

template <typename ET>
consteval bool test_enum_foo_addon() noexcept {
    using minfo = kon::qi::reflect_e<ET>;
    using addon = minfo::addon_type;

    static_assert(kon::qi::have_enum_value_ranges<addon>);

    static_assert(minfo::size() == 4);

    using foo_a_addon = addon::template of<kon::qi::addon_tag<ET::a>>;
    static_assert(foo_a_addon::size() == 2);
    static_assert(foo_a_addon::template get<0>() == 100);
    static_assert(foo_a_addon::template get<1>() == nullptr);

    using foo_b_addon = addon::template of<kon::qi::addon_tag<ET::b>>;
    static_assert(foo_b_addon::size() == 1);
    static_assert(foo_b_addon::template get<0>() == 'X');

    using foo_c_addon = addon::template of<kon::qi::addon_tag<ET::c>>;
    static_assert(foo_c_addon::size() == 0);

    using foo_d_addon = addon::template of<kon::qi::addon_tag<ET::d>>;
    static_assert(foo_d_addon::size() == 0);
    return true;
}

static_assert(test_enum_foo_addon<foo>());
static_assert(test_enum_foo_addon<foo_sparse>());

using foo_minfo = kon::qi::reflect_e<foo_sparse>;
static_assert(!foo_minfo::is_continuous());
static_assert(static_cast<int>(foo_minfo::min()) == 0);
static_assert(static_cast<int>(foo_minfo::max()) == 1001);

static_assert(foo_minfo::to_name(foo_sparse::a) == std::string_view{"a"});
static_assert(foo_minfo::to_name(foo_sparse::b) == std::string_view{"b"});
static_assert(foo_minfo::to_name(foo_sparse::c) == std::string_view{"c"});
static_assert(foo_minfo::to_name(foo_sparse::d) == std::string_view{"d"});
} // namespace kq_addon_enum_test

namespace kq_addon_sparse_enum_test {
enum class foo_bit : int {
    a = 0x20,
    b = 0x40,
    c = 0x80,
    d = 0x100,
};
} // namespace kq_addon_sparse_enum_test

namespace kon::qi {
template <>
struct addon_register<kq_addon_sparse_enum_test::foo_bit> {
    using addon_host_type = kq_addon_sparse_enum_test::foo_bit;
    static constexpr int value_ranges[][2] = {
        KON_QI_ENUM_POINT_RANGE(addon_host_type::a),
        KON_QI_ENUM_POINT_RANGE(addon_host_type::b),
        KON_QI_ENUM_POINT_RANGE(addon_host_type::c),
        KON_QI_ENUM_POINT_RANGE(addon_host_type::d),
    };
};
} // namespace kon::qi

namespace kq_addon_sparse_enum_test {
using minfo = kon::qi::reflect_e<foo_bit>;
using addon = minfo::addon_type;

static_assert(kon::qi::have_enum_value_ranges<addon>);
static_assert(minfo::size() == 4);
static_assert(!minfo::is_continuous());

static_assert(static_cast<int>(minfo::min()) == 0x20);
static_assert(static_cast<int>(minfo::max()) == 0x100);

static_assert(minfo::to_name(foo_bit::a) == std::string_view{"a"});
static_assert(minfo::to_name(foo_bit::b) == std::string_view{"b"});
static_assert(minfo::to_name(foo_bit::c) == std::string_view{"c"});
static_assert(minfo::to_name(foo_bit::d) == std::string_view{"d"});
} // namespace kq_addon_sparse_enum_test