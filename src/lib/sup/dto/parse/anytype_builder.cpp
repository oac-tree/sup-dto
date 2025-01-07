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
 * Copyright (c) : 2010-2025 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#include "anytype_builder.h"

#include <sup/dto/parse/anytype_root_buildnode.h>

#include <sup/dto/anyvalue_exceptions.h>

namespace sup
{
namespace dto
{

AnyTypeBuilder::AnyTypeBuilder(const AnyTypeRegistry* anytype_registry)
  : m_root{std::make_unique<AnyTypeRootBuildNode>(anytype_registry)}
  , m_current{m_root.get()}
{}

AnyTypeBuilder::~AnyTypeBuilder() = default;

AnyType AnyTypeBuilder::MoveAnyType()
{
  // Ensure all nodes were popped
  if (m_current != m_root.get())
  {
    throw ParseException("AnyTypeBuilder::MoveAnyType called before parsing was finished");
  }
  return m_root->MoveAnyType();
}

bool AnyTypeBuilder::Null()
{
  return m_current->Null();
}

bool AnyTypeBuilder::Bool(boolean b)
{
  return m_current->Bool(b);
}

bool AnyTypeBuilder::Int(int32 i)
{
  return m_current->Int32(i);
}

bool AnyTypeBuilder::Uint(uint32 u)
{
  return m_current->Uint32(u);
}

bool AnyTypeBuilder::Int64(int64 i)
{
  return m_current->Int64(i);
}

bool AnyTypeBuilder::Uint64(uint64 u)
{
  return m_current->Uint64(u);
}

bool AnyTypeBuilder::Double(float64 d)
{
  return m_current->Double(d);
}

bool AnyTypeBuilder::RawNumber(const char*, std::size_t, bool)
{
  throw ParseException("AnyTypeBuilder::RawNumber not supported");
}

bool AnyTypeBuilder::String(const char* str, std::size_t length, bool)
{
  const std::string arg(str, length);
  return m_current->String(arg);
}

bool AnyTypeBuilder::StartObject()
{
  m_current = m_current->GetStructureNode();
  return true;
}

bool AnyTypeBuilder::Key(const char* str, std::size_t length, bool)
{
  const std::string arg(str, length);
  return m_current->Member(arg);
}

bool AnyTypeBuilder::EndObject(std::size_t)
{
  if (!m_current->GetParent())
  {
    throw ParseException("AnyTypeBuilder::EndObject current parent node is null");
  }
  m_current = m_current->GetParent();
  return m_current->PopStructureNode();
}

bool AnyTypeBuilder::StartArray()
{
  m_current = m_current->GetArrayNode();
  return true;
}

bool AnyTypeBuilder::EndArray(std::size_t)
{
  if (!m_current->GetParent())
  {
    throw ParseException("AnyTypeBuilder::EndArray current parent node is null");
  }
  m_current = m_current->GetParent();
  return m_current->PopArrayNode();
}

}  // namespace dto

}  // namespace sup
