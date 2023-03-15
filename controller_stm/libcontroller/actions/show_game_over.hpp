//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "libview/ianimations.hpp"
#include "libview/view.hpp"

namespace match3 {

const auto show_game_over = [](view& v, ianimations& a) {
  using namespace std::chrono_literals;
  a.queue_animation(
      [&v] { v.set_text("GAME\nOVER", 20, 230, 48 /*font size*/); }, 200ms);
};

}  // match3
