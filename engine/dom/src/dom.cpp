#include "wind/dom/dom.hpp"
#include <algorithm>
#include <typeindex>
#include <utility>

namespace wind {

  class Behavior {
  public:
    std::string id;
    std::function<void()> onStart;
    std::function<void()> onAction;
    std::function<void()> onEnd;
    std::function<void()> behave;

    Behavior(
      std::string id,
      std::function<void()> onStart,
      std::function<void()> onAction,
      std::function<void()> onEnd
    )
        : id(std::move(id)), onStart(onStart), onAction(onAction),
          onEnd(onEnd) {
      behave = [onStart, onAction, onEnd]() {
        onStart();
        onAction();
        onEnd();
      };
    }
  };

  class BehaviorManager {
  public:
    std::unordered_set<std::shared_ptr<Behavior>> behaviors;

    bool action() {
      for (const std::shared_ptr<Behavior>& behavior : behaviors) {
        behavior->behave();
      }
    };

    bool addBehavior(std::shared_ptr<Behavior> behavior) {
      behaviors.insert(behavior);
    };

    bool removeBehavior(std::shared_ptr<Behavior> behavior) {
      behaviors.erase(behavior);
    };
  };

#define RELEASE(className)                                                     \
  void release() override {                                                    \
    auto pool = PoolManager::getInstance().getPool<className>();               \
    if (pool) {                                                                \
      pool->release(shared_from_this());                                       \
    }                                                                          \
  }

#define REGISTER_POOL(className)                                               \
  static void registerPool(size_t size = 50) {                                 \
    auto pool = wind::share(WidgetPool<className>(size));                      \
    PoolManager::getInstance().registerPool<className>(pool);                  \
  }

  struct Styles {
    glm::vec2 size = {0, 0};
  };
  static const Styles defaultStyles = {};

  struct BaseAttributes {
  public:
    virtual ~BaseAttributes() = default;
  };
  static const BaseAttributes defaultBaseAttributes = {};

  struct ButtonAttributes : BaseAttributes {
    bool disabled = false;
  };
  static const ButtonAttributes defaultButtonAttributes = {};

  struct ImageAttributes : BaseAttributes {
    bool disabled = false;
  };
  static const ImageAttributes defaultImageAttributes = {};

  struct TextAttributes : BaseAttributes {
    bool disabled = false;
  };
  static const TextAttributes defaultTextAttributes = {};

  struct RichTextAttributes : BaseAttributes {
    bool disabled = false;
  };
  static const RichTextAttributes defaultRichTextAttributes = {};

  struct RootAttributes : BaseAttributes {
    bool disabled = false;
  };
  static const RootAttributes defaultRootAttributes = {};

  template <typename T>
  class WidgetPool {
  public:
    using Ptr = std::shared_ptr<T>;

    explicit WidgetPool(size_t size = 50) { prefill(size); }

    Ptr get() {
      if (available.empty()) {
        increasePoolSize(20);
      }

      auto item = available.back();
      available.pop_back();
      reserved.push_back(item);

      return item;
    }

    void release(Ptr item) {
      auto it = std::find(reserved.begin(), reserved.end(), item);
      if (it != reserved.end()) {
        reserved.erase(it);
        available.push_back(item);
      }
    }

  private:
    void prefill(size_t size) {
      reserved.reserve(size);
      for (size_t i = 0; i < size; ++i) {
        available.push_back(std::make_shared<T>());
      }
    }

    void increasePoolSize(size_t size) {
      reserved.reserve(reserved.size() + size);
      available.reserve(available.size() + size);
      for (size_t i = 0; i < size; ++i) {
        available.push_back(std::make_shared<T>());
      }
    }

    std::vector<Ptr> reserved;
    std::vector<Ptr> available;
  };

  class PoolManager {
  public:
    static PoolManager& getInstance() {
      static PoolManager instance;
      return instance;
    }

