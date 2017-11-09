// HORTON: Helpful Open-source Research TOol for N-fermion systems.
// Copyright (C) 2011-2017 The HORTON Development Team
//
// This file is part of HORTON.
//
// HORTON is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or (at your option) any later version.
//
// HORTON is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>
//
//--


// #define DEBUG

#ifdef DEBUG
#include <cstdio>
#endif

#include <cstring>
#include <stdexcept>
#include "common.h"
#include "cartpure.h"

typedef struct {
  int ipure, icart;
  double x;
} type_sparse_el;

static const type_sparse_el cptf0[] = {
    {0, 0, 1.0},
};
static const type_sparse_el cptf1[] = {
    {0, 2, 1.0},
    {1, 0, 1.0},
    {2, 1, 1.0},
};
static const type_sparse_el cptf2[] = {
    {0, 0, -0.5},
    {0, 3, -0.5},
    {0, 5, 1.0},
    {1, 2, 1.0},
    {2, 4, 1.0},
    {3, 0, 0.86602540378443864676},
    {3, 3, -0.86602540378443864676},
    {4, 1, 1.0},
};
static const type_sparse_el cptf3[] = {
    {0, 2, -0.67082039324993690892},
    {0, 7, -0.67082039324993690892},
    {0, 9, 1.0},
    {1, 0, -0.61237243569579452455},
    {1, 3, -0.27386127875258305673},
    {1, 5, 1.0954451150103322269},
    {2, 1, -0.27386127875258305673},
    {2, 6, -0.61237243569579452455},
    {2, 8, 1.0954451150103322269},
    {3, 2, 0.86602540378443864676},
    {3, 7, -0.86602540378443864676},
    {4, 4, 1.0},
    {5, 0, 0.790569415042094833},
    {5, 3, -1.0606601717798212866},
    {6, 1, 1.0606601717798212866},
    {6, 6, -0.790569415042094833},
};
static const type_sparse_el cptf4[] = {
    {0, 0, 0.375},
    {0, 3, 0.21957751641341996535},
    {0, 5, -0.87831006565367986142},
    {0, 10, 0.375},
    {0, 12, -0.87831006565367986142},
    {0, 14, 1.0},
    {1, 2, -0.89642145700079522998},
    {1, 7, -0.40089186286863657703},
    {1, 9, 1.19522860933439364},
    {2, 4, -0.40089186286863657703},
    {2, 11, -0.89642145700079522998},
    {2, 13, 1.19522860933439364},
    {3, 0, -0.5590169943749474241},
    {3, 5, 0.9819805060619657157},
    {3, 10, 0.5590169943749474241},
    {3, 12, -0.9819805060619657157},
    {4, 1, -0.42257712736425828875},
    {4, 6, -0.42257712736425828875},
    {4, 8, 1.1338934190276816816},
    {5, 2, 0.790569415042094833},
    {5, 7, -1.0606601717798212866},
    {6, 4, 1.0606601717798212866},
    {6, 11, -0.790569415042094833},
    {7, 0, 0.73950997288745200532},
    {7, 3, -1.2990381056766579701},
    {7, 10, 0.73950997288745200532},
    {8, 1, 1.1180339887498948482},
    {8, 6, -1.1180339887498948482},
};
static const type_sparse_el cptf5[] = {
    {0, 2, 0.625},
    {0, 7, 0.36596252735569994226},
    {0, 9, -1.0910894511799619063},
    {0, 16, 0.625},
    {0, 18, -1.0910894511799619063},
    {0, 20, 1.0},
    {1, 0, 0.48412291827592711065},
    {1, 3, 0.21128856368212914438},
    {1, 5, -1.2677313820927748663},
    {1, 10, 0.16137430609197570355},
    {1, 12, -0.56694670951384084082},
    {1, 14, 1.2909944487358056284},
    {2, 1, 0.16137430609197570355},
    {2, 6, 0.21128856368212914438},
    {2, 8, -0.56694670951384084082},
    {2, 15, 0.48412291827592711065},
    {2, 17, -1.2677313820927748663},
    {2, 19, 1.2909944487358056284},
    {3, 2, -0.85391256382996653193},
    {3, 9, 1.1180339887498948482},
    {3, 16, 0.85391256382996653193},
    {3, 18, -1.1180339887498948482},
    {4, 4, -0.6454972243679028142},
    {4, 11, -0.6454972243679028142},
    {4, 13, 1.2909944487358056284},
    {5, 0, -0.52291251658379721749},
    {5, 3, 0.22821773229381921394},
    {5, 5, 0.91287092917527685576},
    {5, 10, 0.52291251658379721749},
    {5, 12, -1.2247448713915890491},
    {6, 1, -0.52291251658379721749},
    {6, 6, -0.22821773229381921394},
    {6, 8, 1.2247448713915890491},
    {6, 15, 0.52291251658379721749},
    {6, 17, -0.91287092917527685576},
    {7, 2, 0.73950997288745200532},
    {7, 7, -1.2990381056766579701},
    {7, 16, 0.73950997288745200532},
    {8, 4, 1.1180339887498948482},
    {8, 11, -1.1180339887498948482},
    {9, 0, 0.7015607600201140098},
    {9, 3, -1.5309310892394863114},
    {9, 10, 1.169267933366856683},
    {10, 1, 1.169267933366856683},
    {10, 6, -1.5309310892394863114},
    {10, 15, 0.7015607600201140098},
};
static const type_sparse_el cptf6[] = {
    {0, 0, -0.3125},
    {0, 3, -0.16319780245846672329},
    {0, 5, 0.97918681475080033975},
    {0, 10, -0.16319780245846672329},
    {0, 12, 0.57335309036732873772},
    {0, 14, -1.3055824196677337863},
    {0, 21, -0.3125},
    {0, 23, 0.97918681475080033975},
    {0, 25, -1.3055824196677337863},
    {0, 27, 1.0},
    {1, 2, 0.86356159963469679725},
    {1, 7, 0.37688918072220452831},
    {1, 9, -1.6854996561581052156},
    {1, 16, 0.28785386654489893242},
    {1, 18, -0.75377836144440905662},
    {1, 20, 1.3816985594155148756},
    {2, 4, 0.28785386654489893242},
    {2, 11, 0.37688918072220452831},
    {2, 13, -0.75377836144440905662},
    {2, 22, 0.86356159963469679725},
    {2, 24, -1.6854996561581052156},
    {2, 26, 1.3816985594155148756},
    {3, 0, 0.45285552331841995543},
    {3, 3, 0.078832027985861408788},
    {3, 5, -1.2613124477737825406},
    {3, 10, -0.078832027985861408788},
    {3, 14, 1.2613124477737825406},
    {3, 21, -0.45285552331841995543},
    {3, 23, 1.2613124477737825406},
    {3, 25, -1.2613124477737825406},
    {4, 1, 0.27308215547040717681},
    {4, 6, 0.26650089544451304287},
    {4, 8, -0.95346258924559231545},
    {4, 15, 0.27308215547040717681},
    {4, 17, -0.95346258924559231545},
    {4, 19, 1.4564381625088382763},
    {5, 2, -0.81924646641122153043},
    {5, 7, 0.35754847096709711829},
    {5, 9, 1.0660035817780521715},
    {5, 16, 0.81924646641122153043},
    {5, 18, -1.4301938838683884732},
    {6, 4, -0.81924646641122153043},
    {6, 11, -0.35754847096709711829},
    {6, 13, 1.4301938838683884732},
    {6, 22, 0.81924646641122153043},
    {6, 24, -1.0660035817780521715},
    {7, 0, -0.49607837082461073572},
    {7, 3, 0.43178079981734839863},
    {7, 5, 0.86356159963469679725},
    {7, 10, 0.43178079981734839863},
    {7, 12, -1.5169496905422946941},
    {7, 21, -0.49607837082461073572},
    {7, 23, 0.86356159963469679725},
    {8, 1, -0.59829302641309923139},
    {8, 8, 1.3055824196677337863},
    {8, 15, 0.59829302641309923139},
    {8, 17, -1.3055824196677337863},
    {9, 2, 0.7015607600201140098},
    {9, 7, -1.5309310892394863114},
    {9, 16, 1.169267933366856683},
    {10, 4, 1.169267933366856683},
    {10, 11, -1.5309310892394863114},
    {10, 22, 0.7015607600201140098},
    {11, 0, 0.67169328938139615748},
    {11, 3, -1.7539019000502850245},
    {11, 10, 1.7539019000502850245},
    {11, 21, -0.67169328938139615748},
    {12, 1, 1.2151388809514737933},
    {12, 6, -1.9764235376052370825},
    {12, 15, 1.2151388809514737933},
};
static const type_sparse_el cptf7[] = {
    {0, 2, -0.60670333962134435221},
    {0, 7, -0.31684048566533184861},
    {0, 9, 1.4169537279434593918},
    {0, 16, -0.31684048566533184861},
    {0, 18, 0.82968314787883083417},
    {0, 20, -1.5208343311935928733},
    {0, 29, -0.60670333962134435221},
    {0, 31, 1.4169537279434593918},
    {0, 33, -1.5208343311935928733},
    {0, 35, 1.0},
    {1, 0, -0.41339864235384227977},
    {1, 3, -0.17963167078872714852},
    {1, 5, 1.4370533663098171882},
    {1, 10, -0.13388954226515238921},
    {1, 12, 0.62718150750531807803},
    {1, 14, -2.1422326762424382273},
    {1, 21, -0.1146561540164598136},
    {1, 23, 0.47901778876993906273},
    {1, 25, -0.95803557753987812546},
    {1, 27, 1.4675987714106856141},
    {2, 1, -0.1146561540164598136},
    {2, 6, -0.13388954226515238921},
    {2, 8, 0.47901778876993906273},
    {2, 15, -0.17963167078872714852},
    {2, 17, 0.62718150750531807803},
    {2, 19, -0.95803557753987812546},
    {2, 28, -0.41339864235384227977},
    {2, 30, 1.4370533663098171882},
    {2, 32, -2.1422326762424382273},
    {2, 34, 1.4675987714106856141},
    {3, 2, 0.84254721963085980365},
    {3, 7, 0.14666864502533059662},
    {3, 9, -1.7491256557036030854},
    {3, 16, -0.14666864502533059662},
    {3, 20, 1.4080189922431737275},
    {3, 29, -0.84254721963085980365},
    {3, 31, 1.7491256557036030854},
    {3, 33, -1.4080189922431737275},
    {4, 4, 0.50807509012231371428},
    {4, 11, 0.49583051751369852316},
    {4, 13, -1.3222147133698627284},
    {4, 22, 0.50807509012231371428},
    {4, 24, -1.3222147133698627284},
    {4, 26, 1.6258402883914038857},
    {5, 0, 0.42961647140211000062},
    {5, 3, -0.062226236090912312563},
    {5, 5, -1.2445247218182462513},
    {5, 10, -0.23190348980538452414},
    {5, 12, 0.54315511828342602619},
    {5, 14, 1.2368186122953841287},
    {5, 21, -0.35746251148251142922},
    {5, 23, 1.2445247218182462513},
    {5, 25, -1.6593662957576616683},
    {6, 1, 0.35746251148251142922},
    {6, 6, 0.23190348980538452414},
    {6, 8, -1.2445247218182462513},
    {6, 15, 0.062226236090912312563},
    {6, 17, -0.54315511828342602619},
    {6, 19, 1.6593662957576616683},
    {6, 28, -0.42961647140211000062},
    {6, 30, 1.2445247218182462513},
    {6, 32, -1.2368186122953841287},
    {7, 2, -0.79037935147039945351},
    {7, 7, 0.6879369240987588816},
    {7, 9, 1.025515817677958738},
    {7, 16, 0.6879369240987588816},
    {7, 18, -1.8014417303072302517},
    {7, 29, -0.79037935147039945351},
    {7, 31, 1.025515817677958738},
    {8, 4, -0.95323336395336381126},
    {8, 13, 1.5504341823651057024},
    {8, 22, 0.95323336395336381126},
    {8, 24, -1.5504341823651057024},
    {9, 0, -0.47495887979908323849},
    {9, 3, 0.61914323168888299344},
    {9, 5, 0.82552430891851065792},
    {9, 10, 0.25637895441948968451},
    {9, 12, -1.8014417303072302517},
    {9, 21, -0.65864945955866621126},
    {9, 23, 1.3758738481975177632},
    {10, 1, -0.65864945955866621126},
    {10, 6, 0.25637895441948968451},
    {10, 8, 1.3758738481975177632},
    {10, 15, 0.61914323168888299344},
    {10, 17, -1.8014417303072302517},
    {10, 28, -0.47495887979908323849},
    {10, 30, 0.82552430891851065792},
    {11, 2, 0.67169328938139615748},
    {11, 7, -1.7539019000502850245},
    {11, 16, 1.7539019000502850245},
    {11, 29, -0.67169328938139615748},
    {12, 4, 1.2151388809514737933},
    {12, 11, -1.9764235376052370825},
    {12, 22, 1.2151388809514737933},
    {13, 0, 0.64725984928774934788},
    {13, 3, -1.96875},
    {13, 10, 2.4456993503903949804},
    {13, 21, -1.2566230789301937693},
    {14, 1, 1.2566230789301937693},
    {14, 6, -2.4456993503903949804},
    {14, 15, 1.96875},
    {14, 28, -0.64725984928774934788},
};

