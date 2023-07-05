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

#ifndef SUP_DTO_I_VALUE_DATA_H_
#define SUP_DTO_I_VALUE_DATA_H_

#include <sup/dto/anyvalue.h>

namespace sup
{
namespace dto
{
namespace value_flags
{
enum Constraints
{
  kNone       = 0x00,
  kLockedType = 0x01
};
}
class IValueData
{
public:
  virtual ~IValueData();

  virtual IValueData* Clone() const = 0;
  virtual TypeCode GetTypeCode() const = 0;
  virtual std::string GetTypeName() const;
  virtual AnyType GetType() const = 0;

  // Only used to provide a fast private way for AnyValue to assess if it's scalar
  virtual bool IsScalar() const;

  // All descendants of array values have a locked type to prevent
  // corruption of the value, i.e. elements of the same array with differing type.
  virtual bool HasLockedType() const;

  virtual void AddMember(const std::string& name, const AnyValue& type);
  virtual std::vector<std::string> MemberNames() const;
  virtual std::size_t NumberOfMembers() const;
  virtual void AddElement(const AnyValue& value);
  virtual std::size_t NumberOfElements() const;

  virtual void Assign(const AnyValue& value);

  virtual boolean AsBoolean() const;
  virtual char8 AsCharacter8() const;
  virtual int8 AsSignedInteger8() const;
  virtual uint8 AsUnsignedInteger8() const;
  virtual int16 AsSignedInteger16() const;
  virtual uint16 AsUnsignedInteger16() const;
  virtual int32 AsSignedInteger32() const;
  virtual uint32 AsUnsignedInteger32() const;
  virtual int64 AsSignedInteger64() const;
  virtual uint64 AsUnsignedInteger64() const;
  virtual float32 AsFloat32() const;
  virtual float64 AsFloat64() const;
  virtual std::string AsString() const;

  virtual bool HasField(const std::string& fieldname) const;
  virtual AnyValue& operator[](const std::string& fieldname);
  virtual AnyValue& operator[](std::size_t idx);

  virtual bool Equals(const AnyValue& other) const = 0;
};

IValueData* CreateValueData(const AnyType& anytype);

}  // namespace dto

}  // namespace sup

#endif  // SUP_DTO_I_VALUE_DATA_H_
