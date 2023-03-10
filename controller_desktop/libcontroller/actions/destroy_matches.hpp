//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "libcontroller/events/matches.hpp"
#include "libmodel/board.hpp"
#include <range/v3/action/push_back.hpp>
#include <range/v3/action/push_front.hpp>
#include <range/v3/action/sort.hpp>
#include <range/v3/action/transform.hpp>
#include <range/v3/action/unique.hpp>
#include <range/v3/algorithm/count.hpp>
#include <range/v3/algorithm/find.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/algorithm/remove_if.hpp>
#include <range/v3/algorithm/rotate.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/drop.hpp>
#include <range/v3/view/iota.hpp>  // view::ints
#include <range/v3/view/join.hpp>
#include <range/v3/view/remove_if.hpp>
#include <range/v3/view/stride.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/transform.hpp>

namespace match3 {

const auto destroy_matches = [](board& b, const auto& m) {
  ranges::for_each(m.matches, [&b](auto i) { b.update(i, {}); });
};

}  // match3
