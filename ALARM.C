/*
 * This file was written by Brian D. Smith, however, he considers it too
 * trifling to keep any rights to it. If you find it useful, good. If not, oh
 * well, it was useful to the author.  */

/* Implementation of a rudimentary alarm() function under Borland C/Turbo C.
 *
 * The alarm() function of UNIX relies on the fact that several processes can
 * run simultaneously. DOS is flawed in this respect, and so the following
 * work around was created.
 *
 * The alarm() function takes a single input, a number of seconds before the
 * alarm goes off.  If the input is 0, the alarm is disabled.
 *
 * The check_alarm() function, when called, checks wether or not the alarm
 * should go off. If so, it raises SIGALRM, defined in "alarm.h", the method
 * used in UNIX's alarm() function.
 *
 * To use this module, include "alarm.h" in your headers, and "alarm.c" in
 * your sources.
 *
 * Definitions:
 *  SIGALRM: defined in "alarm.h"
 *  alarmval: defined in "alarm.c".
 */

#include "alarm.h"
#include <time.h>

static time_t alarmval;

alarm( delayval )
int delayval;
{
	if ( delayval != 0 )
	{
		time(&alarmval);
		alarmval += delayval;
		check_alarm();
	}
	else alarmval = 0;
}

check_alarm()
{
	time_t curval;

	if ( alarmval != 0 )
	{
		time(&curval);
		if ( curval >= alarmval ) raise( SIGALRM );
	}
}
