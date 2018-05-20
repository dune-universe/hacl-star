
/* This file was generated by KreMLin <https://github.com/FStarLang/kremlin>
 * KreMLin invocation: /home/mpolubel/work/kremlin/krml -I /home/mpolubel/work/hacl-star/code/lib/kremlin -I /home/mpolubel/work/kremlin/kremlib -I /home/mpolubel/work/hacl-star/specs -I . -ccopt -march=native -verbose -ldopt -flto -verbose -no-prefix C.Loops -drop Prims,FStar,LowStar,C.Loops.Spec.Loops,Hacl.Cast,Hacl.UInt8,Hacl.UInt16,Hacl.UInt32,Hacl.UInt64,Hacl.UInt128 -drop Hacl.Spec.Endianness,Hacl.Endianness,Seq.Create,Spec.* -drop Hacl.SHA256 -add-early-include "Hacl_SHA256.h" -add-include "kremlin/c_string.h" -add-include "kremlin/prims_int.h" -ccopt -march=native -tmpdir rsa-c -no-prefix Hacl.Test.RSA -skip-compilation -bundle Hacl.RSAPSS=Hacl.Impl.*,Hacl.RSAPSS rsa-c/out.krml -o rsa-c/Hacl_RSAPSS.c
 * F* version: d22c8d7b
 * KreMLin version: bb3cc303
 */

#include "Hacl_RSAPSS.h"
#include "Hacl_SHA2_256.h"

inline static bool
Hacl_Impl_Lib_bn_is_bit_set(Prims_int len, uint32_t clen, uint64_t *input, uint32_t ind)
{
  uint32_t i = ind / (uint32_t)64U;
  uint32_t j = ind % (uint32_t)64U;
  uint64_t tmp = input[i];
  uint64_t tmp1 = tmp >> j & (uint64_t)1U;
  return tmp1 == (uint64_t)1U;
}

inline static void
Hacl_Impl_Lib_bn_set_bit(Prims_int len, uint32_t clen, uint64_t *input, uint32_t ind)
{
  uint32_t i = ind / (uint32_t)64U;
  uint32_t j = ind % (uint32_t)64U;
  uint64_t tmp = input[i];
  input[i] = tmp | (uint64_t)1U << j;
}

inline static uint64_t
Hacl_Impl_Lib_bval(Prims_int bLen, uint32_t cbLen, uint64_t *b, uint32_t i)
{
  if (i < cbLen)
    return b[i];
  else
    return (uint64_t)0U;
}

inline static void Hacl_Impl_Lib_fill(Prims_int len, uint32_t clen, uint64_t *b, uint64_t z)
{
  KRML_CHECK_SIZE(sizeof(z), clen);
  uint64_t buf[clen];
  for (uint32_t _i = 0U; _i < clen; ++_i)
    buf[_i] = z;
  for (uint32_t i = (uint32_t)0U; i < clen; i = i + (uint32_t)1U)
  {
    uint64_t src_i = buf[i];
    b[i] = src_i;
  }
}

inline bool Hacl_Impl_Lib_eq_b(Prims_int len, uint32_t clen, uint8_t *b1, uint8_t *b2)
{
  KRML_CHECK_SIZE(sizeof(true), (uint32_t)1U);
  bool buf[1U];
  buf[0U] = true;
  for (uint32_t i = (uint32_t)0U; i < clen; i = i + (uint32_t)1U)
  {
    bool a1 = buf[0U];
    uint8_t x0 = b1[i];
    uint8_t x1 = b2[i];
    bool a2 = x0 == x1;
    buf[0U] = a1 && a2;
  }
  bool r = buf[0U];
  return r;
}

inline void
Hacl_Impl_Convert_text_to_nat(Prims_int len, uint32_t clen, uint8_t *input, uint64_t *res)
{
  uint32_t num_words = (clen - (uint32_t)1U) / (uint32_t)8U + (uint32_t)1U;
  uint32_t tmpLen = (uint32_t)8U * num_words;
  uint32_t m = clen % (uint32_t)8U;
  uint32_t ind;
  if (m == (uint32_t)0U)
    ind = (uint32_t)0U;
  else
    ind = (uint32_t)8U - m;
  KRML_CHECK_SIZE(sizeof (uint8_t), tmpLen);
  uint8_t buf[tmpLen];
  memset(buf, 0U, tmpLen * sizeof buf[0U]);
  uint8_t *tmp1 = buf + ind;
  for (uint32_t i = (uint32_t)0U; i < clen; i = i + (uint32_t)1U)
  {
    uint8_t src_i = input[i];
    tmp1[i] = src_i;
  }
  Prims_int x0 = FStar_UInt32_v(tmpLen);
  for (uint32_t i = (uint32_t)0U; i < num_words; i = i + (uint32_t)1U)
    res[num_words - i - (uint32_t)1U] = load64_be(buf + (uint32_t)8U * i);
}

inline static void
Hacl_Impl_Convert_nat_to_text(Prims_int len, uint32_t clen, uint64_t *input, uint8_t *res)
{
  uint32_t num_words = (clen - (uint32_t)1U) / (uint32_t)8U + (uint32_t)1U;
  uint32_t tmpLen = (uint32_t)8U * num_words;
  uint32_t m = clen % (uint32_t)8U;
  uint32_t ind;
  if (m == (uint32_t)0U)
    ind = (uint32_t)0U;
  else
    ind = (uint32_t)8U - m;
  KRML_CHECK_SIZE(sizeof (uint8_t), tmpLen);
  uint8_t buf[tmpLen];
  memset(buf, 0U, tmpLen * sizeof buf[0U]);
  Prims_int x0 = FStar_UInt32_v((clen - (uint32_t)1U) / (uint32_t)8U + (uint32_t)1U);
  for (uint32_t i = (uint32_t)0U; i < num_words; i = i + (uint32_t)1U)
  {
    uint64_t tmp = input[num_words - i - (uint32_t)1U];
    store64_be(buf + (uint32_t)8U * i, tmp);
  }
  uint8_t *tmp1 = buf + ind;
  for (uint32_t i = (uint32_t)0U; i < clen; i = i + (uint32_t)1U)
  {
    uint8_t src_i = tmp1[i];
    res[i] = src_i;
  }
}

inline static bool
Hacl_Impl_Comparison_bn_is_less_(
  Prims_int aLen,
  Prims_int bLen,
  uint32_t aaLen,
  uint64_t *a,
  uint32_t bbLen,
  uint64_t *b,
  uint32_t i
)
{
  if (i > (uint32_t)0U)
  {
    uint32_t i1 = i - (uint32_t)1U;
    uint64_t t1 = a[i1];
    uint64_t t2 = Hacl_Impl_Lib_bval(bLen, bbLen, b, i1);
    if (!(t1 == t2))
      if (t1 < t2)
        return true;
      else
        return false;
    else
      return Hacl_Impl_Comparison_bn_is_less_(aLen, bLen, aaLen, a, bbLen, b, i1);
  }
  else
    return false;
}

