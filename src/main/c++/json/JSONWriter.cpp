/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - DTO
 *
 * Description   : Unit test code
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

#include "JSONWriter.h"

namespace sup
{
namespace dto
{

JSONStringWriter::JSONStringWriter()
  : buffer{}
  , json_writer{buffer}
{}

JSONStringWriter::~JSONStringWriter() = default;

std::string JSONStringWriter::GetRepresentation() const
{
  return buffer.GetString();
}

void JSONStringWriter::Reset()
{
  buffer.Clear();
  json_writer.Reset(buffer);
}

bool JSONStringWriter::Null()
{
  return json_writer.Null();
}

bool JSONStringWriter::Bool(boolean b)
{
  return json_writer.Bool(b);
}

bool JSONStringWriter::Char(char8 c)
{
  return json_writer.Int(c);
}

bool JSONStringWriter::Int8(int8 i)
{
  return json_writer.Int(i);
}

bool JSONStringWriter::Uint8(uint8 u)
{
  return json_writer.Uint(u);
}

bool JSONStringWriter::Int16(int16 i)
{
  return json_writer.Int(i);
}

bool JSONStringWriter::Uint16(uint16 u)
{
  return json_writer.Uint(u);
}

bool JSONStringWriter::Int32(int32 i)
{
  return json_writer.Int(i);
}

bool JSONStringWriter::Uint32(uint32 u)
{
  return json_writer.Uint(u);
}

bool JSONStringWriter::Int64(int64 i)
{
  return json_writer.Int64(i);
}

bool JSONStringWriter::Uint64(uint64 u)
{
  return json_writer.Uint64(u);
}

bool JSONStringWriter::Float(float32 f)
{
  return json_writer.Double(f);
}

bool JSONStringWriter::Double(float64 d)
{
  return json_writer.Double(d);
}

bool JSONStringWriter::String(const std::string& str)
{
  return json_writer.String(str.c_str(), str.size());
}

bool JSONStringWriter::StartStructure()
{
  return json_writer.StartObject();
}

bool JSONStringWriter::Member(const std::string& str)
{
  return json_writer.Key(str.c_str(), str.size());
}

bool JSONStringWriter::EndStructure()
{
  return json_writer.EndObject();
}

bool JSONStringWriter::StartArray()
{
  return json_writer.StartArray();
}

bool JSONStringWriter::EndArray()
{
  return json_writer.EndArray();
}

}  // namespace dto

}  // namespace sup
