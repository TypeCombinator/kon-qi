#include <kon/qi/struct.hpp>

struct point {
    double x;
    double y;
    double z;
};

namespace kon::qi {
template <>
struct addon_register<point> {
    using addon_host_type = point;
    // Specify the range of the number of struct members.
    static constexpr std::size_t count_range[2] = {0, 5};

    KON_QI_ADDON_M(x, 10, 'X');
    KON_QI_ADDON_M(y, 20);
    // No annotation for the z.

    KON_QI_ADDON_INIT();
};

static_assert(kon::qi::has_struct_count_range<addon_register<point>>);
} // namespace kon::qi

using minfo = kon::qi::reflect_s<point>;
using addon = minfo::addon_type;

static_assert(kon::qi::has_struct_count_range<addon>);

using px_addon = addon::of<minfo::addon_tag_t<0>>;
static_assert(px_addon::size() == 2);
static_assert(px_addon::get<0>() == 10);
static_assert(px_addon::get<1>() == 'X');

using py_addon = addon::of<minfo::addon_tag_t<1>>;
static_assert(py_addon::size() == 1);
static_assert(py_addon::get<0>() == 20);

using pz_addon = addon::of<minfo::addon_tag_t<2>>;
static_assert(pz_addon::size() == 0);

int main(int argc, char *argv[]) {
    return 0;
}