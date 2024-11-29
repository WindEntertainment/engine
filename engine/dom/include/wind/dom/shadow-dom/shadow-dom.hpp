#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include <wind/dom/shadow-dom/pool-manager.hpp>
#include <wind/dom/dom/components/index.hpp>
#include <wind/dom/shadow-dom/components/index.hpp>

namespace wind::dom::shadow {
  void appendChild(std::shared_ptr<Div> child, const Element& parent);
  void appendChild(std::shared_ptr<Root> child, const Element& parent);
  void appendChild(std::shared_ptr<Text> child, const Element& parent);
  void appendChild(std::shared_ptr<Input> child, const Element& parent);
  void appendChild(std::shared_ptr<Checkbox> child, const Element& parent);
  void appendChild(std::shared_ptr<Select> child, const Element& parent);

  void removeChild(unsigned int childId, const Element& parent);

  attributes::Root mergeAttributes(std::shared_ptr<Root> shadow);
  attributes::Div mergeAttributes(std::shared_ptr<Div> shadow);
  attributes::Text mergeAttributes(std::shared_ptr<Text> shadow);
  attributes::Input mergeAttributes(std::shared_ptr<Input> shadow);
  attributes::Checkbox mergeAttributes(std::shared_ptr<Checkbox> shadow);
  attributes::Select mergeAttributes(std::shared_ptr<Select> shadow);

  std::shared_ptr<dom::Root> toReal(std::shared_ptr<Root> shadow);
  std::shared_ptr<dom::Div> toReal(std::shared_ptr<Div> shadow);
  std::shared_ptr<dom::Text> toReal(std::shared_ptr<Text> shadow);
  std::shared_ptr<dom::Input> toReal(std::shared_ptr<Input> shadow);
  std::shared_ptr<dom::Checkbox> toReal(std::shared_ptr<Checkbox> shadow);
  std::shared_ptr<dom::Select> toReal(std::shared_ptr<Select> shadow);

  void destroy(std::shared_ptr<Root> shadow);
  void destroy(std::shared_ptr<Div> shadow);
  void destroy(std::shared_ptr<Text> shadow);
  void destroy(std::shared_ptr<Input> shadow);
  void destroy(std::shared_ptr<Checkbox> shadow);
  void destroy(std::shared_ptr<Select> shadow);

  void
  updateReal(std::shared_ptr<dom::Root> real, std::shared_ptr<Root> shadow);
  void updateReal(std::shared_ptr<dom::Div> real, std::shared_ptr<Div> shadow);
  void
  updateReal(std::shared_ptr<dom::Text> real, std::shared_ptr<Text> shadow);
  void
  updateReal(std::shared_ptr<dom::Input> real, std::shared_ptr<Input> shadow);
  void updateReal(
    std::shared_ptr<dom::Checkbox> real,
    std::shared_ptr<Checkbox> shadow
  );
  void
  updateReal(std::shared_ptr<dom::Select> real, std::shared_ptr<Select> shadow);

  std::shared_ptr<Root> init(std::shared_ptr<wind::dom::Root> realRoot);

  template <typename T>
  std::shared_ptr<T> createElement() {
    auto pool = PoolManager::getInstance().getPool<T>();
    if (!pool) {
      spdlog::warn("Trying to create element that is not registered in pool");
      return nullptr;
    }

    auto element = pool->get();
    element->id = ++wind::dom::shadow::nextId;
    return element;
  }
} // namespace wind::dom::shadow
