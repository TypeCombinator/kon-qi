// Copyright (c) 2026 TypeCombinator <typecombinator@foxmail.com>
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef ADDON_1A34AF33_3863_4910_984C_743C4E4BD1CD
#define ADDON_1A34AF33_3863_4910_984C_743C4E4BD1CD
#include <kon/qi/pack.hpp>

#if defined(KON_QI_ENABLE_INLINE_ADDON)
    // Inline addon for the struct member.
    #if _MSC_VER && not defined(__clang__)
template <auto V>
struct value_identity {
    static constexpr auto value = V;
};

        #define KON_QI_IADDON_M(_m_, ...)                                                          \
            _m_;                                                                                   \
            template <typename AHT>                                                                \
            static kon::qi::value_pack<__VA_ARGS__> of_impl(                                       \
                kon::qi::addon_tag<static_cast<const void *>(                                      \
                    value_identity<&(CODECL<AHT>._m_)>::value)>)
    #else
        #define KON_QI_IADDON_M(_m_, ...)                                                          \
            _m_;                                                                                   \
            template <typename AHT>                                                                \
            static kon::qi::value_pack<__VA_ARGS__> of_impl(                                       \
                kon::qi::addon_tag<static_cast<const void *>(&(CODECL<AHT>._m_))>)
    #endif

    #define KON_QI_IADDON_INIT()                                                                   \
        template <typename AHT>                                                                    \
        static kon::qi::value_pack<> of_impl(auto);                                                \
        template <typename AddonTag>                                                               \
        using of = decltype(of_impl<addon_host_type>(AddonTag{}))
#endif

#if _MSC_VER && not defined(__clang__)
    #define KON_QI_ADDON_M(_m_, ...)                                                               \
        static constexpr auto __mptr_##_m_ = &CODECL<addon_host_type>._m_;                         \
        static kon::qi::value_pack<__VA_ARGS__> of_impl(                                           \
            kon::qi::addon_tag<static_cast<const void *>(__mptr_##_m_)>)
#else
    #define KON_QI_ADDON_M(_m_, ...)                                                               \
        static kon::qi::value_pack<__VA_ARGS__> of_impl(                                           \
            kon::qi::addon_tag<static_cast<const void *>(&(CODECL<addon_host_type>._m_))>)
#endif

#define KON_QI_ADDON_E(_e_, ...)                                                                   \
    static kon::qi::value_pack<__VA_ARGS__> of_impl(kon::qi::addon_tag<addon_host_type::_e_>)

#define KON_QI_ADDON_INIT()                                                                        \
    template <auto MAddr>                                                                          \
    static kon::qi::value_pack<> of_impl(kon::qi::addon_tag<MAddr>);                               \
    template <typename AddonTag>                                                                   \
    using of = decltype(of_impl(AddonTag{}))

namespace kon {
//
namespace qi {
template <auto V>
struct addon_tag { };

template <typename T>
struct addon_register {
    // No annotation by default.
    KON_QI_ADDON_INIT();
};

template <typename T>
concept has_inline_addon = requires() { typename T::addon_host_type; };

template <typename T>
concept has_internal_addon = requires() { typename T::template addon_register<>; };

template <typename T>
concept has_external_addon = requires() { typename addon_register<T>::addon_host_type; };

template <typename Addon>
concept has_enum_value_range = requires() { Addon::value_range; };

template <typename Addon>
concept has_struct_count_range = requires() { Addon::count_range; };
} // namespace qi
} // namespace kon


#endif // addon.hpp