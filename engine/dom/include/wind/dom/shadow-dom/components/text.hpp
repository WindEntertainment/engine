#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include <wind/dom/shadow-dom/pool-manager.hpp>

namespace wind::dom::shadow {
  struct Text : public std::enable_shared_from_this<Text> {
  public:
    Text();
    Text(unsigned int id);

    // void destroy() {
    //   parent = std::nullopt;
    //   for (const auto& child : children) {
    //     // std::visit([](auto c) { c->destroy(); }, child);
    //   }
    //   reset();
    //   PoolManager::releaseFromPool(shared_from_this());
    // }

    // void reset() {
    //   // id = 0;
    //   // children = {};
    //   // children.reserve(3);
    // };

    unsigned int id;

    bool operator==(Text& element) { return attributes == element.attributes; };

    Elements children = {};
    std::optional<Element> parent = std::nullopt;

    attributes::Text attributes = attributes::getDefaultTextAttributes();
    attributes::Text hoverAttributes = {};
    attributes::Text clickAttributes = {};
  };
} // namespace wind::dom::shadow
