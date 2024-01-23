#include <compare>
#include <cstdint>
#include <ratio>

namespace usu
{
    template <typename MassRatioType, typename CountType = std::uint64_t>
    class mass
    {
      public:
        using conversion = MassRatioType;
        using myCountType = CountType;

      private:
        myCountType myCount;

      public:
        mass() :
            myCount(0) {}

        mass(myCountType count) :
            myCount(count) {}

        myCountType count() const
        {
            return myCount;
        }
    };

    template <typename ToMass, typename FromMass>
    ToMass mass_cast(const FromMass& from)
    {
        // count (mg) * (FromMassNum (g))   *  (ToMassDen (lb))
        //              (FromMassDen (mg))     (ToMassNum (g))

        auto g = from.count() * static_cast<double>(FromMass::conversion::num) / static_cast<double>(FromMass::conversion::den);
        auto result = static_cast<ToMass::myCountType>(g * static_cast<double>(ToMass::conversion::den) / static_cast<double>(ToMass::conversion::num));
        return result;
    }

    // +
    template <typename Left, typename Right>
    Left operator+(const Left& x, const Right& y)
    {
        return (x.count() + usu::mass_cast<Left>(y).count());
    }

    // +=
    template <typename Left, typename Right>
    void operator+=(Left& x, const Right& y)
    {
        Left newX = Left(x.count() + usu::mass_cast<Left>(y).count());
        x = newX;
    }

    // -
    template <typename Left, typename Right>
    Left operator-(const Left& x, const Right& y)
    {
        return (x.count() - usu::mass_cast<Left>(y).count());
    }

    // -=
    template <typename Left, typename Right>
    void operator-=(Left& x, const Right& y)
    {
        Left newX = Left(x.count() - usu::mass_cast<Left>(y).count());
        x = newX;
    }

    // x * scalar
    template <typename Left>
    Left operator*(const Left& x, const double& y)
    {
        return Left(x.count() * y);
    }

    // scalar * y
    template <typename Right>
    Right operator*(const double& x, const Right& y)
    {
        return Right(x * y.count());
    }

    // *=
    template <typename Left>
    void operator*=(Left& x, const double& y)
    {
        Left newX = Left(x.count() * y);
        x = newX;
    }

    // x / scalar
    template <typename Left>
    Left operator/(const Left& x, const auto& y)
    {
        return Left(x.count() / y);
    }

    // /=
    template <typename Left>
    void operator/=(Left& x, const auto& y)
    {
        Left newX = Left(x.count() / y);
        x = newX;
    }

    // ==
    template <typename Left, typename Right>
    bool operator==(const Left& x, const Right& y)
    {
        return (x.count() == usu::mass_cast<Left>(y).count());
    }

    // !=
    template <typename Left, typename Right>
    bool operator!=(const Left& x, const Right& y)
    {
        return (x.count() != usu::mass_cast<Left>(y).count());
    }

    // <
    template <typename Left, typename Right>
    bool operator<(const Left& x, const Right& y)
    {
        return (x.count() < usu::mass_cast<Left>(y).count());
    }

    // >
    template <typename Left, typename Right>
    bool operator>(const Left& x, const Right& y)
    {
        return (x.count() > usu::mass_cast<Left>(y).count());
    }

    // <=
    template <typename Left, typename Right>
    bool operator<=(const Left& x, const Right& y)
    {
        return (x.count() <= usu::mass_cast<Left>(y).count());
    }

    // >=
    template <typename Left, typename Right>
    bool operator>=(const Left& x, const Right& y)
    {
        return (x.count() >= usu::mass_cast<Left>(y).count());
    }

    // <=>
    template <typename Left, typename Right>
    auto operator<=>(const Left& x, const Right& y)
    {
        return (x.count() <=> usu::mass_cast<Left>(y).count());
    }

    // defaulting the count of each of these to 0
    // (since the second param is just a type)
    using microgram = usu::mass<std::micro, std::uint64_t>;
    using gram = usu::mass<std::ratio<1, 1>, std::uint64_t>;
    using kilogram = usu::mass<std::kilo, std::uint64_t>;
    using ounce = mass<std::ratio<28349523125, 1000000000>, double>;

    using pound = usu::mass<std::ratio<45359237, 100000>, double>;
    using ton = usu::mass<std::ratio<90718474, 100>, double>;
} // namespace usu
