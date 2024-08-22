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
 * Copyright (c) : 2010-2024 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_SERIALIZATION_CONSTANTS_H_
#define SUP_DTO_SERIALIZATION_CONSTANTS_H_

#include <string>

namespace sup
{
namespace dto
{
namespace serialization
{

const std::string ENCODING_KEY = "encoding";
const std::string JSON_ENCODING_1_0 = "sup-dto/v1.0/JSON";
const std::string DATATYPE_KEY = "datatype";
const std::string INSTANCE_KEY = "instance";

const std::string TYPE_KEY = "type";
const std::string MULTIPLICITY_KEY = "multiplicity";
const std::string ELEMENT_KEY = "element";
const std::string ATTRIBUTES_KEY = "attributes";

}  // namespace serialization

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_SERIALIZATION_CONSTANTS_H_
