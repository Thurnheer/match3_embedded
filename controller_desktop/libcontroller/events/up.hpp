//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include <SDL_events.h>

namespace match3 {

struct up : boost::sml::utility::id<SDL_FINGERUP, SDL_MOUSEBUTTONUP> {
  // clang-format off
  explicit up(const SDL_Event& event)
    : up(EM_ASM_INT_V({return /iPhone|iPad|iPod|Android/i.test(navigator.userAgent);}), event)
  {}
  // clang-format on

  explicit up(bool is_mobile, const SDL_Event& event)
      : x(is_mobile ? int(event.tfinger.x * 320) : int(event.button.x)),
        y(is_mobile ? int(event.tfinger.y * 480) : int(event.button.y)) {}

  const int x, y = 0;
};

}  // match3
