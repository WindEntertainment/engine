#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include <wind/dom/dom/components/index.hpp>
// #include "button.hpp"
// #include "root.hpp"
#include <memory>

namespace wind::dom::shadow {
  // static unsigned int nextId;

  // using ElementPtr = Element;

  // template <typename S, typename R, typename A>
  // class UIElement {
  // public:
  //   // using InnerElementPtr = std::variant<
  //   //   std::monostate,
  //   //   std::shared_ptr<
  //   //     shadow::UIElement<shadow::Button, dom::Button,
  //   attributes::Button>>>; unsigned int id;

  //   using Ptr = std::shared_ptr<S>;
  //   using AttributesPtr = std::shared_ptr<A>;

  //   virtual ~UIElement() = default;

  //   // REMOVE
  //   UIElement() { this->id = ++nextId; };
  //   UIElement(const unsigned int id) : id(id) {};
  //   // REMOVE

  //   UIElement(const A& defaultAttributes)
  //       : attributes(std::make_shared<A>(defaultAttributes)),
  //         hoverAttributes({}), clickAttributes({}), id(++nextId) {
  //           // children.reserve(3);
  //         };

  //   UIElement(const A& defaultAttributes, const unsigned int id)
  //       : attributes(std::make_shared<A>(defaultAttributes)),
  //         hoverAttributes({}), clickAttributes({}), id(id) {
  //           // children.reserve(3);
  //         };

  //   UIElement(
  //     const A& defaultAttributes,
  //     const A& defaultHoverAttributes,
  //     const A& defaultClickAttributes
  //   )
  //       : attributes(std::make_shared<A>(defaultAttributes)),
  //         hoverAttributes(std::make_shared<A>(defaultHoverAttributes)),
  //         clickAttributes(std::make_shared<A>(defaultClickAttributes)),
  //         id(++nextId) {
  //           // children.reserve(3);
  //         };

  //   UIElement(
  //     const A& defaultAttributes,
  //     const A& defaultHoverAttributes,
  //     const A& defaultClickAttributes,
  //     const unsigned int id
  //   )
  //       : attributes(std::make_shared<A>(defaultAttributes)),
  //         hoverAttributes(std::make_shared<A>(defaultHoverAttributes)),
  //         clickAttributes(std::make_shared<A>(defaultClickAttributes)),
  //         id(id) {
  //           // children.reserve(3);
  //         };

  //   // bool operator==(ElementPtr element) {};
  //   // ElementPtr deepCopy() = 0;

  //   // std::shared_ptr<S> deepCopy() {
  //   //   auto element = wind::share(S(this->id));
  //   //   element->attributes = this->attributes;
  //   //   for (const InnerElementPtr& child : this->children) {
  //   // if (child.index() != 0) {
  //   //   child
  //   // }

  //   // std::visit(
  //   //   [](const auto& child) -> std::string {
  //   //     using T = std::decay_t<decltype(child)>;
  //   //     if constexpr (!std::is_same_v<T, std::monostate>) {
  //   //       // spdlog::info("{}", !!child);
  //   //       // child->deepCopy();
  //   //       return "Empty";
  //   //     }
  //   //   },
  //   //   child
  //   // );
  //   //     using T =
  //   //       std::decay_t<decltype(child)>; // Get the underlying type of
  //   //       'arg'
  //   //     // spdlog::info("{}", !!child);

  //   //     // Check if 'arg' is an int at compile-time
  //   //     if constexpr (!std::is_same_v<T, std::monostate>) {
  //   //       spdlog::info("{}", !!child);
  //   //       // child->deepCopy();
  //   //       // return "It's an int: " +
  //   //       //        std::to_string(arg); // Convert int to string and
  //   //       return
  //   //     }

  //   // if constexpr (std::is_same_v<
  //   //                 std::decay_t<decltype(child)>,
  //   //                 std::monostate>) {
  //   //   return;
  //   // } else {
  //   //   child.index();
  //   // }
  //   // if (child) {
  //   //   // child->deepCopy();
  //   // }

  //   // element->appendChild(child->deepCopy());
  //   //   },
  //   //   child
  //   // );
  //   // element->appendChild(child->deepCopy());
  //   //   };
  //   //   return element;
  //   // };

  //   std::shared_ptr<R> toReal() {
  //     return wind::share(R(this->id, this->mergeAttributes()));
  //   };

  //   void updateReal(std::shared_ptr<R> element) {
  //     element->attributes = this->mergeAttributes();
  //   };

  //   AttributesPtr mergeAttributes() { return this->attributes; };

  //   // std::vector<InnerElementPtr> children;
  //   // InnerElementPtr parent;

  //   AttributesPtr attributes;
  //   AttributesPtr hoverAttributes;
  //   AttributesPtr clickAttributes;

  // protected:
  // };

  // #define ATTRIBUTES(attributesType)                                             \
//   attributesType attributes;                                                   \
//   attributesType hoverAttributes;                                              \
//   attributesType clickAttributes;

  // #define TO_REAL(realType)                                                      \
//   std::shared_ptr<realType> toReal() {                                         \
//     return wind::share(R(this->id, this->mergeAttributes()));                  \
//   };

