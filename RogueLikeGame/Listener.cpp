#include "Listener.hpp"

Listener::~Listener()
{
}

void Listener::report(std::string message)
{
  m_strMessages.resize(5);
  m_strMessages.pop_back();
  m_strMessages.push_front(message);
}

