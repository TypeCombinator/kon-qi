#include <kon/qi/enum.hpp>

enum class color : unsigned {
    red,
    green,
    blue
};

using minfo = kon::qi::e_reflect<color>;

static_assert(minfo::to_name(color::red) == std::string_view{"red"});
static_assert(minfo::to_name(color::green) == std::string_view{"green"});
static_assert(minfo::to_name(color::blue) == std::string_view{"blue"});

static_assert(minfo::to_name(static_cast<color>(10)) == std::string_view{""});
static_assert(minfo::to_name(static_cast<color>(10), "invalid") == std::string_view{"invalid"});

int main(int argc, char* argv[]) {
    return 0;
}