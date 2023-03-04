//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <catch2/catch.hpp>
#include "libmodel/guards/is_item_winning.hpp"
#include "libconfig/config.hpp"
#include "libmodel/board.hpp"
#include <libcore/Warnings.hpp>

DISABLE_WARNING_PUSH
DISABLE_WARNING_MISSING_FIELD_INITIALIZER

SCENARIO("no winning", "[guards]")
{
  using namespace match3;
  GIVEN("is item no winning")
  {
    board b{{1, 2, 3, 4, 5, 6}, config{.board_width = 3}};
    REQUIRE(!is_item_winning(b, {0}));
    REQUIRE(!is_item_winning(b, {1}));
    REQUIRE(!is_item_winning(b, {2}));
    REQUIRE(!is_item_winning(b, {3}));
    REQUIRE(!is_item_winning(b, {4}));
    REQUIRE(!is_item_winning(b, {5}));
  }

  GIVEN("is item winning")
  {
    board b{{1, 2, 3, 2, 2, 2}, config{.board_width = 3}};

    REQUIRE(!is_item_winning(b, {0}));
    REQUIRE(!is_item_winning(b, {1}));
    REQUIRE(!is_item_winning(b, {2}));
    REQUIRE(is_item_winning(b, {3}));
    REQUIRE(is_item_winning(b, {4}));
    REQUIRE(is_item_winning(b, {5}));
  }
}
DISABLE_WARNING_POP
