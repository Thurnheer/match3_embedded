//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include <cassert>
#include <range/v3/action/push_front.hpp>
#include <range/v3/action/sort.hpp>
#include <range/v3/action/transform.hpp>
#include <range/v3/action/unique.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/view/iota.hpp>  // view::ints
#include <range/v3/view/remove_if.hpp>
#include <range/v3/view/take.hpp>
#include "libconfig/config.hpp"
#include "libcontroller/data/randomize.hpp"
#include "libcontroller/data/selected.hpp"
#include "libmodel/board.hpp"

namespace match3 {

const auto generate_new = [](board& b, selected& s, const config c,
                             randomize r) {
  auto&& grids =
      ranges::views::ints | ranges::views::take(c.board_width * c.board_height);

  ranges::for_each(
      grids | ranges::views::remove_if([&b](auto i) { return b[i]; }),
      [&b, &r, &c](auto i) { b.update(i, r(1, c.board_colors)); });

  s |= ranges::actions::push_front(grids) | ranges::actions::sort |
       ranges::actions::unique;
};

}  // match3
