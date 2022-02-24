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
 * @file IJSONWriter.h
 * @brief Header file for the IJSONWriter interface.
 * @date 24/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the IJSONWriter interface.
 */

#ifndef _SUP_IJSONWriter_h_
#define _SUP_IJSONWriter_h_

#include "BasicScalarTypes.h"

#include <string>

namespace sup
{
namespace dto
{
/**
 * @brief Interface for writing a JSON representation.
 */
class IJSONWriter
{
public:
  virtual ~IJSONWriter() = default;

  virtual bool Bool(boolean b) = 0;
  virtual bool Int(int32 i) = 0;
  virtual bool UInt(uint32 u) = 0;
  virtual bool Int64(int64 i) = 0;
  virtual bool UInt64(uint64 u) = 0;
  virtual bool Double(float64 d) = 0;
  virtual bool String(const std::string& str) = 0;
  virtual bool StartObject() = 0;
  virtual bool Key(const std::string& str) = 0;
  virtual bool EndObject() = 0;
  virtual bool StartArray() = 0;
  virtual bool EndArray() = 0;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_IJSONWriter_h_