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

#include <sup/rpc/rpc_exceptions.h>

#include <sup/dto/anytype_helper.h>
#include <sup/dto/anyvalue_helper.h>

namespace
{
const sup::dto::AnyType STRING_ARRAY_TYPE{0, sup::dto::StringType};
void FunctionProtocolPrepareOutput(sup::dto::AnyValue& output, const std::string& field_name);
}  // unnamed namespace

namespace sup
{
namespace rpc
{

template <typename T>
void FunctionProtocolPackT(sup::dto::AnyValue& output, const std::string& field_name, const T& val)
{
  FunctionProtocolPrepareOutput(output, field_name);
  output.AddMember(field_name, sup::dto::AnyValue(val));
}

void FunctionProtocolPack(sup::dto::AnyValue& output, const std::string& field_name, bool b)
{
  return FunctionProtocolPackT(output, field_name, b);
}

void FunctionProtocolPack(sup::dto::AnyValue& output, const std::string& field_name,
                          const std::string& str)
{
  return FunctionProtocolPackT(output, field_name, str);
}

void FunctionProtocolPack(sup::dto::AnyValue& output, const std::string& field_name,
                          const std::vector<std::string>& string_list)
{
  FunctionProtocolPrepareOutput(output, field_name);
  sup::dto::AnyValue any_list{STRING_ARRAY_TYPE};
  for (const auto& str : string_list)
  {
    any_list.AddElement(sup::dto::AnyValue(str));
  }
  output.AddMember(field_name, any_list);
}

void FunctionProtocolPack(sup::dto::AnyValue& output, const std::string& field_name,
                          const sup::dto::AnyValue& anyvalue)
{
  if (sup::dto::IsEmptyValue(anyvalue))
  {
    throw sup::rpc::InvalidOperationException("FunctionProtocolPack(): trying to pack an empty "
                                              "value in a structure");
  }
  FunctionProtocolPrepareOutput(output, field_name);
  output.AddMember(field_name, anyvalue);
}

void FunctionProtocolPack(sup::dto::AnyValue& output, const std::string& field_name,
                          const sup::dto::AnyType& anytype)
{
  FunctionProtocolPrepareOutput(output, field_name);
  auto json_type = sup::dto::AnyTypeToJSONString(anytype);
  output.AddMember(field_name, json_type);
}

}  // namespace rpc

}  // namespace sup

namespace
{
void FunctionProtocolPrepareOutput(sup::dto::AnyValue& output, const std::string& field_name)
{
  if (sup::dto::IsEmptyValue(output))
  {
    output = sup::dto::EmptyStruct();
    return;
  }
  if (!sup::dto::IsStructValue(output))
  {
    throw sup::rpc::InvalidOperationException("FunctionProtocolPrepareOutput(): output is not a "
                                              "structure");
  }
  if (output.HasField(field_name))
  {
    std::string error = "FunctionProtocolPrepareOutput(): output already contains a field with "
                        "name [" + field_name + "]";
    throw sup::rpc::InvalidOperationException(error);
  }
}
}  // unnamed namespace
