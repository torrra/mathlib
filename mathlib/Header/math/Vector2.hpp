#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include <string>
#include <sstream>

#include "MathGeneric.hpp"
#include "VectorGeneric.hpp"


#include "Angle.hpp"
#include "Trigonometry.hpp"


namespace math
{

    template <CScalarType TValueType>
    //class Vector<2, TValueType>
    class Vector2 : public Vector < 2, TValueType>
    {
    public:
        // Constructors / destructor
        using Vector<2, TValueType>::Vector;

        inline                Vector2(TValueType x, TValueType y);

        //~Vector2(void) = default;

        // Get angle from this Vector2 to another
        inline
        Radian<TValueType>            AngleFrom(const Vector2& other)                    const;

        // Get angle from this Vector2 to another unit Vector2
        // Should be used if this Vector2 and the other are both
        // unit Vector2s
        inline
        Radian<TValueType>            AngleFromUnit(const Vector2& other)                const;

        // Compute cross product with another
        // this x other
        inline TValueType            Cross(const Vector2& other)                        const;

        // Get distance between 2 points
        inline TValueType            DistanceFrom(const Vector2& other)                    const;

        // Get distance squared between two points
        inline TValueType            DistanceSquaredFrom(const Vector2& other)            const;

        // Compute dot product of two Vector2s
        inline TValueType            Dot(const Vector2& other)                            const;

        // Is this Vector2's magnitude longer than another ?
        inline bool            IsLongerThan(const Vector2& other)                    const;

        // Is this Vector2's magnitude shorter than another ?
        inline bool            IsShorterThan(const Vector2& other)                const;

        // Is this Vector2's magnitude equal to 1 ?
        inline bool            IsUnitVector(void)                                    const;

        inline TValueType            Magnitude(void)                                        const;
        inline TValueType            MagnitudeSquared(void)                                const;

        // Adjust Vector2 to turn into unit Vector2
        inline void            Normalize(void);

        // Get copy of this Vector2 as a unit Vector2
        inline Vector2            Normalized(void)                                    const;

        // Get Vector2 normal to this one
        inline Vector2            Normal(void)                                        const;

        // Project this Vector2 onto another
        inline void            ProjectOnto(const Vector2& other);

        // Reflect this Vector2 onto another
        inline void            ReflectOnto(const Vector2& axis);

        // Reflect this Vector2 onto a UNIT Vector2
        inline void            ReflectOntoUnit(const Vector2& axis);

        // Rotate this point around the z axis
        inline void            Rotate(Radian<TValueType> angle);

        // Multiply this Vector2's components by another's
        inline void            Scale(const Vector2& other);

        // Get components as string
        inline std::string        String(void)                                        const;

        // Get components as verbose string
        inline std::string        StringLong(void)                                    const;

        // Add another Vector2's components to this one's
        inline void            Translate(const Vector2& other);

        // Accessors

        inline TValueType&            X(void);
        inline TValueType&            Y(void);

        inline TValueType            GetX(void)                                            const;
        inline TValueType            GetY(void)                                            const;


        inline Vector2&        operator=(const Vector2& rhs);


        // Boolean test operators

        inline bool            operator==(const Vector2& rhs)                        const;
        inline bool            operator!=(const Vector2& rhs)                        const;

        // Component-wise operations

        inline Vector2            operator+(const Vector2& rhs)                        const;
        inline Vector2            operator-(const Vector2& rhs)                        const;
        inline Vector2            operator*(const Vector2& rhs)                        const;
        inline Vector2            operator/(const Vector2& rhs)                        const;

        // Multiply all components by a single scalar
        inline Vector2            operator*(TValueType rhs)                                const;

        // Divide all components by a single scalar
        inline Vector2            operator/(TValueType rhs)                                const;

        // Flip sign of both componenents
        inline Vector2            operator-(void)                                        const;


        // Component-wise operations

        inline Vector2&        operator+=(const Vector2& rhs);
        inline Vector2&        operator-=(const Vector2& rhs);
        inline Vector2&        operator*=(const Vector2& rhs);
        inline Vector2&        operator/=(const Vector2& rhs);

        // Multiply all components by a single scalar
        inline Vector2&        operator*=(TValueType rhs);

        // Divide all components by a single scalar
        inline Vector2&        operator/=(TValueType rhs);


