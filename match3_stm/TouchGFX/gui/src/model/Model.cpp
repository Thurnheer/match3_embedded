#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <touchgfx/mixins/ClickListener.hpp>

extern match3::game get_game();

Model::Model() : modelListener(0)
, m_game{get_game()}
{

}

void Model::process_click_event(const touchgfx::ClickEvent& event)
{
    auto dispatch_event = boost::sml::utility::make_dispatch_table<touchgfx::ClickEvent, touchgfx::ClickEvent::PRESSED, touchgfx::ClickEvent::CANCEL>(m_game.player_);
    dispatch_event(event, static_cast<int>(event.getType()));
}

void Model::tick()
{
    using namespace match3;
    static int counter{0};
    if(0 == counter % 10)
    {
        //m_game.player_.process_event(time_tick{});
    }
    m_game.player_.process_event(time_tick{});
    counter++;
}