inline static bool
Hacl_Impl_Comparison_bn_is_less(
  Prims_int aLen,
  Prims_int bLen,
  uint32_t aaLen,
  uint64_t *a,
  uint32_t bbLen,
  uint64_t *b
)
{
  return Hacl_Impl_Comparison_bn_is_less_(aLen, bLen, aaLen, a, bbLen, b, aaLen);
}

typedef struct K___uint64_t_uint64_t_s
{
  uint64_t fst;
  uint64_t snd;
}
K___uint64_t_uint64_t;

inline static K___uint64_t_uint64_t
Hacl_Impl_Addition_addcarry_u64(uint64_t carry1, uint64_t a, uint64_t b)
{
  uint64_t t1 = a + carry1;
  uint64_t carry2;
  if (t1 < carry1)
    carry2 = (uint64_t)1U;
  else
    carry2 = (uint64_t)0U;
  uint64_t res = t1 + b;
  uint64_t carry3;
  if (res < t1)
    carry3 = carry2 + (uint64_t)1U;
  else
    carry3 = carry2;
  return ((K___uint64_t_uint64_t){ .fst = carry3, .snd = res });
}

inline static K___uint64_t_uint64_t
Hacl_Impl_Addition_subborrow_u64(uint64_t carry1, uint64_t a, uint64_t b)
{
  uint64_t res = a - b - carry1;
  uint64_t carry2;
  if (carry1 == (uint64_t)1U)
  {
    uint64_t ite;
    if (a <= b)
      ite = (uint64_t)1U;
    else
      ite = (uint64_t)0U;
    carry2 = ite;
  }
  else
  {
    uint64_t ite;
    if (a < b)
      ite = (uint64_t)1U;
    else
      ite = (uint64_t)0U;
    carry2 = ite;
  }
  return ((K___uint64_t_uint64_t){ .fst = carry2, .snd = res });
}

inline static uint64_t
Hacl_Impl_Addition_bn_sub(
  Prims_int aLen,
  Prims_int bLen,
  uint32_t caLen,
  uint64_t *a,
  uint32_t cbLen,
  uint64_t *b,
  uint64_t *res
)
{
  uint64_t buf[1U] = { 0U };
  for (uint32_t i = (uint32_t)0U; i < caLen; i = i + (uint32_t)1U)
  {
    uint64_t t1 = a[i];
    uint64_t t2 = Hacl_Impl_Lib_bval(bLen, cbLen, b, i);
    K___uint64_t_uint64_t scrut = Hacl_Impl_Addition_subborrow_u64(buf[0U], t1, t2);
    uint64_t c = scrut.fst;
    uint64_t res_i = scrut.snd;
    buf[0U] = c;
    res[i] = res_i;
  }
  uint64_t r = buf[0U];
  return r;
}

inline static uint64_t
Hacl_Impl_Addition_bn_add(
  Prims_int aLen,
  Prims_int bLen,
  uint32_t caLen,
  uint64_t *a,
  uint32_t cbLen,
  uint64_t *b,
  uint64_t *res
)
{
  uint64_t buf[1U] = { 0U };
  for (uint32_t i = (uint32_t)0U; i < caLen; i = i + (uint32_t)1U)
  {
    uint64_t t1 = a[i];
    uint64_t t2 = Hacl_Impl_Lib_bval(bLen, cbLen, b, i);
    K___uint64_t_uint64_t scrut = Hacl_Impl_Addition_addcarry_u64(buf[0U], t1, t2);
    uint64_t c = scrut.fst;
    uint64_t res_i = scrut.snd;
    buf[0U] = c;
    res[i] = res_i;
  }
  uint64_t r = buf[0U];
  return r;
}

inline static K___uint64_t_uint64_t
Hacl_Impl_Multiplication_bn_mul_by_limb_addj_f(
  uint64_t a_i,
  uint64_t l,
  uint64_t c,
  uint64_t r_ij
)
{
  FStar_UInt128_uint128
  res =
    FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(a_i, l),
        FStar_UInt128_uint64_to_uint128(c)),
      FStar_UInt128_uint64_to_uint128(r_ij));
  uint64_t r = FStar_UInt128_uint128_to_uint64(res);
  uint64_t c_ = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res, (uint32_t)64U));
  return ((K___uint64_t_uint64_t){ .fst = c_, .snd = r });
}

inline static void
Hacl_Impl_Multiplication_bn_mul(
  Prims_int aLen,
  Prims_int bLen,
  uint32_t aaLen,
  uint64_t *a,
  uint32_t bbLen,
  uint64_t *b,
  uint64_t *res
)
{
  uint32_t resLen = aaLen + bbLen;
  Hacl_Impl_Lib_fill(Prims_op_Addition(aLen, bLen), resLen, res, (uint64_t)0U);
  uint64_t buf[1U] = { 0U };
  for (uint32_t i0 = (uint32_t)0U; i0 < bbLen; i0 = i0 + (uint32_t)1U)
  {
    buf[0U] = (uint64_t)0U;
    uint64_t x3 = b[i0];
    for (uint32_t i = (uint32_t)0U; i < aaLen; i = i + (uint32_t)1U)
    {
      uint32_t ij = i + i0;
      uint64_t res_ij = res[ij];
      K___uint64_t_uint64_t
      scrut = Hacl_Impl_Multiplication_bn_mul_by_limb_addj_f(a[i], x3, buf[0U], res_ij);
      uint64_t c = scrut.fst;
      uint64_t res_ij1 = scrut.snd;
      buf[0U] = c;
      res[ij] = res_ij1;
    }
    res[aaLen + i0] = buf[0U];
  }
}

inline static Hacl_Impl_Multiplication_sign
Hacl_Impl_Multiplication_abs(
  Prims_int aLen,
  uint32_t aaLen,
  uint64_t *a,
  uint64_t *b,
  uint64_t *res
)
{
  if (Hacl_Impl_Comparison_bn_is_less(aLen, aLen, aaLen, a, aaLen, b))
  {
    uint64_t uu____0 = Hacl_Impl_Addition_bn_sub(aLen, aLen, aaLen, b, aaLen, a, res);
    return Hacl_Impl_Multiplication_Negative;
  }
  else
  {
    uint64_t uu____1 = Hacl_Impl_Addition_bn_sub(aLen, aLen, aaLen, a, aaLen, b, res);
    return Hacl_Impl_Multiplication_Positive;
  }
}

