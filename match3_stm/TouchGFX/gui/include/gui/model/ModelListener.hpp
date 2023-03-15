#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    void process_click_event(const touchgfx::ClickEvent& evt)
    {
        model->process_click_event(evt);
    }

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
