#ifndef __VECTOR_GENERIC_H__
#define __VECTOR_GENERIC_H__

#include <string>
#include <cmath>
#include <sstream>

#include "MathGeneric.hpp"

#include "Trigonometry.hpp"
#include "Arithmetic.hpp"

#include "Angle.hpp"

namespace math
{

    // Generic vector class , TDimentions defines the number of components (x, y, z...)
    // TValueType the type of the data it contains
    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value

    class Vector
    {
    public:

        // Constructors / destructor
        Vector(void) = default;

        
        template <typename... TArgs> explicit
        Vector(TArgs... args);

        explicit 
        Vector(TValueType val);

        template <DimensionType TSourceDimensions, CScalarType TTargetValueType>
        Vector(const Vector<TSourceDimensions, TTargetValueType>& other);
        
        Vector(const Vector& other);

        //template <DimensionType TSourceDimensions, CScalarType TSourceValueType> explicit
        //Vector(const Vector<TSourceDimensions, TSourceValueType>& other);

        
        template <DimensionType TSourceDimensions, CScalarType TTargetValueType>
        operator Vector<TSourceDimensions, TTargetValueType>(void) const;

        ~Vector(void) = default;


        // Get angle from this vector to another
        
        Radian<TValueType> AngleFrom(const Vector& other) const;

        // Get angle from this vector to another unit vector
        // Should be used if this vector and the other are both
        // unit vectors
        
        Radian<TValueType> AngleFromUnit(const Vector& other) const;

        // Get distance between 2 points
        template <DimensionType TDistanceDimensions = TDimensions>
        TValueType   DistanceFrom(const Vector& other)                    const;

        // Get distance squared between two points
        template<DimensionType TDistanceDimensions = TDimensions>
            TValueType            DistanceSquaredFrom(const Vector& other)            const;


        // Legacy function. You should use DistanceFrom<2>() instead
        TValueType   Distance2DFrom(const Vector& other)                    const;

        // Legacy function. You should use DistanceSquaredFrom<2>() instead
        TValueType    Distance2DSquaredFrom(const Vector& other)            const;


        // Compute dot product of two vectors
            TValueType            Dot(const Vector& other)                            const;

        // Is this vector's magnitude longer than another ?
            bool            IsLongerThan(const Vector& other)                    const;

        // Is this vector's magnitude shorter than another ?
            bool            IsShorterThan(const Vector& other)                const;

        // Is this vector's magnitude equal to 1 ?
            bool            IsUnitVector(void)                                    const;

            TValueType            Magnitude(void)                                        const;
            TValueType            MagnitudeSquared(void)                                const;

        // Adjust vector to turn into unit vector
            void            Normalize(void);

        // Get copy of this vector as a unit vector
            Vector            Normalized(void)                                    const;

        // Project this vector onto another
            void            ProjectOnto(const Vector& other);

        // Reflect this vector onto another
            void            ReflectOnto(const Vector& axis);

        // Reflect this vector onto a UNIT vector
            void            ReflectOntoUnit(const Vector& axis);

        // Add another vector's components to this one's
            void            Translate(const Vector& other);

        // Multiply this vector's components by another's
            void            Scale(const Vector& other);


        // Compute cross product with another
        // this x other
        auto		Cross(const Vector& other)					const;


        // Rotate this Vector3 around the all 3 axes
         void			Rotate
        (
            Radian<TValueType> angleX,
            Radian<TValueType> angleY,
            Radian<TValueType> angleZ
        );

        // Rotate this Vector3 around an arbitrary axis
         void			Rotate
        (Radian<TValueType> angle, const Vector<3, TValueType>& axis);


         void Rotate(Radian<TValueType> angle);

        // Get components as string
            std::string        String(void)                                        const;

        // Get components as verbose string
            inline std::string	StringLong(void)								const;

        // Accessors

         TValueType& X(void) { return m_values[0]; }
         TValueType& Y(void) { return m_values[1]; }
         TValueType& Z(void) { return m_values[2]; }
         TValueType& W(void) { return m_values[3]; }
                                      
