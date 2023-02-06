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

#include "function_protocol_extract.h"

#include <sup/dto/anytype_helper.h>
#include <sup/dto/anyvalue_helper.h>
#include <sup/dto/json_type_parser.h>

namespace sup
{
namespace rpc
{

bool FunctionProtocolExtract(std::string& str, const sup::dto::AnyValue& input,
                             const std::string& field_name)
{
  if (!input.HasField(field_name) || input[field_name].GetType() != sup::dto::StringType)
  {
    return false;
  }
  str = input[field_name].As<std::string>();
  return true;
}

bool FunctionProtocolExtract(sup::dto::AnyValue& anyvalue, const sup::dto::AnyValue& input,
                             const std::string& field_name)
{
  if (!input.HasField(field_name) || !sup::dto::TryConvert(anyvalue, input[field_name]))
  {
    return false;
  }
  return true;
}

bool FunctionProtocolExtract(sup::dto::AnyType& anytype, const sup::dto::AnyValue& input,
                             const std::string& field_name)
{
  if (!input.HasField(field_name) || input[field_name].GetType() != sup::dto::StringType)
  {
    return false;
  }
  auto json_type = input[field_name].As<std::string>();
  sup::dto::JSONAnyTypeParser parser{};
  if (!parser.ParseString(json_type))
  {
    return false;
  }
  anytype = parser.MoveAnyType();
  return true;
}

}  // namespace rpc

}  // namespace sup
