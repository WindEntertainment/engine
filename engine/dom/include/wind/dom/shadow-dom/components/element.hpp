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

// #pragma once
// #include <wind/dom/shadow-dom/shared.hpp>
// #include <wind/dom/dom/dom.hpp>

// namespace wind::dom::shadow {
//   class UIElement {
//   public:
//     UIElement();
//     UIElement(unsigned int id);

//     virtual bool operator==(UIElement& element) = 0;
//     // virtual UIElement* deepCopy() = 0;
//     // virtual std::shared_ptr<UIElement> getPtr() = 0;
//     // virtual dom::UIElement* toReal() = 0;
//     // virtual void updateReal(dom::UIElement::Ptr element) = 0;
//     // virtual attributes::Base* mergeAttributes() = 0;

//     void appendChild(std::shared_ptr<UIElement> child);
//     void removeChild(unsigned int childId);

//     const unsigned int id;
//     static unsigned int nextId;
//     std::vector<std::shared_ptr<UIElement>> children;
//     std::shared_ptr<UIElement> parent = nullptr;

//   protected:
//   };

//   template <typename S, typename R, typename A>
//   class UIElementCRTP : public UIElement {
//   public:
//     UIElementCRTP(const A& defaultAttributes, const unsigned int id)
//         : UIElement(id) {};

//     UIElementCRTP(const unsigned int id) : UIElement(id) {};

//     UIElementCRTP(const A& defaultAttributes) {};
//     // , attributes(std::make_shared<A>(defaultAttributes))
//     // UIElementCRTP(
//     //   const A& defaultAttributes,
//     //   const A& defaultHoverAttributes,
//     //   const A& defaultClickAttributes,
//     //   const unsigned int id
//     // )
//     //     : UIElement(id),
//     attributes(std::make_shared<A>(defaultAttributes)),
//     //       hoverAttributes(std::make_shared<A>(defaultHoverAttributes)),
//     //       clickAttributes(std::make_shared<A>(defaultClickAttributes)) {};

//     // UIElementCRTP(
//     //   const A& defaultAttributes,
//     //   const A& defaultHoverAttributes,
//     //   const A& defaultClickAttributes
//     // )
//     //     : attributes(std::make_shared<A>(defaultAttributes)),
//     //       hoverAttributes(std::make_shared<A>(defaultHoverAttributes)),
//     //       clickAttributes(std::make_shared<A>(defaultClickAttributes)) {};

//     // UIElementCRTP(const A& defaultAttributes)
//     //     : attributes(std::make_shared<A>(defaultAttributes)),
//     //       hoverAttributes(std::make_shared<A>(defaultAttributes)),
//     //       clickAttributes(std::make_shared<A>(defaultAttributes)) {};

//     virtual std::shared_ptr<S> deepCopy() = 0;
//     virtual std::shared_ptr<S> getPtr() = 0;
//     virtual std::shared_ptr<dom::UIElement> toReal() = 0;
//     virtual void updateReal(std::shared_ptr<R> element) = 0;
//     virtual std::shared_ptr<A> mergeAttributes() = 0;

//     // A* mergeAttributes() override { return this->attributes.get(); };

//     // R* toReal() override { return new R(this->id,
//     *this->mergeAttributes()); };

//     // void updateReal(R element) {
//     //   element->attributes = *this->mergeAttributes();
//     // };

//     // bool operator==(UIElement& elementReference) override {
//     //   S* element = dynamic_cast<S*>(&elementReference);
//     //   if (!element)
//     //     return false;
//     //   return attributes == element->attributes;
//     // };

//     // std::shared_ptr<S> deepCopy() override {
//     //   auto element = new S(this->id);
//     //   // element->attributes = A(this->attributes);
//     //   for (auto&& child : this->children) {
//     //     // element->appendChild(child->deepCopy());
//     //   };
//     //   return element;
//     // };

//     std::shared_ptr<A> attributes;
//     std::shared_ptr<A> hoverAttributes;
//     std::shared_ptr<A> clickAttributes;

//   protected:
//   };

// } // namespace wind::dom::shadow
