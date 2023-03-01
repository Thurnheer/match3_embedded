//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <catch2/catch.hpp>
#include "libcontroller/guards/is_key.hpp"

SCENARIO("", "[guards]")
{
  using namespace match3;
  GIVEN("is key")
  {
    constexpr auto key = 42;
    struct {
      int key;
    } event{key};
    REQUIRE(is_key(key)(event));
  }

  GIVEN("is not key")
  {
    constexpr auto key = 42;
    struct {
      int key;
    } event{0};
    REQUIRE(!is_key(key)(event));
  }
}
