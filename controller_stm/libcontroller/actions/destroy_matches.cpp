// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <catch2/catch.hpp>
#include "libcontroller/actions/destroy_matches.hpp"
#include <range/v3/algorithm/equal.hpp>
#include <vector>
#include "common/utils.hpp"
#include "libmodel/board.hpp"
#include <libcore/Warnings.hpp>

DISABLE_WARNING_PUSH
DISABLE_WARNING_MISSING_FIELD_INITIALIZER

SCENARIO("destroy", "[actions]")
{
  using namespace match3;

  GIVEN("destroy matches")
  {
    constexpr auto width = 3;
    constexpr auto height = 3;

    board b{{4, 2, 3, 3, 2, 2, 1, 2, 3},
            config{.board_width = width, .board_height = height}};
    struct {
      std::vector<board::color_t> matches;
    } event{{1, 4, 7}};

    destroy_matches(b, event);

    REQUIRE(equal<width * height>({4, 0, 3, 3, 0, 2, 1, 0, 3}, b));
  }
}
DISABLE_WARNING_POP
