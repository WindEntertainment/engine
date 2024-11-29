#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include <wind/dom/shadow-dom/pool-manager.hpp>

namespace wind::dom::shadow {
  struct Input : public std::enable_shared_from_this<Input> {
  public:
    Input();
    Input(unsigned int id);

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

    bool operator==(Input& element) {
      return attributes == element.attributes;
    };

    Elements children = {};
    std::optional<Element> parent = std::nullopt;

    attributes::Input attributes = attributes::getDefaultInputAttributes();
    attributes::Input hoverAttributes = {};
    attributes::Input clickAttributes = {};
  };
} // namespace wind::dom::shadow
