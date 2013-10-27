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

    Copyright (C) 2013 Fredrik Johansson
    Copyright (C) 2013 William Hart

******************************************************************************/

#include "nf_elem.h"

void nf_elem_init(nf_elem_t a, nf_t nf)
{
    if (nf->flag & NF_QUADRATIC)
    {
        fmpz_init(QNF_ELEM(a)->a);
        fmpz_init(QNF_ELEM(a)->b);
        fmpz_init(QNF_ELEM(a)->den);
    }
    else
    {
        fmpq_poly_init2(NF_ELEM(a), nf->pol->length - 1);
    }
}
