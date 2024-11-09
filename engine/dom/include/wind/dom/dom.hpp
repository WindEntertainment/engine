#pragma once
#include <wind/utils/utils.hpp>
#include "wind/renderer/command-buffer.hpp"
#include "wind/input-system/input-system.hpp"
#include <algorithm>
#include <typeindex>
#include <utility>

namespace wind {

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
    std::function<void()> onClick;
    std::function<void()> onHover;

  public:
    virtual ~BaseAttributes() = default;
  };
  static const BaseAttributes defaultBaseAttributes = {};

  struct ButtonAttributes : BaseAttributes {
    glm::vec2 position = {0, 0};
    glm::vec2 size = {100, 100};
    glm::vec4 backgroundColor = {0.4f, 0.4f, 0.4f, 1.f};
    bool disabled = false;
  };
  static const ButtonAttributes defaultButtonAttributes = ButtonAttributes();

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

  class UIElement;
  class Root;

  class UIElement {
  public:
    using Ptr = std::shared_ptr<UIElement>;

    UIElement();

    void destroy();

    virtual void release() {};
    virtual void reset() {};
    virtual void update() = 0;

    void appendChild(const Ptr& child);

    void display(wind::CommandBuffer& renderer);

    virtual void render(wind::CommandBuffer& renderer) = 0;

    Styles styles;
    std::weak_ptr<Root> root;

  protected:
    void removeChild(Ptr child);

    // TODO: shared_ptr for parent
    UIElement* parent = nullptr;
    std::vector<Ptr> children;
  };

  class Root : public UIElement, public std::enable_shared_from_this<Root> {
  public:
    Root();

    void render(wind::CommandBuffer& renderer) override;
    void update() override;
    void reset() override;

    RootAttributes attributes;
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
    void render(wind::CommandBuffer& renderer) override;

    REGISTER_POOL(Button);
    RELEASE(Button);

    void update() override;

    void reset() override;

    ButtonAttributes attributes;
  };

  class Image : public UIElement, public std::enable_shared_from_this<Image> {
  public:
    void render(wind::CommandBuffer& renderer) override;

    REGISTER_POOL(Image);
    RELEASE(Image);

    void update() override;

    void reset() override;

    ImageAttributes attributes;
  };

  class Text : public UIElement, public std::enable_shared_from_this<Text> {
  public:
    void render(wind::CommandBuffer& renderer) override;

    REGISTER_POOL(Text);
    RELEASE(Text);

    void update() override;

    void reset() override;

    TextAttributes attributes;
  };

  class RichText : public UIElement,
                   public std::enable_shared_from_this<RichText> {
  public:
    void render(wind::CommandBuffer& renderer) override;

    REGISTER_POOL(RichText);
    RELEASE(RichText);

    void update() override;

    void reset() override;

    RichTextAttributes attributes;
  };

  std::shared_ptr<Root> init();

} // namespace wind
