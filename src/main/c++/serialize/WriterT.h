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
 * @file WriterT.h
 * @brief Header file for the WriterT class template.
 * @date 24/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the WriterT class template.
 */

#ifndef _SUP_WriterT_h_
#define _SUP_WriterT_h_

#include "IWriter.h"
#include "AnyValueExceptions.h"

namespace sup
{
namespace dto
{
/**
 * @brief Class template for writing a JSON representation.
 */
template <typename Writer>
class WriterT : public IWriter
{
public:
  WriterT();
  ~WriterT();

  virtual Writer& Impl() = 0;

  bool Bool(boolean b) override;
  bool Int(int32 i) override;
  bool Uint(uint32 u) override;
  bool Int64(int64 i) override;
  bool Uint64(uint64 u) override;
  bool Double(float64 d) override;
  bool String(const std::string& str) override;
  bool StartObject() override;
  bool Key(const std::string& str) override;
  bool EndObject() override;
  bool StartArray() override;
  bool EndArray() override;
};

template <typename Writer>
WriterT<Writer>::WriterT() = default;

template <typename Writer>
WriterT<Writer>::~WriterT() = default;

template <typename Writer>
bool WriterT<Writer>::Bool(boolean b)
{
  return Impl().Bool(b);
}

template <typename Writer>
bool WriterT<Writer>::Int(int32 i)
{
  return Impl().Int(i);
}

template <typename Writer>
bool WriterT<Writer>::Uint(uint32 u)
{
  return Impl().Uint(u);
}

template <typename Writer>
bool WriterT<Writer>::Int64(int64 i)
{
  return Impl().Int64(i);
}

template <typename Writer>
bool WriterT<Writer>::Uint64(uint64 u)
{
  return Impl().Uint64(u);
}

template <typename Writer>
bool WriterT<Writer>::Double(float64 d)
{
  return Impl().Double(d);
}

template <typename Writer>
bool WriterT<Writer>::String(const std::string& str)
{
  return Impl().String(str.c_str(), str.size());
}

template <typename Writer>
bool WriterT<Writer>::StartObject()
{
  return Impl().StartObject();
}

template <typename Writer>
bool WriterT<Writer>::Key(const std::string& str)
{
  return Impl().Key(str.c_str(), str.size());
}

template <typename Writer>
bool WriterT<Writer>::EndObject()
{
  return Impl().EndObject();
}

template <typename Writer>
bool WriterT<Writer>::StartArray()
{
  return Impl().StartArray();
}

template <typename Writer>
bool WriterT<Writer>::EndArray()
{
  return Impl().EndArray();
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_WriterT_h_