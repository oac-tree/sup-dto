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

#include "function_protocol_pack.h"

#include <sup/dto/anyvalue_helper.h>

namespace
{
const sup::dto::AnyType STRING_ARRAY_TYPE{0, sup::dto::StringType};
bool FunctionProtocolPrepareOutput(sup::dto::AnyValue& output, const std::string& field_name);
}  // unnamed namespace

namespace sup
{
namespace rpc
{

template <typename T>
bool FunctionProtocolPackT(sup::dto::AnyValue& output, const std::string& field_name, const T& val)
{
  if (!FunctionProtocolPrepareOutput(output, field_name))
  {
    return false;
  }
  output.AddMember(field_name, sup::dto::AnyValue(val));
  return true;
}

bool FunctionProtocolPack(sup::dto::AnyValue& output, const std::string& field_name, bool b)
{
  return FunctionProtocolPackT(output, field_name, b);
}

bool FunctionProtocolPack(sup::dto::AnyValue& output, const std::string& field_name,
                          const std::string& str)
{
  return FunctionProtocolPackT(output, field_name, str);
}

bool FunctionProtocolPack(sup::dto::AnyValue& output, const std::string& field_name,
                          const std::vector<std::string>& string_list)
{
  if (!FunctionProtocolPrepareOutput(output, field_name))
  {
    return false;
  }
  sup::dto::AnyValue any_list{STRING_ARRAY_TYPE};
  for (const auto& str : string_list)
  {
    any_list.AddElement(sup::dto::AnyValue(str));
  }
  output.AddMember(field_name, any_list);
  return true;
}

bool FunctionProtocolPack(sup::dto::AnyValue& output, const std::string& field_name,
                          const sup::dto::AnyValue& anyvalue)
{
  if (sup::dto::IsEmptyValue(anyvalue) || !FunctionProtocolPrepareOutput(output, field_name))
  {
    return false;
  }
  output.AddMember(field_name, anyvalue);
  return true;
}

}  // namespace rpc

}  // namespace sup

namespace
{
bool FunctionProtocolPrepareOutput(sup::dto::AnyValue& output, const std::string& field_name)
{
  if (sup::dto::IsEmptyValue(output))
  {
    output = sup::dto::EmptyStruct();
  }
  if (!sup::dto::IsStructValue(output))
  {
    return false;
  }
  if (output.HasField(field_name))
  {
    return false;
  }
  return true;
}
}  // unnamed namespace
