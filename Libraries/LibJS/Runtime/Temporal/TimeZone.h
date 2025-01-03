/*
 * Copyright (c) 2021-2023, Linus Groh <linusg@serenityos.org>
 * Copyright (c) 2024, Tim Flynn <trflynn89@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/String.h>
#include <AK/Vector.h>
#include <LibCrypto/BigInt/SignedBigInteger.h>
#include <LibJS/Runtime/Completion.h>
#include <LibJS/Runtime/Temporal/AbstractOperations.h>
#include <LibJS/Runtime/Value.h>

namespace JS::Temporal {

struct TimeZone {
    Optional<String> name;
    Optional<i64> offset_minutes;
};

enum class Disambiguation {
    Compatible,
    Earlier,
    Later,
    Reject,
};

ISODateTime get_iso_parts_from_epoch(Crypto::SignedBigInteger const& epoch_nanoseconds);
String format_offset_time_zone_identifier(i64 offset_minutes, Optional<TimeStyle> = {});
String format_date_time_utc_offset_rounded(i64 offset_nanoseconds);
ThrowCompletionOr<String> to_temporal_time_zone_identifier(VM&, Value temporal_time_zone_like);
i64 get_offset_nanoseconds_for(StringView time_zone, Crypto::SignedBigInteger const& epoch_nanoseconds);
ISODateTime get_iso_date_time_for(StringView time_zone, Crypto::SignedBigInteger const& epoch_nanoseconds);
ThrowCompletionOr<String> to_temporal_time_zone_identifier(VM&, StringView temporal_time_zone_like);
ThrowCompletionOr<Crypto::SignedBigInteger> get_epoch_nanoseconds_for(VM&, StringView time_zone, ISODateTime const&, Disambiguation);
ThrowCompletionOr<Crypto::SignedBigInteger> disambiguate_possible_epoch_nanoseconds(VM&, Vector<Crypto::SignedBigInteger> possible_epoch_ns, StringView time_zone, ISODateTime const&, Disambiguation);
ThrowCompletionOr<Vector<Crypto::SignedBigInteger>> get_possible_epoch_nanoseconds(VM&, StringView time_zone, ISODateTime const&);
ThrowCompletionOr<TimeZone> parse_time_zone_identifier(VM&, StringView identifier);
TimeZone parse_time_zone_identifier(StringView identifier);
TimeZone parse_time_zone_identifier(ParseResult const&);

}
