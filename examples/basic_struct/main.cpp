#include <kon/qi/struct.hpp>

struct point {
    double x;
    double y;
    double z;
};

using minfo = kon::qi::s_reflect<point>;

static_assert(minfo::size() == 3);
static_assert(minfo::member_name(0) == std::string_view{"x"});
static_assert(minfo::member_name(1) == std::string_view{"y"});
static_assert(minfo::member_name(2) == std::string_view{"z"});

static_assert(minfo::member_name<0>() == std::string_view{"x"});
static_assert(minfo::member_name<1>() == std::string_view{"y"});
static_assert(minfo::member_name<2>() == std::string_view{"z"});

static_assert(minfo::member_offset(0) == 0);
static_assert(minfo::member_offset(1) == 8);
static_assert(minfo::member_offset(2) == 16);

static_assert(minfo::member_offset<0>() == 0);
static_assert(minfo::member_offset<1>() == 8);
static_assert(minfo::member_offset<2>() == 16);

int main(int argc, char* argv[]) {
    return 0;
}