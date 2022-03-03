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
 * @file JSONPerformance.h
 * @brief Header file for the JSON serialize/parse performance tests.
 * @date 03/03/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition for the JSON serialize/parse performance tests.
 */

#ifndef _SUP_JSONPerformance_h_
#define _SUP_JSONPerformance_h_

namespace sup
{
namespace dto
{
class AnyType;

namespace performance
{

AnyType CreateScalarMix_Type();
AnyType CreateScalarMixArray_Type();
AnyType CreateSystemConfigs_Type();
AnyType CreateFullConfig_Type();

void MeasureSerializeParse(const AnyType& anytype);

}  // namespace performance

}  // namespace dto

}  // namespace sup

#endif  // _SUP_JSONPerformance_h_
