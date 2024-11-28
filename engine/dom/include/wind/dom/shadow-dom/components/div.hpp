#pragma once
#include <wind/dom/shadow-dom/shared.hpp>
#include <wind/dom/shadow-dom/pool-manager.hpp>
#include <glm/vec2.hpp>
#include <tuple>

namespace wind::dom::shadow {
  struct Div : public std::enable_shared_from_this<Div> {
  public:
    Div();
    Div(unsigned int id);

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

    bool operator==(Div& element) { return attributes == element.attributes; };

    Elements children = {};
    std::optional<Element> parent = std::nullopt;

    attributes::Div attributes = attributes::getDefaultDivAttributes();
    attributes::Div hoverAttributes = {};
    attributes::Div clickAttributes = {};
  };

  // constexpr std::array<std::pair<bool Div::*, const attributes::Div Div::*>,
  // 4>
  //   defaultPriority =
  //     {&Div::clickAttributes, &Div::hoverAttributes, &Div::attributes};

  // Highest priority at the top
  // constexpr std::array<std::pair<bool Div::*, const attributes::Div Div::*>,
  // 4>
  //   defaultPriority = {
  //     std::make_pair(&Div::isClicked, &Div::clickAttributes),
  //     std::make_pair(&Div::isHovered, &Div::hoverAttributes),
  // };
  // Attributes struct
  // struct Attributes {
  //   glm::vec2 size{0.0f, 0.0f};
  //   glm::vec2 position{0.0f, 0.0f};

  //   // Converts Attributes into a tuple
  //   auto asTuple() const { return std::tie(size, position); }
  //   auto asTuple() { return std::tie(size, position); }
  // };

  // // Helper function to merge fields
  // template <typename T, typename... K>
  // void mergeFieldWithPriority(T& resultValue, const K&... overrideValues) {
  // if constexpr (sizeof...(overrideValues) > 0) {
  //   ((overrideValues ? (resultValue = overrideValues) : void()), ...);
  // }
  // }

  // template <std::size_t... I, typename... T>
  // void
  // logTuplesHelper(const std::tuple<T...>& t1, const std::tuple<T...>& t2,
  // std::index_sequence<I...>) {
  //   // Call log for each pair of elements from both tuples
  //   // (log(std::get<I>(t1)), log(std::get<I>(t2)), ...);
  // }

  // template <typename T, typename... Overrides>
  // void mergeAttributes4(T& base, Overrides&... overrides) {
  //   spdlog::info(sizeof...(overrides));
  //   if constexpr (sizeof...(overrides) > 0) {
  //     if (((overrides != T{}) || ...)) {
  //       ((base = std::forward<Overrides>(overrides)), ...);
  //     }
  //     // ((overrides != T{} ? base = overrides : void()), ...);
  //   }
  // };

  // template <typename T, typename... Overrides>
  // void mergeAttributes34(T& base, Overrides&... overrides) {
  //   auto baseTuple = base.asTuple();
  //   auto overrideTuples =
  //     std::make_tuple(base.asTuple(), overrides.asTuple()...);

  //   // constexpr size_t numFields = std::tuple_size_v<decltype(baseTuple)>;
  //   // constexpr size_t numOverrides = sizeof...(overrides);

  //   [&]<std::size_t... FieldIndices>(std::index_sequence<FieldIndices...>) {
  //     ((mergeAttributes4(
  //        std::get<FieldIndices>(baseTuple),
  //        std::get<FieldIndices>(std::get<OverrideIndices>(overrideTuples))
  //      )),
  //      ...);
  //   }(std::make_index_sequence<numFields>{});

  // [&]<std::size_t...
  // OverrideIndices>(std::index_sequence<OverrideIndices...>) {
  //   ((mergeAttributes4(std::get<FieldIndices>(overrideTuples))), ...)
  // (([&]<std::size_t...
  // FieldIndices>(std::index_sequence<FieldIndices...>) {
  //    ((mergeAttributes4(
  //       std::get<FieldIndices>(baseTuple),
  //       std::get<FieldIndices>(std::get<OverrideIndices>(overrideTuples))
  //     )),
  //     ...);
  //  }(std::make_index_sequence<numFields>{})),
  //  ...)
  //  ...);
  // }(std::make_index_sequence<numOverrides>{});
  // };

  // template <typename T, typename... Overrides>
  // void mergeAttributes4(T& base, Overrides&... overrides) {
  //   // auto baseTuple = std::get<0>(overrideTuples).asTuple();
  //   constexpr size_t numFields = std::tuple_size_v<decltype(baseTuple)>;

  // constexpr size_t numOverrides = sizeof...(overrides);

