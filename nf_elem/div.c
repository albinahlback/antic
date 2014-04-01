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

#include "nf_elem.h"


void _nf_elem_div(nf_elem_t a, const nf_elem_t b, const nf_elem_t c, const nf_t nf)
{
   nf_elem_t cinv;

   nf_elem_init(cinv, nf);

   _nf_elem_inv(cinv, c, nf);
   _nf_elem_mul(a, b, cinv, nf);

   nf_elem_clear(cinv, nf);
}


void nf_elem_div(nf_elem_t a, const nf_elem_t b, const nf_elem_t c, const nf_t nf)
{
   nf_elem_t t;
   
   if (a == b)
   {
      nf_elem_init(t, nf);

      _nf_elem_div(t, b, c, nf);
      fmpq_poly_swap(NF_ELEM(t), NF_ELEM(a));

      nf_elem_clear(t, nf);
   }
   else
      _nf_elem_div(a, b, c, nf);

   fmpq_poly_canonicalise(NF_ELEM(a));
}