  // #define UPDATE_REAL(realType)                                                  \
//   void updateReal(std::shared_ptr<realType> element) {                         \
//     element->attributes = this->mergeAttributes();                             \
//   };

  // class ShadowConvertor {
  //   static dom::UIElement toReal(Element element) {
  //     // return R(shadow.id, shadow.mergeAttributes());
  //   };

  //   static void
  //   updateReal(Element element, std::shared_ptr<dom::UIElement> real) {
  //     // real.attributes = shadow.mergeAttributes();
  //   };
  // };

  static unsigned int nextId;
  struct Tree;

  struct Button {
  public:
    Button();
    Button(unsigned int id);

    unsigned int id;

    // std::shared_ptr<dom::Button> toReal() {
    //   return wind::share(dom::Button(id, mergeAttributes()));
    // };

    // void updateReal(std::shared_ptr<dom::Button> real) {
    //   real->attributes = mergeAttributes();
    // };

    bool operator==(Button& element) {
      return attributes == element.attributes;
    };
    // bool operator==(Element& element) {
    //   using T = std::decay_t<decltype(element)>;
    //   if constexpr (std::is_same_v<T, wind::dom::shadow::Button>) {
    //     return attributes == element.attributes;
    //   }
    //   return false;
    // };
    // void appendChild(E& child);

    // void removeChild(unsigned int childId);

    // std::vector<E> children = {};
    // E* parent = {};
    std::shared_ptr<Tree> tree = std::make_shared<Tree>();

    // attributes::Button mergeAttributes() const;

    attributes::Button attributes;
    attributes::Button hoverAttributes;
    attributes::Button clickAttributes;
  };

  struct Root {
  public:
    Root();
    Root(unsigned int id);

    unsigned int id;

    bool operator==(Root& element) { return attributes == element.attributes; };
    // bool operator==(Element& element) {
    //   using T = std::decay_t<decltype(element)>;
    //   if constexpr (std::is_same_v<T, wind::dom::shadow::Root>) {
    //     return attributes == element.attributes;
    //   }
    //   return false;
    // };
    // void appendChild(E& child);

    // void removeChild(unsigned int childId);

    // std::vector<E> children = {};
    // E* parent = {};

    std::shared_ptr<Tree> tree = std::make_shared<Tree>();

    attributes::Root attributes;
    attributes::Root hoverAttributes;
    attributes::Root clickAttributes;
  };

  using Element = std::variant<Button, Root>;
  using Elements = std::vector<Element>;

  struct Tree {
    Elements children = {};
    std::optional<Element> parent = std::nullopt;
  };

  void appendChild(Button& child, Element& parent);
  void appendChild(Root& child, Element& parent);
  void removeChild(unsigned int childId, Element& parent);
  attributes::Root mergeAttributes(Root& shadow);
  attributes::Button mergeAttributes(Button& shadow);
  std::shared_ptr<dom::Root> toReal(Root& shadow);
  std::shared_ptr<dom::Button> toReal(Button& shadow);
  void updateReal(std::shared_ptr<dom::Root> real, Root& shadow);
  void updateReal(std::shared_ptr<dom::Button> real, Button& shadow);

  // static unsigned int nextId;

  // class Element {
  // public:
  //   unsigned int id;

  //   Element(const ElementVariants& item);
  //   Element(const Element& element);

  //   template <typename T>
  //   T getAttributes() {
  //     return std::visit(
  //       [](auto& arg) -> T {
  //         return static_cast<T>(arg.attributes);
  //         // if constexpr (std::is_same_v<std::decay_t<decltype(arg)>,
  //         Button>) {
  //         //   return arg.attributes;
  //         //   // return std::nullopt;
  //         // } else if constexpr
  //         (std::is_same_v<std::decay_t<decltype(arg)>,
  //         // Root>) {
  //         //   return arg.attributes;
  //         //   // return std::nullopt;
  //         // }
  //       },
  //       item
  //     );
  //   }

  //   ElementVariants item;

  //   std::shared_ptr<dom::UIElement> toReal() {
  //     return std::visit(
  //       [&id = id](const auto& arg) -> std::shared_ptr<dom::UIElement> {
  //         if constexpr (std::is_same_v<std::decay_t<decltype(arg)>,
  //         Button>) {
  //           return wind::share(dom::Button(id, arg.mergeAttributes()));
  //         } else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>,
  //         Root>) {
  //           return wind::share(dom::Root(id, arg.mergeAttributes()));
  //         }
  //       },
  //       item
  //     );
  //   };

  //   template <typename T>
  //   void updateReal(std::shared_ptr<dom::UIElement> real) {
  //     std::visit(
  //       [&id = id](const auto& arg) -> void {
  //         if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, T>) {
  //           real.attributes = arg.mergeAttributes();
  //         }
  //         // else if constexpr (std::is_same_v<std::decay_t<decltype(arg)>,
  //         // Root>) {
  //         //   // real.attributes = arg.mergeAttributes();
  //         // }
  //       },
  //       item
  //     );
  //   };

  //   bool operator==(const Element& element);

  //   void appendChild(Element& child);

  //   void removeChild(unsigned int childId);

  //   // Element deepCopy();

  //   std::vector<Element> children = {};
  //   Element* parent = {};
  // };

  // class Wrapper {};

} // namespace wind::dom::shadow
