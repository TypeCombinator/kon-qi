// SPDX-FileCopyrightText: 2026 TypeCombinator <typecombinator@foxmail.com>
//
// SPDX-License-Identifier: BSD 3-Clause

#ifndef ADDON_1A34AF33_3863_4910_984C_743C4E4BD1CD
#define ADDON_1A34AF33_3863_4910_984C_743C4E4BD1CD
#include <kon/qi/pack.hpp>

#define KON_QI_ADDON_M(_m_, ...)                                                                   \
    static kon::qi::value_pack<__VA_ARGS__> of_impl(                                               \
        kon::qi::addon_tag<&(CODECL<addon_host_type>._m_)>)

#define KON_QI_ADDON_E(_e_, ...)                                                                   \
    static kon::qi::value_pack<__VA_ARGS__> of_impl(kon::qi::addon_tag<addon_host_type::_e_>)

#define KON_QI_ADDON_INIT()                                                                        \
    template <auto maddr>                                                                          \
    static kon::qi::value_pack<> of_impl(kon::qi::addon_tag<maddr>);                               \
    template <typename Tag>                                                                        \
    using of = decltype(of_impl(Tag{}))

namespace kon {
//
namespace qi {
template <auto V>
struct addon_tag { };

template <typename T>
struct addon_register {
    KON_QI_ADDON_INIT();
    // Empty addon.
};

template <typename T>
concept has_internal_addon = requires() { typename T::template addon_register<>; };

template <typename T>
concept has_external_addon = requires() { typename addon_register<T>::addon_host_type; };

template <typename Addon>
concept has_enum_value_range = requires() { Addon::value_range; };
} // namespace qi
} // namespace kon


#endif // addon.hpp