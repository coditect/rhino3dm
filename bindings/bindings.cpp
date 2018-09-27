#include "bindings.h"


using namespace boost::python;

BOOST_PYTHON_MODULE(rhino_geometry) {

    class_<ON_2dPoint>("Point2d")
        .def(init<double, double>())
        .def_readwrite("X", &ON_2dPoint::x)
        .def_readwrite("Y", &ON_2dPoint::y);

    class_<ON_3dPoint>("Point3d")
        .def(init<double, double, double>())
        .def_readwrite("X", &ON_3dPoint::x)
        .def_readwrite("Y", &ON_3dPoint::y)
        .def_readwrite("Z", &ON_3dPoint::z);

    class_<ON_4dPoint>("Point4d")
        .def(init<double, double, double, double>())
        .def_readwrite("X", &ON_4dPoint::x)
        .def_readwrite("Y", &ON_4dPoint::y)
        .def_readwrite("Z", &ON_4dPoint::z)
        .def_readwrite("W", &ON_4dPoint::w);

    class_<ON_3dVector>("Vector3d")
        .def(init<double, double, double>())
        .def_readwrite("X", &ON_3dVector::x)
        .def_readwrite("Y", &ON_3dVector::y)
        .def_readwrite("Z", &ON_3dVector::z);

    class_<ON_3fPoint>("Point3f")
        .def(init<float, float, float>())
        .def_readwrite("X", &ON_3fPoint::x)
        .def_readwrite("Y", &ON_3fPoint::y)
        .def_readwrite("Z", &ON_3fPoint::z);

    class_<BND_Interval>("Interval")
        .def_readwrite("T0", &BND_Interval::m_t0)
        .def_readwrite("T1", &BND_Interval::m_t1);

    class_<BND_BoundingBox>("BoundingBox", init<ON_3dPoint, ON_3dPoint>())
        .def(init<double, double, double, double, double, double>())
        .add_property("Min", &BND_BoundingBox::Min)
        .add_property("Max", &BND_BoundingBox::Max)
        .def("Transform", &BND_BoundingBox::Transform);

    class_<BND_Arc>("Arc", init<ON_3dPoint, double, double>())
        .def("ToNurbsCurve", &BND_Arc::ToNurbsCurve, return_value_policy<manage_new_object>());


    class_<BND_Object>("CommonObject", no_init)
        .def("Encode", &BND_Object::Encode)
        .def("Decode", &BND_Object::Decode, return_value_policy<manage_new_object>())
        .staticmethod("Decode");


    class_<BND_Geometry, bases<BND_Object>>("GeometryBase", no_init)
        .def("GetBoundingBox", &BND_Geometry::BoundingBox)
        .def("Rotate", &BND_Geometry::Rotate);

    class_<BND_Brep, bases<BND_Geometry>>("Brep", init<>());

    class_<BND_Curve, bases<BND_Geometry>>("Curve", no_init)
        .add_property("Domain", &BND_Curve::GetDomain, &BND_Curve::SetDomain)
        .add_property("Dimension", &BND_Geometry::Dimension)
        .add_property("ChangeDimension", &BND_Curve::ChangeDimension)
        .add_property("SpanCount", &BND_Curve::SpanCount)
        .add_property("Degree", &BND_Curve::Degree)
        .add_property("PointAtStart", &BND_Curve::PointAtStart)
        .add_property("PointAtEnd", &BND_Curve::PointAtEnd)
        .add_property("IsLinear", &BND_Curve::IsLinear)
        .add_property("IsPolyline", &BND_Curve::IsPolyline);

    class_<BND_NurbsCurve, bases<BND_Curve>>("NurbsCurve", init<int,int>())
        .def(init<int, bool, int, int>());

    class_<BND_Mesh, bases<BND_Geometry>>("Mesh", init<>())
        .add_property("Vertices", &BND_Mesh::GetVertices)
        .add_property("Faces", &BND_Mesh::GetFaces);

    class_<BND_MeshVertexList>("MeshVertexList", no_init)
        .add_property("Count", &BND_MeshVertexList::Count)
        .def("SetCount", &BND_MeshVertexList::SetCount)
        .def("Get", &BND_MeshVertexList::GetVertex)
        .def("Set", &BND_MeshVertexList::SetVertex);

    class_<BND_MeshFaceList>("MeshFaceList", no_init)
        .add_property("Count", &BND_MeshFaceList::Count)
        .def("Get", &BND_MeshFaceList::GetFace);


    class_<ON_Line>("Line")
        .def(init<ON_3dPoint,ON_3dPoint>())
        .add_property("Length", &ON_Line::Length);

    class_<BND_Circle>("Circle", init<double>())
        .def(init<ON_3dPoint, double>())
        .def_readwrite("Plane", &BND_Circle::m_plane)
        .def_readwrite("Radius", &BND_Circle::m_radius)
        .def("PointAt", &BND_Circle::PointAt)
        .def("ToNurbsCurve", &BND_Circle::ToNurbsCurve, return_value_policy<manage_new_object>());

    class_<BND_PolyCurve, bases<BND_Curve>>("Polycurve");

    class_<BND_PolylineCurve, bases<BND_Curve>>("Polylinecurve", init<>())
        .add_property("PointCount", &BND_PolylineCurve::PointCount)
        .def("Point", &BND_PolylineCurve::Point);

    class_<BND_Sphere>("Sphere", init<ON_3dPoint, double>())
        .add_property("Center", &BND_Sphere::Center)
        .add_property("Radius", &BND_Sphere::Radius)
        .def("ToBrep", &BND_Sphere::ToBrep, return_value_policy<manage_new_object>());

}
