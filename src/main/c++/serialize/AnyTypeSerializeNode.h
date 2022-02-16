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
#include "IAnySerializer.h"

#include <memory>

namespace sup
{
namespace dto
{
class IAnyTypeSerializer;

/**
 * @brief Templated interface for thin nodes that iterate over an AnyType/AnyValue tree in
 * Depth First Search.
 *
 * @details This class hierarchy is used for the serialization of AnyType without recursion.
 */
template <typename T>
class IAnySerializeNode
{
public:
  IAnySerializeNode(const T* val);
  virtual ~IAnySerializeNode() = default;

  const T* GetValue() const;

  virtual std::unique_ptr<IAnySerializeNode> NextChild() = 0;

  virtual void AddProlog(IAnySerializer<T>& serializer) const = 0;
  virtual void AddSeparator(IAnySerializer<T>& serializer) const = 0;
  virtual void AddEpilog(IAnySerializer<T>& serializer) const = 0;

private:
  const T* val;
};

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

  const AnyType* GetValue() const;

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

template <typename T>
IAnySerializeNode<T>::IAnySerializeNode(const T* val_)
  : val{val_}
{}

template <typename T>
const T* IAnySerializeNode<T>::GetValue() const
{
  return val;
}


}  // namespace dto

}  // namespace sup

#endif  // _SUP_AnyTypeSerializeNode_h_
