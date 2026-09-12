#include <kon/qi/enum.hpp>

enum class system_error : int {
    a,
    b,
    c = 1000,
    d,
};

namespace kon::qi {
template <>
struct addon_register<system_error> {
    using addon_host_type = system_error;
    // Specify the scan range.
    static constexpr int value_range[][2] = {
        {   0,   10},
        {1000, 1010},
    };
    KON_QI_ADDON_E(a, 'A', 0);
    KON_QI_ADDON_E(b, 'B');
    KON_QI_ADDON_E(c); // Empty annotation for the c.
    // No annotation for the d.

    KON_QI_ADDON_INIT();
};
} // namespace kon::qi

using minfo = kon::qi::reflect_e<system_error>;
using addon = minfo::addon_type;

static_assert(minfo::min() == system_error::a);
static_assert(minfo::max() == system_error::d);

static_assert(minfo::to_value_from_rank(minfo::to_rank("a")) == system_error::a);
static_assert(minfo::to_value_from_rank(minfo::to_rank("d")) == system_error::d);

using ea_addon = addon::of<kon::qi::addon_tag<system_error::a>>;
static_assert(ea_addon::size() == 2);
static_assert(ea_addon::get<0>() == 'A');
static_assert(ea_addon::get<1>() == 0);

using eb_addon = addon::of<kon::qi::addon_tag<system_error::b>>;
static_assert(eb_addon::size() == 1);
static_assert(eb_addon::get<0>() == 'B');

using ec_addon = addon::of<kon::qi::addon_tag<system_error::c>>;
static_assert(ec_addon::size() == 0);

using ed_addon = addon::of<kon::qi::addon_tag<system_error::d>>;
static_assert(ed_addon::size() == 0);

int main(int argc, char *argv[]) {
    return 0;
}