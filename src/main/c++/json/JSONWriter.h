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
 * @file JSONWriter.h
 * @brief Header file for the JSONWriter classes.
 * @date 24/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the JSONWriter classes.
 */

#ifndef _SUP_JSONWriter_h_
#define _SUP_JSONWriter_h_

#include "IWriter.h"

#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace sup
{
namespace dto
{

class JSONStringWriter : public IWriter
{
public:
  JSONStringWriter(rapidjson::StringBuffer& buffer);
  ~JSONStringWriter();

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
  rapidjson::Writer<rapidjson::StringBuffer> json_writer;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_JSONWriter_h_
