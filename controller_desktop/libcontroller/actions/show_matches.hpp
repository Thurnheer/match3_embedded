
//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "libconfig/config.hpp"
#include "libcontroller/events/matches.hpp"
#include "libview/ianimations.hpp"
#include "libview/view.hpp"

namespace match3 {

const auto show_matches = [](const auto& m, ianimations& a, view& v,
                             const config c) {
  using namespace std::chrono_literals;
  a.queue_animation([m, c, &v] {
    for (auto i : m.matches) {
      v.update_grid(i % c.board_width, i / c.board_width);
    }
  });
};

}  // match3
