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
 * Copyright (c) : 2010-2025 ITER Organization,
 *                 CS 90 046
 *                 13067 St. Paul-lez-Durance Cedex
 *                 France
 *
 * This file is part of ITER CODAC software.
 * For the terms and conditions of redistribution or use of this software
 * refer to the file ITER-LICENSE.TXT located in the top level directory
 * of the distribution package.
 ******************************************************************************/

#ifndef SUP_DTO_COMPOSER_ANYTYPE_COMPOSER_HELPER_H_
#define SUP_DTO_COMPOSER_ANYTYPE_COMPOSER_HELPER_H_

//! @file anytype_composer_helper.h
//! Collection of utility functions to support AbstractTypeComposerComponent and derived classes.

#include <sup/dto/composer/abstract_type_composer_component.h>

namespace sup
{
namespace dto
{

//! Returns true if it is possible to add a type component. This will be the case in one of three
//! cases: 1) the stack is empty 2) last component denotes the start of a structure field 3)
//! last component denotes denotes the start of an array element.
bool CanAddTypeComponent(const std::stack<AbstractTypeComposerComponent::component_t>& stack);

//! Validates if adding of a type component is possible for this stack configuration, and throws if
//! it is not.
void ValidateAddTypeComponent(const std::stack<AbstractTypeComposerComponent::component_t>& stack);

//! Validate if the last component in the stack has a given type and throw otherwise.
void ValidateLastTypeComponent(const std::stack<AbstractTypeComposerComponent::component_t>& stack,
                               AbstractTypeComposerComponent::Type component_type);

//! Validate if the last component corresponds to a completed type component.
void ValidateIfTypeComponentIsComplete(
    const std::stack<AbstractTypeComposerComponent::component_t>& stack);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_COMPOSER_ANYTYPE_COMPOSER_HELPER_H_
