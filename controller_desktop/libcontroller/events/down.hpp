//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include <SDL_events.h>
#include <boost/sml/utility/dispatch_table.hpp>
// clang-format off
#if __has_include(<SDL2/SDL.h>)
#include <SDL2/SDL.h>
#elif __has_include(<SDL.h>)
#include <SDL.h>
#endif
#if __has_include(<SDL2/SDL_image.h>)
#include <SDL2/SDL_image.h>
#elif __has_include(<SDL_image.h>)
#include <SDL_image.h>
#endif
#if __has_include(<SDL2/SDL_ttf.h>)
#include <SDL2/SDL_ttf.h>
#elif __has_include(<SDL_ttf.h>)
#include <SDL_ttf.h>
#endif
// clang-format on
#if defined(EMSCRIPTEN)
#include <emscripten.h>
#define EM(...) __VA_ARGS__ EM_ELSE
#define EM_ELSE(...)
#else
#define EM(...) EM_ELSE
#define EM_ELSE(...) __VA_ARGS__
#define EM_ASM_INT_V(...) 0
#endif

namespace match3 {

struct down : boost::sml::utility::id<SDL_FINGERDOWN, SDL_MOUSEBUTTONDOWN> {
  // clang-format off
  explicit down(const SDL_Event& event)
    : down(EM_ASM_INT_V({return /iPhone|iPad|iPod|Android/i.test(navigator.userAgent);}), event)
  {}
  // clang-format on

  explicit down(bool is_mobile, const SDL_Event& event)
      : x(is_mobile ? int(event.tfinger.x * 320) : int(event.button.x)),
        y(is_mobile ? int(event.tfinger.y * 480) : int(event.button.y)) {}

  const int x, y = 0;
};

}  // match3
