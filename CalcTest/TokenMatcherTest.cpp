#include "TokenMatcherTest.h"

TokenMatcherFicture::TokenMatcherFicture() {
}

TokenMatcherFicture::~TokenMatcherFicture() {
}

BOOST_FIXTURE_TEST_SUITE(TokenMatcherTestSuite, TokenMatcherFicture)

BOOST_AUTO_TEST_CASE(TokenMatcherTest_isNumberStart_method) {
	BOOST_CHECK_EQUAL(true, TokenMatcher(TokenizerContext("323")).isNumberStart());
	BOOST_CHECK_EQUAL(true, TokenMatcher(TokenizerContext(".323")).isNumberStart());
	BOOST_CHECK_EQUAL(false, TokenMatcher(TokenizerContext(".e323")).isNumberStart());
}

BOOST_AUTO_TEST_CASE(TokenMatcherTest_isWordStart_method) {
	BOOST_CHECK_EQUAL(true, TokenMatcher(TokenizerContext("dsadsads")).isWordStart());
	BOOST_CHECK_EQUAL(true, TokenMatcher(TokenizerContext("____Dsadsa2")).isWordStart());
	BOOST_CHECK_EQUAL(false, TokenMatcher(TokenizerContext("2_e323")).isWordStart());
}

BOOST_AUTO_TEST_CASE(TokenMatcherTest_isWhitespaceStart_method) {
	BOOST_CHECK_EQUAL(true, TokenMatcher(TokenizerContext(" ")).isSpaceStart());
	BOOST_CHECK_EQUAL(true, TokenMatcher(TokenizerContext("\n")).isNewLineStart());
	BOOST_CHECK_EQUAL(true, TokenMatcher(TokenizerContext("\t")).isSpaceStart());
}

BOOST_AUTO_TEST_CASE(TokenMatcherTest_is_comment_start_methods) {
	BOOST_CHECK_EQUAL(true, TokenMatcher(TokenizerContext("//test")).isSingleLineCommentStart());
	BOOST_CHECK_EQUAL(true, TokenMatcher(TokenizerContext("%comment")).isSingleLineCommentStart());
	BOOST_CHECK_EQUAL(false, TokenMatcher(TokenizerContext("/")).isSingleLineCommentStart());
	BOOST_CHECK_EQUAL(false, TokenMatcher(TokenizerContext("%{")).isSingleLineCommentStart());
	BOOST_CHECK_EQUAL(true, TokenMatcher(TokenizerContext("%{")).isMultiLineCommentStart());
}

BOOST_AUTO_TEST_SUITE_END()