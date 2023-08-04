#include "dns.h"

void DNS::initDNSRequest(Package &data, const QList<DNSEntry> queries)
{
    HeaderAttribute transactionID("Transaction ID", 16, static_cast<quint16>(QRandomGenerator::global()->generate() % 0xFFFF));
    HeaderAttribute _questions("Questions", 16,  static_cast<quint16>(queries.size()));
    HeaderAttribute _answerRRs("Answer RRs", 16,  static_cast<quint16>(0));
    HeaderAttribute _authorityRRs("Authority RRs", 16, static_cast<quint16>(0));
    HeaderAttribute _additionalRRs("Additional RRs", 16, static_cast<quint16>(0));

    HeaderAttribute _flags("Flags", 16, static_cast<quint16>(0));

    QList<HeaderAttribute> headerList;

    headerList.append(transactionID);
    headerList.append(_flags);
    headerList.append(_questions);
    headerList.append(_answerRRs);
    headerList.append(_authorityRRs);
    headerList.append(_additionalRRs);

    for(auto i = 0; i < queries.size(); i++) {
        HeaderAttribute query("Query " + QString::number(i), queries.at(i).getName().toLatin1().length()*8 + 32, queries.at(i).getName().toLatin1() + QString::number(queries.at(i).getType()) + QString::number(queries.at(i).getDnsClass()));
        headerList.append(query);
    }

    Header dnsHeader(HeaderType::DNS, headerList);
    data.addHeader(dnsHeader);
}

void DNS::initDNSResponse(Package &data, const QList<DNSEntry> queries, const QList<DNSEntry> answers, const QList<DNSEntry> authoritativeNameservers, const QList<DNSEntry> additionalRecords)
{
    HeaderAttribute transactionID("Transaction ID", 16, static_cast<quint16>(QRandomGenerator::global()->generate() % 0xFFFF));

    HeaderAttribute _questions("Questions", 16, static_cast<quint16>(queries.size()));
    HeaderAttribute _answerRRs("Answer RRs", 16,  static_cast<quint16>(answers.size()));
    HeaderAttribute _authorityRRs("Authority RRs", 16,  static_cast<quint16>(authoritativeNameservers.size()));
    HeaderAttribute _additionalRRs("Additional RRs", 16,  static_cast<quint16>(additionalRecords.size()));

    quint16 flagsVal = 0;
    setFlag(&flagsVal, true, 15);
    HeaderAttribute _flags("Flags", 16, flagsVal);

    QList<HeaderAttribute> headerList;
    headerList.append(transactionID);
    headerList.append(_flags);
    headerList.append(_questions);
    headerList.append(_answerRRs);
    headerList.append(_authorityRRs);
    headerList.append(_additionalRRs);

    for(auto i = 0; i < queries.size(); i++) {
        //QVector<quint8> queryData = stringToArray(name);
        HeaderAttribute query("Query " + QString::number(i), queries.at(i).getName().toLatin1().length()*8 + 48, queries.at(i).getName().toLatin1() + QString::number(queries.at(i).getType()) + QString::number(queries.at(i).getDnsClass()));
        headerList.append(query);
    }

    for(auto i = 0; i < answers.size(); i++) {
        HeaderAttribute answer("Answer " + QString::number(i), answers.at(i).getName().toLatin1().length()*8 + 32, answers.at(i).getName() + QString::number(answers.at(i).getType()) + QString::number(answers.at(i).getDnsClass()));
        headerList.append(answer);
    }

    for(auto i = 0; i < authoritativeNameservers.size(); i++) {
        HeaderAttribute authoritativeNameserver("Authoritative Nameserver " + QString::number(i), authoritativeNameservers.at(i).getName().toLatin1().length()*8 + 32, authoritativeNameservers.at(i).getName() + QString::number(authoritativeNameservers.at(i).getType()) + QString::number(authoritativeNameservers.at(i).getDnsClass()));
        headerList.append(authoritativeNameserver);
    }

    for(auto i = 0; i < additionalRecords.size(); i++) {
        HeaderAttribute additionalRecord("Additional Record " + QString::number(i), additionalRecords.at(i).getName().toLatin1().length()*8 + 32, additionalRecords.at(i).getName() + QString::number(additionalRecords.at(i).getType()) + QString::number(additionalRecords.at(i).getDnsClass()));
        headerList.append(additionalRecord);
    }

    Header dnsHeader(HeaderType::DNS, headerList);
    data.addHeader(dnsHeader);
}

void DNS::setFlag(quint16* flags, bool set, quint8 position){
    if (set) {
        // sets the bit at position
        *flags |= (1 << position);
    } else {
        // deletes the bit at position
        *flags &= ~(1 << position);
    }
}

QVector<quint8> DNS::stringToArray(const QString &string) {
    QVector<quint8> array;
    for(auto i = 0; i < string.length(); i++) {
        array.append(string.at(i).toLatin1());
    }
    return array;
}
