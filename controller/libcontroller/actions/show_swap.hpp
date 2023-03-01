//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include <cassert>
#include "libconfig/config.hpp"
#include "libcontroller/data/selected.hpp"
#include "libmodel/board.hpp"
#include "libview/ianimations.hpp"
#include "libview/view.hpp"

namespace match3 {

const auto show_swap = [](const board& b, const selected& s, ianimations& a,
                          view& v, const config c) {
  assert(s.size() == 2);
  using namespace std::chrono_literals;
  a.queue_animation([b, c, s, &v] {
    const auto _1 = s[0];
    const auto _2 = s[1];
    v.set_grid(_1 % c.board_width, _1 / c.board_width, b[_1]);
    v.set_grid(_2 % c.board_width, _2 / c.board_width, b[_2]);
  });
};

}  // match3
