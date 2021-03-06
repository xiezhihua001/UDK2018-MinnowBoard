#ifndef sorcerer_h
#define sorcerer_h

/*
 * sorcerer.h -- header for all sorcerer files
 *
 * SOFTWARE RIGHTS
 *
 * We reserve no LEGAL rights to SORCERER -- SORCERER is in the public
 * domain.  An individual or company may do whatever they wish with
 * source code distributed with SORCERER or the code generated by
 * SORCERER, including the incorporation of SORCERER, or its output, into
 * commerical software.
 *
 * We encourage users to develop software with SORCERER.  However, we do
 * ask that credit is given to us for developing SORCERER.  By "credit",
 * we mean that if you incorporate our source code into one of your
 * programs (commercial product, research project, or otherwise) that you
 * acknowledge this fact somewhere in the documentation, research report,
 * etc...  If you like SORCERER and have developed a nice tool with the
 * output, please mention that you developed it using SORCERER.  In
 * addition, we ask that this header remain intact in our source code.
 * As long as these guidelines are kept, we expect to continue enhancing
 * this system and expect to make other tools available as they are
 * completed.
 *
 * SORCERER 1.00B
 * Terence Parr
 * AHPCRC, University of Minnesota
 * 1992-1994
 */

#include "pcctscfg.h"

#ifdef __USE_PROTOS
#include <stdlib.h>
#else
#include <malloc.h>
#endif

#include <setjmp.h>

/* SUPERCLASS SORAST (your tree must look at minimum like this)
typedef struct _node {
            struct _node *right, *down;
            int token;
      -- user-defined stuff goes here
        } SORAST;
*/

/* Can be used sort of like inheritance to get the desired struct def */
#define AST_REQD_FIELDS \
            struct _node *right, *down; \
            int token;

/* C MATCH */ /* MR21 Short circuit on null pointer */
#define _MATCH(tok)  if (! _t || _t->token!=tok ) if ( _parser->guessing ) _GUESS_FAIL; else mismatched_token(_parser, tok, _t)
#define _MATCHRANGE(tok,tok2) \
    if (! _t || _t->token<tok || _t->token>tok2 ) if ( _parser->guessing ) _GUESS_FAIL; else mismatched_range(_parser, tok, tok2, _t)

/* C++ MATCH */
#define _CPPMATCH(tok)  if ( _t->token()!=tok ) if ( _parser->guessing ) _GUESS_FAIL; else mismatched_token(_parser, tok, _t)
#define _CPPMATCHRANGE(tok,tok2) \
    if ( _t->token()<tok || _t->token()>tok2 ) if ( _parser->guessing ) _GUESS_FAIL; else mismatched_range(_parser, tok, tok2, _t)

/* Normal DOWN and RIGHT */
#define _DOWN        _t=_t->down
#define _RIGHT        _t=_t->right

/* C++ DOWN and RIGHT */
#define _CPPDOWN      _t=(SORAST *) _t->down()
#define _CPPRIGHT      _t=(SORAST *) _t->right()

#define _SAVE        SORAST *_save=_t
#define _RESTORE      _t = _save
#define  _SETLABEL(u)    u=_t
#define _WILDCARD      if ( _t==NULL ) if ( _parser->guessing ) _GUESS_FAIL; else missing_wildcard(_parser)
#define _GUESS_BLOCK    STreeParser _st; int _gv; SORAST *_savet=NULL;
#define _GUESS        {_st = *_parser; \
              _savet = _t; \
              _parser->guessing = 1; \
              _gv = setjmp(_parser->startofguess.state);}
#define _GUESS_FAIL      longjmp(_parser->startofguess.state, 1)
#define _GUESS_DONE      {*_parser = _st; _t = _savet;}

/* These are used mainly by the C output */
#ifndef ast_down
#define ast_down    down
#endif
#ifndef ast_right
#define ast_right    right
#endif

#define STreeTry(r,p,t)     \
      (p)->try_result = NULL;          \
            (p)->sjrv = setjmp((p)->startofguess);  \
            if ( !(p)->sjrv ) {            \
                rule(p,t,&try_result);        \
                (p)->try_ok = 1;          \
      }                    \
            else {                  \
                (p)->try_ok = 0;          \
      }                    \
            if ( (p)->try_ok )


/* Used only during TRANSFORM mode */
#define  TREE_CONSTR_PTRS  SORAST *_r=NULL,*_s=NULL,*_e=NULL

typedef struct _Sjmp_buf {
      jmp_buf state;
    } Sjmp_buf;

#ifndef _PARSER_VARS
#define _PARSER_VARS
#endif

#ifndef _REFVARS
#define _REFVARS
#endif

typedef struct _STreeParser {
      int try_ok, sjrv;  /* used by STreeTry macro */
      SORAST *try_result;  /* tree coming back from try */
      int guessing;
      Sjmp_buf startofguess;
      SORAST *t;
      _REFVARS
      _PARSER_VARS
    } STreeParser;

#define STreeParserInit(_p) { (_p)->guessing = 0; _refvar_inits(_p); }


        /* S a n i t y  C h e c k i n g */

#ifndef require
#define require(expr, err) {if ( !(expr) ) sorcerer_panic(err);}
#endif


               /* T r a n s f o r m  M a c r o s */
#define ast_return(_t)  *_result = _t


#ifdef __USE_PROTOS
extern void mismatched_range(STreeParser *_parser, int looking_for, int upper_token, SORAST *found);
extern void missing_wildcard(STreeParser *_parser);
extern void mismatched_token(STreeParser *_parser, int looking_for, SORAST *found);
extern void no_viable_alt(STreeParser *_parser, char *rulename, SORAST *root);
extern void sorcerer_panic(char *err);
extern void _refvar_inits(STreeParser *);    /* MR15 Kevin J. Cummings */
extern void _mkroot(SORAST **, SORAST **, SORAST **, SORAST *);
extern void _mkchild(SORAST **, SORAST **, SORAST **, SORAST *);
extern SORAST *ast_alloc(void);
extern SORAST *ast_dup(SORAST *t);
extern SORAST *ast_dup_node(SORAST *t);
#else
extern void mismatched_range();
extern void missing_wildcard();
extern void mismatched_token();
extern void no_viable_alt();
extern void sorcerer_panic();
extern void _refvar_inits();    /* MR15 Kevin J. Cummings */
extern void _mkroot();
extern void _mkchild();
extern SORAST *ast_alloc();
extern SORAST *ast_dup();
extern SORAST *ast_dup_node();
#endif

#endif
