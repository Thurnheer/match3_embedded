#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <string>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void click_handler(const Image& img, const ClickEvent& evt);

protected:
    Callback<Screen1View, const Image&, const ClickEvent&> img_clicked_callback;
};

//using view = Screen1View;

#endif // SCREEN1VIEW_HPP
