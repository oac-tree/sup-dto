/******************************************************************************
 * $HeadURL: $
 * $Id: $
 *
 * Project       : SUP - Sequencer
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
 * @file StructTypeData.h
 * @brief Header file for StructTypeData.
 * @date 04/01/2022
 * @author Walter Van Herck (IO)
 * @copyright 2010-2022 ITER Organization
 * @details This header file contains the definition of the StructTypeData interface.
 */

#ifndef _SUP_StructTypeData_h_
#define _SUP_StructTypeData_h_

#include "ITypeData.h"

#include <utility>
#include <vector>

namespace sup
{
namespace dto
{
class StructTypeData : public ITypeData
{
public:
  StructTypeData(std::string name);
  ~StructTypeData() override;

  void AddMember(std::string name, const AnyType& type);
  bool HasMember(const std::string& name) const;

  StructTypeData* Clone() const override;
  TypeCode GetTypeCode() const override;
  std::string GetTypeName() const override;

  std::vector<std::string> MemberNames() const;

  AnyType& operator[](std::string fieldname) override;
  const AnyType& operator[](std::string fieldname) const override;

private:
  std::string name;
  std::vector<std::pair<std::string, AnyType>> members;
  void VerifyMemberName(const std::string& name) const;
};

}  // namespace dto

}  // namespace sup

#endif  // _SUP_StructTypeData_h_
