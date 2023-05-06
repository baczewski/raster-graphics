# Raster Graphics Editor for Clean Code Course FMI

> A powerful raster graphics editor written in C++ with a console interface, supporting multiple image formats and various editing capabilities.

## Features ✨

- Open, read, and create .pgm, .pbm, and .ppm files
- Supports multiple photos at any given moment
- Provides the following editing features:
  - Grayscale filter
  - Black and white filter
  - Rotate left/right
  - Flip horizontally/vertically
  - Invert colors
  - Crop image
  - Apply red/blue/green filters

## Getting Started 🚀

### Requirements ⚙️

- C++ compiler (e.g., GCC, Clang)

### Installation ⬇️

1. Clone the repository:

   ```bash
   git clone https://github.com/baczewski/raster-graphics.git
   ```

2. Build the project using your preferred C++ compiler. For example, with g++::

   ```bash
   g++ main.cpp RasterGraphicsEditor.cpp -o editor
   ```

3. Run the compiled executable:

   ```bash
   ./editor
   ```

## Usage 📋

After running the executable, you will be prompted to enter a command. The following commands are supported:
- `load <path>` - opens the image at the specified path
- `save ` - saves the current image at the specified path
- `saveas <path>` - saves the current image at the specified path
- `grayscale` - applies the grayscale filter to the current image
- `monochrome` - applies the black and white filter to the current image
- `negative` - inverts the colors of the current image
- `rotate left` - rotates the current image 90 degrees to the left
- `rotate right` - rotates the current image 90 degrees to the right
- `flip horizontal` - flips the current image horizontally
- `flip vertical` - flips the current image vertically
- `crop <x> <y> <width> <height>` - crops the current image
- `undo` - undoes the last change to the current image
- `help` - prints the list of commands
- `exit` - exits the program

## Contributors 🤝

- Alex Hristov
- Ionna Aneva
- Martin Marinov
- Bobi Bonev