  // [&]<std::size_t...
  // OverrideIndices>(std::index_sequence<OverrideIndices...>) {
  //   ((mergeAttributes34(std::get<FieldIndices>(overrideTuples), numFields)),
  //    ...)
  // (([&]<std::size_t...
  // FieldIndices>(std::index_sequence<FieldIndices...>) {
  //    ((mergeAttributes4(
  //       std::get<FieldIndices>(baseTuple),
  //       std::get<FieldIndices>(std::get<OverrideIndices>(overrideTuples))
  //     )),
  //     ...);
  //  }(std::make_index_sequence<numFields>{})),
  //  ...)
  //  ...);
  // }(std::make_index_sequence<numOverrides>{});
  // [&]<std::size_t... Indices>(std::index_sequence<Indices...>) {
  //   ((mergeAttributes4(
  //      std::get<Indices>(baseTuple),
  //      std::get<Indices>(std::get<Indices>(overrideTuples))
  //    )),
  //    ...);
  // }(std::make_index_sequence<numFields>{});
  // };

  // template <typename... Tuples, std::size_t... OuterIndices>
  // void
  // printTupleOfTuplesWithIndex(const std::tuple<Tuples...>& t,
  // std::index_sequence<OuterIndices...>) {
  //   // Expand the outer tuple and process each inner tuple
  //   (([]<
  //       std::
  //         size_t... InnerIndices>(const auto& innerTuple,
  //         std::index_sequence<InnerIndices...>) {
  //      // Expand each inner tuple and print its elements with their indices
  //      ((std::cout << "Outer index " << OuterIndices << ", Inner index "
  //                  << InnerIndices << ": " <<
  //                  std::get<InnerIndices>(innerTuple)
  //                  << "  "),
  //       ...);
  //      std::cout << std::endl;
  //    }(std::get<OuterIndices>(t),
  //      std::make_index_sequence<std::tuple_size<std::decay_t<Tuples>>::value>{()
  //      })),
  //    ...);
  // }

  // template <typename... Args>
  // void log(Args&&... args) {
  //   // Log the values of all arguments
  //   ((std::cout << args << " "), ...);
  //   std::cout << std::endl;
  // }

  // // Recursive helper function to process each index of the tuple
  // template <typename... Tuples, std::size_t... Indices>
  // void logIndex(const Tuples&... tuples, std::index_sequence<Indices...>) {
  //   // Call log for each index across all tuples
  //   (log(std::get<Indices>(tuples)...), ...);
  // }

  // // Function to call the log for all tuples
  // template <typename... Tuples>
  // void logTuples(const Tuples&... tuples) {
  //   constexpr size_t tuple_size =
  //   std::tuple_size<std::decay_t<Tuples>>::value; logIndex(tuples...,
  //   std::make_index_sequence<tuple_size>{});
  // }
  // template <typename... Attrs>
  // void a(Attrs&... attrs) {
  //   auto tupleOfTuples = std::make_tuple(attrs.asTuple()...);

  //   constexpr size_t tuplesLength =
  //     std::tuple_size<decltype(tupleOfTuples)>::value;
  //   constexpr size_t fieldsLength =
  //     std::tuple_size<decltype(std::get<0>(tupleOfTuples))>::value;

  //   spdlog::info("Tuple of Tuples Length: {}", tuplesLength);
  //   spdlog::info("First Tuple Length: {}", fieldsLength);
  // }

  // template <typename T>
  // T mergeField(const T&... values) {
  //   // Iterate through the values to find the first non-nullptr
  //   for (const auto& value : {values...}) {
  //     if (value != nullptr) {
  //       return value; // Return the first non-nullptr
  //     }
  //   }
  //   return nullptr; // If all are nullptr, return nullptr
  // }

  // Recursive helper to merge the tuples field by field
  // template <typename Tuple, std::size_t... Indices>
  // auto mergeTuples(const Tuple&... tuples, std::index_sequence<Indices...>) {
  //   return std::make_tuple(mergeField(std::get<Indices>(tuples)...)...);
  // }

  // // Main merge function
  // template <typename... Tuples>
  // auto merge(const Tuples&... tuples) {
  //   static_assert(
  //     sizeof...(Tuples) > 0, "At least one tuple must be provided."
  //   );
  //   constexpr std::size_t tupleSize =
  //     std::tuple_size_v<std::decay_t<decltype(std::get<0>(tuples))>>;
  //   return mergeTuples(tuples..., std::make_index_sequence<tupleSize>{});
  // }

  template <typename T = int>
  void mergeAttributes2(std::shared_ptr<Div> shadow) {
    // std::tuple<std::tuple<int, double>, std::tuple<char, float, bool>>
    // myTuple(
    //   std::make_tuple(1, 3.14), std::make_tuple('a', 2.71f, true)
    // );

    // // Call the function with an index sequence for the outer tuple
    // printTupleOfTuplesWithIndex(
    //   myTuple,
    //   std::make_index_sequence<std::tuple_size<decltype(myTuple)>::value>{}
    // );

    // std::tuple<int, int, int> tuple1 = {1, 2, 3};
    // std::tuple<int, int, int> tuple2 = {4, 5, 6};
    // std::tuple<int, int, int> tuple3 = {7, 8, 9};
    glm::vec2 a;
    spdlog::info(a.x);
    // Call logTuples with any number of tuples
    // a(shadow->attributes, shadow->hoverAttributes, shadow->clickAttributes);
    // logTuples(tuple1, tuple2, tuple3);
  }

