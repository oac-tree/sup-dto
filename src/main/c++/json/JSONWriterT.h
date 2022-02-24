/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Data transfer objects for SUP
 *
 * Author        : Walter Van Herck (IO)
 *
 * Copyright (c) : 2010-2022 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

/**
 * @file JSONWriterT.h
 * @brief Header file for the JSONWriterT class template.
 * @date 24/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the JSONWriterT class template.
 */

#ifndef _SUP_JSONWriterT_h_
#define _SUP_JSONWriterT_h_

#include "IJSONWriter.h"
#include "AnyValueExceptions.h"

namespace sup
{
namespace dto
{
/**
 * @brief Class template for writing a JSON representation.
 */
template <typename Writer>
class JSONWriterT : public IJSONWriter
{
public:
  JSONWriterT(Writer* impl);
  ~JSONWriterT();

  bool Bool(boolean b) override;
  bool Int(int32 i) override;
  bool UInt(uint32 u) override;
  bool Int64(int64 i) override;
  bool UInt64(uint64 u) override;
  bool Double(float64 d) override;
  bool String(const std::string& str) override;
  bool StartObject() override;
  bool Key(const std::string& str) override;
  bool EndObject() override;
  bool StartArray() override;
  bool EndArray() override;

private:
  Writer* impl;
};

template <typename Writer>
JSONWriterT<Writer>::JSONWriterT(Writer* impl_)
  : impl{impl_}
{
  if (impl == nullptr)
  {
    throw InitializationException("JSONWriterT constructor requires non-null implementation "
                                  "pointer");
  }
}

template <typename Writer>
JSONWriterT<Writer>::~JSONWriterT() = default;

template <typename Writer>
bool JSONWriterT<Writer>::Bool(boolean b)
{
  return impl->Bool(b);
}

template <typename Writer>
bool JSONWriterT<Writer>::Int(int32 i)
{
  return impl->Int(i);
}

template <typename Writer>
bool JSONWriterT<Writer>::UInt(uint32 u)
{
  return impl->UInt(u);
}

template <typename Writer>
bool JSONWriterT<Writer>::Int64(int64 i)
{
  return impl->Int64(i);
}

template <typename Writer>
bool JSONWriterT<Writer>::UInt64(uint64 u)
{
  return impl->UInt64(u);
}

template <typename Writer>
bool JSONWriterT<Writer>::Double(float64 d)
{
  return impl->Double(d);
}

template <typename Writer>
bool JSONWriterT<Writer>::String(const std::string& str)
{
  return impl->String(str.c_str(), str.size());
}

template <typename Writer>
bool JSONWriterT<Writer>::StartObject()
{
  return impl->StartObject();
}

template <typename Writer>
bool JSONWriterT<Writer>::Key(const std::string& str)
{
  return impl->Key(str.c_str(), str.size());
}

template <typename Writer>
bool JSONWriterT<Writer>::EndObject()
{
  return impl->EndObject();
}

template <typename Writer>
bool JSONWriterT<Writer>::StartArray()
{
  return impl->StartArray();
}

template <typename Writer>
bool JSONWriterT<Writer>::EndArray()
{
  return impl->EndArray();
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_JSONWriterT_h_