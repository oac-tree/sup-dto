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
 * @file AnyTypeBuilder.h
 * @brief Header file for the AnyTypeBuilder class.
 * @date 28/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the AnyTypeBuilder class.
 */

#ifndef _SUP_AnyTypeBuilder_h_
#define _SUP_AnyTypeBuilder_h_

#include "AnyType.h"
#include "BasicScalarTypes.h"

#include <memory>

namespace sup
{
namespace dto
{
class AnyTypeRootBuildNode;
class IAnyBuildNode;

class AnyTypeBuilder
{
public:
  AnyTypeBuilder();
  ~AnyTypeBuilder();

  AnyType MoveAnyType();

  bool Null();
  bool Bool(boolean b);
  bool Int(int32 i);
  bool Uint(uint32 u);
  bool Int64(int64 i);
  bool Uint64(uint64 u);
  bool Double(float64 d);
  bool RawNumber(const char* str, std::size_t length, bool copy);
  bool String(const char* str, std::size_t length, bool copy);
  bool StartObject();
  bool Key(const char* str, std::size_t length, bool copy);
  bool EndObject(std::size_t memberCount);
  bool StartArray();
  bool EndArray(std::size_t elementCount);

private:
  std::unique_ptr<AnyTypeRootBuildNode> root;
  IAnyBuildNode* current;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyTypeBuilder_h_
