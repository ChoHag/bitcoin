// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
#include "config/bitcoin-config.h"
#endif

#include "compat.h"
#include "logmsg.h"
#include "util.h"

#include <stdarg.h>
#include <stdio.h>

static bool fSyslog;

int loginit (const char *ident, int option, int facility)
{
    fSyslog = GetBoolArg("-syslog", false);
#ifndef WIN32
    openlog("bitcoind", LOG_PID | LOG_CONS, LOG_DAEMON);
#endif // WIN32
}

int logmsg (int pri, const char *message, ...)
{
    int r;
    va_list ap;

    va_start(ap, message);
#ifndef WIN32
    if (fSyslog) {
	vsyslog(pri, message, ap);
	r = 0;
    } else // WARNING: Magic lack of braces with #ifndef
#endif // WIN32
	if (!(r = vfprintf(stderr, message, ap)))
	    r = fprintf(stderr, "\n");
    va_end(ap);

    return r;
}
