/*
 * Copyright (c) 2022-2023, Sam Atkins <atkinssj@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/String.h>
#include <LibWeb/Forward.h>

namespace Web::CSS {
class Frequency {
public:
    enum class Type {
        Hz,
        kHz
    };

    static Optional<Type> unit_from_name(StringView);

    Frequency(int value, Type type);
    Frequency(float value, Type type);
    static Frequency make_hertz(float);
    Frequency percentage_of(Percentage const&) const;

    ErrorOr<String> to_string() const;
    float to_hertz() const;

    bool operator==(Frequency const& other) const
    {
        return m_type == other.m_type && m_value == other.m_value;
    }

private:
    StringView unit_name() const;

    Type m_type;
    float m_value { 0 };
};

}

template<>
struct AK::Formatter<Web::CSS::Frequency> : Formatter<StringView> {
    ErrorOr<void> format(FormatBuilder& builder, Web::CSS::Frequency const& frequency)
    {
        return Formatter<StringView>::format(builder, TRY(frequency.to_string()));
    }
};
