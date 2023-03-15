// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <catch2/catch.hpp>
#include "libcontroller/actions/drop_item.hpp"

SCENARIO("drop", "[actions]")
{
  using namespace match3;
  GIVEN("drop item")
  {
    selected s = {1};
    drop_item(s);
    REQUIRE(s.empty());
  }
}
