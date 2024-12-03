#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include <wind/dom/shadow-dom/pool-manager.hpp>

namespace wind::dom::shadow {
  struct Checkbox : public std::enable_shared_from_this<Checkbox> {
  public:
    Checkbox();
    Checkbox(unsigned int id);

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

    bool operator==(Checkbox& element) {
      return attributes == element.attributes;
    };

    Elements children = Elements(3);
    std::optional<Element> parent = std::nullopt;

    attributes::Checkbox attributes =
      attributes::getDefaultCheckboxAttributes();
    attributes::Checkbox hoverAttributes = {};
    attributes::Checkbox clickAttributes = {};
  };
} // namespace wind::dom::shadow