bool
__eq__Hacl_Impl_Multiplication_sign(
  Hacl_Impl_Multiplication_sign y,
  Hacl_Impl_Multiplication_sign x
)
{
  switch (x)
  {
    case Hacl_Impl_Multiplication_Positive:
      {
        switch (y)
        {
          case Hacl_Impl_Multiplication_Positive:
            {
              return true;
            }
          default:
            {
              return false;
            }
        }
        break;
      }
    case Hacl_Impl_Multiplication_Negative:
      {
        switch (y)
        {
          case Hacl_Impl_Multiplication_Negative:
            {
              return true;
            }
          default:
            {
              return false;
            }
        }
        break;
      }
    default:
      {
        return false;
      }
  }
}

inline static void
Hacl_Impl_Multiplication_add_sign(
  Prims_int a0Len,
  uint32_t aa0Len,
  uint64_t *c0,
  uint64_t *c1,
  uint64_t *c2,
  uint64_t *a0,
  uint64_t *a1,
  uint64_t *a2,
  uint64_t *b0,
  uint64_t *b1,
  uint64_t *b2,
  Hacl_Impl_Multiplication_sign sa2,
  Hacl_Impl_Multiplication_sign sb2,
  uint32_t rresLen,
  uint64_t *res
)
{
  uint32_t c0Len = aa0Len + aa0Len;
  uint64_t *res1 = res;
  uint64_t
  c =
    Hacl_Impl_Addition_bn_add(Prims_op_Addition(a0Len, a0Len),
      Prims_op_Addition(a0Len, a0Len),
      c0Len,
      c0,
      c0Len,
      c1,
      res1);
  res[c0Len] = c;
  if
  (
    __eq__Hacl_Impl_Multiplication_sign(sa2,
      Hacl_Impl_Multiplication_Positive)
    && __eq__Hacl_Impl_Multiplication_sign(sb2, Hacl_Impl_Multiplication_Positive)
    ||
      __eq__Hacl_Impl_Multiplication_sign(sa2,
        Hacl_Impl_Multiplication_Negative)
      && __eq__Hacl_Impl_Multiplication_sign(sb2, Hacl_Impl_Multiplication_Negative)
  )
  {
    uint64_t
    uu____0 =
      Hacl_Impl_Addition_bn_sub(FStar_UInt32_v(rresLen),
        Prims_op_Addition(a0Len, a0Len),
        rresLen,
        res,
        c0Len,
        c2,
        res);
  }
  else
  {
    uint64_t
    uu____1 =
      Hacl_Impl_Addition_bn_add(FStar_UInt32_v(rresLen),
        Prims_op_Addition(a0Len, a0Len),
        rresLen,
        res,
        c0Len,
        c2,
        res);
  }
}

inline static void
Hacl_Impl_Multiplication_karatsuba_(
  Prims_int aLen,
  uint32_t pow2_i,
  uint32_t aaLen,
  uint64_t *a,
  uint64_t *b,
  uint64_t *tmp,
  uint64_t *res
)
{
  uint32_t pow2_i0 = pow2_i / (uint32_t)2U;
  if (aaLen < (uint32_t)32U)
    Hacl_Impl_Multiplication_bn_mul(aLen, aLen, aaLen, a, aaLen, b, res);
  else
  {
    uint64_t *a0 = a;
    uint64_t *b0 = b;
    uint64_t *tmp0 = tmp;
    uint64_t *c0 = res;
    Hacl_Impl_Multiplication_karatsuba_(FStar_UInt32_v(pow2_i0),
      pow2_i0,
      pow2_i0,
      a0,
      b0,
      tmp0,
      c0);
    uint64_t *a1 = a + pow2_i0;
    uint64_t *b1 = b + pow2_i0;
    uint64_t *tmp01 = tmp;
    uint64_t *c1 = res + pow2_i;
    Hacl_Impl_Multiplication_karatsuba_(FStar_UInt32_v(pow2_i0),
      pow2_i0,
      pow2_i0,
      a1,
      b1,
      tmp01,
      c1);
    uint64_t *a2 = tmp;
    uint64_t *b2 = tmp + pow2_i0;
    Hacl_Impl_Multiplication_sign
    sa2 = Hacl_Impl_Multiplication_abs(FStar_UInt32_v(pow2_i0), pow2_i0, a0, a1, a2);
    Hacl_Impl_Multiplication_sign
    sb2 = Hacl_Impl_Multiplication_abs(FStar_UInt32_v(pow2_i0), pow2_i0, b0, b1, b2);
    uint64_t *c2 = tmp + pow2_i;
    uint64_t *tmp02 = tmp + (uint32_t)4U * pow2_i0;
    Hacl_Impl_Multiplication_karatsuba_(FStar_UInt32_v(pow2_i0),
      pow2_i0,
      pow2_i0,
      a2,
      b2,
      tmp02,
      c2);
    uint32_t tmp1Len = pow2_i + (uint32_t)1U;
    uint64_t *tmp1 = tmp + (uint32_t)4U * pow2_i0;
    Hacl_Impl_Multiplication_add_sign(FStar_UInt32_v(pow2_i0),
      pow2_i0,
      c0,
      c1,
      c2,
      a0,
      a1,
      a2,
      b0,
      b1,
      b2,
      sa2,
      sb2,
      tmp1Len,
      tmp1);
    uint32_t res1Len = pow2_i0 + pow2_i;
    uint64_t *res1 = res + pow2_i0;
    uint64_t
    uu____0 =
      Hacl_Impl_Addition_bn_add(FStar_UInt32_v(res1Len),
        FStar_UInt32_v(tmp1Len),
        res1Len,
        res1,
        tmp1Len,
        tmp1,
        res1);
  }
}

inline static void
Hacl_Impl_Multiplication_karatsuba(
  Prims_int aLen,
  uint32_t pow2_i,
  uint32_t aaLen,
  uint64_t *a,
  uint64_t *b,
  uint64_t *st_kara
)
{
  uint64_t *res = st_kara;
  uint64_t *st_mult = st_kara + aaLen + aaLen;
  if (!(pow2_i == aaLen))
    Hacl_Impl_Multiplication_bn_mul(aLen, aLen, aaLen, a, aaLen, b, res);
  else
    Hacl_Impl_Multiplication_karatsuba_(aLen, pow2_i, aaLen, a, b, st_mult, res);
}

inline static void
Hacl_Impl_Shift_bn_lshift1_(
  Prims_int aLen,
  uint32_t aaLen,
  uint64_t *a,
  uint64_t carry1,
  uint32_t i,
  uint64_t *res
)
{
  if (i < aaLen)
  {
    uint64_t tmp = a[i];
    res[i] = tmp << (uint32_t)1U | carry1;
    uint64_t x0 = tmp & (uint64_t)0x8000000000000000U;
    uint64_t carry2;
    if (x0 == (uint64_t)0x8000000000000000U)
      carry2 = (uint64_t)1U;
    else
      carry2 = (uint64_t)0U;
    Hacl_Impl_Shift_bn_lshift1_(aLen, aaLen, a, carry2, i + (uint32_t)1U, res);
  }
}

