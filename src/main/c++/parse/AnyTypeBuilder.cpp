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

#include "AnyTypeBuilder.h"

#include "AnyTypeBuildNode.h"
#include "AnyValueExceptions.h"

namespace sup
{
namespace dto
{

AnyTypeBuilder::AnyTypeBuilder()
  : root{new AnyTypeBuildNode{nullptr}}
  , current{root.get()}
{}

AnyTypeBuilder::~AnyTypeBuilder() = default;

AnyType AnyTypeBuilder::MoveAnyType()
{
  return root->MoveAnyType();
}

bool AnyTypeBuilder::Null()
{
  return current->Null();
}

bool AnyTypeBuilder::Bool(boolean b)
{
  return current->Bool(b);
}

bool AnyTypeBuilder::Int(int32 i)
{
  return current->Int32(i);
}

bool AnyTypeBuilder::Uint(uint32 u)
{
  return current->Uint32(u);
}

bool AnyTypeBuilder::Int64(int64 i)
{
  return current->Int64(i);
}

bool AnyTypeBuilder::Uint64(uint64 u)
{
  return current->Uint64(u);
}

bool AnyTypeBuilder::Double(float64 d)
{
  return current->Double(d);
}

bool AnyTypeBuilder::RawNumber(const char*, std::size_t, bool)
{
  throw InvalidOperationException(
      "AnyTypeBuilder::RawNumber not supported");
}

bool AnyTypeBuilder::String(const char* str, std::size_t length, bool copy)
{
  std::string arg(str, length);
  return current->String(arg);
}

bool AnyTypeBuilder::StartObject()
{
  current = current->GetStructureNode();
  return true;
}

bool AnyTypeBuilder::Key(const char* str, std::size_t length, bool copy)
{
  std::string arg(str, length);
  return current->Member(arg);
}

bool AnyTypeBuilder::EndObject(std::size_t)
{
  current = current->Parent();
  if (!current)
  {
    throw InvalidOperationException(
      "AnyTypeBuilder::EndObject current node is null");
  }
  current->PopStructureNode();
  return true;
}

bool AnyTypeBuilder::StartArray()
{
  current = current->GetArrayNode();
  return true;
}

bool AnyTypeBuilder::EndArray(std::size_t elementCount)
{
  current = current->Parent();
  if (!current)
  {
    throw InvalidOperationException(
      "AnyTypeBuilder::EndArray current node is null");
  }
  current->PopArrayNode();
  return true;
}

}  // namespace dto

}  // namespace sup
