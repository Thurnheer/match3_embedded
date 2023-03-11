#include <gui/screen1_screen/Screen1View.hpp>
Screen1View::Screen1View()
: clicked_callback_(this, &Screen1View::click_handler)
{
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    container1.setClickAction(clicked_callback_);
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::click_handler(const Container&, const ClickEvent& evt)
{
    presenter->process_click_event(evt);
}