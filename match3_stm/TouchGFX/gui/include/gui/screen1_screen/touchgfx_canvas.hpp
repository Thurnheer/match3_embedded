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
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <mvp/MVPApplication.hpp>
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

namespace match3 {

class touchgfx_canvas : public icanvas {

 public:
  explicit touchgfx_canvas(const config c) noexcept
  : config_(c)
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
    int img_nr = *(std::static_pointer_cast<BitmapId>(texture).get());
    auto drawable = std::shared_ptr<Drawable>();
    if(img_nr-1 <= config_.board_colors)
    {
        auto img = std::shared_ptr<Image>(new Image, [](void* ptr){
            if(auto screen = Application::getCurrentScreen())
            {
                auto img = reinterpret_cast<Image*>(ptr);
                static_cast<Screen1ViewBase*>(screen)->remove_drawable(*img);
                delete img;
            }
            });
        
        img->setBitmap(Bitmap(img_nr-1));
        img->setXY(x, y);
        drawable = img;
    }
    else
    {
        auto text = std::shared_ptr<TextAreaWithOneWildcard>(new TextAreaWithOneWildcard, [](void* ptr){
            if(auto screen = Application::getCurrentScreen())
            {
                auto text = reinterpret_cast<TextAreaWithOneWildcard*>(ptr);
                static_cast<Screen1ViewBase*>(screen)->remove_drawable(*text);
                delete text;
            }
            });
            if(img_nr == 10)
            {
                text->setWildcard(textAreaPoints);
                text->resizeToCurrentText();
                text->setTypedText(TypedText(T_POINTS));
                text->setXY(x, y);  
                text->setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
            }
            else if(img_nr == 11)
            {
                text->setWildcard(textAreaMoves);
                text->setTypedText(TypedText(T_MOVES));
                text->setXY(x-50, y);  
                text->setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
            }
            else
            {
                text->setWildcard(textAreaGameOver);
                text->setTypedText(TypedText(T_MOVES));
                text->setXY(x+100, y);  
                text->setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
            }
            text->resizeToCurrentText();
            text->setLinespacing(0);
            drawable = text;
    }
    elements_.emplace_back(std::make_pair(drawable, pos{x, y}));
    if(auto screen = Application::getCurrentScreen())
    {
        static_cast<Screen1ViewBase*>(screen)->add_drawable(*drawable);
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
    if(str.rfind("points", 0) == 0)
    {
        Unicode::strncpy(textAreaPoints, str.data(), str.size() + 1);
        return std::make_shared<int>(10);
    }
    else if(str.rfind("moves", 0) == 0)
    {
        Unicode::strncpy(textAreaMoves, str.data(), str.size() + 1);
        return std::make_shared<int>(11);
    }
    else
    {
        Unicode::strncpy(textAreaGameOver, str.data(), str.size() + 1);
        return std::make_shared<int>(12);
    }
  }

  void render() override {
    using namespace touchgfx;
    if(auto screen = touchgfx::Application::getCurrentScreen())
    {
        static_cast<Screen1ViewBase*>(screen)->redraw();
    }
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
  config config_;
  static const auto TEXT_SIZE = 20u;
  mutable touchgfx::Unicode::UnicodeChar textAreaPoints[TEXT_SIZE];
  mutable touchgfx::Unicode::UnicodeChar textAreaMoves[TEXT_SIZE];
  mutable touchgfx::Unicode::UnicodeChar textAreaGameOver[TEXT_SIZE];
};

}  // match3

