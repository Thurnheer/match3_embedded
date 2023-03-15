//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "libcontroller/actions/clear_selected.hpp"
#include "libcontroller/actions/reset.hpp"
#include "libcontroller/actions/select_item.hpp"
#include "libcontroller/actions/show_game_over.hpp"
#include "libcontroller/actions/show_moves.hpp"
#include "libcontroller/actions/show_points.hpp"
#include "libcontroller/actions/show_swap.hpp"
#include "libcontroller/actions/swap_items.hpp"
#include "libmodel/data/moves.hpp"
#include "libcontroller/events/down.hpp"
#include "libcontroller/events/key_pressed.hpp"
#include "libcontroller/events/matches.hpp"
#include "libcontroller/events/quit.hpp"
#include "libcontroller/events/time_tick.hpp"
#include "libcontroller/events/up.hpp"
#include "libmodel/guards/is_allowed.hpp"
#include "libmodel/guards/is_key.hpp"
#include "libmodel/guards/is_swap_items_winning.hpp"
#include "libcontroller/switcher.hpp"

namespace sml = boost::sml;

namespace match3 {

struct player {
  auto operator()() const {
    using namespace sml;

    const auto reset_and_show = (reset, show_board, show_points, show_moves);
    const auto select_and_swap_items = (select_item, swap_items, show_swap);

    /**
     * Transition table for player
     *
     * \code{.cpp}
     *   dst_state <= src_state + event [ guard ] / action
     * \endcode
     */
    // clang-format off
    return make_transition_table(
     // +-----------------------------------------------------------------------------------------------------------------+
       (*"idle"_s)                        / reset_and_show                                       = "first item"_s,
         "game over?"_s     + event<up>   [ ([](ianimations& a) { return a.done(); }) ] /
                                            reset_and_show                                       = "first item"_s,
         "first item"_s     + event<down> / select_item                                          = "second item"_s,
         "second item"_s    + event<up>   [ is_allowed ] / select_and_swap_items                 = "match items"_s,
         "second item"_s    + event<up>   / drop_item                                            = "first item"_s,
         "match items"_s                  [ is_swap_items_winning ] / (
                                            [](moves& m) {--m;}, show_moves,
                                            process(matches{.arity=2, .matches{}})
                                          )                                                      = "play"_s.sm<switcher>(),
         "match items"_s                  / (swap_items, show_swap, clear_selected)              = "first item"_s,
         "play"_s.sm<switcher>()          [ ([](moves& m) { return 0 == m; }) ] / show_game_over = "game over?"_s,
         "play"_s.sm<switcher>()                                                                 = "first item"_s,
     // +-----------------------------------------------------------------------------------------------------------------+
       //(*"UI"_s)            + event<key_pressed> [ is_key(SDLK_ESCAPE) ]                         = X,
         //"UI"_s             + event<quit>                                                        = X,
     // +-----------------------------------------------------------------------------------------------------------------+
       (*"animations"_s)    + event<time_tick> / [](ianimations& a) { a.update(); }
     // +-----------------------------------------------------------------------------------------------------------------+
    );
    // clang-format on
  }
};

}  // match3
