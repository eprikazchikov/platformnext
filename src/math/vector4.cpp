#include "math/math.h"

/*!
    \class Vector4
    \brief The Vector4 class represents a vector or vertex in 4D space.
    \since Next 1.0
    \inmodule Math

    Vectors are one of the main building blocks of 4D representation and
    drawing. They consist of three coordinates, traditionally called
    x, y, z and w.

    The Vector4 class can also be used to represent vertices in 4D space.
    We therefore do not need to provide a separate vertex class.

    \note By design values in the Vector4 instance are stored as \c float.
    This means that on platforms where the \c areal arguments to Vector4
    functions are represented by \c double values, it is possible to
    lose precision.

    \sa Vector2, Vector3, Quaternion
*/

/*!
    Constructs a null vector, i.e. with coordinates (0, 0, 0, 1).
*/
Vector4::Vector4() :
    x(0),
    y(0),
    z(0),
    w(1) {
}
/*!
    Constructs a vector with coordinates (\a v).
*/
Vector4::Vector4(areal v) :
    x(v),
    y(v),
    z(v),
    w(v) {
}
/*!
    Constructs a vector with coordinates (\a x, \a y, \a z, \a w).
*/
Vector4::Vector4(areal x, areal y, areal z, areal w) :
    x(x),
    y(y),
    z(z),
    w(w) {
}
/*!
    Constructs a 4D vector from the specified 2D \a v. The z and w
    coordinates is set to \a z and \a w.

    \sa Vector2::Vector2()
*/
Vector4::Vector4(const Vector2 &v, areal z, areal w) :
    x(v.x),
    y(v.y),
    z(z),
    w(w) {
}
/*!
    Constructs a 4D vector from the specified 3D \a v. The w
    coordinate is set to \a w.

    \sa Vector3::Vector3()
*/
Vector4::Vector4(const Vector3 &v, areal w) :
    x(v.x),
    y(v.y),
    z(v.z),
    w(w) {
}
/*!
    Returns true if this vector is equal to given \a vector; otherwise returns false.
    This operator uses an exact floating-point comparison.
*/
bool Vector4::operator==(const Vector4 &vector) const {
    return (x == vector.x) && (y == vector.y) && (z == vector.z) && (w == vector.w);
}
/*!
    Returns true if this vector is NOT equal to given \a vector; otherwise returns false.
    This operator uses an exact floating-point comparison.
*/
bool Vector4::operator!=(const Vector4 &vector) const {
    return !(*this == vector);
}
/*!
    Returns true if this vector is bigger than given \a vector; otherwise returns false.
    This operator uses an exact floating-point comparison.
*/
bool Vector4::operator>(const Vector4 &vector) const {
    return (x > vector.x) && (y > vector.y) && (z > vector.z) && (w > vector.w);
}
/*!
    Returns true if this vector is less than \a vector; otherwise returns false.
    This operator uses an exact floating-point comparison.
*/
bool Vector4::operator<(const Vector4 &vector) const {
    return (x < vector.x) && (y < vector.y) && (z < vector.z) && (w < vector.w);
}
/*!
    Returns a copy of this vector, multiplied by the given \a factor.

    \sa operator*=()
*/
const Vector4 Vector4::operator*(areal factor) const {
    return Vector4(x * factor, y * factor, z * factor, w * factor);
}
/*!
    Returns a copy of this vector, multiplied by the given \a vector.

    \sa operator*=()
*/
const Vector4 Vector4::operator*(const Vector4 &vector) const {
    return Vector4(x * vector.x, y * vector.y, z * vector.z, w * vector.w);
}
/*!
    Returns a copy of this vector, divided by the given \a divisor.

    \sa operator/=()
*/
const Vector4 Vector4::operator/(areal divisor) const {
    return Vector4(x / divisor, y / divisor, z / divisor, w / divisor);
}
/*!
    Returns a Vector4 object that is the sum of the this vector and \a vector; each component is added separately.

    \sa operator+=()
*/
const Vector4 Vector4::operator+(const Vector4 &vector) const {
    return Vector4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
}
/*!
    Returns a Vector4 object that is formed by changing the sign of
    all three components of the this vector.

    Equivalent to \c {Vector4(0,0,0,1) - vector}.
*/
const Vector4 Vector4::operator-() const {
    return Vector4(-x, -y, -z, -w);
}
/*!
    Returns a Vector4 object that is formed by subtracting \a vector from this vector;
    each component is subtracted separately.

    \sa operator-=()
*/
const Vector4 Vector4::operator-(const Vector4 &vector) const {
    return Vector4(x - vector.x, y - vector.y, z - vector.z, z - vector.w);
}
/*!
    Multiplies this vector's coordinates by the given \a factor, and
    returns a reference to this vector.

    \sa operator/=()
*/
Vector4 &Vector4::operator*=(areal factor) {
    return *this = *this * factor;
}
/*!
    Divides this vector's coordinates by the given \a divisor, and
    returns a reference to this vector.

    \sa operator*=()
*/
Vector4 &Vector4::operator/=(areal divisor) {
    return *this = *this / divisor;
}
/*!
    Adds the given \a vector to this vector and returns a reference to
    this vector.

    \sa operator-=()
*/
Vector4 &Vector4::operator+=(const Vector4 &vector) {
    return *this = *this + vector;
}
/*!
    Subtracts the given \a vector from this vector and returns a reference to
    this vector.

    \sa operator+=()
*/
Vector4 &Vector4::operator-=(const Vector4 &vector) {
    return *this = *this - vector;
}
/*!
    Returns the component of the vector at index position i as a modifiable reference.
    \a i must be a valid index position in the vector (i.e., 0 <= i < 4).
*/
areal &Vector4::operator[](int i) {
    return v[i];
}
/*!
    Returns the component of the vector at index position.
    \a i must be a valid index position in the vector (i.e., 0 <= i < 4).
*/
const areal Vector4::operator[](int i) const {
    return v[i];
}
/*!
    Returns the length of this vector.

    \sa sqrLength()
*/
areal Vector4::length() const {
    return (areal)sqrt(sqrLength());
}
/*!
    Returns the squared length of this vector.

    \sa length()
*/
areal Vector4::sqrLength() const {
    return x * x + y * y + z * z + w * w;
}
/*!
    Normalizes the currect vector in place.
    Returns length of prenormalized vector.

    \sa length()
*/
areal Vector4::normalize() {
    areal len = length();
    if (len == 0.0f)
        return 0.0f;
    (*this) *= (1.0f / len);

    return len;
}
/*!
    Returns the dot-product of this vector and given \a vector.
*/
areal Vector4::dot(const Vector4 &vector) const {
    return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
}
