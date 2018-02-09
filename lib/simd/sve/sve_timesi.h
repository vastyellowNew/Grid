#ifndef SVE_TIMESI_H
#define SVE_TIMESI_H

#pragma message("include sve_timesi.h")

  struct TimesI{
    // Complex
    template <typename T>
    inline vec<T> operator()(const vec<T> &a, const vec<T> &b){

      vec<T> out;
      svbool_t pg1 = acle<T>::pg1();
      typename acle<T>::vt a_v = svld1(pg1, a.v);
      typename acle<T>::vt im_v = svtrn2(a_v, a_v);
      im_v = svneg_x(pg1, im_v);
      typename acle<T>::vt r_v = svtrn1(im_v, a_v);
      svst1(pg1, out.v, r_v);

      return out;
    }
  };

#endif