        // Constants

        inline static Vector2    Zero(void);
        inline static Vector2    One(void);
        inline static Vector2    Up(void);
        inline static Vector2    Down(void);
        inline static Vector2    Left(void);
        inline static Vector2    Right(void);

    };


    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;
    using Vector2i = Vector2<int32_t>;



    // Non-member functions (similar to member functions but provided for readability)

    template <CScalarType TValueType> inline
    TValueType                Dot(const Vector2<TValueType>& first, const Vector2<TValueType>& second);

    template <CScalarType TValueType> inline
    TValueType                Cross(const Vector2<TValueType>& first, const Vector2<TValueType>& second);


    template <CScalarType TValueType> inline
    Vector2<TValueType>                Reflect(const Vector2<TValueType>& target, const Vector2<TValueType>& ontoNormal);

    template <CScalarType TValueType> inline
    Vector2<TValueType>                ReflectUnit(const Vector2<TValueType>& target, const Vector2<TValueType>& ontoNormal);

    template <CScalarType TValueType> inline
    Vector2<TValueType>                Project(const Vector2<TValueType>& target, const Vector2<TValueType>& ontoVector);


    template <CScalarType TValueType> inline
    Vector2<TValueType>                Normalize(const Vector2<TValueType>& target);


    template <CScalarType TValueType> inline
    TValueType                Distance(const Vector2<TValueType>& start, const Vector2<TValueType>& end);


    template <CScalarType TValueType> inline
    TValueType                DistanceSquared(const Vector2<TValueType>& start, const Vector2<TValueType>& end);


    template <CScalarType TValueType> inline
    Vector2<TValueType>                Rotate(const Vector2<TValueType>& target, Radian<TValueType> angle);


    // Send a Vector2<TValueType>'s components to an output stream
    template <CScalarType TValueType> inline
    std::ostream&        operator<<(std::ostream& os, Vector2<TValueType> const& vector);

    // Get components from an input stream
    template <CScalarType TValueType> inline
    std::istream&        operator>>(std::istream& is, Vector2<TValueType>& vector);





// ---- Implementation ----


    template<CScalarType TValueType>
    inline Vector2<TValueType>::Vector2(TValueType x, TValueType y)
    {
        Vector<2, TValueType>::m_values[0] = x;
        Vector<2, TValueType>::m_values[1] = y;
    }

    template <CScalarType TValueType> inline
    Radian<TValueType> Vector2<TValueType>::AngleFrom(const Vector2<TValueType>& other) const
    {
        if constexpr (std::is_integral<TValueType>::value)
            throw std::logic_error("cannot find angle between vectors of integral types");
    
        else
        {
            TValueType        magnitudes = MagnitudeSquared() * other.MagnitudeSquared();

            // Only run square root once
            magnitudes = SquareRoot(magnitudes);

            // Transform dot product equation to get cos angle,
            // then run acos
            return Acos(Dot(other) / magnitudes);
        }
    }


    template <CScalarType TValueType> inline
    Radian<TValueType> Vector2<TValueType>::AngleFromUnit(const Vector2<TValueType>& other) const
    {
        if constexpr (std::is_integral<TValueType>::value)
            throw std::logic_error("cannot find angle between vectors of integral types");

        // Clamp dot to avoid acos domain error (NaN result)
        // and call acos as both vectors are assumed to be
        // unit vectors
        else
            return Acos(Clamp(Dot(other), static_cast<TValueType>(MIN_COS), static_cast<TValueType>(MAX_COS)));
    }


    template <CScalarType TValueType> inline
    TValueType Vector2<TValueType>::Cross(const Vector2<TValueType>& other) const
    {
        // Only compute result for result's  z component as
        // both x and y will be zero for vec2 cross product
        return (GetX() * other.GetY()) - (GetY() * other.GetX());
    }


    template <CScalarType TValueType> inline
    TValueType Vector2<TValueType>::DistanceFrom(const Vector2<TValueType>& other) const
    {
        return SquareRoot(DistanceSquaredFrom(other));
    }


    template <CScalarType TValueType> inline
    TValueType Vector2<TValueType>::DistanceSquaredFrom(const Vector2<TValueType>& other) const
    {
        // Find distance vector and get magnitude
        return (other - *this).MagnitudeSquared();
    }


