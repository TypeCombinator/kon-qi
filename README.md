# `kon::qi`

`kon::qi` is header-only reflection library for C++20 with **annotation** support.

## Features

- **Annotations**: Attach arbitrary compile-time metadata to enum and struct, just like C++26.
- **Enum reflection with multi-interval scanning**: Declare any number of disjoint value ranges to scan, so sparse enums cost almost no extra compile time.
- **Optimized aggregate member count scanning**: Use binary search for scanning, and support scanning within a specified interval.
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

using minfo = kon::qi::e_reflect<color>;

static_assert(minfo::to_name(color::red) == std::string_view{"red"});
static_assert(minfo::to_name(color::green) == std::string_view{"green"});
static_assert(minfo::to_name(color::blue) == std::string_view{"blue"});

static_assert(minfo::to_name(static_cast<color>(10)) == std::string_view{""});
static_assert(minfo::to_name(static_cast<color>(10), "invalid") == std::string_view{"invalid"});
```

#### Struct (Only aggregate types are supported)

```c++
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
```

### Annotation

#### Enum with annotations

#### Struct with annotations