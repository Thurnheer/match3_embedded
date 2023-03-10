#include <gui/screen1_screen/Screen1View.hpp>
Screen1View::Screen1View()
: img_clicked_callback(this, &Screen1View::click_handler)
{
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    image2.setClickAction(img_clicked_callback);
    image3.setClickAction(img_clicked_callback);
    image4.setClickAction(img_clicked_callback);
    image5.setClickAction(img_clicked_callback);
    image6.setClickAction(img_clicked_callback);
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::click_handler(const Image&, const ClickEvent& evt)
{
    presenter->process_click_event(evt);
}