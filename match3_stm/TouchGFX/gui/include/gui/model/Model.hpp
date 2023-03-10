#ifndef MODEL_HPP
#define MODEL_HPP

//#include <make_game.hpp>
#include <touchgfx/mixins/ClickListener.hpp>
#include <game.hpp>

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void process_click_event(const touchgfx::ClickEvent&);
    void tick();
protected:
    ModelListener* modelListener;
    match3::game m_game;
    bool m_first_tick{true};
};

#endif // MODEL_HPP
