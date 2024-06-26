// ------------------------------------------------------------------------
//
// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright (C) 2000 - 2020 by the deal.II authors
//
// This file is part of the deal.II library.
//
// Part of the source code is dual licensed under Apache-2.0 WITH
// LLVM-exception OR LGPL-2.1-or-later. Detailed license information
// governing the source code and code contributions can be found in
// LICENSE.md and CONTRIBUTING.md at the top level directory of deal.II.
//
// ------------------------------------------------------------------------



#include <deal.II/base/timer.h>

#include "../tests.h"

// burn computer time

double s = 0.;
void
burn(unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      for (unsigned int j = 1; j < 100000; ++j)
        {
          s += 1. / j * i;
        }
    }
}


int
main()
{
  initlog();

  Timer t;
  burn(50);

  double s1 = t.cpu_time();

  if (s1 > 0.)
    deallog << "OK" << std::endl;
  else
    deallog << "ERROR - s1 should be nonzero" << std::endl;

  burn(50);
  t.stop();
  double s2 = t.cpu_time();

  if (s2 > s1)
    deallog << "OK" << std::endl;
  else
    deallog << "ERROR - s2 should be greater than s1" << std::endl;

  burn(50);
  double s3 = t.cpu_time();

  if (s3 == s2)
    deallog << "OK" << std::endl;
  else
    deallog << "ERROR - s3 should be equal to s2" << std::endl;

  t.start();
  burn(50);
  double s4 = t.cpu_time();

  if (s4 > s3)
    deallog << "OK" << std::endl;
  else
    deallog << "ERROR - s4 should be greater than s3" << std::endl;

  t.stop();
  t.reset();
  burn(50);
  double s5 = t.cpu_time();

  if (s5 == 0.)
    deallog << "OK" << std::endl;
  else
    deallog << "ERROR - s5 should be zero" << std::endl;

  t.start();
  burn(50);
  t.reset();
  burn(50);
  double s6 = t.cpu_time();

  if (s6 == 0.)
    deallog << "OK" << std::endl;
  else
    deallog << "ERROR - s6 should be zero" << std::endl;
}
