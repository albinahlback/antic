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

    Copyright (C) 2013 William Hart

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

    flint_printf("init/clear....");
    fflush(stdout);

    flint_randinit(state);

    for (i = 0; i < 100 * flint_test_multiplier(); i++)
    {
        fmpq_poly_t pol;
        nf_t nf;
        nf_elem_t a, b;
        fmpz_mat_t mat;
        slong rows, j;
        fmpz_t d;

        fmpq_poly_init(pol);
        do {
           fmpq_poly_randtest_not_zero(pol, state, 40, 200);
        } while (fmpq_poly_degree(pol) < 1);

        nf_init(nf, pol);

        rows = n_randint(state, 100) + 1;
        j = n_randint(state, rows);
        fmpz_mat_init(mat, rows, fmpq_poly_degree(pol));

        nf_elem_init(a, nf);
        nf_elem_init(b, nf);

        nf_elem_randtest(a, state, 200, nf);

        fmpz_init(d);
        
        nf_elem_get_fmpz_mat_row(mat, j, d, a, nf);
        nf_elem_set_fmpz_mat_row(b, mat, j, d, nf);

        result = nf_elem_equal(a, b, nf);
        if (!result)
        {
           flint_printf("FAIL:\n");
           flint_printf("rows = %wd, cols = %wd, j = %wd\n", rows, fmpq_poly_degree(pol), j);
           flint_printf("a = "); nf_elem_print_pretty(a, nf, "x"); printf("\n");
           flint_printf("b = "); nf_elem_print_pretty(b, nf, "x"); printf("\n");
           flint_printf("d = "); fmpz_print(d); printf("\n");
           abort();
        }

        nf_elem_clear(a, nf);
        nf_elem_clear(b, nf);
        
        fmpz_mat_clear(mat);

        fmpz_clear(d);

        nf_clear(nf);

        fmpq_poly_clear(pol);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return 0;
}
