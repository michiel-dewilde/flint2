/*============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

===============================================================================*/
/****************************************************************************

   Copyright (C) 2009 William Hart

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "ulong_extras.h"

int main(void)
{
   int result;
   printf("remove2_precomp....");
   fflush(stdout);
 
   n_compute_primes(10000UL);

   for (ulong i = 0; i < 100000UL; i++) /* Test random numbers */
   {
      mp_limb_t n1, n2, p, orig_n;
      mpz_t d_n2, d_n1, d_p;
      int exp1, exp2;
      
      mpz_init(d_n1);
      mpz_init(d_n2);
      mpz_init(d_p);

      n1 = n_randtest_not_zero();
      orig_n = n1;

      for (ulong i = 0; i < FLINT_NUM_PRIMES_SMALL/10; i++)
      {
         mpz_set_ui(d_n1, n1);
         mpz_set_ui(d_p, flint_primes_small[i]);
         exp1 = n_remove2_precomp(&n1, flint_primes[i], flint_prime_inverses[i]);
         exp2 = mpz_remove(d_n2, d_n1, d_p);
         n2 = mpz_get_ui(d_n2);

         result = ((exp1 == exp2) && (n1 == n2));

         if (!result)
         {
            printf("FAIL\n");
            printf("n = %lu, exp1 = %d, exp2 = %d, n1 = %lu, n2 = %lu, p = %d\n", orig_n, exp1, exp2, n1, n2, flint_primes_small[i]); 
            abort();
         }
      }

      mpz_clear(d_n1);
      mpz_clear(d_n2);
      mpz_clear(d_p);
   }
         
   for (ulong i = 0; i < 100000UL; i++) /* Test perfect powers */
   {
      mp_limb_t n1, n2, p, orig_n, base;
      mpz_t d_n2, d_n1, d_p;
      int exp1, exp2, exp;
      
      mpz_init(d_n1);
      mpz_init(d_n2);
      mpz_init(d_p);

      base = n_randtest_not_zero();
      n1 = base;
      exp = n_randint(64/FLINT_BIT_COUNT(n1)) + 1;
      n1 = n_pow(base, exp);

      orig_n = n1;

      for (ulong i = 0; i < FLINT_NUM_PRIMES_SMALL/10; i++)
      {
         mpz_set_ui(d_n1, n1);
         mpz_set_ui(d_p, flint_primes_small[i]);
         exp1 = n_remove2_precomp(&n1, flint_primes[i], flint_prime_inverses[i]);
         exp2 = mpz_remove(d_n2, d_n1, d_p);
         n2 = mpz_get_ui(d_n2);

         result = ((exp1 == exp2) && (n1 == n2));

         if (!result)
         {
            printf("FAIL\n");
            printf("n = %lu, exp1 = %d, exp2 = %d, n1 = %lu, n2 = %lu, p = %d\n", orig_n, exp1, exp2, n1, n2, flint_primes_small[i]); 
            abort();
         }
      }

      mpz_clear(d_n1);
      mpz_clear(d_n2);
      mpz_clear(d_p);
   }
   
   printf("PASS\n");
   return 0;
}