inline static void
Hacl_Impl_Shift_bn_lshift1(Prims_int aLen, uint32_t aaLen, uint64_t *a, uint64_t *res)
{
  Hacl_Impl_Shift_bn_lshift1_(aLen, aaLen, a, (uint64_t)0U, (uint32_t)0U, res);
}

inline static void
Hacl_Impl_Shift_bn_pow2_mod_n_(
  Prims_int aLen,
  Prims_int rLen,
  uint32_t aaLen,
  uint64_t *a,
  uint32_t i,
  uint32_t p,
  uint32_t rrLen,
  uint64_t *res
)
{
  if (i < p)
  {
    Hacl_Impl_Shift_bn_lshift1(rLen, rrLen, res, res);
    if (!Hacl_Impl_Comparison_bn_is_less(rLen, aLen, rrLen, res, aaLen, a))
    {
      uint64_t uu____0 = Hacl_Impl_Addition_bn_sub(rLen, aLen, rrLen, res, aaLen, a, res);
    }
    Hacl_Impl_Shift_bn_pow2_mod_n_(aLen, rLen, aaLen, a, i + (uint32_t)1U, p, rrLen, res);
  }
}

inline static void
Hacl_Impl_Shift_bn_pow2_mod_n(
  Prims_int aLen,
  uint32_t aaLen,
  uint32_t aBits,
  uint64_t *a,
  uint32_t p,
  uint64_t *res
)
{
  uint32_t rLen = aaLen + (uint32_t)1U;
  KRML_CHECK_SIZE(sizeof (uint64_t), rLen);
  uint64_t buf[rLen];
  memset(buf, 0U, rLen * sizeof buf[0U]);
  Hacl_Impl_Lib_bn_set_bit(FStar_UInt32_v(rLen), rLen, buf, aBits);
  uint64_t
  uu____0 = Hacl_Impl_Addition_bn_sub(FStar_UInt32_v(rLen), aLen, rLen, buf, aaLen, a, buf);
  Hacl_Impl_Shift_bn_pow2_mod_n_(aLen, FStar_UInt32_v(rLen), aaLen, a, aBits, p, rLen, buf);
  uint64_t *tmp_ = buf;
  for (uint32_t i = (uint32_t)0U; i < aaLen; i = i + (uint32_t)1U)
  {
    uint64_t src_i = tmp_[i];
    res[i] = src_i;
  }
}

inline static uint64_t Hacl_Impl_Montgomery_mod_inv_u64(uint64_t n0)
{
  uint64_t alpha = (uint64_t)1U << (uint32_t)63U;
  uint64_t beta = n0;
  uint64_t buf[2U] = { 0U };
  buf[0U] = (uint64_t)1U;
  buf[1U] = (uint64_t)0U;
  for (uint32_t i = (uint32_t)0U; i < (uint32_t)64U; i = i + (uint32_t)1U)
  {
    uint64_t ub = buf[0U];
    uint64_t vb = buf[1U];
    uint64_t u_is_odd = (uint64_t)0U - (ub & (uint64_t)1U);
    uint64_t beta_if_u_is_odd = beta & u_is_odd;
    buf[0U] = ((ub ^ beta_if_u_is_odd) >> (uint32_t)1U) + (ub & beta_if_u_is_odd);
    uint64_t alpha_if_u_is_odd = alpha & u_is_odd;
    buf[1U] = (vb >> (uint32_t)1U) + alpha_if_u_is_odd;
  }
  uint64_t r = buf[1U];
  return r;
}

inline static void
Hacl_Impl_Montgomery_mont_reduction_a(
  Prims_int nLen,
  Prims_int rLen,
  uint32_t nnLen,
  uint32_t rrLen,
  uint64_t *c,
  uint64_t *n1,
  uint64_t nInv_u64
)
{
  uint64_t buf[1U] = { 0U };
  for (uint32_t i0 = (uint32_t)0U; i0 < nnLen; i0 = i0 + (uint32_t)1U)
  {
    buf[0U] = (uint64_t)0U;
    uint64_t ci = c[i0];
    uint64_t qi = nInv_u64 * ci;
    for (uint32_t i = (uint32_t)0U; i < nnLen; i = i + (uint32_t)1U)
    {
      uint32_t ij = i + i0;
      uint64_t res_ij = c[ij];
      K___uint64_t_uint64_t
      scrut = Hacl_Impl_Multiplication_bn_mul_by_limb_addj_f(n1[i], qi, buf[0U], res_ij);
      uint64_t c0 = scrut.fst;
      uint64_t res_ij1 = scrut.snd;
      buf[0U] = c0;
      c[ij] = res_ij1;
    }
    uint64_t c_ni = c[nnLen + i0];
    K___uint64_t_uint64_t scrut = Hacl_Impl_Addition_addcarry_u64((uint64_t)0U, c_ni, buf[0U]);
    uint64_t c1 = scrut.fst;
    uint64_t c_ni1 = scrut.snd;
    c[nnLen + i0] = c_ni1;
    uint64_t c_ni11 = c[nnLen + i0 + (uint32_t)1U];
    c[nnLen + i0 + (uint32_t)1U] = c_ni11 + c1;
  }
  uint64_t ci = c[nnLen];
  uint64_t qi = nInv_u64 * ci;
  for (uint32_t i = (uint32_t)0U; i < nnLen; i = i + (uint32_t)1U)
  {
    uint32_t ij = i + nnLen;
    uint64_t res_ij = c[ij];
    K___uint64_t_uint64_t
    scrut = Hacl_Impl_Multiplication_bn_mul_by_limb_addj_f(n1[i], qi, buf[0U], res_ij);
    uint64_t c0 = scrut.fst;
    uint64_t res_ij1 = scrut.snd;
    buf[0U] = c0;
    c[ij] = res_ij1;
  }
  uint64_t c_ni = c[nnLen + nnLen];
  uint64_t c1 = buf[0U];
  c[nnLen + nnLen] = c_ni + c1;
}

inline static void
Hacl_Impl_Montgomery_mont_reduction(
  Prims_int nLen,
  Prims_int rLen,
  uint32_t nnLen,
  uint32_t rrLen,
  uint64_t *n1,
  uint64_t nInv_u64,
  uint64_t *c,
  uint64_t *tmp,
  uint64_t *res
)
{
  uint32_t nLen2 = nnLen + nnLen;
  uint64_t *tmp1 = tmp;
  for (uint32_t i = (uint32_t)0U; i < nLen2; i = i + (uint32_t)1U)
  {
    uint64_t src_i = c[i];
    tmp1[i] = src_i;
  }
  tmp[nLen2] = (uint64_t)0U;
  Hacl_Impl_Montgomery_mont_reduction_a(nLen, rLen, nnLen, rrLen, tmp, n1, nInv_u64);
  uint64_t *tmp11 = tmp + rrLen;
  for (uint32_t i = (uint32_t)0U; i < nnLen; i = i + (uint32_t)1U)
  {
    uint64_t src_i = tmp11[i];
    res[i] = src_i;
  }
}

