#ifndef CPLR_PRIVATE_H
#define CPLR_PRIVATE_H

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <libtcc.h>

#include <cext/list.h>
#include <cext/string.h>

/* cplr flags */
typedef enum {
   CPLR_FLAG_DUMP = 1,
   CPLR_FLAG_NORUN = 2,
   CPLR_FLAG_VERBOSE = 4,
   CPLR_FLAG_PRISTINE = 8,
} cplr_flag_t;

/* code generation state machine */
typedef enum {
   CPLR_GSTATE_INITIAL = 0,
   CPLR_GSTATE_COMMENT = 1,
   CPLR_GSTATE_INTERNAL = 2,
   CPLR_GSTATE_PREPROC = 3,
   CPLR_GSTATE_TOPLEVEL = 4,
   CPLR_GSTATE_STATEMENT = 5,
} cplr_gstate_t;

typedef struct cplr {
  /* flags */
  cplr_flag_t flag;

  /* compiler arguments */
  int    argc;
  char **argv;
  /* offset of first program argument */
  int    argp;

  /* the piles */
  lh_t defdef;
  lh_t defsys;
  lh_t sysdirs;
  lh_t incdirs;
  lh_t mlbdirs;
  lh_t libdirs;
  lh_t defs;
  lh_t syss;
  lh_t incs;
  lh_t mlbs;
  lh_t libs;
  lh_t pkgs;
  lh_t srcs;
  lh_t tlfs;
  lh_t stms;
  lh_t befs;
  lh_t afts;

  /* code generation state */
  cplr_gstate_t g_state;
  /* state for line numbering */
  int   g_prevline;
  char *g_prevfile;
  /* output streams */
  FILE *g_code;
  FILE *g_dump;
  /* stream buffers in case of memory streams */
  char *g_codebuf;
  char *g_dumpbuf;

  /* compiler state */
  TCCState *tcc;
} cplr_t;

extern cplr_t *cplr_new(void);
extern void cplr_free(cplr_t *c);

extern int cplr_optparse(cplr_t *c, int argc, char **argv);
extern int cplr_defaults(cplr_t *c);
extern int cplr_prepare(cplr_t *c);
extern int cplr_generate(cplr_t *c);
extern int cplr_compile(cplr_t *c);
extern int cplr_execute(cplr_t *c);

extern int cplr_prepare_package(cplr_t *c, const char *name);
extern int cplr_add_package(cplr_t *c, const char *name, const char *args);

#endif /* CPLR_PRIVATE_H */
