/*
 * Copyright (c) 1997, 1998, 1999
 *      Inferno Nettverk A/S, Norway.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. The above copyright notice, this list of conditions and the following
 *    disclaimer must appear in all copies of the software, derivative works
 *    or modified versions, and any portions thereof, aswell as in all
 *    supporting documentation.
 * 2. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by
 *      Inferno Nettverk A/S, Norway.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Inferno Nettverk A/S requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  sdc@inet.no
 *  Inferno Nettverk A/S
 *  Oslo Research Park
 *  Gaustadal�en 21
 *  N-0349 Oslo
 *  Norway
 *
 * any improvements or extensions that they make and grant Inferno Nettverk A/S
 * the rights to redistribute these changes.
 *
 */

#include "common.h"

#if HAVE_EXTRA_OSF_SYMBOLS

#if SOCKSLIBRARY_DYNAMIC

#include "interposition.h"

static const char rcsid[] =
"$Id: int_osf1.c,v 1.4 1999/07/08 18:54:41 karls Exp $";

#undef accept
#undef getpeername
#undef getsockname
#undef readv
#undef recvfrom
#undef recvmsg
#undef sendmsg
#undef writev

	/* the system calls. */

int
sys_Eaccept(s, addr, addrlen)
	int s;
	struct sockaddr * addr;
	socklen_t *addrlen;
{
	int rc;
	int (*function)(int s, struct sockaddr * addr, socklen_t *addrlen);

	SYSCALL_START(s);
	function = symbolfunction(SYMBOL_EACCEPT);
	rc = function(s, addr, addrlen);
	SYSCALL_END(s);
	return rc;
}

int
sys_Egetpeername(s, name, namelen)
	int s;
	struct sockaddr * name;
	socklen_t *namelen;
{
	int rc;
	int (*function)(int s, const struct sockaddr * name, socklen_t *namelen);

	SYSCALL_START(s);
	function = symbolfunction(SYMBOL_EGETPEERNAME);
	rc = function(s, name, namelen);
	SYSCALL_END(s);
	return rc;
}

int
sys_Egetsockname(s, name, namelen)
	int s;
	struct sockaddr * name;
	socklen_t *namelen;
{
	int rc;
	int (*function)(int s, const struct sockaddr * name, socklen_t *namelen);

	SYSCALL_START(s);
	function = symbolfunction(SYMBOL_EGETSOCKNAME);
	rc = function(s, name, namelen);
	SYSCALL_END(s);
	return rc;
}
ssize_t
sys_Ereadv(d, iov, iovcnt)
	int d;
	const struct iovec *iov;
	int iovcnt;
{
	ssize_t rc;
	int (*function)(int d, const struct iovec *iov, int iovcnt);

	SYSCALL_START(d);
	function = symbolfunction(SYMBOL_EREADV);
	rc = function(d, iov, iovcnt);
	SYSCALL_END(d);
	return rc;
}

int
sys_Erecvfrom(s, buf, len, flags, from, fromlen)
	int s;
	void *buf;
	size_t len;
	int flags;
	struct sockaddr * from;
	size_t *fromlen;
{
	int rc;
	int (*function)(int s, void *buf, size_t len, int flags,
					    struct sockaddr * from, socklen_t *fromlen);

	SYSCALL_START(s);
	function = symbolfunction(SYMBOL_ERECVFROM);
	rc = function(s, buf, len, flags, from, fromlen);
	SYSCALL_END(s);
	return rc;
}

ssize_t
sys_Erecvmsg(s, msg, flags)
	int s;
	struct msghdr *msg;
	int flags;
{
	ssize_t rc;
	int (*function)(int s, struct msghdr *msg, int flags);

	SYSCALL_START(s);
	function = symbolfunction(SYMBOL_ERECVMSG);
	rc = function(s, msg, flags);
	SYSCALL_END(s);
	return rc;
}

ssize_t
sys_Esendmsg(s, msg, flags)
	int s;
	const struct msghdr *msg;
	int flags;
{
	ssize_t rc;
	int (*function)(int s, const struct msghdr *msg, int flags);

	SYSCALL_START(s);
	function = symbolfunction(SYMBOL_ESENDMSG);
	rc = function(s, msg, flags);
	SYSCALL_END(s);
	return rc;
}


ssize_t
sys_Ewritev(d, iov, iovcnt)
	int d;
	const struct iovec *iov;
	int iovcnt;
{
	ssize_t rc;
	int (*function)(int d, const struct iovec *buf, int iovcnt);

	SYSCALL_START(d);
	function = symbolfunction(SYMBOL_EWRITEV);
	rc = function(d, iov, iovcnt);
	SYSCALL_END(d);
	return rc;
}

	/*
	 * the interpositioned functions.
	*/


int
Eaccept(s, addr, addrlen)
	int s;
	struct sockaddr * addr;
	socklen_t *addrlen;
{
	if (ISSYSCALL(s))
		return sys_Eaccept(s, addr, addrlen);
	return Raccept(s, addr, addrlen);
}
int
Egetpeername(s, name, namelen)
	int s;
	struct sockaddr * name;
	socklen_t *namelen;
{
	if (ISSYSCALL(s))
		return sys_Egetpeername(s, name, namelen);
	return Rgetpeername(s, name, namelen);
}

int
Egetsockname(s, name, namelen)
	int s;
	struct sockaddr * name;
	socklen_t *namelen;
{
	if (ISSYSCALL(s))
		return sys_Egetpeername(s, name, namelen);
	return Rgetsockname(s, name, namelen);
}


ssize_t
Ereadv(d, iov, iovcnt)
	int d;
	const struct iovec *iov;
	int iovcnt;
{
	if (ISSYSCALL(d))
		return sys_Ereadv(d, iov, iovcnt);
	return Rreadv(d, iov, iovcnt);
}


ssize_t
Erecvfrom(s, buf, len, flags, from, fromlen)
	int s;
	void *buf;
	size_t len;
	int flags;
	struct sockaddr * from;
	size_t *fromlen;
{
	if (ISSYSCALL(s))
		return sys_Erecvfrom(s, buf, len, flags, from, fromlen);
	return Rrecvfrom(s, buf, len, flags, from, fromlen);
}

ssize_t
Erecvmsg(s, msg, flags)
	int s;
	struct msghdr *msg;
	int flags;
{
	if (ISSYSCALL(s))
		return sys_Erecvmsg(s, msg, flags);
	return Rrecvmsg(s, msg, flags);
}



ssize_t
Ewritev(d, iov, iovcnt)
	int d;
	const struct iovec *iov;
	int iovcnt;
{
	if (ISSYSCALL(d))
		return sys_Ewritev(d, iov, iovcnt);
	return Rwritev(d, iov, iovcnt);
}

ssize_t
Esendmsg(s, msg, flags)
	int s;
	const struct msghdr *msg;
	int flags;
{
	if (ISSYSCALL(s))
		return sys_Esendmsg(s, msg, flags);
	return Rsendmsg(s, msg, flags);
}

#endif /* SOCKSLIBRARY_DYNAMIC */

#endif /* HAVE_EXTRA_OSF_SYMBOLS */