inline static void
Hacl_Impl_Montgomery_to_mont(
  Prims_int nLen,
  Prims_int rLen,
  uint32_t nnLen,
  uint32_t rrLen,
  uint32_t pow2_i,
  uint64_t *n1,
  uint64_t nInv_u64,
  uint64_t *r2,
  uint64_t *a,
  uint64_t *st_kara,
  uint64_t *aM
)
{
  uint32_t cLen = nnLen + nnLen;
  uint64_t *c = st_kara;
  Hacl_Impl_Multiplication_karatsuba(nLen, pow2_i, nnLen, a, r2, st_kara);
  uint64_t *tmp = st_kara + cLen;
  Hacl_Impl_Montgomery_mont_reduction(nLen, rLen, nnLen, rrLen, n1, nInv_u64, c, tmp, aM);
}

inline static void
Hacl_Impl_Montgomery_from_mont(
  Prims_int nLen,
  Prims_int rLen,
  uint32_t nnLen,
  uint32_t rrLen,
  uint32_t pow2_i,
  uint64_t *n1,
  uint64_t nInv_u64,
  uint64_t *aM,
  uint64_t *tmp,
  uint64_t *a
)
{
  uint32_t tmpLen = nnLen + rrLen;
  Hacl_Impl_Lib_fill(Prims_op_Addition(nLen, rLen), tmpLen, tmp, (uint64_t)0U);
  uint64_t *tmp1 = tmp;
  for (uint32_t i = (uint32_t)0U; i < nnLen; i = i + (uint32_t)1U)
  {
    uint64_t src_i = aM[i];
    tmp1[i] = src_i;
  }
  Hacl_Impl_Montgomery_mont_reduction_a(nLen, rLen, nnLen, rrLen, tmp, n1, nInv_u64);
  uint64_t *tmp11 = tmp + rrLen;
  for (uint32_t i = (uint32_t)0U; i < nnLen; i = i + (uint32_t)1U)
  {
    uint64_t src_i = tmp11[i];
    a[i] = src_i;
  }
}

inline static void
Hacl_Impl_Exponentiation_mul_mod_mont(
  Prims_int nLen,
  Prims_int rLen,
  uint32_t nnLen,
  uint32_t rrLen,
  uint32_t pow2_i,
  uint64_t *n1,
  uint64_t nInv_u64,
  uint64_t *st_kara,
  uint64_t *aM,
  uint64_t *bM,
  uint64_t *resM
)
{
  uint32_t cLen = nnLen + nnLen;
  uint64_t *c = st_kara;
  uint64_t *tmp = st_kara + cLen;
  Hacl_Impl_Multiplication_karatsuba(nLen, pow2_i, nnLen, aM, bM, st_kara);
  Hacl_Impl_Montgomery_mont_reduction(nLen, rLen, nnLen, rrLen, n1, nInv_u64, c, tmp, resM);
}

inline static void
Hacl_Impl_Exponentiation_mod_exp_(
  Prims_int nLen,
  Prims_int rLen,
  uint32_t nnLen,
  uint32_t rrLen,
  uint32_t pow2_i,
  uint64_t *n1,
  uint64_t nInv_u64,
  uint64_t *st_kara,
  uint64_t *st_exp,
  uint32_t bBits,
  uint32_t bLen,
  uint64_t *b,
  uint32_t i
)
{
  uint64_t *aM = st_exp;
  uint64_t *accM = st_exp + nnLen;
  if (i < bBits)
  {
    if (Hacl_Impl_Lib_bn_is_bit_set(FStar_UInt32_v(bLen), bLen, b, i))
      Hacl_Impl_Exponentiation_mul_mod_mont(nLen,
        rLen,
        nnLen,
        rrLen,
        pow2_i,
        n1,
        nInv_u64,
        st_kara,
        aM,
        accM,
        accM);
    Hacl_Impl_Exponentiation_mul_mod_mont(nLen,
      rLen,
      nnLen,
      rrLen,
      pow2_i,
      n1,
      nInv_u64,
      st_kara,
      aM,
      aM,
      aM);
    Hacl_Impl_Exponentiation_mod_exp_(nLen,
      rLen,
      nnLen,
      rrLen,
      pow2_i,
      n1,
      nInv_u64,
      st_kara,
      st_exp,
      bBits,
      bLen,
      b,
      i + (uint32_t)1U);
  }
}

inline static void
Hacl_Impl_Exponentiation_mod_exp(
  Prims_int nLen,
  uint32_t pow2_i,
  uint32_t modBits,
  uint32_t nnLen,
  uint64_t *n1,
  uint64_t *a,
  uint32_t bBits,
  uint64_t *b,
  uint64_t *res
)
{
  uint32_t rrLen = nnLen + (uint32_t)1U;
  uint32_t exp_r = (uint32_t)64U * rrLen;
  uint32_t exp2 = exp_r + exp_r;
  uint32_t bLen = (bBits - (uint32_t)1U) / (uint32_t)64U + (uint32_t)1U;
  uint32_t karaLen = nnLen + nnLen + (uint32_t)4U * pow2_i;
  uint32_t stLen = (uint32_t)4U * nnLen + karaLen;
  KRML_CHECK_SIZE(sizeof (uint64_t), stLen);
  uint64_t buf[stLen];
  memset(buf, 0U, stLen * sizeof buf[0U]);
  uint64_t *r2 = buf;
  uint64_t *acc = buf + nnLen;
  uint64_t *aM = buf + (uint32_t)2U * nnLen;
  uint64_t *accM = buf + (uint32_t)3U * nnLen;
  uint64_t *st_exp = buf + (uint32_t)2U * nnLen;
  uint64_t *st_kara = buf + (uint32_t)4U * nnLen;
  uint64_t *tmp = buf + (uint32_t)4U * nnLen;
  acc[0U] = (uint64_t)1U;
  Hacl_Impl_Shift_bn_pow2_mod_n(nLen, nnLen, modBits, n1, exp2, r2);
  uint64_t n0 = n1[0U];
  uint64_t nInv_u64 = Hacl_Impl_Montgomery_mod_inv_u64(n0);
  Hacl_Impl_Montgomery_to_mont(nLen,
    FStar_UInt32_v(rrLen),
    nnLen,
    rrLen,
    pow2_i,
    n1,
    nInv_u64,
    r2,
    a,
    st_kara,
    aM);
  Hacl_Impl_Montgomery_to_mont(nLen,
    FStar_UInt32_v(rrLen),
    nnLen,
    rrLen,
    pow2_i,
    n1,
    nInv_u64,
    r2,
    acc,
    st_kara,
    accM);
  Hacl_Impl_Exponentiation_mod_exp_(nLen,
    FStar_UInt32_v(rrLen),
    nnLen,
    rrLen,
    pow2_i,
    n1,
    nInv_u64,
    st_kara,
    st_exp,
    bBits,
    bLen,
    b,
    (uint32_t)0U);
  Hacl_Impl_Montgomery_from_mont(nLen,
    FStar_UInt32_v(rrLen),
    nnLen,
    rrLen,
    pow2_i,
    n1,
    nInv_u64,
    accM,
    tmp,
    res);
}

