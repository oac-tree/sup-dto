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
 * @file IWriter.h
 * @brief Header file for the IWriter interface.
 * @date 24/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the IWriter interface.
 */

#ifndef _SUP_IWriter_h_
#define _SUP_IWriter_h_

#include "BasicScalarTypes.h"

#include <string>

namespace sup
{
namespace dto
{
class AnyValue;

/**
 * @brief Interface for writing a JSON representation.
 */
class IWriter
{
public:
  virtual ~IWriter();

  virtual std::string GetRepresentation() const = 0;

  virtual bool Null() = 0;
  virtual bool Bool(boolean b) = 0;
  virtual bool Char(char8 c) = 0;
  virtual bool Int8(int8 i) = 0;
  virtual bool Uint8(uint8 u) = 0;
  virtual bool Int16(int16 i) = 0;
  virtual bool Uint16(uint16 u) = 0;
  virtual bool Int32(int32 i) = 0;
  virtual bool Uint32(uint32 u) = 0;
  virtual bool Int64(int64 i) = 0;
  virtual bool Uint64(uint64 u) = 0;
  virtual bool Float(float32 f) = 0;
  virtual bool Double(float64 d) = 0;
  virtual bool String(const std::string& str) = 0;
  virtual bool StartStructure() = 0;
  virtual bool Member(const std::string& str) = 0;
  virtual bool EndStructure() = 0;
  virtual bool StartArray() = 0;
  virtual bool EndArray() = 0;
};

bool WriteScalarValue(const AnyValue& anyvalue, IWriter* writer);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_IWriter_h_