#include "Logging.hpp"

Logging::Logging(Messenger* messenger)
{
	m_messenger = messenger;
}

bool Logging::send()
{
	if (m_queue.size() < 1)
	{
		return true;
	}
	
	String msg = m_queue.front();
	bool result = m_messenger->post_request("/log", msg.c_str(), msg.length());
	if (result)
	{
		m_queue.pop();
	}
	return result;
}

void Logging::encode(String& msg)
{
	for (int i = 0; i < msg.length(); i++)
	{
		if (msg[i] == ' ')
		{
			msg[i] = '+';
		}
	}
}

void Logging::log(const String& level, const String& msg)
{
	if (m_queue.size() < MAX_SIZE)
	{
		String msg = "level=" + level + "&msg=" + msg;
		encode(msg);
		m_queue.push(msg);
	}
}

void Logging::debug(const String& msg)
{
	log(DEBUG, msg);
}

void Logging::info(const String& msg)
{
	log(INFO, msg);
}

void Logging::warn(const String& msg)
{
	log(WARN, msg);
}

void Logging::error(const String& msg)
{
	log(ERROR, msg);
}
