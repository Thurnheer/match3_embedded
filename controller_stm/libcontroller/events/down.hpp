//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include <boost/sml/utility/dispatch_table.hpp>
#include <touchgfx/mixins/ClickListener.hpp>

namespace match3 {

struct down : boost::sml::utility::id<touchgfx::ClickEvent::PRESSED> {
  // clang-format off
  explicit down(const touchgfx::ClickEvent& event)
      : x(int(event.getX())),
        y( int(event.getY())) {}

  const int x, y = 0;
};

}  // match3
