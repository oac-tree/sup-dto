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

#include "anyvalue_value_builder.h"

#include <sup/dto/parse/anyvalue_valueelement_buildnode.h>
#include <sup/dto/parse/serialization_constants.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

AnyValueValueBuilder::AnyValueValueBuilder(const AnyType& anytype)
  : m_value{anytype}
  , m_registry{}
  , root{new AnyValueValueElementBuildNode{&m_registry, nullptr, m_value}}
  , current{root.get()}
{
  current->Member(serialization::INSTANCE_KEY);
}

AnyValueValueBuilder::~AnyValueValueBuilder() = default;

AnyValue AnyValueValueBuilder::MoveAnyValue()
{
  // Ensure all nodes were popped
  if (current != root.get())
  {
    throw ParseException("AnyValueValueBuilder::MoveAnyValue called before parsing was finished");
  }
  return std::move(m_value);
}

bool AnyValueValueBuilder::Null()
{
  return current->Null();
}

bool AnyValueValueBuilder::Bool(boolean b)
{
  return current->Bool(b);
}

bool AnyValueValueBuilder::Int(int32 i)
{
  return current->Int32(i);
}

bool AnyValueValueBuilder::Uint(uint32 u)
{
  return current->Uint32(u);
}

bool AnyValueValueBuilder::Int64(int64 i)
{
  return current->Int64(i);
}

bool AnyValueValueBuilder::Uint64(uint64 u)
{
  return current->Uint64(u);
}

bool AnyValueValueBuilder::Double(float64 d)
{
  return current->Double(d);
}

bool AnyValueValueBuilder::RawNumber(const char*, std::size_t, bool)
{
  throw ParseException("AnyValueValueBuilder::RawNumber not supported");
}

bool AnyValueValueBuilder::String(const char* str, std::size_t length, bool copy)
{
  (void)copy;
  const std::string arg(str, length);
  return current->String(arg);
}

bool AnyValueValueBuilder::StartObject()
{
  current = current->GetStructureNode();
  return true;
}

bool AnyValueValueBuilder::Key(const char* str, std::size_t length, bool copy)
{
  (void)copy;
  const std::string arg(str, length);
  return current->Member(arg);
}

bool AnyValueValueBuilder::EndObject(std::size_t)
{
  if (!current->Parent())
  {
    throw ParseException("AnyValueValueBuilder::EndObject current node is null");
  }
  current = current->Parent();
  current->PopStructureNode();
  return true;
}

bool AnyValueValueBuilder::StartArray()
{
  current = current->GetArrayNode();
  return true;
}

bool AnyValueValueBuilder::EndArray(std::size_t elementCount)
{
  (void)elementCount;
  if (!current->Parent())
  {
    throw ParseException("AnyValueValueBuilder::EndArray current node is null");
  }
  current = current->Parent();
  current->PopArrayNode();
  return true;
}

}  // namespace dto

}  // namespace sup
