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
    static constexpr kon::qi::enum_range<addon_host_type> value_ranges[] = {
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
    static constexpr kon::qi::enum_range<addon_host_type> value_ranges[] = {
        {   0, 10},
        {1000, 10},
    };
    KON_QI_ADDON_E(a, 100, nullptr);
    KON_QI_ADDON_E(b, 'X');
    KON_QI_ADDON_E(c);

    KON_QI_ADDON_INIT();
};
} // namespace kon::qi

namespace kq_addon_enum_test {
template <typename T>
struct empty {
    enum class type : T {
    };
};

static_assert(kon::qi::default_enum_value_ranges<empty<char>::type>[0].m_min < 0);
static_assert(kon::qi::default_enum_value_ranges<empty<short>::type>[0].m_min < 0);
static_assert(kon::qi::default_enum_value_ranges<empty<int>::type>[0].m_min < 0);
static_assert(kon::qi::default_enum_value_ranges<empty<long>::type>[0].m_min < 0);
static_assert(kon::qi::default_enum_value_ranges<empty<long long>::type>[0].m_min < 0);

static_assert(kon::qi::default_enum_value_ranges<empty<unsigned char>::type>[0].m_min == 0);
static_assert(kon::qi::default_enum_value_ranges<empty<unsigned short>::type>[0].m_min == 0);
static_assert(kon::qi::default_enum_value_ranges<empty<unsigned int>::type>[0].m_min == 0);
static_assert(kon::qi::default_enum_value_ranges<empty<unsigned long>::type>[0].m_min == 0);
static_assert(kon::qi::default_enum_value_ranges<empty<unsigned long long>::type>[0].m_min == 0);

template <typename ET>
consteval bool test_enum_foo_addon() noexcept {
    using minfo = kon::qi::reflect_e<ET>;
    using addon = minfo::addon_type;

    static_assert(kon::qi::has_enum_value_ranges<addon>);

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