/**
 * threadpool_test.c, copyright 2001 Steve Gribble
 *
 * Just a regression test for the threadpool code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include "threadpool.h"

#include "spthread.h"

extern int errno;

void mylog( FILE * fp, const  char  *format,  /*args*/ ...)
{
	va_list ltVaList;
	va_start( ltVaList, format );
	vprintf( format, ltVaList );
	va_end( ltVaList );

	fflush( stdout );
}

void dispatch_threadpool_to_me(void *arg) {
  int seconds = (int) arg;

  fprintf(stdout, "  in dispatch_threadpool %d\n", seconds);
  fprintf(stdout, "  thread#%ld\n", sp_thread_self() );
  sp_sleep(seconds);
  fprintf(stdout, "  done dispatch_threadpool %d\n", seconds);
}

int main(int argc, char **argv) {
  threadpool tp;

  tp = create_threadpool(2);

  fprintf(stdout, "**main** dispatch_threadpool 3\n");
  dispatch_threadpool(tp, dispatch_threadpool_to_me, (void *) 3);
  fprintf(stdout, "**main** dispatch_threadpool 6\n");
  dispatch_threadpool(tp, dispatch_threadpool_to_me, (void *) 6);
  fprintf(stdout, "**main** dispatch_threadpool 7\n");
  dispatch_threadpool(tp, dispatch_threadpool_to_me, (void *) 7);

  fprintf(stdout, "**main** done first\n");
  sp_sleep(20);
  fprintf(stdout, "\n\n");

  fprintf(stdout, "**main** dispatch_threadpool 3\n");
  dispatch_threadpool(tp, dispatch_threadpool_to_me, (void *) 3);
  fprintf(stdout, "**main** dispatch_threadpool 6\n");
  dispatch_threadpool(tp, dispatch_threadpool_to_me, (void *) 6);
  fprintf(stdout, "**main** dispatch_threadpool 7\n");
  dispatch_threadpool(tp, dispatch_threadpool_to_me, (void *) 7);

  fprintf(stdout, "**main done second\n");

  destroy_threadpool( tp );

  //sp_sleep(20);
  return -1;
}

