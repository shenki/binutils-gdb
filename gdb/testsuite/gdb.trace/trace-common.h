/* This testcase is part of GDB, the GNU debugger.

   Copyright 2011-2015 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifdef SYMBOL_PREFIX
#define SYMBOL(str)     SYMBOL_PREFIX #str
#else
#define SYMBOL(str)     #str
#endif

/* TRACEPOINT_ASM expands to an assembly instruction large enough to fit
   a fast tracepoint jump.  The parameter is the label where we'll set
   tracepoints and breakpoints.  */

#if (defined __x86_64__ || defined __i386__)

static void
x86_trace_dummy ()
{
  int x = 0;
  int y = x + 4;
}

#define TRACEPOINT_ASM(name) \
  asm ("    .global " SYMBOL(name) "\n" \
       SYMBOL(name) ":\n" \
       "    call " SYMBOL(x86_trace_dummy) "\n" \
       )

#elif (defined __aarch64__)

#define TRACEPOINT_ASM(name) \
  asm ("    .global " SYMBOL(name) "\n" \
       SYMBOL(name) ":\n" \
       "    nop\n" \
       )

#else

#error "unsupported architecture for trace tests"

#endif
