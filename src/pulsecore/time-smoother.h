#ifndef foopulsetimesmootherhfoo
#define foopulsetimesmootherhfoo

/***
  This file is part of PulseAudio.

  Copyright 2007 Lennart Poettering

  PulseAudio is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) any later version.

  PulseAudio is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with PulseAudio; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA.
***/

#include <pulsecore/macro.h>
#include <pulse/sample.h>

typedef struct pa_smoother pa_smoother;

pa_smoother* pa_smoother_new(pa_usec_t x_adjust_time, pa_usec_t x_history_time, pa_bool_t monotonic, unsigned min_history);
void pa_smoother_free(pa_smoother* s);

/* Adds a new value to our dataset. x = local/system time, y = remote time */
void pa_smoother_put(pa_smoother *s, pa_usec_t x, pa_usec_t y);

/* Returns an interpolated value based on the dataset. x = local/system time, return value = remote time */
pa_usec_t pa_smoother_get(pa_smoother *s, pa_usec_t x);

/* Translates a time span from the remote time domain to the local one. x = local/system time when to estimate, y_delay = remote time span */
pa_usec_t pa_smoother_translate(pa_smoother *s, pa_usec_t x, pa_usec_t y_delay);

void pa_smoother_set_time_offset(pa_smoother *s, pa_usec_t x_offset);

void pa_smoother_pause(pa_smoother *s, pa_usec_t x);
void pa_smoother_resume(pa_smoother *s, pa_usec_t x);

#endif