void Hacl_Impl_MGF_hash_sha256(Prims_nat x0, uint8_t *mHash, uint32_t len, uint8_t *m)
{
  Hacl_SHA2_256_hash(mHash, m, len);
}

inline static void
Hacl_Impl_MGF_mgf_sha256(
  Prims_int mgfseedLen,
  Prims_int maskLen,
  uint32_t mmgfseedLen,
  uint8_t *mgfseed,
  uint32_t mmaskLen,
  uint8_t *res
)
{
  uint32_t count_max = (mmaskLen - (uint32_t)1U) / (uint32_t)32U + (uint32_t)1U;
  uint32_t accLen = count_max * (uint32_t)32U;
  uint32_t mgfseed_counterLen0 = mmgfseedLen + (uint32_t)4U;
  uint32_t stLen = mgfseed_counterLen0 + (uint32_t)32U + accLen;
  KRML_CHECK_SIZE(sizeof (uint8_t), stLen);
  uint8_t buf[stLen];
  memset(buf, 0U, stLen * sizeof buf[0U]);
  uint8_t *mgfseed_counter0 = buf;
  uint8_t *mgfseed_st = mgfseed_counter0;
  for (uint32_t i = (uint32_t)0U; i < mmgfseedLen; i = i + (uint32_t)1U)
  {
    uint8_t src_i = mgfseed[i];
    mgfseed_st[i] = src_i;
  }
  Prims_int x0 = FStar_UInt32_v(stLen);
  for (uint32_t i0 = (uint32_t)0U; i0 < count_max; i0 = i0 + (uint32_t)1U)
  {
    uint32_t mgfseed_counterLen = mmgfseedLen + (uint32_t)4U;
    uint8_t *mgfseed_counter = buf;
    uint8_t *mHash = buf + mgfseed_counterLen;
    uint8_t *acc = buf + mgfseed_counterLen + (uint32_t)32U;
    uint8_t *c = mgfseed_counter + mmgfseedLen;
    c[0U] = (uint8_t)(i0 >> (uint32_t)24U);
    c[1U] = (uint8_t)(i0 >> (uint32_t)16U);
    c[2U] = (uint8_t)(i0 >> (uint32_t)8U);
    c[3U] = (uint8_t)i0;
    Hacl_Impl_MGF_hash_sha256(FStar_UInt32_v(mgfseed_counterLen),
      mHash,
      mgfseed_counterLen,
      mgfseed_counter);
    uint8_t *acc_ = acc + (uint32_t)32U * i0;
    for (uint32_t i = (uint32_t)0U; i < (uint32_t)32U; i = i + (uint32_t)1U)
    {
      uint8_t src_i = mHash[i];
      acc_[i] = src_i;
    }
  }
  uint8_t *acc = buf + mgfseed_counterLen0 + (uint32_t)32U;
  uint8_t *acc1 = acc;
  for (uint32_t i = (uint32_t)0U; i < mmaskLen; i = i + (uint32_t)1U)
  {
    uint8_t src_i = acc1[i];
    res[i] = src_i;
  }
}

inline static void
Hacl_Impl_RSA_xor_bytes(Prims_int len, uint32_t clen, uint8_t *b1, uint8_t *b2)
{
  for (uint32_t i = (uint32_t)0U; i < clen; i = i + (uint32_t)1U)
  {
    uint8_t i1 = b1[i];
    uint8_t i2 = b2[i];
    b1[i] = i1 ^ i2;
  }
}

static void
Hacl_Impl_RSA_pss_encode(
  Prims_int sLen,
  Prims_int msgLen,
  Prims_int emLen,
  uint32_t ssLen,
  uint8_t *salt,
  uint32_t mmsgLen,
  uint8_t *msg,
  uint32_t emBits,
  uint8_t *em
)
{
  uint32_t emLen1 = (emBits - (uint32_t)1U) / (uint32_t)8U + (uint32_t)1U;
  uint32_t msBits = emBits % (uint32_t)8U;
  uint32_t m1Len = (uint32_t)40U + ssLen;
  uint32_t dbLen = emLen1 - (uint32_t)32U - (uint32_t)1U;
  uint32_t stLen = (uint32_t)32U + m1Len + (uint32_t)32U + dbLen + dbLen;
  KRML_CHECK_SIZE(sizeof (uint8_t), stLen);
  uint8_t buf[stLen];
  memset(buf, 0U, stLen * sizeof buf[0U]);
  uint8_t *mHash = buf;
  uint8_t *m1 = buf + (uint32_t)32U;
  uint8_t *m1Hash = buf + (uint32_t)32U + m1Len;
  uint8_t *db = buf + (uint32_t)32U + m1Len + (uint32_t)32U;
  uint8_t *dbMask = buf + (uint32_t)32U + m1Len + (uint32_t)32U + dbLen;
  Hacl_Impl_MGF_hash_sha256(msgLen, mHash, mmsgLen, msg);
  uint8_t *m1_hash = m1 + (uint32_t)8U;
  for (uint32_t i = (uint32_t)0U; i < (uint32_t)32U; i = i + (uint32_t)1U)
  {
    uint8_t src_i = mHash[i];
    m1_hash[i] = src_i;
  }
  uint8_t *m1_salt = m1 + (uint32_t)40U;
  for (uint32_t i = (uint32_t)0U; i < ssLen; i = i + (uint32_t)1U)
  {
    uint8_t src_i = salt[i];
    m1_salt[i] = src_i;
  }
  Hacl_Impl_MGF_hash_sha256(FStar_UInt32_v(m1Len), m1Hash, m1Len, m1);
  uint32_t last_before_salt = dbLen - ssLen - (uint32_t)1U;
  db[last_before_salt] = (uint8_t)1U;
  uint8_t *db_salt = db + last_before_salt + (uint32_t)1U;
  for (uint32_t i = (uint32_t)0U; i < ssLen; i = i + (uint32_t)1U)
  {
    uint8_t src_i = salt[i];
    db_salt[i] = src_i;
  }
  Hacl_Impl_MGF_mgf_sha256((krml_checked_int_t)32,
    FStar_UInt32_v(dbLen),
    (uint32_t)32U,
    m1Hash,
    dbLen,
    dbMask);
  Hacl_Impl_RSA_xor_bytes(FStar_UInt32_v(dbLen), dbLen, db, dbMask);
  if (msBits > (uint32_t)0U)
  {
    uint32_t shift_bits = (uint32_t)8U - msBits;
    db[0U] = db[0U] & (uint8_t)0xffU >> shift_bits;
  }
  uint8_t *em_db = em;
  for (uint32_t i = (uint32_t)0U; i < dbLen; i = i + (uint32_t)1U)
  {
    uint8_t src_i = db[i];
    em_db[i] = src_i;
  }
  uint8_t *em_hash = em + dbLen;
  for (uint32_t i = (uint32_t)0U; i < (uint32_t)32U; i = i + (uint32_t)1U)
  {
    uint8_t src_i = m1Hash[i];
    em_hash[i] = src_i;
  }
  em[emLen1 - (uint32_t)1U] = (uint8_t)0xbcU;
}

