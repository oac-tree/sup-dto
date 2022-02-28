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

#include "JSONWriter.h"
#include "JSONWriterT.h"

#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace sup
{
namespace dto
{

template <typename Buffer>
using RapidJSONWriter = rapidjson::Writer<Buffer>;
template <typename Buffer>
using RapidJSONPrettyWriter = rapidjson::PrettyWriter<Buffer>;

using JSONStringWriter = JSONStringWriterT<rapidjson::StringBuffer, RapidJSONWriter>;
using PrettyJSONStringWriter = JSONStringWriterT<rapidjson::StringBuffer, RapidJSONPrettyWriter>;

std::unique_ptr<IWriter> CreateJSONStringWriter()
{
  return std::unique_ptr<IWriter>(new JSONStringWriter());
}

std::unique_ptr<IWriter> CreatePrettyJSONStringWriter()
{
  return std::unique_ptr<IWriter>(new PrettyJSONStringWriter());
}

}  // namespace dto

}  // namespace sup
