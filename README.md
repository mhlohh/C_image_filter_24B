# C_image_filter_24B
# Filters-Less Project
This repository contains my implementation of the “filters-less” problem set from Harvard’s CS50 course. The project involves creating various image filters such as grayscale, sepia, reflect, and blur, by manipulating the RGB values of bitmap images.
This repository contains my implementation of the “filters-less” problem set from Harvard’s CS50 course. The project involves creating various image filters such as grayscale, sepia, reflect, and blur, by manipulating the RGB values of bitmap images.

## Features
- **Grayscale Filter**: Converts images to grayscale by averaging the RGB values of each pixel.
- **Sepia Filter**: Applies a sepia tone to images using a specific formula to adjust the RGB values.
- **Reflect Filter**: Reflects images horizontally, creating a mirror effect.
- **Blur Filter**: Blurs images by averaging the RGB values of neighboring pixels.

  ## Getting Started
  1. Clone the Repository:
     ```
     git clone https://github.com/<youruserName>/C_image_filter_24B.git
     ```
     ```
     cd C_image_filter_24B
     ```

  2. Compile the Code:
     ```
     make filter
     ```

  4. Run the Filters:
     ```
      ./filter -g input.bmp output.bmp
     # For grayscale
     ./filter -s input.bmp output.bmp
     # For sepia
     ./filter -r input.bmp output.bmp
     # For reflect
     ./filter -b input.bmp output.bmp
     # For blur
     ```
  ## Documentation
  - **filter.c**: Contains the main logic for applying the filters.
  - **helpers.c**: Includes helper functions used by `filter.c`.
  - **bmp.h**: Header file defining the BMP file format.
  - **helpers.h**: Header file for helper functions.
