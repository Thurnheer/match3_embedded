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

namespace match3 {

class touchgfx_canvas : public icanvas {

 public:
  explicit touchgfx_canvas(const config c) noexcept
  {
  }
  void draw(std::shared_ptr<void> texture, int x, int y, bool clean) override {
      using namespace touchgfx;
    if (clean) {
      elements_.erase(ranges::remove_if(elements_,
                                        [=](const auto& pair) {
                                          return pair.second.x == x &&
                                                 pair.second.y == y;
                                        }),
                      elements_.end());
    }
    auto img_nr = *(std::static_pointer_cast<BitmapId>(texture).get());
    auto itr = ranges::find_if(elements_, [=](const auto& pair) {
                                            return pair.second == pos{x, y};
                                            });
    if(itr == elements_.end())
    {
        auto img = std::shared_ptr<touchgfx::Image>(new Image, [](void* ptr){
            if(auto screen = touchgfx::Application::getCurrentScreen())
            {
                auto img = reinterpret_cast<Image*>(ptr);
                static_cast<Screen1ViewBase*>(screen)->remove(*img);
                delete img;
            }
            });
        img->setBitmap(touchgfx::Bitmap(img_nr));
        img->setXY(x, y);
        if(auto screen = touchgfx::Application::getCurrentScreen())
        {
            static_cast<Screen1ViewBase*>(screen)->add_image(*img);
        }
        elements_.push_back(std::make_pair(img, pos{x, y}));
    }
    else
    {
        auto img = std::static_pointer_cast<Image>(itr->first);
        img->setBitmap(Bitmap(img_nr));
        img->setXY(x, y);
        img->invalidate();
        itr->second = pos{x, y};
    }
  }

  std::shared_ptr<void> load_image(const std::string& file) const override {
      auto img_nr = std::make_shared<int>(file[0] - 0x30);
      //*img_nr = file[0] - 0x30;
    return img_nr;
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
  struct pos {int x; int y;};
  friend inline bool operator==(const pos& lhs, const pos& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
  //std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> window_;
  //std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> renderer_;
  //std::vector<std::pair<std::shared_ptr<void>, SDL_Rect>> elements_;
  std::vector<std::pair<std::shared_ptr<void>, pos>> elements_{};
};

}  // match3

