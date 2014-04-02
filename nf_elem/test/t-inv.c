/*=============================================================================

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

=============================================================================*/
/******************************************************************************

    Copyright (C) 2014 William Hart

******************************************************************************/

#include <stdio.h>
#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"
#include "nf.h"
#include "nf_elem.h"
#include "ulong_extras.h"

int
main(void)
{
    int i, result;
    flint_rand_t state;

    flint_printf("inv....");
    fflush(stdout);

    flint_randinit(state);

    /* test a*^-1 = 1 */
    for (i = 0; i < 10*flint_test_multiplier(); i++)
    {
        fmpq_poly_t g, pol;
        nf_t nf;
        nf_elem_t a, ainv, p1;

        fmpq_poly_init(g);
        fmpq_poly_init(pol);
        do {
           fmpq_poly_randtest_not_zero(pol, state, 25, 100);
        } while (fmpq_poly_degree(pol) < 1);
   
        nf_init(nf, pol);
        
        nf_elem_init(a, nf);
        nf_elem_init(ainv, nf);
        nf_elem_init(p1, nf);
        
        do {
           nf_elem_randtest_not_zero(a, state, 100, nf);
           fmpq_poly_gcd(g, NF_ELEM(a), pol);
        } while (!fmpq_poly_is_one(g));
        
        nf_elem_inv(ainv, a, nf);
        nf_elem_mul(p1, ainv, a, nf);
        
        result = (nf_elem_is_one(p1, nf));
        if (!result)
        {
           printf("FAIL:\n");
           printf("a = "); nf_elem_print(a, nf); printf("\n");
           printf("ainv = "); nf_elem_print(ainv, nf); printf("\n");
           printf("p1 = "); nf_elem_print(p1, nf); printf("\n");
           abort();
        }

        nf_elem_clear(a, nf);
        nf_elem_clear(ainv, nf);
        nf_elem_clear(p1, nf);
         
        nf_clear(nf);

        fmpq_poly_clear(g);
        fmpq_poly_clear(pol);
    }
    
    /* test aliasing a and b */
    for (i = 0; i < 10 * flint_test_multiplier(); i++)
    {
        fmpq_poly_t g, pol;
        nf_t nf;
        nf_elem_t a, b;

        fmpq_poly_init(g);
        fmpq_poly_init(pol);

        do {
           fmpq_poly_randtest_not_zero(pol, state, 25, 100);
        } while (fmpq_poly_degree(pol) < 1);
   
        nf_init(nf, pol);

        nf_elem_init(a, nf);
        nf_elem_init(b, nf);
        
        do {
           nf_elem_randtest_not_zero(b, state, 100, nf);
           fmpq_poly_gcd(g, NF_ELEM(b), pol);
        } while (!fmpq_poly_is_one(g));
        
        nf_elem_inv(a, b, nf);
        nf_elem_inv(b, b, nf);
        
        result = (nf_elem_equal(a, b, nf));
        if (!result)
        {
           printf("FAIL:\n");
           printf("a = "); nf_elem_print(a, nf); printf("\n");
           printf("b = "); nf_elem_print(b, nf); printf("\n");
           abort();
        }

        nf_elem_clear(a, nf);
        nf_elem_clear(b, nf);
         
        nf_clear(nf);

        fmpq_poly_clear(g);
        fmpq_poly_clear(pol);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return 0;
}