typedef struct {
  long size;
  const type_sparse_el *elements;
} type_sparse_tf;

static const type_sparse_tf cptf[MAX_SHELL_TYPE + 1] = {
    {1, cptf0},
    {3, cptf1},
    {8, cptf2},
    {16, cptf3},
    {28, cptf4},
    {46, cptf5},
    {70, cptf6},
    {102, cptf7}
};

/*
    Convert results for a Cartesian basis into results for a Pure basis, just
    by taking pre-programmed linear combinations.

    **Arguments:**

    work_cart
        The input array with the Cartesian results in contiguous storage

    work_pure
        The output array for the Pure results, also in contiguous storage

    shell_type
        The Cartesian shell type that must be converted, i.e. >= 0

    nant, npost
        These two integer parameters describe how each record of Cartesian
        and Pure results is stored. A record is defined as a set of results
        for a single shell. The convention is as follows:

            work_cart[(ca*ncart + icart)*npost + cp]
            work_pure[(ca*npure + ipure)*npost + cp]

        where:

        * ca = anterior counter for the records (0..nant-1)
        * cp = anterior counter for the records (0..npost-1)
        * ncart = the number of Cartesian basis functions in this shell
        * npure = the number of Pure basis functions in this shell
        * icart = a counter for the Cartesian basis function in this shell
        * ipure = a counter for the Pure basis function in this shell
        * nant*npost = the number of records
        * npost = the stride between two values in the same record
*/

