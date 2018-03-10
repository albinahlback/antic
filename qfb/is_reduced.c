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

    Copyright (C) 2012 William Hart

******************************************************************************/

#include <stdlib.h>
#include <gmp.h>
#include "flint/flint.h"
#include "flint/ulong_extras.h"
#include "flint/fmpz.h"
#include "qfb.h"

int qfb_is_reduced(qfb_t r)
{
   if (fmpz_cmp(r->c, r->a) < 0)
      return 0;

   if (fmpz_cmpabs(r->b, r->a) > 0)
      return 0;

   if (fmpz_cmpabs(r->a, r->b) == 0 || fmpz_cmp(r->a, r->c) == 0)
      if (fmpz_sgn(r->b) < 0)
         return 0;

   return 1;
}
