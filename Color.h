#pragma once

#include <iostream>

class Color {
public:
  Color();
  Color(double red, double green, double blue);
  double red() const;
  double green() const;
  double blue() const;

  void set_color(double red, double green, double blue);

private:
  double r{};
  double g{};
  double b{};
};


//Тут явно можно было сделать как-то покрасивее, но я не понял как, по этому сделал
//через сеттеры
inline std::istream& operator>>(std::istream& stream, Color& color) {
  double red, green, blue;
  stream >> red >> green >> blue;
  color.set_color(red, green, blue);
  return stream;
}