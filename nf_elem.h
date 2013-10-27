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

#ifndef NF_ELEM_H
#define NF_ELEM_H

#include <mpir.h>
#include "flint.h"
#include "fmpq_poly.h"
#include "nf.h"

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct /* element of a quadratic number field */
{
   fmpz_t a;
   fmpz_t b;
   fmpz_t den;
} qnf_elem_struct;

typedef qnf_elem_struct qnf_elem_t[1];

typedef union /* element in a number field (specified by an nf_t) */
{
   fmpq_poly_t elem; /* general case */
   qnf_elem_t qelem; /* quadratic number field */
} nf_elem_struct;

typedef nf_elem_struct nf_elem_t[1];

#define NF_ELEM_NUMREF(xxx) fmpq_poly_numref((xxx)->elem)
#define NF_ELEM(xxx) (xxx)->elem
#define QNF_ELEM(xxx) (xxx)->qelem

/******************************************************************************

    Initialisation

******************************************************************************/

void nf_elem_init(nf_elem_t a, nf_t nf);

void nf_elem_clear(nf_elem_t a, nf_t nf);

void nf_elem_randtest(nf_elem_t a, flint_rand_t state, mp_bitcnt_t bits, nf_t nf);

/******************************************************************************

    Comparison

******************************************************************************/

int nf_elem_equal(nf_elem_t a, nf_elem_t b, nf_t nf);

/******************************************************************************

    I/O

******************************************************************************/

void nf_elem_print(nf_elem_t a, nf_t nf);

/******************************************************************************

    Arithmetic

******************************************************************************/

void nf_elem_set(nf_elem_t a, nf_elem_t b, nf_t nf);

void nf_elem_add(nf_elem_t a, nf_elem_t b, nf_elem_t c, nf_t nf);

void nf_elem_sub(nf_elem_t a, nf_elem_t b, nf_elem_t c, nf_t nf);

void nf_elem_mul(nf_elem_t a, nf_elem_t b, nf_elem_t c, nf_t nf);

void nf_elem_inv(nf_elem_t a, nf_elem_t b, nf_t nf);

#ifdef __cplusplus
}
#endif

#endif
