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
 * Copyright (c) : 2010-2024 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "anyvalue_builder.h"

#include <sup/dto/parse/anyvalue_root_buildnode.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

AnyValueBuilder::AnyValueBuilder(const AnyTypeRegistry* anytype_registry)
  : m_root{new AnyValueRootBuildNode{anytype_registry}}
  , m_current{m_root.get()}
{}

AnyValueBuilder::~AnyValueBuilder() = default;

AnyValue AnyValueBuilder::MoveAnyValue()
{
  // Ensure all nodes were popped
  if (m_current != m_root.get())
  {
    throw ParseException("AnyValueBuilder::MoveAnyValue called before parsing was finished");
  }
  return m_root->MoveAnyValue();
}

bool AnyValueBuilder::Null()
{
  return m_current->Null();
}

bool AnyValueBuilder::Bool(boolean b)
{
  return m_current->Bool(b);
}

bool AnyValueBuilder::Int(int32 i)
{
  return m_current->Int32(i);
}

bool AnyValueBuilder::Uint(uint32 u)
{
  return m_current->Uint32(u);
}

bool AnyValueBuilder::Int64(int64 i)
{
  return m_current->Int64(i);
}

bool AnyValueBuilder::Uint64(uint64 u)
{
  return m_current->Uint64(u);
}

bool AnyValueBuilder::Double(float64 d)
{
  return m_current->Double(d);
}

bool AnyValueBuilder::RawNumber(const char*, std::size_t, bool)
{
  throw ParseException("AnyValueBuilder::RawNumber not supported");
}

bool AnyValueBuilder::String(const char* str, std::size_t length, bool)
{
  const std::string arg(str, length);
  return m_current->String(arg);
}

bool AnyValueBuilder::StartObject()
{
  m_current = m_current->GetStructureNode();
  return true;
}

bool AnyValueBuilder::Key(const char* str, std::size_t length, bool)
{
  const std::string arg(str, length);
  return m_current->Member(arg);
}

bool AnyValueBuilder::EndObject(std::size_t)
{
  if (!m_current->GetParent())
  {
    throw ParseException("AnyValueBuilder::EndObject current node is null");
  }
  m_current = m_current->GetParent();
  return m_current->PopStructureNode();
}

bool AnyValueBuilder::StartArray()
{
  m_current = m_current->GetArrayNode();
  return true;
}

bool AnyValueBuilder::EndArray(std::size_t)
{
  if (!m_current->GetParent())
  {
    throw ParseException("AnyValueBuilder::EndArray current node is null");
  }
  m_current = m_current->GetParent();
  return m_current->PopArrayNode();
}

}  // namespace dto

}  // namespace sup
