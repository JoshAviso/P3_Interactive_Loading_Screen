#include <Core/Logger.h>

void Logger::Log(ELogLevel level, const String & message) {
	if (_instance == nullptr) return;
	if (level < _instance->_logLevel) return;
	String prefix;
	switch (level) {
	case ELogLevel::Error:   prefix = "\033[31m[ERROR]:\033[0m "; break;
	case ELogLevel::Warning: prefix = "\033[33m[WARN]:\033[0m "; break;
	case ELogLevel::Info:    prefix = "\033[36m[INFO]:\033[0m "; break;
	}
	std::cout << prefix << message << std::endl;
};
void Logger::Log(const String& message) {
	Log(ELogLevel::Info, message);
};
void Logger::LogWarning(const String& message) {
	Log(ELogLevel::Warning, message);
};
void Logger::LogError(const String& message) {
	Log(ELogLevel::Error, message);
};

// SINGLETON
Logger* Logger::_instance = nullptr;
void Logger::Initialize(ELogLevel logLevel)
{
	if (_instance != nullptr) return;
	_instance = new Logger(logLevel);
};
Logger::Logger(ELogLevel logLevel) {
	_logLevel = logLevel;
};
