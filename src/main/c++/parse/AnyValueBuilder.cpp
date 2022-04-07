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

#include "AnyValueBuilder.h"

#include "AnyValueRootBuildNode.h"
#include "AnyValueExceptions.h"

namespace sup
{
namespace dto
{

AnyValueBuilder::AnyValueBuilder()
  : root{new AnyValueRootBuildNode{}}
  , current{root.get()}
{}

AnyValueBuilder::~AnyValueBuilder() = default;

AnyValue AnyValueBuilder::MoveAnyValue()
{
  // Ensure all nodes were popped
  if (current != root.get())
  {
    throw ParseException("AnyValueBuilder::MoveAnyValue called before parsing was finished");
  }
  return root->MoveAnyValue();
}

bool AnyValueBuilder::Null()
{
  return current->Null();
}

bool AnyValueBuilder::Bool(boolean b)
{
  return current->Bool(b);
}

bool AnyValueBuilder::Int(int32 i)
{
  return current->Int32(i);
}

bool AnyValueBuilder::Uint(uint32 u)
{
  return current->Uint32(u);
}

bool AnyValueBuilder::Int64(int64 i)
{
  return current->Int64(i);
}

bool AnyValueBuilder::Uint64(uint64 u)
{
  return current->Uint64(u);
}

bool AnyValueBuilder::Double(float64 d)
{
  return current->Double(d);
}

bool AnyValueBuilder::RawNumber(const char*, std::size_t, bool)
{
  throw ParseException("AnyValueBuilder::RawNumber not supported");
}

bool AnyValueBuilder::String(const char* str, std::size_t length, bool copy)
{
  std::string arg(str, length);
  return current->String(arg);
}

bool AnyValueBuilder::StartObject()
{
  current = current->GetStructureNode();
  return true;
}

bool AnyValueBuilder::Key(const char* str, std::size_t length, bool copy)
{
  std::string arg(str, length);
  return current->Member(arg);
}

bool AnyValueBuilder::EndObject(std::size_t)
{
  if (!current->Parent())
  {
    throw ParseException("AnyValueBuilder::EndObject current node is null");
  }
  current = current->Parent();
  current->PopStructureNode();
  return true;
}

bool AnyValueBuilder::StartArray()
{
  current = current->GetArrayNode();
  return true;
}

bool AnyValueBuilder::EndArray(std::size_t elementCount)
{
  if (!current->Parent())
  {
    throw ParseException("AnyValueBuilder::EndArray current node is null");
  }
  current = current->Parent();
  current->PopArrayNode();
  return true;
}

}  // namespace dto

}  // namespace sup