         TValueType	GetX(void) const { return m_values[0]; }			
         TValueType	GetY(void) const { return m_values[1]; }			
         TValueType	GetZ(void) const { return m_values[2]; }			
         TValueType	GetW(void) const { return m_values[3]; }			


            Vector& operator=(const Vector& rhs);

        // Boolean test operators

            bool            operator==(const Vector& rhs)                        const;
            bool            operator!=(const Vector& rhs)                        const;


        // Component-wise operations

            Vector            operator+(const Vector& rhs)                        const;
            Vector            operator-(const Vector& rhs)                        const;
            Vector            operator*(const Vector& rhs)                        const;
            Vector            operator/(const Vector& rhs)                        const;


        // Multiply all components by a single scalar
            Vector            operator*(TValueType rhs)                                const;

        // Divide all components by a single scalar
            Vector            operator/(TValueType rhs)                                const;

        // Flip sign of every component
            Vector            operator-(void)                                        const;


        // Component-wise operations

            Vector& operator+=(const Vector& rhs);
            Vector& operator-=(const Vector& rhs);
            Vector& operator*=(const Vector& rhs);
            Vector& operator/=(const Vector& rhs);

        // Multiply all components by a single scalar
            Vector& operator*=(TValueType rhs);

        // Divide all components by a single scalar
            Vector& operator/=(TValueType rhs);

        
        TValueType& operator[](int index);
        
        TValueType operator[](int index)   const;

        // Constants

         static Vector	Zero(void);
         static Vector	One(void);
         static Vector	Up(void);
         static Vector	Down(void);
         static Vector	Left(void);
         static Vector	Right(void);
         static Vector	Back(void);
         static Vector	Front(void);

    private:

        template <typename... Args>
        DimensionType InternalVariadicInitializer(DimensionType index, TValueType initializer, Args... args);

    protected:

        TValueType m_values[TDimensions]{};

    };

 

    // Non-member functions (similar to member functions but provided for readability)
    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value inline
    TValueType Dot(const Vector<TDimensions, TValueType>& first, const Vector<TDimensions, TValueType>& second);

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value inline
    Vector<TDimensions, TValueType> Reflect(const Vector<TDimensions, TValueType>& target, const Vector<TDimensions, TValueType>& ontoNormal);

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value inline
    Vector<TDimensions, TValueType> ReflectUnit(const Vector<TDimensions, TValueType>& target, const Vector<TDimensions, TValueType>& ontoNormal);

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value inline
    Vector<TDimensions, TValueType> Project(const Vector<TDimensions, TValueType>& target, const Vector<TDimensions, TValueType>& ontoVector);

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value inline
    Vector<TDimensions, TValueType> Normalize(const Vector<TDimensions, TValueType>& target);

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value inline
    TValueType Distance(const Vector<TDimensions, TValueType>& start, const Vector<TDimensions, TValueType>& end);

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value inline
    TValueType DistanceSquared(const Vector<TDimensions, TValueType>& start, const Vector<TDimensions, TValueType>& end);

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value inline
    auto	   Cross
        (const Vector<TDimensions, TValueType>& first, const Vector<TDimensions, TValueType>& second);

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value inline
        Vector<TDimensions, TValueType>				Rotate
        (
            const Vector<TDimensions, TValueType>& target,
            Radian<TValueType> angleX,
            Radian<TValueType> angleY,
            Radian<TValueType> angleZ
        );


    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value inline
        Vector<TDimensions, TValueType>					Rotate
        (
            const Vector<TDimensions, TValueType>& target,
            Radian<TValueType> angle, const Vector<3, TValueType>& axis
        );

    template <CScalarType TValueType> inline
        Vector<2, TValueType> Rotate(const Vector<2, TValueType>& target, Radian<TValueType> angle);
    

    // Send a vector's components to an output stream
    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value inline
    std::ostream& operator<<(std::ostream& os, Vector<TDimensions, TValueType> const& vector);

