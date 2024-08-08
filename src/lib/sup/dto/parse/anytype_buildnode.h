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

#ifndef SUP_DTO_ANYTYPE_BUILDNODE_H_
#define SUP_DTO_ANYTYPE_BUILDNODE_H_

#include <sup/dto/parse/i_any_buildnode.h>

#include <sup/dto/anytype.h>

#include <memory>
#include <utility>
#include <vector>

namespace sup
{
namespace dto
{
class MemberTypeArrayBuildNode;

class AnyTypeBuildNode : public IAnyBuildNode
{
public:
  AnyTypeBuildNode(const AnyTypeRegistry* anytype_registry, IAnyBuildNode* parent);
  ~AnyTypeBuildNode() override;

  AnyTypeBuildNode(const AnyTypeBuildNode& other) = delete;
  AnyTypeBuildNode(AnyTypeBuildNode&& other) = delete;
  AnyTypeBuildNode& operator=(const AnyTypeBuildNode& other) = delete;
  AnyTypeBuildNode& operator=(AnyTypeBuildNode&& other) = delete;


  bool Int32(int32 i) override;
  bool Uint32(uint32 u) override;
  bool Int64(int64 i) override;
  bool Uint64(uint64 u) override;
  bool String(const std::string& str) override;
  bool Member(const std::string& str) override;

  IAnyBuildNode* GetStructureNode() override;
  IAnyBuildNode* GetArrayNode() override;
  bool PopStructureNode() override;
  bool PopArrayNode() override;

  AnyType GetAnyType() const;

private:
  bool IsComplexType() const;
  AnyType GetStructuredType() const;
  AnyType GetArrayType() const;
  AnyType GetTypeFromRegistry() const;
  std::unique_ptr<AnyTypeBuildNode> m_element_node;
  std::unique_ptr<MemberTypeArrayBuildNode> m_member_array_node;
  std::string m_current_member_name;
  bool m_struct_type;  // true if structure
  bool m_array_type;  // true if array
  std::string m_type_name;
  std::size_t m_number_elements;
  bool m_array_bound_specified;
  std::vector<std::pair<std::string, AnyType>> m_member_types;
  AnyType m_element_type;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYTYPE_BUILDNODE_H_
