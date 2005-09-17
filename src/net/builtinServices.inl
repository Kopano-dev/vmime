//
// VMime library (http://www.vmime.org)
// Copyright (C) 2002-2005 Vincent Richard <vincent@vincent-richard.net>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
// Linking this library statically or dynamically with other modules is making
// a combined work based on this library.  Thus, the terms and conditions of
// the GNU General Public License cover the whole combination.
//

#ifndef VMIME_BUILDING_DOC


#define REGISTER_SERVICE(p_class, p_name) \
	vmime::net::service::initializer <vmime::net::p_class> p_name(#p_name)


#if VMIME_BUILTIN_MESSAGING_PROTO_POP3
	#include "vmime/net/pop3/POP3Store.hpp"
	REGISTER_SERVICE(pop3::POP3Store, pop3);
#endif


#if VMIME_BUILTIN_MESSAGING_PROTO_SMTP
	#include "vmime/net/smtp/SMTPTransport.hpp"
	REGISTER_SERVICE(smtp::SMTPTransport, smtp);
#endif


#if VMIME_BUILTIN_MESSAGING_PROTO_IMAP
	#include "vmime/net/imap/IMAPStore.hpp"
	REGISTER_SERVICE(imap::IMAPStore, imap);
#endif


#if VMIME_BUILTIN_MESSAGING_PROTO_MAILDIR
	#include "vmime/net/maildir/maildirStore.hpp"
	REGISTER_SERVICE(maildir::maildirStore, maildir);
#endif

#if VMIME_BUILTIN_MESSAGING_PROTO_SENDMAIL
	#include "vmime/net/sendmail/sendmailTransport.hpp"
	REGISTER_SERVICE(sendmail::sendmailTransport, sendmail);
#endif


#endif // VMIME_BUILDING_DOC
