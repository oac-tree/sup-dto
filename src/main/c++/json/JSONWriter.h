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

/**
 * @file JSONWriter.h
 * @brief Header file for the JSONWriter classes.
 * @date 28/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the JSONWriter classes.
 */

#ifndef _SUP_JSONWriter_h_
#define _SUP_JSONWriter_h_

#include <ostream>

namespace sup
{
namespace dto
{
class AnyType;
class AnyValue;

void JSONSerializeAnyType(std::ostream& json_stream, const AnyType& anytype, bool pretty = false);

void JSONSerializeAnyValue(std::ostream& json_stream, const AnyValue& anyvalue,
                           bool pretty = false);

void JSONSerializeAnyValueValues(std::ostream& json_stream, const AnyValue& anyvalue,
                                 bool pretty = false);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_JSONWriter_h_
