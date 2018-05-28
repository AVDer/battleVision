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

#ifndef SC_GL_TEXTURE_H
#define SC_GL_TEXTURE_H

#include "glad/glad.h"
#include "FileTGA.h"

class OGLTexture {
 public:
  GLuint id() const { return id_; };

  GLuint width() const { return width_; }

  GLuint height() const { return height_; }

  double_t ratio() const { return ratio_; }

  OGLTexture() = default;

  explicit OGLTexture(const TGAFile &texture_file) {
    uint8_t *pixels = texture_file.data();
    width_ = texture_file.width();
    height_ = texture_file.height();
    ratio_ = static_cast<double_t>(width_) / height_;
    // Use tightly packed data
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // Generate a texture object
    glGenTextures(1, &id_);
    // Bind the texture object
    glBindTexture(GL_TEXTURE_2D, id_);
    {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      // Load the texture
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
      Logger::info("BattleField: Texture %s loaded", texture_file.filename().c_str());
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
  }

 private:
  GLuint id_{0};
  GLuint width_{0};
  GLuint height_{0};
  double_t ratio_{1.};
};

#endif
