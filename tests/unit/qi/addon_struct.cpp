#include <kon/qi/struct.hpp>

namespace kq_addon_struct_test {
template <char V>
struct foo {
    int a;
    double b;
    const char c;
    short d;

    template <typename addon_host_type = foo>
    struct addon_register {
        static constexpr std::size_t count_range[2] = {3, 10};

        KON_QI_ADDON_M1(a, 100, nullptr);
        KON_QI_ADDON_M1(b, V);
        KON_QI_ADDON_M1(c);

        KON_QI_ADDON_INIT1();
    };
};

static_assert(kon::qi::has_internal_addon<foo<'X'>>);
static_assert(!kon::qi::has_external_addon<foo<'X'>>);

template <typename T, char V>
consteval bool test_struct_foo_addon() noexcept {
    using minfo = kon::qi::s_reflect<T>;
    using addon = minfo::addon_type;

    using foo_a_addon = addon::template of<typename minfo::template addon_tag_t<0>>;
    static_assert(foo_a_addon::size() == 2);
    static_assert(foo_a_addon::template get<0>() == 100);
    static_assert(foo_a_addon::template get<1>() == nullptr);

    using foo_b_addon = addon::template of<typename minfo::template addon_tag_t<1>>;
    static_assert(foo_b_addon::size() == 1);
    static_assert(foo_b_addon::template get<0>() == V);

    using foo_c_addon = addon::template of<typename minfo::template addon_tag_t<2>>;
    static_assert(foo_c_addon::size() == 0);

    using foo_d_addon = addon::template of<typename minfo::template addon_tag_t<3>>;
    static_assert(foo_c_addon::size() == 0);
    return true;
}

static_assert(test_struct_foo_addon<foo<'X'>, 'X'>());
static_assert(test_struct_foo_addon<foo<'Y'>, 'Y'>());

template <char V>
struct foo_ext {
    int a;
    double b;
    const char c;
    short d;
};
} // namespace kq_addon_struct_test

namespace kon::qi {
template <char V>
struct addon_register<kq_addon_struct_test::foo_ext<V>> {
    using addon_host_type = kq_addon_struct_test::foo_ext<V>;
    static constexpr std::size_t count_rasnge[2] = {3, 10};

    KON_QI_ADDON_M1(a, 100, nullptr);
    KON_QI_ADDON_M1(b, V);
    KON_QI_ADDON_M1(c);

    KON_QI_ADDON_INIT1();
};
} // namespace kon::qi

namespace kq_addon_struct_test {
static_assert(!kon::qi::has_internal_addon<foo_ext<'X'>>);
static_assert(kon::qi::has_external_addon<foo_ext<'X'>>);

static_assert(test_struct_foo_addon<foo_ext<'X'>, 'X'>());
static_assert(test_struct_foo_addon<foo_ext<'Y'>, 'Y'>());
} // namespace kq_addon_struct_test