void cart_to_pure_low(double *work_cart, double *work_pure, long shell_type,
                      long nant, long npost) {
  if ((shell_type > MAX_SHELL_TYPE) || (shell_type < 0)) {
    throw std::domain_error("The shell type must be in the interval [0,9].");
  }
  if ((nant < 1) || (npost < 1)) {
    throw std::domain_error("Both nant and npost have to be strictly positive.");
  }

  int ca, cp, i;
  const long npure = 2 * shell_type + 1;
  const long ncart = ((shell_type + 1) * (shell_type + 2)) / 2;
  const type_sparse_tf *tf = &cptf[shell_type];
  const type_sparse_el *el;

  // Reset elements in work_pure. We make use of the fact that a floating
  // point zero consists of consecutive zero bytes.
  memset(work_pure, 0, nant * npure * npost * sizeof(double));

  for (ca = nant - 1; ca >= 0; ca--) {
    for (cp = npost - 1; cp >= 0; cp--) {
      // B) Write linear combinations in work_pure
      el = tf->elements;
      for (i = tf->size - 1; i >= 0; i--) {
#ifdef DEBUG
        printf("pure[%i] += cart[%i]*%f\n",
               (ca * npure + el->ipure) * npost + cp,
               (ca * ncart + el->icart) * npost + cp,
               el->x);
#endif
        work_pure[
            (ca * npure + el->ipure) * npost + cp
        ] += el->x * work_cart[
            (ca * ncart + el->icart) * npost + cp
        ];
        el++;
      }
    }
  }
}