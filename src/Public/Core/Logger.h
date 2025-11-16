
#pragma once

#include <iostream>
#include <Core/String.h>

class Logger {
public:
	enum ELogLevel { Error, Warning, Info };

public:
	static void Log(ELogLevel level, const String& message);
	static void Log(const String& message);
	static void LogWarning(const String& message);
	static void LogError(const String& message);

private:
	ELogLevel _logLevel;

// SINGLETON
public:
	static void Initialize(ELogLevel logLevel);
private:
	static Logger* _instance;
	explicit Logger(ELogLevel logLevel);
	~Logger() = default;
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
};
