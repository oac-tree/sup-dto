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
 * @file AnyTypeNode.h
 * @brief Header file for AnyType iterator node classes.
 * @date 15/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the AnyType iterator node classes.
 */

#ifndef _SUP_AnyTypeNode_h_
#define _SUP_AnyTypeNode_h_

#include "AnyType.h"

namespace sup
{
namespace dto
{
class IAnyTypeSerializer;

class AnyTypeDFSNode
{
public:
  AnyTypeDFSNode(const AnyType* anytype);
  virtual ~AnyTypeDFSNode();

  const AnyType* GetAnyType() const;

  virtual AnyTypeDFSNode* NextChild() = 0;

  virtual void AddProlog(IAnyTypeSerializer* serializer) = 0;
  virtual void AddSeparator(IAnyTypeSerializer* serializer) = 0;
  virtual void AddEpilog(IAnyTypeSerializer* serializer) = 0;

private:
  const AnyType* anytype;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyTypeNode_h_