    template <typename T>
    void registerPool(std::shared_ptr<WidgetPool<T>> pool) {
      pools[std::type_index(typeid(T))] = pool;
    }

    template <typename T>
    std::shared_ptr<WidgetPool<T>> getPool() {
      auto it = pools.find(std::type_index(typeid(T)));
      if (it != pools.end()) {
        return std::static_pointer_cast<WidgetPool<T>>(it->second);
      }
      return nullptr;
    }

  private:
    std::unordered_map<std::type_index, std::shared_ptr<void>> pools;
    PoolManager() = default;
  };

  class UIElement {
  public:
    using Ptr = std::shared_ptr<UIElement>;

    UIElement() { children.reserve(3); }

    void destroy() {
      parent = nullptr;
      for (const auto& child : children) {
        child->destroy();
      }
      reset();
      release();
    }

    virtual void release() = 0;
    virtual void reset() = 0;

    void appendChild(const Ptr& child) {
      if (child) {
        children.push_back(child);
        child->parent = this;
      }
    }

    void display() {
      render();
      for (const auto& child : children) {
        child->display();
      }
    }

    virtual void render() = 0;

    Styles styles;
    BehaviorManager behaviorManager;

  protected:
    void removeChild(Ptr child) {
      if (child) {
        auto it = std::ranges::find_if(children, [&](const Ptr& item) {
          return item == child;
        });

        if (it == children.end())
          return;

        (*it)->parent = nullptr;
        children.erase(it);
      }
    }

    UIElement* parent = nullptr;
    std::vector<Ptr> children;
  };

  template <typename T>
  std::shared_ptr<T> createElement() {
    auto pool = PoolManager::getInstance().getPool<T>();
    if (pool) {
      return pool->get();
    }
    return nullptr;
  }

  class Button : public UIElement, public std::enable_shared_from_this<Button> {
  public:
    void render() override { std::cout << "I'm Button"; }

    REGISTER_POOL(Button);
    RELEASE(Button);

    void reset() override {
      attributes = defaultButtonAttributes;
      styles = defaultStyles;
    }

    ButtonAttributes attributes;
  };

  class Image : public UIElement, public std::enable_shared_from_this<Image> {
  public:
    void render() override { std::cout << "I'm Image"; }

    REGISTER_POOL(Image);
    RELEASE(Image);

    void reset() override {
      attributes = defaultImageAttributes;
      styles = defaultStyles;
    }

    ImageAttributes attributes;
  };

  class Text : public UIElement, public std::enable_shared_from_this<Text> {
  public:
    void render() override { std::cout << "I'm Text"; }

    REGISTER_POOL(Text);
    RELEASE(Text);

    void reset() override {
      attributes = defaultTextAttributes;
      styles = defaultStyles;
    }

    TextAttributes attributes;
  };

  class RichText : public UIElement,
                   public std::enable_shared_from_this<RichText> {
  public:
    void render() override { std::cout << "I'm RichText"; }

    REGISTER_POOL(RichText);
    RELEASE(RichText);

    void reset() override {
      attributes = defaultRichTextAttributes;
      styles = defaultStyles;
    }

    RichTextAttributes attributes;
  };

  class Root : public UIElement, public std::enable_shared_from_this<Root> {
  public:
    void render() override { std::cout << "I'm Root"; }

    REGISTER_POOL(Root);
    RELEASE(Root);

    void reset() override {
      attributes = defaultRootAttributes;
      styles = defaultStyles;
    }

    RootAttributes attributes;
  };

  int main() {
    Button::registerPool();
    Image::registerPool();
    Text::registerPool();
    RichText::registerPool();
    Root::registerPool();

    auto root = createElement<Root>();
    auto button = createElement<Button>();
    auto text = createElement<Text>();

    root->appendChild(text);
    root->appendChild(button);

    root->display();

    root->destroy();

    return 0;
  }

} // namespace wind
