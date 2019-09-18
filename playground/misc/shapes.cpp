#include <iostream>
using namespace std;

class Shape
{
public:
  virtual float GetPermiter() = 0;
  virtual float GetArea() = 0;
};

class Rectangle : public Shape
{
public:
  float width;
  float height;

  Rectangle(float w = 1, float h = 1)
  {
    width = w;
    height = h;
  }

  float GetPermiter()
  {
    return 2 * width + 2 * height;
  }

  float GetArea()
  {
    return width * height;
  }
};

int main(int argc, char const *argv[])
{
  Rectangle *rect = new Rectangle();

  cout << rect->GetArea();

  return 0;
}
