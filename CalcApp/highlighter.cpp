#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
	: QSyntaxHighlighter(parent)
{
	HighlightingRule rule;

	keywordFormat.setForeground(Qt::darkBlue);
	keywordFormat.setFontWeight(QFont::Bold);
	QStringList keywordPatterns;
	
	keywordPatterns << "\\bwhile\\b" << "\\bfor\\b" << "\\bend\\b" << "\\bif\\b" << "\\belse\\b" << "\\bfunction\\b"
		<< "\\bendfor\\b" << "\\bendwhile\\b" << "\\bendif\\b" << "\\bendfunction\\b" << "\\belseif\\b" << "\\breturn\\b"
		<< "\\bcontinue\\b" << "\\bbreak\\b";
	
	foreach(const QString &pattern, keywordPatterns) 
	{
		rule.pattern = QRegExp(pattern);
		rule.format = keywordFormat;
		highlightingRules.append(rule);
	}

	singleLineCommentFormat.setForeground(Qt::darkGreen);
	rule.pattern = QRegExp("(//|%)[^\\n\\r%\\}]*");
	rule.format = singleLineCommentFormat;
	highlightingRules.append(rule);



	multiLineCommentFormat.setForeground(Qt::darkGreen);
	commentStartExpression = QRegExp("%\\{");
	commentEndExpression = QRegExp("%\\}");
}

Highlighter::~Highlighter()
{
	
}

void Highlighter::highlightBlock(const QString &text)
{
	foreach(const HighlightingRule &rule, highlightingRules) 
	{
		QRegExp expression(rule.pattern);
		int index = expression.indexIn(text);
		while (index >= 0) 
		{
			int length = expression.matchedLength();
			setFormat(index, length, rule.format);
			index = expression.indexIn(text, index + length);
		}
	}

	setCurrentBlockState(0);

	int startIndex = 0;
	if (previousBlockState() != 1)
		startIndex = commentStartExpression.indexIn(text);

	while (startIndex >= 0) {
		int endIndex = commentEndExpression.indexIn(text, startIndex);
		int commentLength;
		if (endIndex == -1) {
			setCurrentBlockState(1);
			commentLength = text.length() - startIndex;
		}
		else {
			commentLength = endIndex - startIndex
				+ commentEndExpression.matchedLength();
		}
		setFormat(startIndex, commentLength, multiLineCommentFormat);
		startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
	}
}