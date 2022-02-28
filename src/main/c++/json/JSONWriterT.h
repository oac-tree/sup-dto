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
 * @date 28/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the JSONWriterT class template.
 */

#ifndef _SUP_JSONWriterT_h_
#define _SUP_JSONWriterT_h_

#include "IWriter.h"

namespace sup
{
namespace dto
{

template <typename Buffer, template <typename> typename WriterImpl>
class JSONStringWriterT : public IWriter
{
public:
  JSONStringWriterT();
  ~JSONStringWriterT();

  std::string GetRepresentation() const override;

  bool Null() override;
  bool Bool(boolean b) override;
  bool Char(char8 c) override;
  bool Int8(int8 i) override;
  bool Uint8(uint8 u) override;
  bool Int16(int16 i) override;
  bool Uint16(uint16 u) override;
  bool Int32(int32 i) override;
  bool Uint32(uint32 u) override;
  bool Int64(int64 i) override;
  bool Uint64(uint64 u) override;
  bool Float(float32 f) override;
  bool Double(float64 d) override;
  bool String(const std::string& str) override;
  bool StartStructure() override;
  bool Member(const std::string& str) override;
  bool EndStructure() override;
  bool StartArray() override;
  bool EndArray() override;

private:
  Buffer buffer;
  WriterImpl<Buffer> json_writer;
};

template <typename Buffer, template <typename> typename WriterImpl>
JSONStringWriterT<Buffer, WriterImpl>::JSONStringWriterT()
  : buffer{}
  , json_writer{buffer}
{}

template <typename Buffer, template <typename> typename WriterImpl>
JSONStringWriterT<Buffer, WriterImpl>::~JSONStringWriterT() = default;

template <typename Buffer, template <typename> typename WriterImpl>
std::string JSONStringWriterT<Buffer, WriterImpl>::GetRepresentation() const
{
  return buffer.GetString();
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::Null()
{
  return json_writer.Null();
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::Bool(boolean b)
{
  return json_writer.Bool(b);
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::Char(char8 c)
{
  return json_writer.Int(c);
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::Int8(int8 i)
{
  return json_writer.Int(i);
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::Uint8(uint8 u)
{
  return json_writer.Uint(u);
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::Int16(int16 i)
{
  return json_writer.Int(i);
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::Uint16(uint16 u)
{
  return json_writer.Uint(u);
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::Int32(int32 i)
{
  return json_writer.Int(i);
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::Uint32(uint32 u)
{
  return json_writer.Uint(u);
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::Int64(int64 i)
{
  return json_writer.Int64(i);
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::Uint64(uint64 u)
{
  return json_writer.Uint64(u);
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::Float(float32 f)
{
  return json_writer.Double(f);
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::Double(float64 d)
{
  return json_writer.Double(d);
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::String(const std::string& str)
{
  return json_writer.String(str.c_str(), str.size());
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::StartStructure()
{
  return json_writer.StartObject();
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::Member(const std::string& str)
{
  return json_writer.Key(str.c_str(), str.size());
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::EndStructure()
{
  return json_writer.EndObject();
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::StartArray()
{
  return json_writer.StartArray();
}

template <typename Buffer, template <typename> typename WriterImpl>
bool JSONStringWriterT<Buffer, WriterImpl>::EndArray()
{
  return json_writer.EndArray();
}

}  // namespace dto

}  // namespace sup

#endif  // _SUP_JSONWriterT_h_
