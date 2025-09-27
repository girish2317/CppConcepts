/**
 * Typedefs for built-in integer and floating point types.
 *
 * @copyright 2024 ADC Automotive Distance Control Systems GmbH / Continental Corporation
 *
 * @author Ralph Tandetzky <ralph.tandetzky@continental-corporation.com>
 *
 * @ingroup visu_fundamentals
 */

 #ifndef VISU_FUN_BASE_TYPES_H
 #define VISU_FUN_BASE_TYPES_H
 
 #include <cstddef>
 #include <limits>
 #include <cstdint>
 
 namespace visu {
 
 using char_t = char;
 using i8 = std::int8_t;
 using u8 = std::uint8_t;
 using i16 = std::int16_t;
 using u16 = std::uint16_t;
 using i32 = std::int32_t;
 using u32 = std::uint32_t;
 using i64 = std::int64_t;
 using u64 = std::uint64_t;
 
 using f32 = float;
 static_assert(std::numeric_limits<f32>::is_iec559, "`f32` must be IEEE-754 compliant.");
 static_assert(std::numeric_limits<unsigned char>::digits * sizeof(f32) == 32,
               "`f32` must have 32 bits.");
 
 using f64 = double;
 static_assert(std::numeric_limits<f64>::is_iec559, "`f64` must be IEEE-754 compliant.");
 static_assert(std::numeric_limits<unsigned char>::digits * sizeof(f64) == 64,
               "`f64` must have 64 bits.");
 
 using isize = std::ptrdiff_t;
 using usize = std::size_t;
 
 }  // namespace visu
 
 #endif  // VISU_FUN_BASE_TYPES_H
 