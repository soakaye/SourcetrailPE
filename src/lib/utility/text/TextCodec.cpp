#include "TextCodec.h"

#include <array>

using namespace std;

static const QStringConverter::Encoding USE_ISU = (QStringConverter::Encoding)(QStringConverter::Encoding::LastEncoding + 1);

static constexpr array AVAILABLE_ENCODINGS = {
	QStringConverter::Encoding::Utf8,
	QStringConverter::Encoding::Utf16,
	QStringConverter::Encoding::Utf16LE,
	QStringConverter::Encoding::Utf16BE,
	QStringConverter::Encoding::Utf32,
	QStringConverter::Encoding::Utf32LE,
	QStringConverter::Encoding::Utf32BE,
	QStringConverter::Encoding::Latin1,
	QStringConverter::Encoding::System,
	USE_ISU
};
static_assert(AVAILABLE_ENCODINGS.size() == QStringConverter::Encoding::LastEncoding + 2, "Encoding missing");

static QStringConverter::Encoding makeValidEncoding(const string &name)
{
	for (const auto encoding : AVAILABLE_ENCODINGS)
	{
		if (encoding != USE_ISU)
		{
			if (QStringConverter::nameForEncoding(encoding) == name)
				return encoding;
		}
	}

	QStringList availableIcuCodecs = QStringConverter::availableCodecs();
	if (availableIcuCodecs.contains(QString::fromStdString(name)))
		return USE_ISU;

	return QStringConverter::Encoding::System;
}

QStringList TextCodec::availableCodecs()
{
	QStringList availableCodecs;

	for (const auto encoding : AVAILABLE_ENCODINGS)
	{
		if (encoding != USE_ISU)
		{
			availableCodecs += QStringConverter::nameForEncoding(encoding);
		}
	}
	
	QStringList availableIcuCodecs = QStringConverter::availableCodecs();
	for (const auto &name : availableIcuCodecs) {
		if (!availableCodecs.contains(name))
			availableCodecs += name;
	}

	return availableCodecs;
}

TextCodec::TextCodec(const string &name)
{
	QStringConverter::Encoding encoding = makeValidEncoding(name);
	if (encoding == USE_ISU)
	{
		m_name = name;
		m_decoder = QStringDecoder(QString::fromStdString(name));
		m_encoder = QStringEncoder(QString::fromStdString(name));
	}
	else
	{
		m_name = QStringConverter::nameForEncoding(encoding);
		m_decoder = QStringDecoder(encoding);
		m_encoder = QStringEncoder(encoding);
	}
}

TextCodec::TextCodec(QStringConverter::Encoding encoding)
	: m_name(QStringConverter::nameForEncoding(encoding))
	, m_decoder(encoding)
	, m_encoder(encoding)
{
}

string TextCodec::decode(const string &encodedString)
{
	return decodeBytes(QByteArray::fromStdString(encodedString)).toStdString();
}

string TextCodec::encode(const string &decodedString)
{
	return encodeBytes(QString::fromStdString(decodedString)).toStdString();
}

QString TextCodec::decodeBytes(const QByteArray &encodedBytes)
{
	return static_cast<QString>(m_decoder.decode(encodedBytes));
}

QByteArray TextCodec::encodeBytes(const QString &decodedString)
{
	return static_cast<QByteArray>(m_encoder.encode(decodedString));
}

string TextCodec::getName() const
{
	return m_name;
}
