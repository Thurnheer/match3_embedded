//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "libmodel/data/selected.hpp"
#include "libcontroller/events/down.hpp"
#include "libcontroller/events/up.hpp"
#include "libview/view.hpp"

namespace match3 {

const auto select_item = [](const auto& event, const view& v, selected& s) {
  s.emplace_back(v.get_position(event.x, event.y));
};

}  // match3
