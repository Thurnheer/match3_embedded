// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <catch2/catch.hpp>
#include "libcontroller/actions/find_matches.hpp"
#include <range/v3/algorithm/equal.hpp>
#include <vector>
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

SCENARIO("matches", "[actions]")
{
  using namespace match3;
  GIVEN("find matches empty") {
    board b{{1, 2, 3, 4}, config{.board_width = 2}};
    selected s = {0, 1};
    struct {
      int arity;
      mutable std::vector<board::color_t> matches = {};
    } event{int(s.size())};

    find_matches(b, event, s);

    REQUIRE(s.empty());
    REQUIRE(event.matches.empty());
  };

  GIVEN("find matches") {
    board b{{1, 2, 3, 1, 3, 2, 1, 2, 3}, config{.board_width = 3}};
    selected s = {0};
    struct {
      int arity;
      mutable std::vector<board::color_t> matches = {};
    } event{int(s.size())};

    find_matches(b, event, s);

    REQUIRE(s.empty());
    REQUIRE(equal_to({0, 3, 6}, event.matches));
  };

  GIVEN("find matches more") {
    board b{{1, 2, 3, 1, 1, 1, 1, 2, 3}, config{.board_width = 3}};
    selected s = {1, 3};
    struct {
      int arity;
      mutable std::vector<board::color_t> matches = {};
    } event{int(s.size())};

    find_matches(b, event, s);

    REQUIRE(s.empty());
    REQUIRE(equal_to({0, 3, 4, 5, 6}, event.matches));
  };
}

DISABLE_WARNING_POP