static bool
Hacl_Impl_RSA_pss_verify(
  Prims_int msgLen,
  Prims_int emLen,
  uint32_t sLen,
  uint32_t mmsgLen,
  uint8_t *msg,
  uint32_t emBits,
  uint8_t *em
)
{
  uint32_t emLen1 = (emBits - (uint32_t)1U) / (uint32_t)8U + (uint32_t)1U;
  uint32_t msBits = emBits % (uint32_t)8U;
  uint8_t em_0;
  if (msBits > (uint32_t)0U)
    em_0 = em[0U] & (uint8_t)0xffU << msBits;
  else
    em_0 = (uint8_t)0U;
  uint8_t em_last = em[emLen1 - (uint32_t)1U];
  uint32_t padLen = emLen1 - sLen - (uint32_t)32U - (uint32_t)1U;
  uint32_t dbLen = emLen1 - (uint32_t)32U - (uint32_t)1U;
  uint32_t m1Len = (uint32_t)40U + sLen;
  uint32_t stLen = (uint32_t)32U + padLen + dbLen + m1Len + (uint32_t)32U;
  KRML_CHECK_SIZE(sizeof (uint8_t), stLen);
  uint8_t buf[stLen];
  memset(buf, 0U, stLen * sizeof buf[0U]);
  bool r;
  if (!(em_0 == (uint8_t)0U && em_last == (uint8_t)0xbcU))
    r = false;
  else
  {
    uint8_t *mHash = buf;
    uint8_t *pad2 = buf + (uint32_t)32U;
    uint8_t *dbMask = buf + (uint32_t)32U + padLen;
    uint8_t *m1 = buf + (uint32_t)32U + padLen + dbLen;
    uint8_t *m1Hash_ = buf + stLen - (uint32_t)32U;
    uint8_t *maskedDB = em;
    uint8_t *m1Hash = em + dbLen;
    Hacl_Impl_MGF_hash_sha256(msgLen, mHash, mmsgLen, msg);
    Hacl_Impl_MGF_mgf_sha256((krml_checked_int_t)32,
      FStar_UInt32_v(dbLen),
      (uint32_t)32U,
      m1Hash,
      dbLen,
      dbMask);
    Hacl_Impl_RSA_xor_bytes(FStar_UInt32_v(dbLen), dbLen, dbMask, maskedDB);
    if (msBits > (uint32_t)0U)
    {
      uint32_t shift_bits = (uint32_t)8U - msBits;
      dbMask[0U] = dbMask[0U] & (uint8_t)0xffU >> shift_bits;
    }
    pad2[padLen - (uint32_t)1U] = (uint8_t)0x01U;
    uint8_t *pad = dbMask;
    uint8_t *salt = dbMask + padLen;
    uint8_t *m1_hash = m1 + (uint32_t)8U;
    for (uint32_t i = (uint32_t)0U; i < (uint32_t)32U; i = i + (uint32_t)1U)
    {
      uint8_t src_i = mHash[i];
      m1_hash[i] = src_i;
    }
    uint8_t *m1_salt = m1 + (uint32_t)40U;
    for (uint32_t i = (uint32_t)0U; i < sLen; i = i + (uint32_t)1U)
    {
      uint8_t src_i = salt[i];
      m1_salt[i] = src_i;
    }
    Hacl_Impl_MGF_hash_sha256(FStar_UInt32_v(m1Len), m1Hash_, m1Len, m1);
    bool ite;
    if (!Hacl_Impl_Lib_eq_b(FStar_UInt32_v(padLen), padLen, pad, pad2))
      ite = false;
    else
      ite = Hacl_Impl_Lib_eq_b((krml_checked_int_t)32, (uint32_t)32U, m1Hash, m1Hash_);
    r = ite;
  }
  return r;
}

