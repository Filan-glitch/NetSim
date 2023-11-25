#include "package.h"

using namespace NetSim;

Package::Package(const QString &info) : m_info(info) {}

Package::Package(const QString &info, const QBitArray &content)
    : m_content(content), m_info(info) {}

QBitArray Package::content() const { return m_content; }

QString Package::info() const { return m_info; }

void Package::setContent(const QBitArray &content) { this->m_content = content; }

// Returns the size of a package (content + all headers)
qsizetype Package::size() const {
  return m_content.size();
}

void Package::appendData(const QBitArray &data) {
  m_content.resize(m_content.size() + data.size());

  for (int i = 0; i < data.size(); i++) {
    m_content.setBit(m_content.size() - data.size() + i, data.at(i));
  }
}
