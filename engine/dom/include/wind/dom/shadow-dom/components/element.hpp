#pragma once
#include <wind/dom/shadow-dom/shared.hpp>

namespace wind::dom::shadow {
  class UIElement {
  public:
    using Ptr = std::shared_ptr<UIElement>;

    UIElement();
    UIElement(unsigned int id);

    virtual bool operator==(UIElement& element) = 0;
    virtual Ptr deepCopy() = 0;
    virtual Ptr getPtr() = 0;

    void appendChild(Ptr child);
    void removeChild(unsigned int childId);

    const unsigned int id;
    static unsigned int nextId;
    std::vector<Ptr> children;
    Ptr parent = nullptr;

  protected:
  };

} // namespace wind::dom::shadow
