//
// VMime library (http://www.vmime.org)
// Copyright (C) 2002 Vincent Richard <vincent@vmime.org>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3 of
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

#include "tests/testUtils.hpp"


VMIME_TEST_SUITE_BEGIN(bodyTest)

	VMIME_TEST_LIST_BEGIN
		VMIME_TEST(testGenerate_Mailbox)
		VMIME_TEST(testGenerate_Text)
		VMIME_TEST(testGenerate_NonText)
	VMIME_TEST_LIST_END

	void testGenerate_Mailbox() {
		using namespace vmime;

		// Check that ASCII display names are not encoded more than necessary
		emailAddress e("a@b.com");
		auto a = make_shared<mailbox>(text(word("Foo B@r", charsets::US_ASCII)), e);
		VASSERT_EQ("generate", "\"Foo B@r\" <a@b.com>", a->generate());
		VASSERT_NEQ("generate", "=?utf-8?Q?Foo_B=40r?= <a@b.com>", a->generate());

		a = make_shared<mailbox>(text(word("Foo B@r", charsets::UTF_8)), e);
		VASSERT_EQ("generate", "=?utf-8?Q?Foo_B=40r?= <a@b.com>", a->generate());
	}

	void testGenerate_Text() {

		// RFC-2015: [Quoted-Printable encoding] A line break in a text body,
		// represented as a CRLF sequence in the text canonical form, must be
		// represented by a line break which is also a CRLF sequence, in the
		// Quoted-Printable encoding

		vmime::bodyPart p;
		p.getBody()->setContents(
			vmime::make_shared <vmime::stringContentHandler>(
				"Foo éé\r\né bar\r\nbaz"
			),
			vmime::mediaType("text", "plain"),
			vmime::charset("utf-8"),
			vmime::encoding("quoted-printable")
		);

		VASSERT_EQ(
			"generate",
			"Foo =C3=A9=C3=A9\r\n"
			"=C3=A9 bar\r\n"
			"baz",
			p.getBody()->generate()
		);
	}

	void testGenerate_NonText() {

		vmime::bodyPart p;
		p.getBody()->setContents(
			vmime::make_shared <vmime::stringContentHandler>(
				"Binary\xfa\xfb\r\ndata\r\n\r\n\xfc"
			),
			vmime::mediaType("application", "octet-stream"),
			vmime::charset("utf-8"),
			vmime::encoding("quoted-printable")
		);

		VASSERT_EQ(
			"generate",
			"Binary=FA=FB=0D=0Adata=0D=0A=0D=0A=FC",
			p.getBody()->generate()
		);
	}

VMIME_TEST_SUITE_END
