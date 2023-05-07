#include <iostream>
#include <fstream>
#include <vector>

class Pixel {
public:
  virtual void print() const = 0; // Pure virtual function

  virtual std::vector<unsigned char> getPixel() const = 0; // Pure virtual function
  
  virtual ~Pixel() {} // Virtual destructor

  virtual std::ostream& operator<<(std::ostream& os) const {
    print();
    return os;
  }
};

class RGBPixel : public Pixel {
private:
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  
public:
  RGBPixel(unsigned char r, unsigned char g, unsigned char b, const unsigned char maxVal = 255) {
    setRed(r, maxVal);
    setGreen(g, maxVal);
    setBlue(b, maxVal);
  }

  void setRed(unsigned char r, const unsigned char maxVal) {
    try {
        if (r > maxVal) {
            red = maxVal;
            throw std::out_of_range("Red value greater than max value");
        }
        if(r < 0) {
            red = 0;
            throw std::out_of_range("Red value less than 0");
        }
        red = r;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
  }

  void setGreen(unsigned char g, const unsigned char maxVal) {
    try {
        if (g > maxVal) {
            green = maxVal;
            throw std::out_of_range("Green value greater than max value");
        }
        if(g < 0) {
            green = 0;
            throw std::out_of_range("Green value less than 0");
        }
        green = g;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
  }

  void setBlue(unsigned char b, const unsigned char maxVal) {
    try {
        if (b > maxVal) {
            blue = maxVal;
            throw std::out_of_range("Blue value greater than max value");
        }
        if(b < 0) {
            blue = 0;
            throw std::out_of_range("Blue value less than 0");
        }
        blue = b;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
  }

  void print() const override {
    std::cout << int(red) << ' ' << int(green) << ' ' << int(blue) << '\t';
  }

  std::vector<unsigned char> getPixel() const override {
    std::vector<unsigned char> pixel;
    pixel.push_back(red);
    pixel.push_back(green);
    pixel.push_back(blue);
    return pixel;
  }

  std::ostream &operator<<(std::ostream &os) const override {
    os << int(red) << ' ' << int(green) << ' ' << int(blue) << ' ';
    return os;
  }
};

class GrayPixel : public Pixel {
private:
  unsigned char intensity;
  
public:
  GrayPixel(unsigned char i, const unsigned char maxVal = 255) {
    setIntensity(i, maxVal);
  }

  void setIntensity(unsigned char i, const unsigned char maxVal) {
    try {
        if (i > maxVal) {
            intensity = maxVal;
            throw std::out_of_range("Intensity value greater than max value");
        }
        if(i < 0) {
            intensity = 0;
            throw std::out_of_range("Intensity value less than 0");
        }
        intensity = i;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
  }

  void print() const override {
    std::cout << int(intensity) << '\t';
  }

  std::vector<unsigned char> getPixel() const override {
    std::vector<unsigned char> pixel;
    pixel.push_back(intensity);
    return pixel;
  }

  std::ostream &operator<<(std::ostream &os) const override {
    os << int(intensity) << ' ';
    return os;
  }
};

class BWPixel : public Pixel {
private:
  bool isBlack;
  
public:
  BWPixel(bool black) {
    setBlack(black);
  }

  void setBlack(bool black) {
    isBlack = black;
  }

  void print() const override {
    std::cout << isBlack << '\t';
  }

  std::vector<unsigned char> getPixel() const override {
    std::vector<unsigned char> pixel;
    pixel.push_back(isBlack);
    return pixel;
  }

  std::ostream &operator<<(std::ostream &os) const override {
    os << isBlack << ' ';
    return os;
  }
};
