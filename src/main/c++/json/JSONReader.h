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
 * @file JSONReader.h
 * @brief Header file for the JSONReader classes.
 * @date 01/03/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the JSONReader classes.
 */

#ifndef _SUP_JSONReader_h_
#define _SUP_JSONReader_h_

#include <istream>

namespace sup
{
namespace dto
{
class AnyType;
class AnyValue;

AnyType JSONParseAnyType(std::istream& json_stream);

AnyValue JSONParseAnyValue(std::istream& json_stream);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_JSONReader_h_
