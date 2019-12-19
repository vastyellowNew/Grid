/*************************************************************************************

Grid physics library, www.github.com/paboyle/Grid

Source file: ./lib/simd/Grid_sve_types.h

    Copyright (C) 2018

Author: Nils Meyer          <nils.meyer@ur.de>
Author: Andra-Maria Ilies   <andra-maria.ilies@arm.com>

Based on Grid_generic_types.h, original work copyright (C) 2015, 2017:

        Antonin Portelli <antonin.portelli@me.com>
        Andrew Lawson    <andrew.lawson1991@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

See the full license in the file "LICENSE" in the top level distribution directory
*************************************************************************************/
/*  END LEGAL */

/*
    ARM SVE layer by

    Nils Meyer <nils.meyer@ur.de>,
    University of Regensburg, Germany
    SFB/TRR55

    Andra-Maria Ilies   <andra-maria.ilies@arm.com>
*/

static_assert(GEN_SIMD_WIDTH % 16u == 0, "SVE vector size is not an integer multiple of 16 bytes");
static_assert(((GEN_SIMD_WIDTH > 1) & !(GEN_SIMD_WIDTH & (GEN_SIMD_WIDTH - 1))) != 0, \
    "SVE vector size is not a power of two");
//static_assert(GEN_SIMD_WIDTH > 64u,      "SVE vector size may not exceed 64 bytes (512 bits)");

//#define VECTOR_LOOPS

// playing with compiler pragmas
/*
#ifdef VECTOR_LOOPS
#ifdef __clang__
#define VECTOR_FOR(i, w, inc)\
_Pragma("clang loop unroll(full) vectorize(enable) interleave(enable) vectorize_width(w)")\
for (unsigned int i = 0; i < w; i += inc)
#else
#define VECTOR_FOR(i, w, inc)\
for (unsigned int i = 0; i < w; i += inc)
#endif
#else
#define VECTOR_FOR(i, w, inc)\
for (unsigned int i = 0; i < w; i += inc)
#endif
*/
#define VECTOR_FOR(i, w, inc)\
for (unsigned int i = 0; i < w; i += inc)

namespace Grid {
namespace Optimization {

  // type traits giving the number of elements for each vector type
  template <typename T> struct W;
  template <> struct W<double> {
    constexpr static unsigned int c = GEN_SIMD_WIDTH/16u;
    constexpr static unsigned int r = GEN_SIMD_WIDTH/8u;
  };
  template <> struct W<float> {
    constexpr static unsigned int c = GEN_SIMD_WIDTH/8u;
    constexpr static unsigned int r = GEN_SIMD_WIDTH/4u;
  };
  template <> struct W<Integer> {
    constexpr static unsigned int r = GEN_SIMD_WIDTH/4u;
  };
  template <> struct W<uint16_t> {
    constexpr static unsigned int c = GEN_SIMD_WIDTH/4u;
    constexpr static unsigned int r = GEN_SIMD_WIDTH/2u;
  };
  template <> struct W<uint64_t> {
    constexpr static unsigned int c = GEN_SIMD_WIDTH/16u;
    constexpr static unsigned int r = GEN_SIMD_WIDTH/8u;
  };
  template <> struct W<uint32_t> {
    constexpr static unsigned int c = GEN_SIMD_WIDTH/8u;
    constexpr static unsigned int r = GEN_SIMD_WIDTH/4u;
  };

  // SIMD vector types
  template <typename T>
  struct vec {
    alignas(GEN_SIMD_WIDTH) T v[W<T>::r];
  };

  typedef vec<float>     vecf;
  typedef vec<double>    vecd;
  typedef vec<uint16_t>  vech; // half precision comms
  typedef vec<Integer>   veci;

}}
