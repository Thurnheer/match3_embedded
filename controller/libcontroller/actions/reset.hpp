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
#include "libcontroller/data/moves.hpp"
#include "libcontroller/data/points.hpp"
#include "libcontroller/data/randomize.hpp"
#include "libcontroller/data/selected.hpp"
#include "libmodel/board.hpp"
#include "libview/view.hpp"

namespace match3 {

const auto reset = [](config c, board original, board& b, points& p, moves& m,
                      view& v) {
  b = original;
  p = {};
  m = static_cast<short>(c.max_moves);
  v.clear();
  v.update();
};

}  // match3
