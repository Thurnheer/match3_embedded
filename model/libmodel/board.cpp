//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <catch2/catch.hpp>
#include "libmodel/board.hpp"
#include <range/v3/algorithm/equal.hpp>
 
template <typename R, typename T>
constexpr bool equal_to(std::initializer_list<T> il, R&& r) 
{
    return ranges::equal(r, il);
}

SCENARIO("", "[model]")
{
  using namespace match3::board_logic;

  GIVEN("row") {
    int v[] = {1, 2, 3, 4, 5, 6};
    REQUIRE(equal_to({1, 2}, row(v, 0, 2)));
    REQUIRE(equal_to({3, 4}, row(v, 1, 2)));
    REQUIRE(equal_to({5, 6}, row(v, 2, 2)));
    REQUIRE(equal_to({1, 2, 3}, row(v, 0, 3)));
  }

  GIVEN("col") {
    int v[] = {1, 2, 3, 4, 5, 6};
    REQUIRE(equal_to({1, 3, 5}, col(v, 0, 2)));
    REQUIRE(equal_to({2, 4, 6}, col(v, 1, 2)));
    REQUIRE(equal_to({1, 4}, col(v, 0, 3)));
  }

  GIVEN("match n fail") {
    int v[] = {1, 3, 2, 3, 2};
    auto m = match_n(v, 3);
    REQUIRE(0 == m.begin);
    REQUIRE(0 == m.length);
  }

  GIVEN("match n success 3") {
    int v[] = {1, 3, 3, 3, 2};
    auto m = match_n(v, 3);
    REQUIRE(1 == m.begin);
    REQUIRE(3 == m.length);
  }

  GIVEN("match n success 4") {
    int v[] = {1, 3, 3, 3, 3, 2};
    auto m = match_n(v, 3);
    REQUIRE(1 == m.begin);
    REQUIRE(4 == m.length);
  }

  GIVEN("match n success 5") {
    int v[] = {1, 2, 3, 3, 3, 3, 3, 1, 2};
    auto m = match_n(v, 3);
    REQUIRE(2 == m.begin);
    REQUIRE(5 == m.length);
  }

  GIVEN("is match fail") {
    int v[] = {1, 2, 3, 4, 3, 6, 7, 2, 9};

    REQUIRE(!is_match(v, 1, 3));
  }

  GIVEN("is match success") {
    int v[] = {1, 2, 3, 4, 2, 6, 7, 2, 9};

    REQUIRE(is_match(v, 1, 3));
  }

  GIVEN("match fail") {
    int v[] = {1, 2, 3, 4, 3, 3, 7, 2, 4};

    REQUIRE(std::vector<int>{} == (match(v, 2, 3) | ranges::to<std::vector<int>>));
  }

  GIVEN("match success") {
    int v[] = {1, 2, 3, 4, 3, 3, 7, 2, 3};

    REQUIRE(equal_to({2, 5, 8}, match(v, 2, 3)));
  }

  GIVEN("scroll") {
    int v[] = {1, 1, 3, 4, 0, 2, 7, 2, 3};

    scroll(v, 4, 3);

    REQUIRE(equal_to({1, 0, 3, 4, 1, 2, 7, 2, 3}, v));
  }

  GIVEN("scroll many") {
    int v[] = {1, 1, 3, 4, 0, 2, 7, 0, 3};

    scroll(v, 4, 3);
    REQUIRE(equal_to({1, 0, 3, 4, 1, 2, 7, 0, 3}, v));

    scroll(v, 7, 3);
    REQUIRE(equal_to({1, 0, 3, 4, 0, 2, 7, 1, 3}, v));
  }
}
