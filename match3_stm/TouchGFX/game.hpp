#pragma once
#include "libconfig/config.hpp"
#include <random>
#include <algorithm>
#include <deque>
#include <range/v3/action/action.hpp>
#include <libmodel/data/randomize.hpp>
#include <libmodel/board.hpp>
#include <vector>
#include <libview/animations.hpp>
#include <range/v3/action/sort.hpp>
#include <range/v3/action/transform.hpp>
#include <range/v3/action/unique.hpp>
#include <range/v3/algorithm/count.hpp>
#include <range/v3/algorithm/find.hpp>
#include <range/v3/algorithm/rotate.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/drop.hpp>
#include <range/v3/view/iota.hpp>  // view::ints
#include <range/v3/view/stride.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/remove_if.hpp>
#include <boost/sml.hpp>
#include <queue>
#include <libcontroller/player.hpp>


namespace match3
{

struct game
{
    boost::sml::sm<player,  boost::sml::defer_queue<std::deque>,  boost::sml::process_queue<std::queue>>
        player_;
};
}

