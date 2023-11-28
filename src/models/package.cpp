#include "package.h"

using namespace NetSim;

Package::Package(const QString &info) : m_info(info) {}

Package::Package(const QString &info, const RawData &content)
    : m_content(content), m_info(info) {}

RawData Package::content() const { return m_content; }

QString Package::info() const { return m_info; }

void Package::setContent(const RawData &content) { this->m_content = RawData(content); }

// Returns the size of a package (content + all headers)
qsizetype Package::size() const {
  return m_content.size() / 8;
}

