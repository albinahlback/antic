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

    Copyright (C) 2015 William Hart

******************************************************************************/

#include "nf_elem.h"

void nf_elem_fmpz_sub(nf_elem_t a, const fmpz_t c, const nf_elem_t b, const nf_t nf)
{
   if (nf->flag & NF_LINEAR)
   {
      fmpz * den = LNF_ELEM_DENREF(a);
	  fmpz * num = LNF_ELEM_NUMREF(a);
	  const fmpz * const den2 = LNF_ELEM_DENREF(b);
	  const fmpz * const num2 = LNF_ELEM_NUMREF(b);
	  
      _fmpq_sub_fmpz(num, den, num2, den2, c);
	  fmpz_neg(num, num);
   }
   else if (nf->flag & NF_QUADRATIC)
   {
      fmpz * den = QNF_ELEM_DENREF(a);
	  fmpz * num = QNF_ELEM_NUMREF(a);
	  slong len = 2, i;
	  
	  nf_elem_set(a, b, nf);
	  
	  while (len != 0 && fmpz_is_zero(num + len - 1))
	     len--;


          fmpz_submul(num, den, c);

          for(i=0; i<= len; i++)
             fmpz_neg(num+i, num+i);

	  _fmpq_poly_canonicalise(num, den, len);
   } else
   {
      fmpq_poly_fmpz_sub(NF_ELEM(a), c, NF_ELEM(b));
   }
}
