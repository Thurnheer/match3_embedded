//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include "libconfig/config.hpp"
#include "game.hpp"
#include <gui/screen1_screen/touchgfx_canvas.hpp>
#include <boost/di.hpp>
#include <random>
#include <algorithm>
#include <deque>
#include <range/v3/action/action.hpp>
#include <libmodel/data/randomize.hpp>
#include <vector>
#include <cstdlib>
#include <touchgfx/mixins/ClickListener.hpp>

auto configuration = []() {
  using namespace match3;
    namespace di = boost::di;


  // clang-format off
  return di::make_injector(
    di::bind<icanvas>.to<touchgfx_canvas>()
  , di::bind<ianimations>.to<animations>()

  , di::bind<>.to(
      config{.win_title = "match3",
             .win_width = 272,
             .win_height = 480,
             .board_width = 6,
             .board_height = 8,
             .board_colors = 5,
             .max_moves = 10}
    )

  , di::bind<board>()(
    std::vector{
      3,5,1,4,3,2,
      1,1,4,2,5,1,
      5,3,5,4,5,3,
      4,4,2,1,3,4,
      5,1,1,2,4,5,
      5,2,3,5,4,2,
      1,5,5,1,5,5,
      2,3,3,1,3,3
      }

      , config{.win_title = "match3",
             .win_width = 272,
             .win_height = 480,
             .board_width = 6,
             .board_height = 8,
             .board_colors = 5,
             .max_moves = 10}

    )

  , di::bind<randomize>.to([](int begin, int end) {
      /*static std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<int> dis(begin, end);
      return dis(gen);*/
        return (rand() % end) + begin;
    })
  );
  // clang-format on
};


match3::game get_game() {

namespace di = boost::di;
  const auto injector = di::make_injector(configuration());
  /*static auto game_ =*/ return injector.create<match3::game>();
  //return game_;
}

//static std::decay_t<decltype(get_game())> game_{get_game()};

/*void  process_click_events(const touchgfx::ClickEvent& event)
{
    auto dispatch_event = boost::sml::utility::make_dispatch_table<touchgfx::ClickEvent, touchgfx::ClickEvent::PRESSED, touchgfx::ClickEvent::CANCEL>(game_.player_);
    dispatch_event(event, static_cast<int>(event.getType()));
}

void process_tick_event()
{
    using namespace match3;
    game_.player_.process_event(time_tick{});
}*/
