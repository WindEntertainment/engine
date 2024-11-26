#pragma once
#include <wind/dom/dom/shared.hpp>

namespace wind::dom {
  class UIElement {
  public:
    using Ptr = std::shared_ptr<UIElement>;

    UIElement(unsigned int id);

    virtual void reset() {};
    virtual void update() = 0;
    // virtual Ptr getPtr() = 0;
    virtual void render(wind::CommandBuffer& renderer) = 0;

    void appendChild(Ptr child, Ptr parent);
    void display(wind::CommandBuffer& renderer);
    void removeChild(unsigned int childId);

    const unsigned int id;
    std::vector<Ptr> children;
    Ptr parent = nullptr;

  protected:
  };

} // namespace wind::dom
