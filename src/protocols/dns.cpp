#include "dns.h"

void DNS::initDNSRequest(Package &data, const QList<DNSEntry> queries) {
  HeaderAttribute transactionID(
      "Transaction ID", 16,
      static_cast<quint16>(QRandomGenerator::global()->generate() % 0xFFFF));
  HeaderAttribute _questions("Questions", 16,
                             static_cast<quint16>(queries.size()));
  HeaderAttribute _answerRRs("Answer RRs", 16, static_cast<quint16>(0));

  HeaderAttribute _flags("Flags", 16, static_cast<quint16>(0));

  QList<HeaderAttribute> headerList;

  headerList.append(transactionID);
  headerList.append(_flags);
  headerList.append(_questions);
  headerList.append(_answerRRs);

  for (auto i = 0; i < queries.size(); i++) {
    QByteArray queryData = queries.at(i).name().toLatin1();
    queryData = queryData.append('\0');
    QVector<quint8> queryDataVector;
    for (auto i = 0; i < queryData.length(); i++) {
      queryDataVector.append(static_cast<quint8>(queryData.at(i)));
    }
    queryDataVector.append(queries.at(i).type() >> 8);
    queryDataVector.append(queries.at(i).type() & 0xFF);
    queryDataVector.append(queries.at(i).dnsClass() >> 8);
    queryDataVector.append(queries.at(i).dnsClass() & 0xFF);

    HeaderAttribute query("Query " + QString::number(i),
                          queryDataVector.size() * 8, queryDataVector);
    headerList.append(query);
  }

  Header dnsHeader(NetSim::HeaderType::DNS, headerList);
  data.addHeader(dnsHeader);
}

void DNS::initDNSResponse(Package &data, const QList<DNSEntry> queries,
                          const QList<DNSEntry> answers, bool nxDomain) {
  HeaderAttribute transactionID(
      "Transaction ID", 16,
      static_cast<quint16>(QRandomGenerator::global()->generate() % 0xFFFF));

  HeaderAttribute _questions("Questions", 16,
                             static_cast<quint16>(queries.size()));
  HeaderAttribute _answerRRs("Answer RRs", 16,
                             static_cast<quint16>(answers.size()));

  quint16 flagsVal = 0;
  setFlag(&flagsVal, true, 15);
  if (nxDomain) {
    setFlag(&flagsVal, true, 0);
    setFlag(&flagsVal, true, 1);
  }
  HeaderAttribute _flags("Flags", 16, flagsVal);

  QList<HeaderAttribute> headerList;
  headerList.append(transactionID);
  headerList.append(_flags);
  headerList.append(_questions);
  headerList.append(_answerRRs);

  for (auto i = 0; i < queries.size(); i++) {
    QByteArray queryData = queries.at(i).name().toLatin1();
    queryData = queryData.append('\0');
    QVector<quint8> queryDataVector;
    for (auto i = 0; i < queryData.length(); i++) {
      queryDataVector.append(static_cast<quint8>(queryData.at(i)));
    }
    queryDataVector.append(queries.at(i).type() >> 8);
    queryDataVector.append(queries.at(i).type() & 0xFF);
    queryDataVector.append(queries.at(i).dnsClass() >> 8);
    queryDataVector.append(queries.at(i).dnsClass() & 0xFF);

    HeaderAttribute query("Query " + QString::number(i),
                          queryDataVector.size() * 8, queryDataVector);
    headerList.append(query);
  }

  for (auto i = 0; i < answers.size(); i++) {
    QByteArray answerData = answers.at(i).name().toLatin1().append('\0');
    QVector<quint8> answerDataVector;
    for (auto i = 0; i < answerData.length(); i++) {
      answerDataVector.append(static_cast<quint8>(answerData.at(i)));
    }
    answerDataVector.append(answers.at(i).type() >> 8);
    answerDataVector.append(answers.at(i).type() & 0xFF);
    answerDataVector.append(answers.at(i).dnsClass() >> 8);
    answerDataVector.append(answers.at(i).dnsClass() & 0xFF);
    answerDataVector.append(answers.at(i).ttl() >> 24);
    answerDataVector.append(answers.at(i).ttl() >> 16 & 0xFF);
    answerDataVector.append(answers.at(i).ttl() >> 8 & 0xFF);
    answerDataVector.append(answers.at(i).ttl() & 0xFF);
    answerDataVector.append(answers.at(i).dataLength() >> 8);
    answerDataVector.append(answers.at(i).dataLength() & 0xFF);
    answerDataVector.append(answers.at(i).data());

    HeaderAttribute answer("Answer " + QString::number(i),
                           answerDataVector.size() * 8, answerDataVector);
    headerList.append(answer);
  }

  Header dnsHeader(NetSim::HeaderType::DNS, headerList);
  data.addHeader(dnsHeader);
}

void DNS::setFlag(quint16 *flags, bool set, quint8 position) {
  if (set) {
    *flags |= (1 << position);
  } else {
    *flags &= ~(1 << position);
  }
}

QVector<quint8> DNS::stringToArray(const QString &string) {
  QVector<quint8> array;
  for (auto i = 0; i < string.length(); i++) {
    array.append(string.at(i).toLatin1());
  }
  return array;
}
