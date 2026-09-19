// Copyright (c) 2026 TypeCombinator <typecombinator@foxmail.com>
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <kon/qi/struct.hpp>

// Only aggregate types are supported.
struct point {
    double x;
    double y;
    double z;
};

using minfo = kon::qi::reflect_s<point>;

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