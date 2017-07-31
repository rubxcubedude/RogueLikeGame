#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <list>
class Listener
{
  private:
    Listener(){};
    Listener(Listener const& copy);
    Listener& operator=(Listener const& copy);

    std::list<std::string> m_strMessages;
  public:
    ~Listener();
    static Listener& Instance()
    {
      static Listener instance;
      return instance;
    };

    void report(std::string message);

    std::list<std::string> getMessages(void);
};

inline std::list<std::string> Listener::getMessages()
{
  return m_strMessages;
}
#endif
