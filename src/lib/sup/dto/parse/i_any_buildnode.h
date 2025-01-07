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

#ifndef SUP_DTO_I_ANY_BUILDNODE_H_
#define SUP_DTO_I_ANY_BUILDNODE_H_

#include <sup/dto/basic_scalar_types.h>

#include <string>

namespace sup
{
namespace dto
{
class AnyTypeRegistry;

class IAnyBuildNode
{
public:
  IAnyBuildNode(const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent);
  virtual ~IAnyBuildNode();

  IAnyBuildNode(const IAnyBuildNode& other) = delete;
  IAnyBuildNode(IAnyBuildNode&& other) = delete;
  IAnyBuildNode& operator=(const IAnyBuildNode& other) = delete;
  IAnyBuildNode& operator=(IAnyBuildNode&& other) = delete;

  const AnyTypeRegistry* GetTypeRegistry() const &;
  IAnyBuildNode* GetParent() const &;

  virtual bool Null();
  virtual bool Bool(boolean b);
  virtual bool Int32(int32 i);
  virtual bool Uint32(uint32 u);
  virtual bool Int64(int64 i);
  virtual bool Uint64(uint64 u);
  virtual bool Double(float64 d);
  virtual bool String(const std::string& str);
  virtual bool Member(const std::string& str);

  virtual IAnyBuildNode* GetStructureNode();
  virtual IAnyBuildNode* GetArrayNode();
  virtual bool PopStructureNode();
  virtual bool PopArrayNode();

private:
  const AnyTypeRegistry* m_anytype_registry;
  IAnyBuildNode* m_parent;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_I_ANY_BUILDNODE_H_
