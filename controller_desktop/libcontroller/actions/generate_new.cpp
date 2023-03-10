// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <catch2/catch.hpp>
#include "libcontroller/actions/generate_new.hpp"
#include <range/v3/algorithm/equal.hpp>
#include "common/utils.hpp"
#include "libconfig/config.hpp"
#include "libmodel/board.hpp"
#include <libcore/Warnings.hpp>

DISABLE_WARNING_PUSH
DISABLE_WARNING_MISSING_FIELD_INITIALIZER

template <typename R, typename T>
constexpr bool equal_to(std::initializer_list<T> il, R&& r) 
{
    return ranges::equal(r, il);
}

SCENARIO("new", "[actions]")
{
  using namespace match3;

  GIVEN("generate new") {
    static constexpr auto NEW = 42;
    constexpr auto width = 3;
    constexpr auto height = 3;
    board b{{4, 0, 3, 3, 0, 2, 1, 0, 3},
            config{.board_width = width, .board_height = height}};
    selected s = {0, 5};
    generate_new(b, s, config{.board_width = width, .board_height = height},
                 [](auto...) { return NEW; });

    REQUIRE(equal<width * height>({4, NEW, 3, 3, NEW, 2, 1, NEW, 3}, b));
    REQUIRE(equal_to({0, 1, 2, 3, 4, 5, 6, 7, 8}, s));
  }
}
DISABLE_WARNING_POP
