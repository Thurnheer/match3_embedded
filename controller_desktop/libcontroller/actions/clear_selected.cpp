// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <catch2/catch.hpp>
#include "libcontroller/actions/clear_selected.hpp"

SCENARIO("clear selected", "[actions]")
{
  using namespace match3;

  GIVEN("clear selected")
  {
    selected s = {1, 2, 3};
    clear_selected(s);
    REQUIRE(s.empty());
  }
}
