/******************************************************************************
This file is part of battleVision.

battleVision is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

battleVision is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with battleVision.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#ifndef SC_TGA_FILE_H
#define SC_TGA_FILE_H

#include <string>

#include "Logger.h"

class TGAFile
{
public:

  uint8_t* data() const { return data_; }
  auto width() const { return width_; }
  auto height() const { return height_; }
  std::string filename() const { return filename_; }

  explicit TGAFile(const std::string& filename) {
    load(filename);
  }

  ~TGAFile() {
    delete[] data_;
  }

  bool load(const std::string& filename) {
    FILE *file_handler;
    uint8_t byte_ignore;
    uint16_t short_ignore;
    uint64_t size;
    uint32_t color_mode;

    filename_ = filename;
    // Open the TGA file.
    file_handler = fopen(filename.c_str(), "rb");
    if (file_handler == nullptr)
    {
      Logger::error("File %s can't be opened", filename.c_str());
      return false;
    }
  
    // Read the two first bytes we don't need.
    fread(&byte_ignore, sizeof(byte_ignore), 1, file_handler);
    fread(&byte_ignore, sizeof(byte_ignore), 1, file_handler);
  
    // Which type of image gets stored in imageTypeCode.
    fread(&type_code_, sizeof(type_code_), 1, file_handler);
  
    // For our purposes, the type code should be 2 (uncompressed RGB image)
    // or 3 (uncompressed black-and-white images).
    if (type_code_ != 2 && type_code_ != 3)
    {
      fclose(file_handler);
      Logger::error("Incorrect type code: %d", type_code_);
      return false;
    }
  
    // Read 13 bytes of data we don't need.
    fread(&short_ignore, sizeof(short_ignore), 1, file_handler);
    fread(&short_ignore, sizeof(short_ignore), 1, file_handler);
    fread(&byte_ignore, sizeof(byte_ignore), 1, file_handler);
    fread(&short_ignore, sizeof(short_ignore), 1, file_handler);
    fread(&short_ignore, sizeof(short_ignore), 1, file_handler);
  
    // Read the image's width and height.
    fread(&width_, sizeof(width_), 1, file_handler);
    fread(&height_, sizeof(height_), 1, file_handler);
  
    // Read the bit depth.
    fread(&bit_count_, sizeof(bit_count_), 1, file_handler);
  
    // Read one byte of data we don't need.
    fread(&byte_ignore, sizeof(byte_ignore), 1, file_handler);
  
    // Color mode -> 3 = BGR, 4 = BGRA.
    color_mode = bit_count_ >> 3;
    size = width_ * height_ * color_mode;
  
    // Allocate memory for the image data.
    data_ = new uint8_t[size];
  
    // Read the image data.
    fread(data_, sizeof(uint8_t), size, file_handler);
  
    // Change from BGR to RGB so OpenGL can read the image data.
    for (uint64_t index {0}; index < size; index += color_mode) {
      std::swap(data_[index], data_[index + 2]);
    }
  
    fclose(file_handler);
  
    Logger::info("TGA loader: file %s successfully loaded: %dx%d", filename.c_str(), width_, height_);
  
    return true;
  }
private:
  std::string filename_;
  uint8_t type_code_ {0};
  uint16_t width_ {0};
  uint16_t height_ {0};
  uint8_t bit_count_ {0};
  uint8_t *data_ {nullptr};
};

#endif