#include "bindings.h"

#pragma once

class BND_Geometry : public BND_Object
{
  std::shared_ptr<ON_Geometry> m_geometry;
protected:
  BND_Geometry();
  void SetSharedGeometryPointer(const std::shared_ptr<ON_Geometry>& sp);

public:
  BND_Geometry(ON_Geometry* geometry);
  int Dimension() const;
  BND_BoundingBox BoundingBox() const;
  bool Rotate(double rotation_angle, const ON_3dVector& rotation_axis, const ON_3dPoint& rotation_center);
};