  // // Define the Attributes struct
  // struct Attributes {
  //   std::optional<int> a;
  //   std::optional<std::string> b;

  //   // Helper to represent all fields as a tuple
  //   auto asTuple() const { return std::tie(a, b); }

  //   auto asTuple() { return std::tie(a, b); }
  // };

  // // Helper to get the first valid value for a field from the base and
  // overrides template <typename T> std::optional<T> findFirstOverride(const
  // std::optional<T>& base) {
  //   return base; // If no overrides, return base.
  // }

  // template <typename T, typename... Overrides>
  // std::optional<T> findFirstOverride(
  //   const std::optional<T>& base,
  //   const std::optional<T>& override,
  //   const Overrides&... overrides
  // ) {
  //   return override.has_value() ? override
  //                               : findFirstOverride(base, overrides...);
  // }

  // // Merge function for attribute structs
  // template <typename T, typename... Overrides>
  // T mergeAttributes(const T& base, const Overrides&... overrides) {
  //   T merged = base;

  //   // Use tuple iteration to merge each field
  //   auto mergedTuple = merged.asTuple();
  //   const auto baseTuple = base.asTuple();
  //   const auto overrideTuples = std::make_tuple(overrides.asTuple()...);

  //   std::apply(
  //     [&](auto&... mergedFields) {
  //       std::apply(
  //         [&](const auto&... baseFields) {
  //           size_t i = 0;
  //           ((mergedFields =
  //               findFirstOverride(baseFields, std::get<i>(overrideTuples[0])),
  //             ++i),
  //            ...);
  //         },
  //         baseTuple
  //       );
  //     },
  //     mergedTuple
  //   );

  //   return merged;
  // }

  // template <typename T = int>
  // void test() {
  //   Attributes baseAttributes = {42, "Base"};
  //   Attributes hoverAttributes = {std::nullopt, "Hover"};
  //   Attributes clickAttributes = {84, std::nullopt};
  //   Attributes dragAttributes = {std::nullopt, "Drag"};
  //   Attributes focusAttributes = {std::nullopt, "Focus"};

  //   // Merge attributes with multiple overrides
  //   Attributes mergedAttributes = mergeAttributes(
  //     baseAttributes,
  //     hoverAttributes,
  //     clickAttributes,
  //     dragAttributes,
  //     focusAttributes
  //   );

  //   // Output the merged results
  //   std::cout << "a: "
  //             << (mergedAttributes.a.has_value()
  //                   ? std::to_string(mergedAttributes.a.value())
  //                   : "none")
  //             << "\n";
  //   std::cout << "b: "
  //             << (mergedAttributes.b.has_value() ? mergedAttributes.b.value()
  //                                                : "none")
  //             << "\n";
  // }

  // Main function to merge attributes
  // template <typename T>
  // attributes::Div mergeAttributes2(std::shared_ptr<Div> shadow) {
  //   attributes::Div result = shadow->attributes;

  //   // auto baseTuple = shadow->attributes.asTuple();
  //   auto hoverTuple = shadow->hoverAttributes.asTuple();
  //   auto clickTuple = shadow->hoverAttributes.asTuple();
  //   auto overrideTuples[2] = {
  //     shadow->hoverAttributes.asTuple(), shadow->hoverAttributes.asTuple()
  //   };

  //   auto resultTuple = result.asTuple();

  //   constexpr size_t numFields = std::tuple_size_v<decltype(resultTuple)>;

  //   // mergeField(
  //   //          std::get<Indices>(overrideTuple),
  //   std::get<Indices>(resultTuple)
  //   //        )

  //   [&]<std::size_t... Indices>(std::index_sequence<Indices...>) {
  //     ((mergeField(
  //        std::get<Indices>(resultTuple),
  //        std::get<Indices>(hoverTuple),
  //        std::get<Indices>(clickTuple)
  //      )),
  //      ...);
  //   }(std::make_index_sequence<numFields>{});

  //   return result;
  // }

  // attributes::Div
  // resolveAttributes(std::shared_ptr<Div> component
  //                   // const attributes::Div& baseAttributes,
  //                   // const std::optional<
  //                   //   std::array<std::pair<bool Div::*, const
  //                   attributes::Div
  //                   //   Div::*>, 4>>& customPriority = std::nullopt
  // ) {
  //   attributes::Div resolved = component->attributes;

  //   resolved.angle = component->hoverAttributes.angle
  //                      ? component->hoverAttributes.angle
  //                      : component->attributes.angle;

  //   // const auto& priority = customPriority.value_or(defaultPriority);
  //   // for (const auto& [stateFlag, attributesPtr] : priority) {
  //   //   if (component.*stateFlag && attributesPtr) {
  //   //     mergeAttributes(component.*attributesPtr, resolved);
  //   //   }
  //   // }

  //   // return resolved;
  // }

} // namespace wind::dom::shadow
