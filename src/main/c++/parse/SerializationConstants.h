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

#ifndef _SUP_SerializationConstants_h_
#define _SUP_SerializationConstants_h_

#include <string>

namespace sup
{
namespace dto
{
namespace serialization
{

static const std::string ENCODING_KEY = "encoding";
static const std::string JSON_ENCODING_1_0 = "sup-dto/v1.0/JSON";
static const std::string DATATYPE_KEY = "datatype";
static const std::string INSTANCE_KEY = "instance";

static const std::string TYPE_KEY = "type";
static const std::string MULTIPLICITY_KEY = "multiplicity";
static const std::string ELEMENT_KEY = "element";
static const std::string ATTRIBUTES_KEY = "attributes";

}  // namespace serialization

}  // namespace dto

}  // namespace sup

#endif  // _SUP_SerializationConstants_h_
