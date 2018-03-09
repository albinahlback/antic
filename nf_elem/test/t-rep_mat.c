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

    Copyright (C) 2018 Tommy Hofmann

******************************************************************************/

#include <stdio.h>
#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_poly.h"
#include "fmpq_mat.h"
#include "nf.h"
#include "nf_elem.h"
#include "ulong_extras.h"

int
main(void)
{
    int i;
    flint_rand_t state;

    flint_printf("rep_mat....");
    fflush(stdout);

    flint_randinit(state);

    /* test mul_gen(b) = a * b, where a is the generator */
    for (i = 0; i < 100 * flint_test_multiplier(); i++)
    {
        fmpq_poly_t pol;
        nf_t nf;
        nf_elem_t a, b, p1, p2, t;
        slong d;
        slong j, k;
        fmpq_mat_t R;

        fmpq_poly_init(pol);
        do {
           fmpq_poly_randtest_not_zero(pol, state, 20, 100);
        } while (fmpq_poly_degree(pol) < 1);

        nf_init(nf, pol);

        d = fmpq_poly_degree(pol);

        fmpq_mat_init(R, d, d);

        nf_elem_init(a, nf);
        nf_elem_init(b, nf);
        nf_elem_init(p1, nf);
        nf_elem_init(p2, nf);
        nf_elem_init(t, nf);

        nf_elem_randtest(b, state, 100, nf);

        nf_elem_rep_mat(R, b, nf);

        for (j = 0; j < d; j++)
        {
            nf_elem_gen(a, nf);
            nf_elem_pow(a, a, j, nf);
            nf_elem_mul(p1, b, a, nf);

            nf_elem_zero(p2, nf);

            for (k = 0; k < d; k++)
            {
                nf_elem_gen(t, nf);
                nf_elem_pow(t, t, k, nf);
                nf_elem_scalar_mul_fmpq(t, t, fmpq_mat_entry(R, j, k), nf);
                nf_elem_add(p2, p2, t, nf);
            }

            if (!nf_elem_equal(p1, p2, nf))
            {
                printf("FAIL:\n");
                printf("K = "); nf_print(nf); printf("\n");
                printf("b = "); nf_elem_print_pretty(b, nf, "x"); printf("\n");
                printf("p1 = "); nf_elem_print_pretty(p1, nf, "x"); printf("\n");
                printf("p2 = "); nf_elem_print_pretty(p2, nf, "x"); printf("\n");
                abort();
            }
        }


        nf_elem_clear(a, nf);
        nf_elem_clear(b, nf);
        nf_elem_clear(p1, nf);
        nf_elem_clear(p2, nf);
        nf_elem_clear(t, nf);
        fmpq_mat_clear(R);

        nf_clear(nf);

        fmpq_poly_clear(pol);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return 0;
}
