#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include <wind/dom/shadow-dom/pool-manager.hpp>

namespace wind::dom::shadow {
  struct Root : public std::enable_shared_from_this<Root> {
  public:
    Root();
    Root(unsigned int id);

    // void destroy() {
    //   parent = std::nullopt;
    //   for (const auto& child : children) {
    //     // std::visit([](auto c) { c->destroy(); }, child);
    //   }
    //   reset();
    // }

    // void reset() {
    //   // id = 0;
    //   // children = {};
    //   // children.reserve(3);
    // };

    unsigned int id;

    bool operator==(Root& element) { return attributes == element.attributes; };

    Elements children = {};
    std::optional<Element> parent = std::nullopt;

    attributes::Root attributes;
    attributes::Root hoverAttributes;
    attributes::Root clickAttributes;
  };
} // namespace wind::dom::shadow
