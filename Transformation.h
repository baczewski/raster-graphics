#include "Picture.h"
#include <cmath>

class Transformation 
{
private:
    static void left(std::vector<std::vector<Pixel*>>& pixels) 
    {
        std::vector<std::vector<Pixel*>> temp;

        int rows = pixels.size();
        int columns = pixels[0].size();

        for (int i = 0; i < columns; i++)
        {
            std::vector<Pixel*> currentRow;

            for (int j = 0; j < rows; j++)
            {
                currentRow.push_back(pixels[j][i]->clone());
            }

            temp.push_back(currentRow);
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0, k = columns - 1; j < columns / 2; j++, k--)
            {
                Pixel* save = temp[j][i];
                temp[j][i] = temp[k][i];
                temp[k][i] = save; 
            }
        }

        pixels = temp;
    }

    static void right(std::vector<std::vector<Pixel*>>& pixels)
    {
        std::vector<std::vector<Pixel*>> temp;

        int rows = pixels.size(); 
        int columns = pixels[0].size();

        for (int i = 0; i < columns; i++)
        {
            std::vector<Pixel*> currentRow;

            for (int j = 0; j < rows; j++)
            {
                currentRow.push_back(pixels[j][i]->clone());
            }

            temp.push_back(currentRow);
        }

        for (int i = 0; i < columns; i++)
        {
            for (int j = 0, k = rows - 1; j < rows / 2; j++, k--)
            {
                Pixel* save = temp[i][j];
                temp[i][j] = temp[i][k];
                temp[i][k] = save; 
            }
        }

        pixels = temp;
    }

    static void vertical(std::vector<std::vector<Pixel*>>& pixels)
    {
        int rows = pixels.size();
        int columns = pixels[0].size();

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0, k = columns - 1; j < k; j++, k--)
            {
                Pixel* save = pixels[i][j];
                pixels[i][j] = pixels[i][k];
                pixels[i][k] = save; 
            }
        }
    }

    static void horizontal(std::vector<std::vector<Pixel*>>& pixels)
    {
        std::cout << "horizontal" << std::endl;
        int rows = pixels.size();
        int columns = pixels[0].size();

        for (int i = 0; i < columns; i++)
        {
            for (int j = 0, k = rows - 1; j < k; j++, k--)
            {
                Pixel* save = pixels[j][i];
                pixels[j][i] = pixels[k][i];
                pixels[k][i] = save; 
            }
        }
    }

    static void negative(std::vector<std::vector<Pixel*>>& pixels, const short maxValue, const Type& picType)
    {
        const int type = picType == 1 ? 1 : picType == 2 ? 2 : 3;

        int rows = pixels.size();
        int columns = pixels[0].size();

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (type == 1)
                {
                    BWPixel* pixel = dynamic_cast<BWPixel*>(pixels[i][j]);
                    std::vector<unsigned char> blackColor = pixel->getPixel();

                    pixel->setBlack(blackColor.front() != 0);
                }
                else if (type == 2)
                {
                    GrayPixel* pixel = dynamic_cast<GrayPixel*>(pixels[i][j]);
                    std::vector<unsigned char> intensity = pixel->getPixel();

                    pixel->setIntensity(abs(intensity.front() - maxValue), maxValue);
                }
                else if (type == 3)
                {
                    RGBPixel* pixel = dynamic_cast<RGBPixel*>(pixels[i][j]);
                    std::vector<unsigned char> colors = pixel->getPixel();

                    pixel->setRed(abs(colors[0] - maxValue), maxValue);
                    pixel->setGreen(abs(colors[1] - maxValue), maxValue);
                    pixel->setBlue(abs(colors[2] - maxValue), maxValue);
                }
            }
        }
    }

    static void monochrome(std::vector<std::vector<Pixel*>>& pixels, const short maxValue, const Type& picType)
    {
        if (picType == 1)
        {
            std::cout << "Already in monochrome" << std::endl;
            return;            
        }

        const int type = picType == 2 ? 2 : 3;

        int rows = pixels.size();
        int columns = pixels[0].size();

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (type == 2)
                {
                    GrayPixel* pixel = dynamic_cast<GrayPixel*>(pixels[i][j]);
                    std::vector<unsigned char> colors = pixel->getPixel();

                    if (colors.front() > maxValue / 2)
                    {
                        pixel->setIntensity(maxValue, maxValue);
                    }
                    else
                    {
                        pixel->setIntensity(0, maxValue);
                    }
                }
                else
                {
                    RGBPixel* pixel = dynamic_cast<RGBPixel*>(pixels[i][j]);
                    std::vector<unsigned char> colors = pixel->getPixel();

                    short specialValue = std::round(0.299 * colors[0] + 0.587 * colors[1] + 0.114 * colors[2]);

                    if (specialValue > maxValue / 2)
                    {
                        pixel->setRed(maxValue, maxValue);
                        pixel->setGreen(maxValue, maxValue);
                        pixel->setBlue(maxValue, maxValue);
                    }
                    else
                    {
                        pixel->setRed(0, maxValue);
                        pixel->setGreen(0, maxValue);
                        pixel->setBlue(0, maxValue);
                    }
                }
            }
        }
    }

    static void grayscale(std::vector<std::vector<Pixel*>>& pixels, const short maxValue, const Type& picType)
    {
        if (picType == 1 || picType == 2)
        {
            std::cout << "Already in grayscale." << std::endl;
            return;
        }

        int rows = pixels.size();
        int columns = pixels[0].size();

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                RGBPixel* pixel = dynamic_cast<RGBPixel*>(pixels[i][j]);
                std::vector<unsigned char> colors = pixel->getPixel();

                short specialValue = std::round(0.299 * colors[0] + 0.587 * colors[1] + 0.114 * colors[2]);

                pixel->setRed(specialValue, maxValue);
                pixel->setGreen(specialValue, maxValue);
                pixel->setBlue(specialValue, maxValue);
            }
        }
    }

