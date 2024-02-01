// vgmul.vs vd, vs2

#include "zvk_ext_macros.h"

require_zvkgs;
require(P.VU.vsew == 32);
require_egw_fits(128);

VI_ZVK_VD_VS2_NOOPERANDS_PRELOOP_EGU32x4_NOVM_LOOP(
  {},
  // scalar Multiplicand
  const EGU32x4_t H = EGU32x4_BREV8(P.VU.elt_group<EGU4x32_t>(vs2_num, 0));,
  {
    EGU32x4_t Y = vd;  // Multiplier
    EGU32x4_BREV8(Y);
    EGU32x4_t Z = {};

    for (int bit = 0; bit < 128; bit++) {
      if (EGU32x4_ISSET(Y, bit)) {
        EGU32x4_XOREQ(Z, H);
      }

      bool reduce = EGU32x4_ISSET(H, 127);
      EGU32x4_LSHIFT(H);  // Lef shift by 1
      if (reduce) {
        H[0] ^= 0x87; // Reduce using x^7 + x^2 + x^1 + 1 polynomial
      }
    }
    EGU32x4_BREV8(Z);
    vd = Z;
  }
);
