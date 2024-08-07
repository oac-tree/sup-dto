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
 * Copyright (c) : 2010-2023 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_JSON_WRITER_T_H_
#define SUP_DTO_JSON_WRITER_T_H_

#include <sup/dto/rapidjson/prettywriter.h>
#include <sup/dto/rapidjson/ostreamwrapper.h>
#include <sup/dto/rapidjson/writer.h>
#include <sup/dto/serialize/i_writer.h>

#include <ostream>

namespace
{
const sup::dto::uint32 kIndentSize = 2u;
}

namespace sup
{
namespace dto
{
using RapidJSONWriter = rapidjson::Writer<rapidjson::OStreamWrapper>;
using RapidJSONPrettyWriter = rapidjson::PrettyWriter<rapidjson::OStreamWrapper>;

template <typename WriterImpl>
class JSONStringWriterT : public IWriter
{
public:
  explicit JSONStringWriterT(std::ostream& out_stream);
  ~JSONStringWriterT();

  JSONStringWriterT(const JSONStringWriterT& other) = delete;
  JSONStringWriterT(JSONStringWriterT&& other) = delete;
  JSONStringWriterT& operator=(const JSONStringWriterT& other) = delete;
  JSONStringWriterT& operator=(JSONStringWriterT&& other) = delete;


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
  rapidjson::OStreamWrapper m_out_stream;
  WriterImpl m_json_writer;
};

template <typename WriterImpl>
JSONStringWriterT<WriterImpl>::JSONStringWriterT(std::ostream& out_stream)
  : m_out_stream{out_stream}
  , m_json_writer{m_out_stream}
{}

template <>
JSONStringWriterT<RapidJSONPrettyWriter>::JSONStringWriterT(std::ostream& out_stream)
  : m_out_stream{out_stream}
  , m_json_writer{m_out_stream}
{
  (void)m_json_writer.SetIndent(' ', kIndentSize);
}

template <typename WriterImpl>
JSONStringWriterT<WriterImpl>::~JSONStringWriterT() = default;

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::Null()
{
  return m_json_writer.Null();
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::Bool(boolean b)
{
  return m_json_writer.Bool(b);
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::Char(char8 c)
{
  return m_json_writer.Int(c);
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::Int8(int8 i)
{
  return m_json_writer.Int(i);
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::Uint8(uint8 u)
{
  return m_json_writer.Uint(u);
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::Int16(int16 i)
{
  return m_json_writer.Int(i);
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::Uint16(uint16 u)
{
  return m_json_writer.Uint(u);
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::Int32(int32 i)
{
  return m_json_writer.Int(i);
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::Uint32(uint32 u)
{
  return m_json_writer.Uint(u);
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::Int64(int64 i)
{
  return m_json_writer.Int64(i);
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::Uint64(uint64 u)
{
  return m_json_writer.Uint64(u);
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::Float(float32 f)
{
  return m_json_writer.Double(f);
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::Double(float64 d)
{
  return m_json_writer.Double(d);
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::String(const std::string& str)
{
  return m_json_writer.String(str.c_str(), static_cast<unsigned int>(str.size()));
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::StartStructure()
{
  return m_json_writer.StartObject();
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::Member(const std::string& str)
{
  return m_json_writer.Key(str.c_str(), static_cast<unsigned int>(str.size()));
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::EndStructure()
{
  return m_json_writer.EndObject();
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::StartArray()
{
  return m_json_writer.StartArray();
}

template <typename WriterImpl>
bool JSONStringWriterT<WriterImpl>::EndArray()
{
  return m_json_writer.EndArray();
}

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_JSON_WRITER_T_H_
