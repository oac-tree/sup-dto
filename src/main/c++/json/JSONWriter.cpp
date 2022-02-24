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

namespace sup
{
namespace dto
{

JSONStringWriter::JSONStringWriter(rapidjson::StringBuffer& buffer)
  : json_writer{buffer}
{}

JSONStringWriter::~JSONStringWriter() = default;

rapidjson::Writer<rapidjson::StringBuffer>& JSONStringWriter::Impl()
{
  return json_writer;
}

}  // namespace dto

}  // namespace sup
