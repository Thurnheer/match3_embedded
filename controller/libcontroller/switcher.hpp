//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "libcontroller/actions/add_points.hpp"
#include "libcontroller/actions/destroy_matches.hpp"
#include "libcontroller/actions/drop_item.hpp"
#include "libcontroller/actions/find_matches.hpp"
#include "libcontroller/actions/generate_new.hpp"
#include "libcontroller/actions/scroll_board.hpp"
#include "libcontroller/actions/show_board.hpp"
#include "libcontroller/actions/show_matches.hpp"
#include "libcontroller/actions/show_points.hpp"
#include "libcontroller/events/matches.hpp"
#include "libmodel/guards/has_items.hpp"
#include "libmodel/guards/is_item_winning.hpp"

namespace sml = boost::sml;

namespace match3 {

struct switcher {
  auto operator()() const {
    using namespace sml;

    /**
     * Transition table for player
     *
     * \code{.cpp}
     *   dst_state <= src_state + event [ guard ] / action
     * \endcode
     */
    // clang-format off
    return make_transition_table(
      (*"handle matches"_s) + event<matches> [ has_items and is_item_winning ] / (
                                               find_matches, show_matches,
                                               destroy_matches, show_board,
                                               add_points, show_points,
                                               scroll_board, show_board,
                                               generate_new, show_board,
                                               process(matches{.arity = 1, .matches{}}))
      , "handle matches"_s + event<matches> [ has_items and not is_item_winning ] / (
                                               drop_item, process(matches{.arity = 1, .matches{}}))
      , "handle matches"_s + event<matches> [ not has_items ] = X
    );
    // clang-format on
  }
};

}  // match3
