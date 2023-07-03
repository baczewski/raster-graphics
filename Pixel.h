#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <exception>

class Pixel {
protected: 
  static const unsigned char MAX_VALUE;

public:
  virtual void print() const = 0; // Pure virtual functions
  virtual std::vector<unsigned char> getPixel() const = 0;
  virtual Pixel* clone() const = 0;
  
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
  RGBPixel(unsigned char r, unsigned char g, unsigned char b, const unsigned char maxVal);

  void setRed(unsigned char r, const unsigned char maxVal);
  void setGreen(unsigned char g, const unsigned char maxVal);
  void setBlue(unsigned char b, const unsigned char maxVal);

  void print() const override;
  std::vector<unsigned char> getPixel() const override;
  RGBPixel* clone() const override;

  std::ostream& operator<<(std::ostream& os) const override;
};

class GrayPixel : public Pixel {
private:
  unsigned char intensity;
  
public:
  GrayPixel(unsigned char i, const unsigned char maxVal);

  void setIntensity(unsigned char i, const unsigned char maxVal);

  void print() const override;
  std::vector<unsigned char> getPixel() const override;
  GrayPixel* clone() const override;
  
  std::ostream& operator<<(std::ostream& os) const override;
};

class BWPixel : public Pixel {
private:
  bool isBlack;
  
public:
  BWPixel(bool black);

  void setBlack(bool black);

  void print() const override;
  std::vector<unsigned char> getPixel() const override;
  BWPixel* clone() const override;
  
  std::ostream& operator<<(std::ostream& os) const override;
};
