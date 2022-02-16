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
 * @file AnyTypeSerializeNode.h
 * @brief Header file for AnyType serialization node classes.
 * @date 15/02/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the AnyType serialization node classes.
 */

#ifndef _SUP_AnyTypeSerializeNode_h_
#define _SUP_AnyTypeSerializeNode_h_

#include "AnyType.h"

#include <memory>

namespace sup
{
namespace dto
{
class IAnyTypeSerializer;

/**
 * @brief Interface for thin nodes that iterate over an AnyType in Depth First Search.
 *
 * @details This class hierarchy is used for the serialization of AnyType without recursion.
 */
class IAnyTypeSerializeNode
{
public:
  IAnyTypeSerializeNode(const AnyType* anytype);
  virtual ~IAnyTypeSerializeNode();

  const AnyType* GetAnyType() const;

  virtual std::unique_ptr<IAnyTypeSerializeNode> NextChild() = 0;

  virtual void AddProlog(IAnyTypeSerializer& serializer) const = 0;
  virtual void AddSeparator(IAnyTypeSerializer& serializer) const = 0;
  virtual void AddEpilog(IAnyTypeSerializer& serializer) const = 0;

private:
  const AnyType* anytype;
};

/**
 * @brief RAII class for IAnyTypeSerializeNode classes.
 */
class AnyTypeSerializeNode
{
public:
  AnyTypeSerializeNode(std::unique_ptr<IAnyTypeSerializeNode> node);
  ~AnyTypeSerializeNode();

  AnyTypeSerializeNode(AnyTypeSerializeNode&& other);
  AnyTypeSerializeNode& operator=(AnyTypeSerializeNode&& other);

  AnyTypeSerializeNode(const AnyTypeSerializeNode&) = delete;
  AnyTypeSerializeNode& operator=(const AnyTypeSerializeNode& other) = delete;

  AnyTypeSerializeNode NextChild();
  bool IsValid() const;

  void AddProlog(IAnyTypeSerializer& serializer) const;
  void AddSeparator(IAnyTypeSerializer& serializer) const;
  void AddEpilog(IAnyTypeSerializer& serializer) const;

private:
  std::unique_ptr<IAnyTypeSerializeNode> node;
};

std::unique_ptr<IAnyTypeSerializeNode> CreateSerializeNode(const AnyType* anytype);

AnyTypeSerializeNode CreateRootNode(const AnyType* anytype);

}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyTypeSerializeNode_h_
