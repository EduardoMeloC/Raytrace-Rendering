#include "../include/Shape.h"

Shape::Shape(const Vector3& position, const Color& albedo, const Material& material) : Object(position), albedo(albedo), material(material) {}
Shape::Shape(const Vector3& position, const Color& albedo) : Shape(position, albedo, Material::diffuse) {}
Shape::Shape(const Vector3& position) : Shape(position, Color(255)) {}
Shape::~Shape() {}
