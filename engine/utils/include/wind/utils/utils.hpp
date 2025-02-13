#pragma once
#include "wind/utils/includes.hpp"

namespace wind {

  namespace chrono = std::chrono;
  using uint = unsigned int;

  template <typename C, typename T>
    requires requires(C c, T t) {
      c.find(t);
      c.end();
    }
  bool contains(C _container, T _value) {
    auto it = _container.find(_value);
    return it != _container.end();
  }

  template <class T, class U>
  bool
  compareSharedByValue(const std::shared_ptr<T>& a, const std::shared_ptr<U>& b) {
    if (a && b)
      return *a == *b;

    return !a && !b;
  }

  template <class T, class U>
  bool compareSharedByTypeId(
    const std::shared_ptr<T>& a,
    const std::shared_ptr<U>& b
  ) {
    if (!a || !b)
      return false;

    return typeid(*a) == typeid(*b);
  }

  // template <class Error, typename... T>
  //   requires std::derived_from<Error, std::exception>
  // void verify(bool _value, const char* _message, T&&... _args) {
  //   if (!_value)
  //     throw new Error(fmt::vformat(_message,
  //     fmt::make_format_args(_args...)).c_str());
  // }

  // template <typename T, typename... Args>
  // std::shared_ptr<T> shared(Args &&...args) {
  //   T instance(args...);
  //   return instance;
  //   // return std::make_shared<T>(instance);
  // }

  template <typename T>
  std::shared_ptr<T> share(T&& instance) {
    return std::shared_ptr<T>(new T(std::forward<T>(instance)));
  }

#define verify(errorType, condition)                                           \
  if (!(condition))                                                            \
  throw (errorType)(fmt::format("{}: {}", #errorType, #condition))

  // static auto forEach = std::ranges::for_each;
  template <typename Range, typename Func>
  static auto forEach(const Range& range, Func func) {
    std::for_each(std::begin(range), std::end(range), func);
  }

#ifdef _WIN32
  static auto stringToWindowsString(std::string input) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
    std::wstring wide_string = converter.from_bytes(input);
    return wide_string;
  }

  static auto windowsStringToChar(std::wstring input) {
    std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);

    std::string narrowString =
      std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(input);

    const char* charPtr = narrowString.c_str();
    return charPtr;
  }
#endif

  static auto replaceAll(
    std::string input,
    const std::string& searched,
    const std::string& replacement
  ) {
    size_t pos = 0;
    while ((pos = input.find(searched, pos)) != std::string::npos) {
      input.replace(pos, searched.length(), replacement);
      pos += replacement.length();
    }
    return input;
  }

  static fs::path removeFirstDirectory(const fs::path& filePath) {
    fs::path sourceFile;

    bool first = true;
    for (const auto& part : filePath) {
      if (first) {
        first = false;
        continue;
      }
      sourceFile /= part;
    }

    return sourceFile;
  }

  class Stopwatch {
  public:
    Stopwatch(const std::string& message) : message(message) {
      start_time = std::chrono::high_resolution_clock::now();
    }

    ~Stopwatch() {
      auto end_time = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time
      );
      spdlog::info("{} took {} milliseconds", message, duration.count());
    }

  private:
    std::string message;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
  };

} // namespace wind
