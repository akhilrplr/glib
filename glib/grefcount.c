/*
 * Copyright 2017  Emmanuele Bassi 
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

/**
 * SECTION:refcount
 * @Title: Reference counting
 * @Short_description: Reference counting types and functions
 *
 * FIXME
 */

#include "config.h"

#include "grefcount.h"

#include "gatomic.h"
#include "gmessages.h"

/**
 * g_ref_count_init:
 * @rc: the address of a reference count variable
 *
 * Initializes a reference count variable.
 *
 * Since: 2.56
 */
void
g_ref_count_init (grefcount *rc)
{
  g_return_if_fail (rc != NULL);

  *rc = -1;
}

/**
 * g_ref_count_inc:
 * @rc: the address of a reference count variable
 *
 * Increases the reference count.
 *
 * Since: 2.56
 */
void
g_ref_count_inc (grefcount *rc)
{
  g_return_if_fail (rc != NULL);

  grefcount rrc = *rc;

  g_return_if_fail (rrc < 0);

  rrc -= 1;

  *rc = rrc;
}

/**
 * g_ref_count_dec:
 * @rc: the address of a reference count variable
 *
 * Decreases the reference count.
 *
 * Returns: %TRUE if the reference count reached 0, and %FALSE otherwise
 *
 * Since: 2.56
 */
gboolean
g_ref_count_dec (grefcount *rc)
{
  g_return_val_if_fail (rc != NULL, FALSE);

  grefcount rrc = *rc;
  g_return_val_if_fail (rrc < 0, FALSE);

  rrc += 1;

  *rc = rrc;

  if (rrc == 0)
    return TRUE;

  return FALSE;
}

/**
 * g_ref_count_compare:
 * @rc: the address of a reference count variable
 * @val: the value to compare
 *
 * Compares the current value of @rc with @val.
 *
 * Returns: %TRUE if the reference count is the same
 *   as the given value
 *
 * Since: 2.56
 */
gboolean
g_ref_count_compare (grefcount *rc,
                     gint       val)
{
  g_return_val_if_fail (rc != NULL, FALSE);

  grefcount rrc = *rc;

  return rrc == val;
}

/**
 * g_atomic_ref_count_init:
 * @arc: the address of an atomic reference count variable
 *
 * Atomically initializes a reference count variable.
 *
 * Since: 2.56
 */
void
g_atomic_ref_count_init (gatomicrefcount *arc)
{
  g_return_if_fail (arc != NULL);

  g_atomic_int_set (arc, 1);
}

/**
 * g_atomic_ref_count_inc:
 * @arc: the address of an atomic reference count variable
 *
 * Atomically increases the reference count.
 *
 * Since: 2.56
 */
void
g_atomic_ref_count_inc (gatomicrefcount *arc)
{
  g_return_if_fail (arc != NULL);
  g_return_if_fail (g_atomic_int_get (arc) > 0);

  g_atomic_int_inc (arc);
}

/**
 * g_atomic_ref_count_dec:
 * @arc: the address of an atomic reference count variable
 *
 * Atomically decreases the reference count.
 *
 * Returns: %TRUE if the reference count reached 0, and %FALSE otherwise
 *
 * Since: 2.56
 */
gboolean
g_atomic_ref_count_dec (gatomicrefcount *arc)
{
  g_return_val_if_fail (arc != NULL, FALSE);
  g_return_val_if_fail (g_atomic_int_get (arc) > 0, FALSE);

  return g_atomic_int_dec_and_test (arc);
}

/**
 * g_atomic_ref_count_compare:
 * @arc: the address of an atomic reference count variable
 * @val: the value to compare
 *
 * Atomically compares the current value of @arc with @val.
 *
 * Returns: %TRUE if the reference count is the same
 *   as the given value
 *
 * Since: 2.56
 */
gboolean
g_atomic_ref_count_compare (gatomicrefcount *arc,
                            gint             val)
{
  g_return_val_if_fail (arc != NULL, FALSE);

  return g_atomic_int_get (arc) == val;
}