static void
Hacl_Impl_RSA_rsa_sign(
  Prims_int sLen,
  Prims_int msgLen,
  Prims_int nLen,
  uint32_t pow2_i,
  uint32_t modBits,
  uint32_t eBits,
  uint32_t dBits,
  uint32_t pLen,
  uint32_t qLen,
  uint64_t *skey,
  uint64_t rBlind,
  uint32_t ssLen,
  uint8_t *salt,
  uint32_t mmsgLen,
  uint8_t *msg,
  uint8_t *sgnt
)
{
  uint32_t nLen1 = (modBits - (uint32_t)1U) / (uint32_t)64U + (uint32_t)1U;
  uint32_t eLen = (eBits - (uint32_t)1U) / (uint32_t)64U + (uint32_t)1U;
  uint32_t dLen = (dBits - (uint32_t)1U) / (uint32_t)64U + (uint32_t)1U;
  uint64_t *n1 = skey;
  uint64_t *d = skey + nLen1 + eLen;
  uint64_t *p = skey + nLen1 + eLen + dLen;
  uint64_t *q = skey + nLen1 + eLen + dLen + pLen;
  uint32_t k = (modBits - (uint32_t)1U) / (uint32_t)8U + (uint32_t)1U;
  uint32_t emBits = modBits - (uint32_t)1U;
  uint32_t emLen = (emBits - (uint32_t)1U) / (uint32_t)8U + (uint32_t)1U;
  uint32_t n2Len = nLen1 + nLen1;
  uint32_t pqLen = pLen + qLen;
  uint32_t stLen = n2Len + pqLen + pqLen + (uint32_t)2U;
  KRML_CHECK_SIZE(sizeof (uint8_t), emLen);
  uint8_t buf[emLen];
  memset(buf, 0U, emLen * sizeof buf[0U]);
  Hacl_Impl_RSA_pss_encode(sLen,
    msgLen,
    FStar_UInt32_v(emLen),
    ssLen,
    salt,
    mmsgLen,
    msg,
    emBits,
    buf);
  KRML_CHECK_SIZE(sizeof (uint64_t), stLen);
  uint64_t buf1[stLen];
  memset(buf1, 0U, stLen * sizeof buf1[0U]);
  uint64_t *m = buf1;
  uint64_t *s = buf1 + nLen1;
  uint64_t *phi_n = buf1 + n2Len;
  uint64_t *p1 = buf1 + n2Len + pqLen;
  uint64_t *q1 = buf1 + n2Len + pqLen + pLen;
  uint32_t dLen_ = pLen + qLen + (uint32_t)1U;
  uint64_t *d_ = buf1 + n2Len + pqLen;
  uint32_t bn1_start = n2Len + pqLen + pLen + qLen + (uint32_t)1U;
  uint64_t *bn1 = buf1 + bn1_start;
  Hacl_Impl_Convert_text_to_nat(FStar_UInt32_v(emLen), emLen, buf, m);
  bn1[0U] = (uint64_t)1U;
  uint64_t
  uu____0 =
    Hacl_Impl_Addition_bn_sub(FStar_UInt32_v(pLen),
      (krml_checked_int_t)1,
      pLen,
      p,
      (uint32_t)1U,
      bn1,
      p1);
  uint64_t
  uu____1 =
    Hacl_Impl_Addition_bn_sub(FStar_UInt32_v(qLen),
      (krml_checked_int_t)1,
      qLen,
      q,
      (uint32_t)1U,
      bn1,
      q1);
  Hacl_Impl_Multiplication_bn_mul(FStar_UInt32_v(pLen),
    FStar_UInt32_v(qLen),
    pLen,
    p1,
    qLen,
    q1,
    phi_n);
  bn1[0U] = rBlind;
  Hacl_Impl_Multiplication_bn_mul(FStar_UInt32_v(pqLen),
    (krml_checked_int_t)1,
    pqLen,
    phi_n,
    (uint32_t)1U,
    bn1,
    d_);
  uint64_t
  uu____2 =
    Hacl_Impl_Addition_bn_add(FStar_UInt32_v(dLen_),
      FStar_UInt32_v(dLen),
      dLen_,
      d_,
      dLen,
      d,
      d_);
  Hacl_Impl_Exponentiation_mod_exp(FStar_UInt32_v(nLen1),
    pow2_i,
    modBits,
    nLen1,
    n1,
    m,
    dLen_ * (uint32_t)64U,
    d_,
    s);
  Hacl_Impl_Convert_nat_to_text(FStar_UInt32_v((modBits - (uint32_t)1U)
      / (uint32_t)8U
      + (uint32_t)1U),
    k,
    s,
    sgnt);
}

static bool
Hacl_Impl_RSA_rsa_verify(
  Prims_int msgLen,
  Prims_int nLen,
  uint32_t pow2_i,
  uint32_t modBits,
  uint32_t eBits,
  uint64_t *pkey,
  uint32_t sLen,
  uint8_t *sgnt,
  uint32_t mmsgLen,
  uint8_t *msg
)
{
  uint32_t nLen1 = (modBits - (uint32_t)1U) / (uint32_t)64U + (uint32_t)1U;
  uint64_t *n1 = pkey;
  uint64_t *e = pkey + nLen1;
  uint32_t k = (modBits - (uint32_t)1U) / (uint32_t)8U + (uint32_t)1U;
  uint32_t emBits = modBits - (uint32_t)1U;
  uint32_t emLen = (emBits - (uint32_t)1U) / (uint32_t)8U + (uint32_t)1U;
  uint32_t n2Len = nLen1 + nLen1;
  KRML_CHECK_SIZE(sizeof (uint64_t), n2Len);
  uint64_t buf[n2Len];
  memset(buf, 0U, n2Len * sizeof buf[0U]);
  KRML_CHECK_SIZE(sizeof (uint8_t), k);
  uint8_t buf1[k];
  memset(buf1, 0U, k * sizeof buf1[0U]);
  uint64_t *m = buf;
  uint64_t *s = buf + nLen1;
  Hacl_Impl_Convert_text_to_nat(FStar_UInt32_v((modBits - (uint32_t)1U)
      / (uint32_t)8U
      + (uint32_t)1U),
    k,
    sgnt,
    s);
  bool r;
  if
  (
    Hacl_Impl_Comparison_bn_is_less(FStar_UInt32_v(nLen1),
      FStar_UInt32_v(nLen1),
      nLen1,
      s,
      nLen1,
      n1)
  )
  {
    Hacl_Impl_Exponentiation_mod_exp(FStar_UInt32_v(nLen1),
      pow2_i,
      modBits,
      nLen1,
      n1,
      s,
      eBits,
      e,
      m);
    Hacl_Impl_Convert_nat_to_text(FStar_UInt32_v(k), emLen, m, buf1);
    r = Hacl_Impl_RSA_pss_verify(msgLen, FStar_UInt32_v(emLen), sLen, mmsgLen, msg, emBits, buf1);
  }
  else
    r = false;
  bool r0 = r;
  return r0;
}

void
Hacl_RSAPSS_rsa_pss_sign(
  Prims_int sLen,
  Prims_int msgLen,
  Prims_int nLen,
  uint32_t pow2_i,
  uint32_t modBits,
  uint32_t eBits,
  uint32_t dBits,
  uint32_t pLen,
  uint32_t qLen,
  uint64_t *skey,
  uint64_t rBlind,
  uint32_t ssLen,
  uint8_t *salt,
  uint32_t mmsgLen,
  uint8_t *msg,
  uint8_t *sgnt
)
{
  Hacl_Impl_RSA_rsa_sign(sLen,
    msgLen,
    nLen,
    pow2_i,
    modBits,
    eBits,
    dBits,
    pLen,
    qLen,
    skey,
    rBlind,
    ssLen,
    salt,
    mmsgLen,
    msg,
    sgnt);
}

bool
Hacl_RSAPSS_rsa_pss_verify(
  Prims_int sLen,
  Prims_int msgLen,
  Prims_int nLen,
  uint32_t pow2_i,
  uint32_t modBits,
  uint32_t eBits,
  uint64_t *pkey,
  uint32_t ssLen,
  uint8_t *sgnt,
  uint32_t mmsgLen,
  uint8_t *msg
)
{
  bool
  res =
    Hacl_Impl_RSA_rsa_verify(sLen,
      msgLen,
      pow2_i,
      modBits,
      eBits,
      pkey,
      ssLen,
      sgnt,
      mmsgLen,
      msg);
  return res;
}

