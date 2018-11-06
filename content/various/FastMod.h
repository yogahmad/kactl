/**
 * Author: Simon Lindholm
 * Date: 2016-07-23
 * License: CC0
 * Source: me
 * Description: Fast MOD
 * Usage: rem(a*b). Dont forget to use manual C++ MOD at the end
 * USE MM as (2^61) / MOD for safety
 * Status: tested
 */
inline int rem(long long a) {
  return a-mod*((a>>29)*MM>>32);
}