    template <CScalarType TValueType> inline
    TValueType Vector2<TValueType>::Dot(const Vector2<TValueType>& other) const
    {
        // Multiply components
        return (GetX() * other.GetX()) + (GetY() * other.GetY());
    }


    template <CScalarType TValueType> inline
    bool Vector2<TValueType>::IsLongerThan(const Vector2<TValueType>& other) const
    {
        // Compare squared magnitudes to avoid two sqrt calls
        return MagnitudeSquared() > other.MagnitudeSquared();
    }


    template <CScalarType TValueType> inline
    bool Vector2<TValueType>::IsShorterThan(const Vector2<TValueType>& other) const
    {
        // Compare squared magnitudes to avoid two sqrt calls
        return MagnitudeSquared() < other.MagnitudeSquared();
    }


    template <CScalarType TValueType> inline
    bool Vector2<TValueType>::IsUnitVector() const
    {
        // 1 squared == 1 so avoiding sqrt call is possible
        return AlmostEqual(MagnitudeSquared(), static_cast<TValueType>(1));
    }


    template <CScalarType TValueType> inline
    TValueType Vector2<TValueType>::Magnitude() const
    {
        return SquareRoot(MagnitudeSquared());
    }

    template <CScalarType TValueType> inline
    TValueType Vector2<TValueType>::MagnitudeSquared() const
    {
        // Square components
        return Dot(*this);
    }