    // Get components from an input stream
    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value inline
    std::istream& operator>>(std::istream& is, Vector<TDimensions, TValueType>& vector);




    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    Vector<TDimensions, TValueType>::Vector(TValueType val)
    {
        for (TValueType& currentValue : m_values)
            currentValue = val;
    }


    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    Vector<TDimensions, TValueType>::Vector(const Vector<TDimensions, TValueType>& other)
    {
        for (DimensionType index = 0; index < TDimensions; ++index)
            m_values[index] = other[index];
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    template <DimensionType TSourceDimensions, CScalarType TTargetValueType>
    Vector<TDimensions, TValueType>::Vector(const Vector<TSourceDimensions, TTargetValueType>& other)
    {
        // Take smallest vector size
        constexpr DimensionType maxDimensions = (TDimensions > TSourceDimensions) ? TSourceDimensions : TDimensions;

        for (DimensionType dimensionIndex = 0; dimensionIndex < maxDimensions; ++dimensionIndex)
            m_values[dimensionIndex] = static_cast<TTargetValueType>(other[dimensionIndex]);

        if constexpr (maxDimensions < TDimensions)
        {
            for (DimensionType remainderIndex = maxDimensions; remainderIndex < TDimensions; ++remainderIndex)
                m_values[remainderIndex] = static_cast<TTargetValueType>(0);
        }
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    template<typename ... TArgs>
    inline Vector<TDimensions, TValueType>::Vector(TArgs... arg)
    {
        DimensionType counter = 0;

        ([&]
            {
                m_values[counter++] = arg;

            } (), ...);
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    template <DimensionType TSourceDimensions, CScalarType TTargetValueType>
    Vector<TDimensions, TValueType>::operator Vector<TSourceDimensions, TTargetValueType>(void) const
    {
        Vector<TSourceDimensions, TTargetValueType> convertedVector;

        // Take smallest vector size
        constexpr DimensionType maxDimensions = (TDimensions > TSourceDimensions) ? TSourceDimensions : TDimensions;

        for (DimensionType dimensionIndex = 0; dimensionIndex < maxDimensions; ++dimensionIndex)
            convertedVector[dimensionIndex] = static_cast<TTargetValueType>(m_values[dimensionIndex]);

        if constexpr (maxDimensions < TSourceDimensions)
        {
            for (DimensionType remainderIndex = maxDimensions; remainderIndex < TSourceDimensions; ++remainderIndex)
                convertedVector[remainderIndex] = static_cast<TTargetValueType>(0);
        }

        return convertedVector;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Radian<TValueType> Vector<TDimensions, TValueType>::AngleFrom(const Vector<TDimensions, TValueType>& other) const
    {
        if constexpr (std::is_integral<TValueType>::value)
            return {};

        else
        {
            TValueType		magnitudes = MagnitudeSquared() * other.MagnitudeSquared();

            // Only run square root once
            magnitudes = SquareRoot(magnitudes);

            // Transform dot product equation to get cos angle,
            // then run acos
            return Acos(Dot(other) / magnitudes);
        }
     }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Radian<TValueType> Vector<TDimensions, TValueType>::AngleFromUnit(const Vector<TDimensions, TValueType>& other) const
    {
        if constexpr (std::is_integral<TValueType>::value)
            return {};

        // Clamp dot to avoid acos domain error (NaN result)
        // and call acos as both vectors are assumed to be
        // unit vectors
        else
            return Acos(Clamp(Dot(other), static_cast<TValueType>(MIN_COS),
                static_cast<TValueType>(MAX_COS)));
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    template<DimensionType TDistanceDimensions>
    inline TValueType Vector<TDimensions, TValueType>::DistanceFrom(const Vector<TDimensions, TValueType>& other) const
    {
        return SquareRoot(DistanceSquaredFrom<TDistanceDimensions>(other));
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    template<DimensionType TDistanceDimensions>
    inline TValueType Vector<TDimensions, TValueType>::DistanceSquaredFrom(const Vector& other) const
    {
        // Find distance vector and get magnitude
        if constexpr (TDimensions == TDistanceDimensions)
            return (other - *this).MagnitudeSquared();

        else
        {
            Vector<TDistanceDimensions, TValueType> selfCopy = static_cast<Vector<TDistanceDimensions, TValueType>>(*this);
            Vector<TDistanceDimensions, TValueType> otherCopy = static_cast<Vector<TDistanceDimensions, TValueType>>(other);

            return selfCopy.DistanceSquaredFrom(otherCopy);
        }
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline TValueType Vector<TDimensions, TValueType>::Distance2DFrom(const Vector<TDimensions, TValueType>& other) const
    {
        return DistanceFrom<2>(other);
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline TValueType Vector<TDimensions, TValueType>::Distance2DSquaredFrom(const Vector& other) const
    {
        return DistanceSquaredFrom<2>(other);
    }


    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline TValueType Vector<TDimensions, TValueType>::Dot(const Vector<TDimensions, TValueType>& other) const
    {
        TValueType result = static_cast<TValueType>(0);

        for (DimensionType index = 0; index < TDimensions; ++index)
            result += m_values[index] * other[index];

        return result;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline bool Vector<TDimensions, TValueType>::IsLongerThan(const Vector& other) const
    {
        // Compare squared magnitudes to avoid two sqrt calls
        return MagnitudeSquared() > other.MagnitudeSquared();
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline bool Vector<TDimensions, TValueType>::IsShorterThan(const Vector& other) const
    {
        return MagnitudeSquared() < other.MagnitudeSquared();
    }


    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline bool Vector<TDimensions, TValueType>::IsUnitVector(void) const
    {
        // 1 squared == 1 so avoiding sqrt call is possible
        return AlmostEqual(MagnitudeSquared(), static_cast<TValueType>(1));
    }


    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline TValueType Vector<TDimensions, TValueType>::Magnitude(void) const
    {
        return SquareRoot(MagnitudeSquared());
    }


    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline TValueType Vector<TDimensions, TValueType>::MagnitudeSquared(void) const
    {
        // Square components
        return Dot(*this);
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline void Vector<TDimensions, TValueType>::Normalize(void)
    {
        // Only divide once
        TValueType		invMagnitude = Magnitude();

        invMagnitude = static_cast<TValueType>(1) / invMagnitude;

        for (DimensionType index = 0; index < TDimensions; ++index)
            m_values[index] *= invMagnitude;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Vector<TDimensions, TValueType> Vector<TDimensions, TValueType>::Normalized(void) const
    {
        Vector<TDimensions, TValueType>		result = *this;

        result.Normalize();

        // Return normalized copy
        return result;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline void Vector<TDimensions, TValueType>::ProjectOnto(const Vector<TDimensions, TValueType>& other)
    {
        // Apply projection formula
        TValueType		squareMagnitude = other.MagnitudeSquared();
        TValueType		projFactor = Dot(other) / squareMagnitude;

        for (DimensionType index = 0; index < TDimensions; ++index)
            m_values[index] = other[index] * projFactor;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline void Vector<TDimensions, TValueType>::ReflectOnto(const Vector<TDimensions, TValueType>& axis)
    {
        // Only reflect onto unit vector
        Vector<TDimensions, TValueType>		normal = math::Normalize(axis);

        *this -= normal * (Dot(normal) * static_cast<TValueType>(2));
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline void Vector<TDimensions, TValueType>::ReflectOntoUnit(const Vector<TDimensions, TValueType>& axis)
    {
        // Assume normal is already unit vector and skip normalize call
        *this -= axis * (Dot(axis) * static_cast<TValueType>(2));
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline void Vector<TDimensions, TValueType>::Translate(const Vector<TDimensions, TValueType>& other)
    {
        *this += other;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline void Vector<TDimensions, TValueType>::Scale(const Vector<TDimensions, TValueType>& other)
    {
        *this *= other;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline auto Vector<TDimensions, TValueType>::Cross(const Vector& other) const
    {
        if constexpr (TDimensions == 3)
        {
            return Vector<3, TValueType>
                (
                    static_cast<TValueType>((this->GetY() * other.GetZ()) - (this->GetZ() * other.GetY())),
                    static_cast<TValueType>((this->GetZ() * other.GetX()) - (this->GetX() * other.GetZ())),
                    static_cast<TValueType>((this->GetX() * other.GetY()) - (this->GetY() * other.GetX()))
                );
        }

        else if constexpr (TDimensions == 2)
            return (GetX() * other.GetY()) - (GetY() * other.GetX());

        else
            return Vector();
    }

    /*template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline TValueType Vector<TDimensions, TValueType>::Cross(const Vector<2, TValueType>& other) const
    {
       
    }*/

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline void Vector<TDimensions, TValueType>::Rotate(Radian<TValueType> angle, const Vector<3, TValueType>& axis)
    {
        if constexpr (TDimensions >= 3)
        {
            const Vector<3, TValueType>		norm = math::Normalize(axis);
            const TValueType				            xCpy = this->X(), yCpy = this->Y(), zCpy = this->Z();

            // lib math trig functions are not precise enough,
            // use the standard ones instead :(
            const TValueType			cosAngle = Cos(angle);
            const TValueType			sinAngle = Sin(angle);

            const TValueType			oneMinCos = static_cast<TValueType>(1) - cosAngle;
            const Vector<3, TValueType>		oneMinAxis =
                                                        static_cast<Vector<3, TValueType>>(norm * oneMinCos);

            // Create multiplication matrix and multiply manually
            // TODO: Clean up
            TValueType				factorX = cosAngle + norm.GetX() *
                norm.GetX() * oneMinCos;

            TValueType				factorY = norm.GetX() * norm.GetY() *
                oneMinCos - norm.GetZ() * sinAngle;
            TValueType				factorZ = norm.GetX() * norm.GetZ() *
                oneMinCos + norm.GetY() * sinAngle;

            this->X() = xCpy * factorX + yCpy * factorY + factorZ * zCpy;

            factorX = norm.GetY() * norm.GetX() *
                oneMinCos + norm.GetZ() * sinAngle;

            factorY = cosAngle + norm.GetY() *
                norm.GetY() * oneMinCos;

            factorZ = norm.GetY() * norm.GetZ() *
                oneMinCos - norm.GetX() * sinAngle;

            this->Y() = xCpy * factorX + yCpy * factorY + factorZ * zCpy;

            factorX = norm.GetZ() * norm.GetX() *
                oneMinCos - norm.GetY() * sinAngle;

            factorY = norm.GetZ() * norm.GetY() *
                oneMinCos + norm.GetX() * sinAngle;

            factorZ = cosAngle + norm.GetZ() *
                norm.GetZ() * oneMinCos;

            this->Z() = xCpy * factorX + yCpy * factorY + factorZ * zCpy;
        }
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline void Vector<TDimensions, TValueType>::Rotate(Radian<TValueType> angleX, Radian<TValueType> angleY, Radian<TValueType> angleZ)
    {
        // can't rotate an unsigned vector
        if constexpr (std::is_unsigned<TValueType>::value)
            return;

        else if constexpr (TDimensions >= 3)
        {
            Vector<3, TValueType>		copy = static_cast<Vector<3, TValueType>>(*this);

            TValueType				cosYaw = Cos(angleZ), sinYaw = Sin(angleZ);
            TValueType				cosPitch = Cos(angleX), sinPitch = Sin(angleX);
            TValueType				cosRoll = Cos(angleY), sinRoll = Sin(angleY);
            TValueType				rowResult;


            // Create rotation matrix.
            // Not an actual matrix3 object to avoid circular includes
            TValueType		rotation[][3] =
            {
                {
                    cosYaw * cosRoll + sinYaw * sinPitch * sinRoll,
                    -cosYaw * sinRoll + sinYaw * sinPitch * cosRoll,
                    sinYaw * cosPitch
                },


                {
                    sinRoll * cosPitch,
                    cosRoll * cosPitch,
                    -sinPitch
                },


                {
                    -sinYaw * cosRoll + cosYaw * sinPitch * sinRoll,
                    sinRoll * sinYaw + cosYaw * sinPitch * cosRoll,
                    cosYaw * cosPitch
                }
            };


            // Multiply vector by matrix
            for (int row = 0; row < 3; ++row)
            {
                // Accumulator
                rowResult = static_cast<TValueType>(0);

                for (int column = 0; column < 3; ++column)
                {
                    rowResult += rotation[row][column] * copy[column];
                }

                (*this)[row] = rowResult;
            }
        }
        else
            return;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline void Vector<TDimensions, TValueType>::Rotate(Radian<TValueType> angle)
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

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline std::string Vector<TDimensions, TValueType>::String() const
    {
        if constexpr (TDimensions < 1)
            return {};

        else
        {
            // Use stream for easy conversion
            std::stringstream		stream;

            stream << "{" << m_values[0];

            // Pass components to stream
            for (DimensionType index = 1; index < TDimensions; ++index)
                stream << "," << m_values[index];

            stream << "}";
            return stream.str();
        }
    }


    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline std::string Vector<TDimensions, TValueType>::StringLong() const
    {
        // Use stream for easy conversion
        std::stringstream		stream;

        // Pass components to stream
        stream << "Vector" << TDimensions << "{ x:" << this->GetX();
        
        if constexpr (TDimensions > 1)
            stream << ", y:" << this->GetY();

        if constexpr (TDimensions > 2)
            stream << ", z:" << this->GetZ();

        if constexpr (TDimensions > 3)
            stream << ", w:" << this->GetW();


        stream << " }";

        return stream.str();
    }



    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Vector<TDimensions, TValueType>& Vector<TDimensions, TValueType>::operator=(const Vector<TDimensions, TValueType>& rhs)
    {
        for (DimensionType index = 0; index < TDimensions; ++index)
            m_values[index] = rhs[index];

        return *this;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline bool Vector<TDimensions, TValueType>::operator==(const Vector<TDimensions, TValueType>& rhs) const
    {
        for (DimensionType index = 0; index < TDimensions; ++index)
        {
            if (!AlmostEqual(m_values[index], rhs[index]))
                return false;
        }

        return true;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline bool Vector<TDimensions, TValueType>::operator!=(const Vector<TDimensions, TValueType>& rhs) const
    {
        return !((*this) == rhs);
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Vector<TDimensions, TValueType> Vector<TDimensions, TValueType>::operator+(const Vector<TDimensions, TValueType>& rhs) const
    {
        Vector<TDimensions, TValueType> result = *this;

        for (DimensionType index = 0; index < TDimensions; ++index)
            result[index] += rhs[index];

        return result;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Vector<TDimensions, TValueType> Vector<TDimensions, TValueType>::operator-(const Vector<TDimensions, TValueType>& rhs) const
    {
        Vector<TDimensions, TValueType> result = *this;

        for (DimensionType index = 0; index < TDimensions; ++index)
            result[index] -= rhs[index];

        return result;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Vector<TDimensions, TValueType> Vector<TDimensions, TValueType>::operator*(const Vector<TDimensions, TValueType>& rhs) const
    {
        Vector<TDimensions, TValueType> result = *this;

        for (DimensionType index = 0; index < TDimensions; ++index)
            result[index] *= rhs[index];

        return result;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Vector<TDimensions, TValueType> Vector<TDimensions, TValueType>::operator/(const Vector<TDimensions, TValueType>& rhs) const
    {
        Vector<TDimensions, TValueType> result = *this;

        for (DimensionType index = 0; index < TDimensions; ++index)
            result[index] /= rhs[index];

        return result;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Vector<TDimensions, TValueType> Vector<TDimensions, TValueType>::operator-(void) const
    {
        if constexpr (std::is_unsigned<TValueType>::value)
            return *this;

        else
        {
            Vector<TDimensions, TValueType> negated;

            for (DimensionType index = 0; index < TDimensions; ++index)
                negated[index] = -m_values[index];

            return negated;
        }
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Vector<TDimensions, TValueType> Vector<TDimensions, TValueType>::operator*(TValueType rhs) const
    {
        Vector<TDimensions, TValueType> result;

        for (DimensionType index = 0; index < TDimensions; ++index)
            result[index] = m_values[index] * rhs;

        return result;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Vector<TDimensions, TValueType> Vector<TDimensions, TValueType>::operator/(TValueType rhs) const
    {
        TValueType multiplier = static_cast<TValueType>(1) / rhs;

        return (*this) * multiplier;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Vector<TDimensions, TValueType>& Vector<TDimensions, TValueType>::operator*=(TValueType rhs)
    {
        for (TValueType& value : m_values)
            value *= rhs;

        return *this;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Vector<TDimensions, TValueType>& Vector<TDimensions, TValueType>::operator/=(TValueType rhs)
    {
        TValueType multiplier = static_cast<TValueType>(1) / rhs;

        return (*this) *= multiplier;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Vector<TDimensions, TValueType>& Vector<TDimensions, TValueType>::operator+=(const Vector<TDimensions, TValueType>& rhs)
    {
        for (DimensionType index = 0; index < TDimensions; ++index)
            m_values[index] += rhs[index];

        return *this;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Vector<TDimensions, TValueType>& Vector<TDimensions, TValueType>::operator-=(const Vector<TDimensions, TValueType>& rhs)
    {
        for (DimensionType index = 0; index < TDimensions; ++index)
            m_values[index] -= rhs[index];

        return *this;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Vector<TDimensions, TValueType>& Vector<TDimensions, TValueType>::operator*=(const Vector<TDimensions, TValueType>& rhs)
    {
        for (DimensionType index = 0; index < TDimensions; ++index)
            m_values[index] *= rhs[index];

        return *this;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    inline Vector<TDimensions, TValueType>& Vector<TDimensions, TValueType>::operator/=(const Vector<TDimensions, TValueType>& rhs)
    {
        for (DimensionType index = 0; index < TDimensions; ++index)
            m_values[index] /= rhs[index];

        return *this;
    }

    // Constants

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
        Vector<TDimensions, TValueType> Vector<TDimensions, TValueType>::Zero(void)
    {
        return Vector<TDimensions, TValueType>(static_cast<TValueType>(0));
    }



    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
        Vector<TDimensions, TValueType> Vector<TDimensions, TValueType>::One(void)
    {
        return Vector<TDimensions, TValueType>(static_cast<TValueType>(1));
    }


    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
        Vector<TDimensions, TValueType> Vector<TDimensions, TValueType>::Up(void)
    {
        if constexpr (TDimensions > 1)
        {
            return Vector<TDimensions, TValueType>(static_cast<TValueType>(0),
                static_cast<TValueType>(1));
        }
        else
            return Vector<TDimensions, TValueType>(static_cast<TValueType>(0));
    }


    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
        Vector<TDimensions, TValueType> Vector<TDimensions, TValueType>::Down(void)
    {
        if constexpr (TDimensions > 1)
        {
            return Vector<TDimensions, TValueType>(static_cast<TValueType>(0),
                static_cast<TValueType>(-1));
        }
        else
            return Vector<TDimensions, TValueType>(static_cast<TValueType>(0));
    }


    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
        Vector<TDimensions, TValueType> Vector<TDimensions, TValueType>::Left(void)
    {
        if constexpr (TDimensions > 1)
        {
            return Vector<TDimensions, TValueType>(static_cast<TValueType>(-1),
                static_cast<TValueType>(0));
        }
        else
            return Vector<TDimensions, TValueType>(static_cast<TValueType>(0));
    }


    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
        Vector<TDimensions, TValueType> Vector<TDimensions, TValueType>::Right(void)
    {
        if constexpr (TDimensions > 1)
        {
            return Vector<TDimensions, TValueType>(static_cast<TValueType>(1),
                static_cast<TValueType>(0));
        }
        else
            return Vector<TDimensions, TValueType>(static_cast<TValueType>(0));
    }


    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
        Vector<TDimensions, TValueType> Vector<TDimensions, TValueType>::Back(void)
    {
        if constexpr (TDimensions > 2)
        {
            return Vector<TDimensions, TValueType>(static_cast<TValueType>(0),
                static_cast<TValueType>(0),
                static_cast<TValueType>(-1));
        }
        else
            return Vector<TDimensions, TValueType>(static_cast<TValueType>(0));
    }


    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
        Vector<TDimensions, TValueType> Vector<TDimensions, TValueType>::Front(void)
    {
        if constexpr (TDimensions > 2)
        {
            return Vector<TDimensions, TValueType>(static_cast<TValueType>(0),
                static_cast<TValueType>(0),
                static_cast<TValueType>(1));
        }
        else
            return Vector<TDimensions, TValueType>(static_cast<TValueType>(0));
    }


    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    TValueType& Vector<TDimensions, TValueType>::operator[](int index)
    {
        return m_values[index];
    }


    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    TValueType Vector<TDimensions, TValueType>::operator[](int index) const
    {
        return m_values[index];
    }


    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value inline
        TValueType Dot(const Vector<TDimensions, TValueType>& first, const Vector<TDimensions, TValueType>& second)
    {
        return first.Dot(second);
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    Vector<TDimensions, TValueType> Reflect(const Vector<TDimensions, TValueType>& target, const Vector<TDimensions, TValueType>& ontoNormal)
    {
        Vector<TDimensions, TValueType> result = target;

        result.ReflectOnto(ontoNormal);
        return result;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    Vector<TDimensions, TValueType> ReflectUnit(const Vector<TDimensions, TValueType>& target, const Vector<TDimensions, TValueType>& ontoNormal)
    {
        Vector<TDimensions, TValueType> result = target;

        result.ReflectOntoUnit(ontoNormal);
        return result;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    Vector<TDimensions, TValueType> Project(const Vector<TDimensions, TValueType>& target, const Vector<TDimensions, TValueType>& ontoVector)
    {
        Vector<TDimensions, TValueType> result = target;

        result.ProjectOnto(ontoVector);
        return result;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    Vector<TDimensions, TValueType> Normalize(const Vector<TDimensions, TValueType>& target)
    {
        return target.Normalized();
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    TValueType Distance(const Vector<TDimensions, TValueType>& start, const Vector<TDimensions, TValueType>& end)
    {
        return start.DistanceFrom(end);
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    TValueType DistanceSquared(const Vector<TDimensions, TValueType>& start, const Vector<TDimensions, TValueType>& end)
    {
        return start.DistanceSquaredFrom(end);
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    auto Cross(const Vector<TDimensions, TValueType>& first, const Vector<TDimensions, TValueType>& second)
    {
        return first.Cross(second);
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    Vector<TDimensions, TValueType> Rotate(const Vector<TDimensions, TValueType>& target, 
        Radian<TValueType> angleX, Radian<TValueType> angleY, Radian<TValueType> angleZ)
    {
        Vector<TDimensions, TValueType> copy = target;

        copy.Rotate(angleX, angleY, angleZ);
        return copy;
    }

    template <CScalarType TValueType> inline
    Vector<2, TValueType> Rotate(const Vector<2, TValueType>& target, Radian<TValueType> angle)
    {
        Vector<2, TValueType>        result = target;

        // Return rotated copy
        result.Rotate(angle);

        return result;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    Vector<TDimensions, TValueType> Rotate(const Vector<TDimensions, TValueType>& target,
        Radian<TValueType> angle, const Vector<3, TValueType>& axis)
    {
        Vector<TDimensions, TValueType> copy = target;

        copy.Rotate(angle, axis);
        return copy;
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    std::ostream& operator<<(std::ostream& os, Vector<TDimensions, TValueType> const& vector)
    {
        return os << vector.String();
    }

    template <DimensionType TDimensions, CScalarType TValueType> requires IsGreaterThanZero<TDimensions>::value
    std::istream& operator>>(std::istream& is, Vector<TDimensions, TValueType>& vector)
    {
        char discard;

        for (DimensionType index = 0; index < TDimensions; ++index)
        {
            is >> discard;
            is >> vector[index];
        }

        is >> discard;
        return is;
    }
}



#endif