#ifndef COLOR_H
#define COLOR_H 1

#include <memory>
#include <string>
#include <iostream>

namespace colored {

class ColorString {
public:
  static const constexpr std::string_view RESET_ALL = "\e[0m";

  ColorString &withBlack() noexcept {
    features.append("30;");
    return *this;
  }

  ColorString &withRed() noexcept {
    features.append("31;");
    return *this;
  }

  ColorString &withGreen() noexcept {
    features.append("32;");
    return *this;
  }

  ColorString &withYellow() noexcept {
    features.append("33;");
    return *this;
  }

  ColorString &withBlue() noexcept {
    features.append("34;");
    return *this;
  }

  ColorString &withMagenta() noexcept {
    features.append("35;");
    return *this;
  }

  ColorString &withCyan() noexcept {
    features.append("36;");
    return *this;
  }

  ColorString &withWhite() noexcept {
    features.append("37;");
    return *this;
  }

  ColorString &withBlackBackground() noexcept {
    features.append("40;");
    return *this;
  }

  ColorString &withRedBackground() noexcept {
    features.append("41;");
    return *this;
  }

  ColorString &withGreenBackground() noexcept {
    features.append("42;");
    return *this;
  }

  ColorString &withYellowBackground() noexcept {
    features.append("43;");
    return *this;
  }

  ColorString &withBlueBackground() noexcept {
    features.append("44;");
    return *this;
  }

  ColorString &withMagentaBackground() noexcept {
    features.append("45;");
    return *this;
  }

  ColorString &withCyanBackground() noexcept {
    features.append("46;");
    return *this;
  }

  ColorString &withWhiteBackground() noexcept {
    features.append("47;");
    return *this;
  }

  ColorString &withHighlight() noexcept {
    features.append("1;");
    return *this;
  }

  ColorString &withUnderline() noexcept {
    features.append("4;");
    return *this;
  }

  ColorString &withFlicker() noexcept {
    features.append("5;");
    return *this;
  }

  ColorString &invertColor() noexcept {
    features.append("7;");
    return *this;
  }

  ColorString &hide() noexcept {
    features.append("8;");
    return *this;
  }

  std::string to_string() const noexcept {
    std::string resultString;
    resultString.reserve(features.length() + content.length() + RESET_ALL.length());
    resultString.assign(features.cbegin(), features.cend() - 1);
    resultString.append("m");
    resultString.append(content);
    resultString.append(RESET_ALL);
    return resultString;
  }

  template <class T> ColorString &append(T &&next) noexcept {
    content.append(std::forward(next));
    return *this;
  }

  template <class T> ColorString &append(T *next) noexcept {
    content.append(next);
    return *this;
  }

  template <class T> ColorString &operator+(T &&next) noexcept {
    content.append(next);
    return *this;
  }

  template <class T> ColorString &operator+(T *next) noexcept {
    content.append(next);
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& stream, const ColorString& thiz) noexcept {
	  stream << thiz.to_string();
	  return stream;
  }

  template <class T>
  static inline ColorString create(T value, size_t size) noexcept {
	  return ColorString(value, size);
  }

  static inline ColorString create(std::string str) noexcept {
	  return ColorString(str, str.length());
  }

private:
  ColorString(std::string str, size_t size)
      : content(str), size(size), features("\e[") {}
  std::string content;
  size_t size;
  std::string features;

  friend ColorString operator""_c(const char *str, size_t size) noexcept;
};

ColorString operator""_c(const char *str, size_t size) noexcept {
  return ColorString(str, size);
}

template <> ColorString &ColorString::append(ColorString &&next) noexcept {
  this->content.append(next.to_string());
  return *this;
}

template <> ColorString &ColorString::append(ColorString *next) noexcept {
  this->content.append(next->to_string());
  return *this;
}

template <> ColorString &ColorString::operator+(ColorString &&next) noexcept {
  this->content.append(next.to_string());
  return *this;
}

template <> ColorString &ColorString::operator+(ColorString *next) noexcept {
  this->content.append(next->to_string());
  return *this;
}
}; // namespace colored

colored::ColorString operator""_c(const char *str, size_t size) noexcept {
  return colored::ColorString::create(str, size);
}

#endif /* end of include guard: COLOR_H */
