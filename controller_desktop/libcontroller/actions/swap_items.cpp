// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <catch2/catch.hpp>
#include "libcontroller/actions/swap_items.hpp"
#include <range/v3/algorithm/equal.hpp>
#include "common/utils.hpp"
#include "libconfig/config.hpp"
#include "libmodel/board.hpp"

SCENARIO("swap", "[actions]")
{
  using namespace match3;

  GIVEN("swap items") {
    board b{{1, 2}, config{}};
    selected s = {0, 1};
    swap_items(s, b);
    REQUIRE(equal<2>({2, 1}, b));
  }
}