public:
    static void crop(std::vector<std::vector<Pixel*>>& pixels, int x, int y, int width, int height)
    {
        int rows = pixels.size();
        int columns = pixels[0].size();

        if (x + width > rows || y + height > columns)
        {
            std::cout << "Crop impossible, it\'s outside the image." << std::endl;
            return;
        }

        std::vector<std::vector<Pixel*>> temp;

        for (int i = y; i < height + y; i++)
        {
            std::vector<Pixel*> currentRow;

            for (int j = x; j < width + x; j++)
            {
                currentRow.push_back(pixels[i][j]->clone());
            }

            temp.push_back(currentRow);
        }

        pixels = temp;
    }

public:
    static bool transform(std::vector<std::string>& transform, std::vector<std::vector<Pixel*>>& pixels, const Type& picType, const short maxValue)
    {
        std::cout << "Enter transform: ";

        if (transform.size() > 1)
        {

        }

        std::cout << "Optimized transform." << std::endl;

        if (transform.size() == 0)
        {
            std::cout << "After optimization there is no need to change the picture." << std::endl;
            return false;
        }

        for (int i = 0; i < transform.size(); i++)
        {
            std::string transformation = transform[i];

            if (transformation == "rotate left")
            {
                Transformation::left(pixels);
            }
            else if (transformation == "rotate right")
            {
                Transformation::right(pixels);
            }
            else if (transformation == "flip vertical")
            {
                Transformation::vertical(pixels);
            }
            else if (transformation == "flip horizontal")
            {
                Transformation::horizontal(pixels);
            }
            else if (transformation == "negative")
            {
                Transformation::negative(pixels, maxValue, picType);
            }
            else if (transformation == "monochrome")
            {
                Transformation::monochrome(pixels, maxValue, picType);
            }
            else if (transformation == "grayscale")
            {
                Transformation::grayscale(pixels, maxValue, picType);
            }
            else if (transformation.find("crop")) {
                std::istringstream iss(transformation);
                std::vector<std::string> cropParams;
                std::string word;

                while (std::getline(iss, word, ' '))
                {
                    cropParams.push_back(word);
                }

                int x = std::stoi(cropParams[1]);
                int y = std::stoi(cropParams[2]);
                int width = std::stoi(cropParams[3]);
                int height = std::stoi(cropParams[4]);

                Transformation::crop(pixels, x, y, width, height);
            }
        }

        return true;
    }
};