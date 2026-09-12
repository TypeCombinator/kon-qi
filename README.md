# `kon::qi`

`kon::qi` is header-only reflection library for C++20 with **annotation** support.

## Features

- **Annotations**: Attach arbitrary compile-time metadata to enum and struct, just like C++26.
- **Enum reflection with multi-interval scanning**: Declare any number of disjoint value ranges to scan, so sparse enums cost almost no extra compile time.
- **Optimized aggregate member count scanning**: Use *binary search* for scanning, and support scanning within a specified interval.
- **Near-zero dependencies**: Only depends on the standard library's `<string_view>`, no `<array>`, no `<tuple>`!
- **Only a few macros**: Macros are only needed when annotations are required, and these macros are only intended to reduce boilerplate code, so they are not mandatory either.

## Examples

### Basic

#### Enum

```c++
#include <kon/qi/enum.hpp>

enum class color : unsigned {
    red,
    green,
    blue
};

using minfo = kon::qi::reflect_e<color>;

static_assert(minfo::to_name(color::red) == std::string_view{"red"});
static_assert(minfo::to_name(color::green) == std::string_view{"green"});
static_assert(minfo::to_name(color::blue) == std::string_view{"blue"});

static_assert(minfo::to_name(static_cast<color>(10)) == std::string_view{""});
static_assert(minfo::to_name(static_cast<color>(10), "invalid") == std::string_view{"invalid"});
```

#### Struct

```c++
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
```

### Annotation

The word `annotation` is too long, so this library uses `addon` instead. As you know, naming is a hard problem.

#### Enum with annotations

```c++
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
```

#### Struct with internal annotations

```c++
#include <kon/qi/struct.hpp>

struct point {
    double x;
    double y;
    double z;

    template <typename addon_host_type = point>
    struct addon_register {
        // Specify the range of the number of struct members.
        static constexpr std::size_t count_range[2] = {0, 5};

        KON_QI_ADDON_M(x, 10, 'X');
        KON_QI_ADDON_M(y, 20);
        // No annotation for the z.

        KON_QI_ADDON_INIT();
    };
};

using minfo = kon::qi::reflect_s<point>;
using addon = minfo::addon_type;

using pa_addon = addon::of<minfo::addon_tag_t<0>>;
static_assert(pa_addon::size() == 2);
static_assert(pa_addon::get<0>() == 10);
static_assert(pa_addon::get<1>() == 'X');

using py_addon = addon::of<minfo::addon_tag_t<1>>;
static_assert(py_addon::size() == 1);
static_assert(py_addon::get<0>() == 20);

using pz_addon = addon::of<minfo::addon_tag_t<2>>;
static_assert(pz_addon::size() == 0);
```

#### Struct with external annotations

```c++
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
} // namespace kon::qi

using minfo = kon::qi::reflect_s<point>;
using addon = minfo::addon_type;

using pa_addon = addon::of<minfo::addon_tag_t<0>>;
static_assert(pa_addon::size() == 2);
static_assert(pa_addon::get<0>() == 10);
static_assert(pa_addon::get<1>() == 'X');

using py_addon = addon::of<minfo::addon_tag_t<1>>;
static_assert(py_addon::size() == 1);
static_assert(py_addon::get<0>() == 20);

using pz_addon = addon::of<minfo::addon_tag_t<2>>;
static_assert(pz_addon::size() == 0);
```

### Others

#### Opinter to member

```c++
#include <kon/qi/member.hpp>

struct foo {
    int a;
    char b;
    const double c;
};

static_assert(kon::qi::member_name<&foo::a>() == std::string_view{"a"});
static_assert(kon::qi::member_name<&foo::b>() == std::string_view{"b"});
static_assert(kon::qi::member_name<&foo::c>() == std::string_view{"c"});

static_assert(kon::qi::offset_of(&foo::a) == 0);
static_assert(kon::qi::offset_of(&foo::b) == 4);
static_assert(kon::qi::offset_of(&foo::c) == 8);
```

## How to build

```shell
cmake -B build/release \
-G Ninja \
-DKON_QI_BUILD_EXAMPLES=ON \
-DKON_QI_BUILD_TESTING=ON \
-DCMAKE_BUILD_TYPE=Release
```

## Inspiration

The [qlibs/reflect](https://github.com/qlibs/reflect) library provided some inspiration, but it lacks annotation support. Because `kon::qi` implements annotations, its implementation of enum reflection is no longer limited by scan ranges. In addition, this library includes numerous optimizations at the implementation level, minimizing repeated compile-time computations.
