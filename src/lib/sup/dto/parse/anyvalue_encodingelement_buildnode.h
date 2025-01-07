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

#ifndef SUP_DTO_ANYVALUE_ENCODINGELEMENT_BUILDNODE_H_
#define SUP_DTO_ANYVALUE_ENCODINGELEMENT_BUILDNODE_H_

#include <sup/dto/parse/i_any_buildnode.h>

#include <sup/dto/anyvalue.h>

#include <memory>

namespace sup
{
namespace dto
{
class AnyTypeBuildNode;
class AnyValueBuildNode;

class AnyValueEncodingElementBuildNode : public IAnyBuildNode
{
public:
  AnyValueEncodingElementBuildNode(const AnyTypeRegistry* anytype_registry,
                                   IAnyBuildNode* parent);
  ~AnyValueEncodingElementBuildNode() override;

  AnyValueEncodingElementBuildNode(const AnyValueEncodingElementBuildNode& other) = delete;
  AnyValueEncodingElementBuildNode(AnyValueEncodingElementBuildNode&& other) = delete;
  AnyValueEncodingElementBuildNode& operator=(const AnyValueEncodingElementBuildNode& other) = delete;
  AnyValueEncodingElementBuildNode& operator=(AnyValueEncodingElementBuildNode&& other) = delete;


  bool String(const std::string& str) override;
  bool Member(const std::string& str) override;

  bool EncodingOK() const;

private:
  std::string m_member_name;
  bool m_encoding_ok;
};

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_ANYVALUE_ENCODINGELEMENT_BUILDNODE_H_
