/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "caching_encoder.h"
#include "encoderbase.h"

#include <memory>
#include <string>

#include <unicode/ucnv.h>

class ICUEncoder: public EncoderBase {
public:
  ICUEncoder(const char* const name);

  ICUEncoder(const std::string& name);

  ICUEncoder(const ICUEncoder& other): ICUEncoder(other.enc_name) {}

  ICUEncoder& operator=(const ICUEncoder& other) {
    init(other.enc_name.c_str());
    return *this;
  }

  ICUEncoder(ICUEncoder&& other) = default;

  ICUEncoder& operator=(ICUEncoder&& other) = default;

  virtual ICUEncoder* clone() const { return new ICUEncoder(*this); }

  virtual uint32_t maxByteLength() const;

  virtual std::string name() const;

  virtual uint32_t write(int cp, byte buf[]) const;

  using EncoderBase::write;

private:
  void init(const char* const name);

  std::string enc_name;
  std::unique_ptr<UConverter,void(*)(UConverter*)> src_conv{nullptr, nullptr};
  std::unique_ptr<UConverter,void(*)(UConverter*)> dst_conv{nullptr, nullptr};
  std::unique_ptr<UChar[]> pivot;

  uint32_t max_bytes;
};

class CachingICUEncoder: public CachingEncoder<ICUEncoder> {
public:
  CachingICUEncoder(const char* const name):
    CachingEncoder<ICUEncoder>({}, name) {}

  CachingICUEncoder(const std::string& name):
    CachingEncoder<ICUEncoder>({}, name) {}
};
