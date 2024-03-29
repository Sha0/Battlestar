/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef lint
/*static char sccsid[] = "from: @(#)room.c	5.3 (Berkeley) 6/1/90";*/
static char rcsid[] = "room.c,v 1.2 1993/08/01 18:55:54 mycroft Exp";
#endif /* not lint */

#include "externs.h"

void writedes(void)
{
	int compass;
	register char *p;
	register int c;

	(void) rcsid;

	printf("\n\t%s\n", location[position].name);
	if (beenthere[position] < 3) {
		compass = NORTH;
		for (p = location[position].desc; (c = *p++);)
			if (c != '-' && c != '*' && c != '+')
				putchar(c);
			else {
				if (c != '*')
					printf(truedirec(compass, c));
				compass++;
			}
	}
}

void printobjs(void)
{
	register unsigned int *p = location[position].objects;
	register int n;

	printf("\n");
	for (n = 0; n < NUMOFOBJECTS; n++)
		if (testbit(p, n) && objdes[n])
			puts(objdes[n]);
}

void whichway(struct room here)
{
	switch(direction) {

		case NORTH:
			left = here.west;
			right = here.east;
			ahead = here.north;
			back = here.south;
			break;
		
		case SOUTH:
			left = here.east;
			right = here.west;
			ahead = here.south;
			back = here.north;
			break;

		case EAST:
			left = here.north;
			right = here.south;
			ahead = here.east;
			back = here.west;
			break;

		case WEST:
			left = here.south;
			right = here.north;
			ahead = here.west;
			back = here.east;
			break;

	}
}

char *
truedirec(way, option)
int way;
char option;
{
	switch(way) {

		case NORTH:
			switch(direction) {
				case NORTH:
					return("ahead");
				case SOUTH:
					return(option == '+' ? "behind you" : "back");
				case EAST:
					return("left");
				case WEST:
					return("right");
			}

		case SOUTH:
			switch(direction) {
				case NORTH:
					return(option == '+' ? "behind you" : "back");
				case SOUTH:
					return("ahead");
				case EAST:
					return("right");
				case WEST:
					return("left");
			}

		case EAST:
			switch(direction) {
				case NORTH:
					return("right");
				case SOUTH:
					return("left");
				case EAST:
					return("ahead");
				case WEST:	
					return(option == '+' ? "behind you" : "back");
			}

		case WEST:
			switch(direction) {
				case NORTH:
					return("left");
				case SOUTH:
					return("right");
				case EAST:
					return(option == '+' ? "behind you" : "back");
				case WEST:
					return("ahead");
			}

		default:
			printf("Error: room %d.  More than four directions wanted.", position);
			return("!!");
      }
}

void newway(int thisway)
{
	switch(direction){

		case NORTH:
			switch(thisway){
				case LEFT:
					direction = WEST;
					break;
				case RIGHT:
					direction = EAST;
					break;
				case BACK:
					direction = SOUTH;
					break;
			}
			break;
		case SOUTH:
			switch(thisway){
				case LEFT:
					direction = EAST;
					break;
				case RIGHT:
					direction = WEST;
					break;
				case BACK:
					direction = NORTH;
					break;
			}
			break;
		case EAST:
			switch(thisway){
				case LEFT:
					direction = NORTH;
					break;
				case RIGHT:
					direction = SOUTH;
					break;
				case BACK:
					direction = WEST;
					break;
			}
			break;
		case WEST:
			switch(thisway){
				case LEFT:
					direction = SOUTH;
					break;
				case RIGHT:
					direction = NORTH;
					break;
				case BACK:
					direction = EAST;
					break;
			}
			break;
      }
}
