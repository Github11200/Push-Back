// #ifndef TIMER_H
// #define TIMER_H

// enum TimeUnits
// {
//   SECONDS,
//   MILLESECONDS
// };

// struct Time
// {
//   double time;
//   TimeUnits units;

//   Time() = default;
//   Time(double time, TimeUnits units) : time(time), units(units) {}

//   constexpr Time operator*(double other) const { return Time(time * other, units); }
//   constexpr Time operator+(double other) const { return Time(time + other, units); }
//   constexpr Time operator-(double other) const { return Time(time - other, units); }
//   constexpr Time operator/(double other) const { return Time(time / other, units); }

//   constexpr Time toSeconds() const { return Time(time / 1000, TimeUnits::SECONDS); }
//   constexpr Time toMilleseconds() const { return Time(time * 1000, TimeUnits::MILLESECONDS); }
// };

// #endif