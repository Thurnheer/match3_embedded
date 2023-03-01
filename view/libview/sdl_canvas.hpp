//
// Copyright (c) 2016 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "libview/icanvas.hpp"
#include <SDL_events.h>

namespace match3 {

struct sdl {
  sdl() noexcept {
    assert(!SDL_Init(SDL_INIT_VIDEO));
    assert(!TTF_Init());
  }

  ~sdl() noexcept {
    TTF_Quit();
    SDL_Quit();
  }
};

class sdl_canvas : sdl, public icanvas {
  static constexpr auto RENDER_DRIVER = -1;
  static constexpr auto RENDER_FLAGS = SDL_RENDERER_ACCELERATED;

 public:
  explicit sdl_canvas(const config c) noexcept
      : window_(SDL_CreateWindow(c.win_title.c_str(), SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, c.win_width,
                                 c.win_height, SDL_WINDOW_SHOWN),
                SDL_DestroyWindow),
        renderer_(SDL_CreateRenderer(window_.get(), RENDER_DRIVER,
                                     RENDER_FLAGS),
                  SDL_DestroyRenderer) {}

  void draw(std::shared_ptr<void> texture, int x, int y, bool clean) override {
    SDL_Rect pos{x, y, 0, 0};
    const auto sprite = static_cast<SDL_Texture*>(texture.get());
    SDL_QueryTexture(sprite, nullptr, nullptr, &pos.w, &pos.h);
    if (clean) {
      elements_.erase(ranges::remove_if(elements_,
                                        [=](const auto& pair) {
                                          return pair.second.x == x &&
                                                 pair.second.y == y;
                                        }),
                      elements_.end());
    }
    elements_.push_back(std::make_pair(texture, pos));
  }

  std::shared_ptr<void> load_image(const std::string& file) const override {
    return std::shared_ptr<void>(IMG_LoadTexture(renderer_.get(), file.c_str()),
                                 SDL_DestroyTexture);
  }

  std::shared_ptr<void> create_text(const std::string& str,
                                    const std::string& font_file,
                                    int font_size) const override {
    std::shared_ptr<TTF_Font> font(TTF_OpenFont(font_file.c_str(), font_size),
                                   TTF_CloseFont);
    std::shared_ptr<SDL_Surface> surface(
        TTF_RenderText_Blended(font.get(), str.c_str(),
                               SDL_Color{255, 255, 255, 0}),
        SDL_FreeSurface);
    return std::shared_ptr<void>(
        SDL_CreateTextureFromSurface(renderer_.get(), surface.get()),
        SDL_DestroyTexture);
  }

  void render() override {
    SDL_RenderClear(renderer_.get());
    for (const auto& element : elements_) {
      const auto sprite = static_cast<SDL_Texture*>(element.first.get());
      SDL_RenderCopy(renderer_.get(), sprite, nullptr, &element.second);
    }
    SDL_RenderPresent(renderer_.get());
  }

  void clear() override { elements_.clear(); }

 private:
  std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> window_;
  std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> renderer_;
  std::vector<std::pair<std::shared_ptr<void>, SDL_Rect>> elements_;
};

}  // match3
