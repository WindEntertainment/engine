#pragma once
#include <wind/dom/shadow-dom/shared.hpp>

#include <algorithm>
#include <typeindex>
#include <utility>

namespace wind::dom::shadow {

  static unsigned int nextId;

  struct Root;
  struct Div;
  struct Text;
  struct Input;
  struct Checkbox;
  struct Select;

  using Element = std::variant<
    std::shared_ptr<wind::dom::shadow::Div>,
    std::shared_ptr<wind::dom::shadow::Text>,
    std::shared_ptr<wind::dom::shadow::Input>,
    std::shared_ptr<wind::dom::shadow::Checkbox>,
    std::shared_ptr<wind::dom::shadow::Select>,
    std::shared_ptr<wind::dom::shadow::Root>>;
  using Elements = std::vector<Element>;

  template <typename T>
  class WidgetPool {
  public:
    explicit WidgetPool(size_t size = 50) { prefill(size); }

    std::shared_ptr<T> get() {
      if (available.empty()) {
        increasePoolSize(20);
      }

      auto item = available.back();
      available.pop_back();
      reserved.push_back(item);

      return item;
    }

    void release(std::shared_ptr<T> item) {
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

    std::vector<std::shared_ptr<T>> reserved;
    std::vector<std::shared_ptr<T>> available;
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

    template <typename T>
    static void registerPool(size_t size = 50) {
      auto pool = wind::share(WidgetPool<T>(size));
      PoolManager::getInstance().registerPool<T>(pool);
    }

    template <typename T>
    static void releaseFromPool(std::shared_ptr<T> item) {
      auto pool = PoolManager::getInstance().getPool<T>();
      if (pool) {
        pool->release(item);
      }
    }

  private:
    std::unordered_map<std::type_index, std::shared_ptr<void>> pools;
    PoolManager() = default;
  };

} // namespace wind::dom::shadow
