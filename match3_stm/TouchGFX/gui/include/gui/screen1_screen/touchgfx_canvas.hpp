//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "libview/icanvas.hpp"
#include <touchgfx/widgets/Image.hpp>
#include <mvp/MVPApplication.hpp>
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <memory_resource>

namespace match3 {

static char buffer[10000] = {};
static std::pmr::monotonic_buffer_resource pool{std::data(buffer), std::size(buffer)};

class touchgfx_canvas : public icanvas {

 public:
  explicit touchgfx_canvas(const config c) noexcept
  {
  }
  void draw(std::shared_ptr<void> texture, int x, int y, bool clean) override {
      using namespace touchgfx;
    if (clean) {
      /*elements_.erase(ranges::remove_if(elements_,
                                        [=](const auto& pair) {
                                          return pair.second.x == x &&
                                                 pair.second.y == y;
                                        }),
                      elements_.end());*/
    }
    auto img = std::static_pointer_cast<touchgfx::Image>(texture);
    auto itr = std::find_if(elements_.begin(), elements_.end(), [x, y](const std::pair<std::shared_ptr<void>, pos>& e)
            {
               if(e.second == pos{x, y})
               {
                    return true;
                }
                return false;
            });
    if(itr == elements_.end())
    {
        auto tmp = std::shared_ptr<touchgfx::Image>(reinterpret_cast<Image*>(&resource_[counter_]), [](void* ptr){
        if(auto screen = touchgfx::Application::getCurrentScreen())
        {
            auto i = reinterpret_cast<touchgfx::Image*>(ptr);
            static_cast<Screen1ViewBase*>(screen)->remove(*i);
        }
        });
        tmp->setXY(x, y);
        tmp->setBitmap(img->getBitmap());
        //tmp->invalidate();
        if(auto screen = touchgfx::Application::getCurrentScreen())
        {
            static_cast<Screen1ViewBase*>(screen)->add_image(*tmp);
        }
        elements_.emplace_back(std::make_pair(tmp, pos(counter_++, x, y)));
    }
    //elements_.push_back(std::make_pair(texture, pos{x, y}));
  }

  std::shared_ptr<void> load_image(const std::string& file) const override {
      using namespace touchgfx;
      const auto img_nr = file[0] - 0x30;
      auto img = std::shared_ptr<touchgfx::Image>(reinterpret_cast<Image*>(&resource_[counter_++]), [](void* ptr){
        if(auto screen = touchgfx::Application::getCurrentScreen())
        {
            auto img = reinterpret_cast<touchgfx::Image*>(ptr);
            static_cast<Screen1ViewBase*>(screen)->remove(*img);
        }
        });
      img->setBitmap(touchgfx::Bitmap(img_nr));
    return img;
  }

  std::shared_ptr<void> create_text(const std::string& str,
                                    const std::string& font_file,
                                    int font_size) const override {
    return std::shared_ptr<void>();
  }

  void render() override {
    /*SDL_RenderClear(renderer_.get());
    for (const auto& element : elements_) {
      const auto sprite = static_cast<SDL_Texture*>(element.first.get());
      SDL_RenderCopy(renderer_.get(), sprite, nullptr, &element.second);
    }
    SDL_RenderPresent(renderer_.get());*/
      /*auto screen = touchgfx::Application::getCurrentScreen();
      if(screen)
      {
          if(first_draw_)
          {
            first_draw_ = false;
            for(auto& e : elements_)
            {
                static_cast<Screen1ViewBase*>(screen)->add_image(e.first);
            }
          }
          for(auto& e : elements_)
          {
              e.first.setXY(e.second.x, e.second.y);
          }
      }*/
  }

  void clear() override {
      elements_.clear();
  }

 private:
  struct pos {int counter; int x; int y;};
  mutable int counter_{0};
  friend inline bool operator==(const pos& lhs, const pos& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
  bool first_draw_{true};
  //std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> window_;
  //std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> renderer_;
  //std::vector<std::pair<std::shared_ptr<void>, SDL_Rect>> elements_;
  std::pmr::vector<std::pair<std::shared_ptr<void>, pos>> elements_{&pool};
  mutable std::array<touchgfx::Image, 180> resource_;
};

}  // match3