    template <CScalarType TValueType> inline
    void Vector2<TValueType>::Normalize()
    {
        TValueType        invMagnitude = Magnitude();

        if (AlmostEqual(invMagnitude, static_cast<TValueType>(0), std::numeric_limits<TValueType>::epsilon()))
        {
            throw std::logic_error("Cannot divide by zero magnitude");
        }

        // Only divide once
        else
            invMagnitude = static_cast<TValueType>(1) / invMagnitude;

        X() *= invMagnitude;
        Y() *= invMagnitude;
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType> Vector2<TValueType>::Normalized(void) const
    {
        Vector2<TValueType>        result = *this;

        result.Normalize();

        // Return normalized copy
        return result;
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType> Vector2<TValueType>::Normal(void) const
    {
        if constexpr (std::is_unsigned<TValueType>::value)
            return *this;

        // Swap x and y and flip one sign (y here)
        else
            return Vector2<TValueType>(-GetY(), GetX());
    }



    template <CScalarType TValueType> inline
    void Vector2<TValueType>::ProjectOnto(const Vector2<TValueType>& other)
    {
        // Apply projection formula
        TValueType        squareMagnitude = other.MagnitudeSquared();
        TValueType        projFactor = Dot(other) / squareMagnitude;

        X() = other.GetX() * projFactor;
        Y() = other.GetY() * projFactor;

    }



    template <CScalarType TValueType> inline
    void Vector2<TValueType>::ReflectOnto(const Vector2<TValueType>& axis)
    {
        // Only reflect onto unit vector
        Vector2<TValueType>        normal = math::Normalize(axis);

        // Apply reflection formula
        *this -= normal * (Dot(normal) * static_cast<TValueType>(2));
    }


    template <CScalarType TValueType> inline
    void Vector2<TValueType>::ReflectOntoUnit(const Vector2<TValueType>& axis)
    {
        // Assume normal is already unit vector and skip normalize call
        *this -= axis * (Dot(axis) * static_cast<TValueType>(2));
    }



    template <CScalarType TValueType> inline
    void Vector2<TValueType>::Rotate(Radian<TValueType> angle)
    {
        TValueType        cosAngle = Cos(angle),
                    sinAngle = Sin(angle);

        // Copy x as base x value is needed for
        // both x and y results
        TValueType        xCopy = GetX();

        // Manually multiply by 2x2 rotation matrix
        X() = cosAngle * xCopy - GetY() * sinAngle;
        Y() = sinAngle * xCopy + GetY() * cosAngle;
    }



    template <CScalarType TValueType> inline
    void Vector2<TValueType>::Scale(const Vector2<TValueType>& other)
    {
        *this *= other;
    }


    template <CScalarType TValueType> inline
    std::string Vector2<TValueType>::String() const
    {
        // Use stream for easy conversion
        std::stringstream        stream;

        // Pass components to stream
        stream << '{' << GetX() << ',' << GetY() << '}';

        return stream.str();
    }


    template <CScalarType TValueType> inline
    std::string Vector2<TValueType>::StringLong() const
    {
        // Use stream for easy conversion
        std::stringstream        stream;

        // Pass components to stream with some extra
        stream << "Vector2{ x:" << GetX() << ", y:" << GetY() << " }";

        return stream.str();
    }


    template <CScalarType TValueType> inline
    void Vector2<TValueType>::Translate(const Vector2<TValueType>& other)
    {
        *this += other;
    }



    template <CScalarType TValueType> inline
    TValueType& Vector2<TValueType>::X()
    {
        return Vector<2, TValueType>::m_values[0];
    }



    template <CScalarType TValueType> inline
    TValueType& Vector2<TValueType>::Y()
    {
        return Vector<2, TValueType>::m_values[1];
    }



    template <CScalarType TValueType> inline
    TValueType Vector2<TValueType>::GetX() const
    {
        return Vector<2, TValueType>::m_values[0];
    }


    template <CScalarType TValueType> inline
    TValueType Vector2<TValueType>::GetY() const
    {
        return Vector<2, TValueType>::m_values[1];
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType>& Vector2<TValueType>::operator=(const Vector2<TValueType>& rhs)
    {
        // Copy assign
        X() = rhs.GetX();
        Y() = rhs.GetY();

        return *this;
    }


    template <CScalarType TValueType> inline
    bool Vector2<TValueType>::operator==(const Vector2<TValueType>& rhs) const
    {
        // Compare both components
        return
        (
            AlmostEqual(GetX(), rhs.GetX()) &&
            AlmostEqual(GetY(), rhs.GetY())
        );
    }



    template <CScalarType TValueType> inline
    bool Vector2<TValueType>::operator!=(const Vector2<TValueType>& rhs) const
    {
        return !(*this == rhs);
    }


    template <CScalarType TValueType> inline
    TValueType Dot(const Vector2<TValueType>& first, const Vector2<TValueType>& second)
    {
        return first.Dot(second);
    }


    template <CScalarType TValueType> inline
    TValueType Cross(const Vector2<TValueType>& first, const Vector2<TValueType>& second)
    {
        return first.Cross(second);
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType> Reflect(const Vector2<TValueType>& target, const Vector2<TValueType>& ontoNormal)
    {
        Vector2<TValueType>        result = target;

        // Return reflected copy
        result.ReflectOnto(ontoNormal);

        return result;
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType> ReflectUnit(const Vector2<TValueType>& target, const Vector2<TValueType>& ontoNormal)
    {
        Vector2<TValueType>        result = target;

        // Return reflected copy
        result.ReflectOntoUnit(ontoNormal);

        return result;
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType> Project(const Vector2<TValueType>& target, const Vector2<TValueType>& ontoVector)
    {
        Vector2<TValueType>        result = target;

        // Return projected copy
        result.ProjectOnto(ontoVector);

        return result;
    }



    template <CScalarType TValueType> inline
    Vector2<TValueType> Normalize(const Vector2<TValueType>& target)
    {
        Vector2<TValueType>        result = target;

        // Return normalized copy
        result.Normalize();

        return result;
    }


    template <CScalarType TValueType> inline
    TValueType Distance(const Vector2<TValueType>& start, const Vector2<TValueType>& end)
    {
        return start.DistanceFrom(end);
    }


    template <CScalarType TValueType> inline
    TValueType DistanceSquared(const Vector2<TValueType>& start, const Vector2<TValueType>& end)
    {
        return start.DistanceSquaredFrom(end);
    }



    template <CScalarType TValueType> inline
    Vector2<TValueType> Rotate(const Vector2<TValueType>& target, Radian<TValueType> angle)
    {
        Vector2<TValueType>        result = target;

        // Return rotated copy
        result.Rotate(angle);

        return result;
    }


    // Component-wise operators


    template <CScalarType TValueType> inline
    Vector2<TValueType> Vector2<TValueType>::operator+(const Vector2<TValueType>& rhs) const
    {
        return Vector2<TValueType>(GetX() + rhs.GetX(), GetY() + rhs.GetY());
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType> Vector2<TValueType>::operator-(const Vector2<TValueType>& rhs) const
    {
        return Vector2<TValueType>(GetX() - rhs.GetX(), GetY() - rhs.GetY());
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType> Vector2<TValueType>::operator*(const Vector2<TValueType>& rhs) const
    {
        return Vector2<TValueType>(GetX() * rhs.GetX(), GetY() * rhs.GetY());
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType> Vector2<TValueType>::operator/(const Vector2<TValueType>& rhs) const
    {
        return Vector2<TValueType>(GetX() / rhs.GetX(), GetY() / rhs.GetY());
    }



    template <CScalarType TValueType> inline
    Vector2<TValueType> Vector2<TValueType>::operator*(TValueType rhs) const
    {
        return Vector2<TValueType>(GetX() * rhs, GetY() * rhs);
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType> Vector2<TValueType>::operator/(TValueType rhs) const
    {
        rhs = static_cast<TValueType>(1) / rhs;

        return Vector2<TValueType>(GetX() * rhs, GetY() * rhs);
    }



    template <CScalarType TValueType> inline
    Vector2<TValueType> Vector2<TValueType>::operator-(void) const
    {
        if constexpr (std::is_unsigned<TValueType>::value)
            return *this;

        else
            return Vector2<TValueType>(-GetX(), -GetY());
    }



    template <CScalarType TValueType> inline
    Vector2<TValueType>& Vector2<TValueType>::operator+=(const Vector2<TValueType>& rhs)
    {
        X() += rhs.GetX();
        Y() += rhs.GetY();

        return *this;
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType>& Vector2<TValueType>::operator-=(const Vector2<TValueType>& rhs)
    {
        X() -= rhs.GetX();
        Y() -= rhs.GetY();

        return *this;
    }



    template <CScalarType TValueType> inline
    Vector2<TValueType>& Vector2<TValueType>::operator*=(const Vector2<TValueType>& rhs)
    {
        X() *= rhs.GetX();
        Y() *= rhs.GetY();

        return *this;
    }



    template <CScalarType TValueType> inline
    Vector2<TValueType>& Vector2<TValueType>::operator/=(const Vector2<TValueType>& rhs)
    {
        X() /= rhs.GetX();
        Y() /= rhs.GetY();

        return* this;
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType>& Vector2<TValueType>::operator*=(TValueType rhs)
    {
        X() *= rhs;
        Y() *= rhs;

        return *this;
    }



    template <CScalarType TValueType> inline
    Vector2<TValueType>& Vector2<TValueType>::operator/=(TValueType rhs)
    {
        rhs = static_cast<TValueType>(1) / rhs;

        X() *= rhs;
        Y() *= rhs;

        return *this;
    }

    // !Component-wise operators


    // Constants


    template <CScalarType TValueType> inline
    Vector2<TValueType> Vector2<TValueType>::Zero(void)
    {
        return Vector2<TValueType>();
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType> Vector2<TValueType>::One(void)
    {
        return Vector2<TValueType>(static_cast<TValueType>(1), static_cast<TValueType>(1));
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType> Vector2<TValueType>::Up(void)
    {
        return Vector2<TValueType>(static_cast<TValueType>(0), static_cast<TValueType>(1));
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType> Vector2<TValueType>::Down(void)
    {
        return Vector2<TValueType>(static_cast<TValueType>(0), static_cast<TValueType>(-1));
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType> Vector2<TValueType>::Left(void)
    {
        return Vector2<TValueType>(static_cast<TValueType>(-1), static_cast<TValueType>(0));
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType> Vector2<TValueType>::Right(void)
    {
        return Vector2<TValueType>(static_cast<TValueType>(1), static_cast<TValueType>(0));
    }

    // !Constants


    template <CScalarType TValueType> inline
    std::ostream& operator<<(std::ostream& os, Vector2<TValueType> const& vector)
    {
        // Pass components to stream
        os << '{' << vector.GetX() << ',' << vector.GetY() << '}';

        return os;
    }


    template <CScalarType TValueType> inline
    std::istream& operator>>(std::istream& is, Vector2<TValueType>& vector)
    {
        char    discard;

        // Get input from stream
        is >> discard >> vector.X() >> discard >> vector.Y() >> discard;

        return is;
    }

}

namespace LibMath = math;
namespace lm = LibMath;

#endif