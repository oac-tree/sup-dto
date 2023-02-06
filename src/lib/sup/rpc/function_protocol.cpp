/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : Supervision and Automation - Configuration
 *
 * Description   : Configuration and CVVF libraries for the Supervision and Automation System.
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

#include "function_protocol.h"

#include <sup/dto/anytype_helper.h>
#include <sup/dto/anyvalue_helper.h>

namespace sup
{
namespace rpc
{

bool FunctionProtocolPack(sup::dto::AnyValue& output, const std::string& field_name,
                          const std::vector<std::string>& string_list)
{
  if (!sup::dto::IsStructValue(output) || output.HasField(field_name))
  {
    return false;
  }
  output.AddMember(field_name, sup::dto::AnyValue(0, sup::dto::StringType));
  for (const auto& str : string_list)
  {
    output[field_name].AddElement(str);
  }
  return true;
}

bool FunctionProtocolPack(sup::dto::AnyValue& output, const std::string& field_name,
                          const sup::dto::AnyType& anytype)
{
  if (!sup::dto::IsStructValue(output) || output.HasField(field_name))
  {
    return false;
  }
  auto json_type = sup::dto::AnyTypeToJSONString(anytype);
  output.AddMember(field_name, sup::dto::AnyValue(json_type));
  return true;
}

bool FunctionProtocolPack(sup::dto::AnyValue& output, const std::string& field_name,
                          const sup::dto::AnyValue& anyvalue)
{
  if (!sup::dto::IsStructValue(output) || output.HasField(field_name) ||
      sup::dto::IsEmptyValue(anyvalue))
  {
    return false;
  }
  output.AddMember(field_name, anyvalue);
  return true;
}

}  // namespace rpc

}  // namespace sup
