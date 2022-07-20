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

#ifndef _SUP_AnyValueEncodingElementBuildNode_h_
#define _SUP_AnyValueEncodingElementBuildNode_h_

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
  ~AnyValueEncodingElementBuildNode();

  bool String(const std::string& str) override;
  bool Member(const std::string& str) override;

  bool EncodingOK() const;

private:
  std::string member_name;
  bool encoding_ok;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyValueEncodingElementBuildNode_h_
