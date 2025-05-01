//
// Created by Roman Maximov on 01.05.2025.
// License: MIT License.
// Copyright (c) 2024 Roman Maximov.
//

#ifndef LOGERRORS_H
#define LOGERRORS_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define LOG_ERROR(msg) logError(__FILE__, __func__, __LINE__, msg)
#define LOG_INFO(fmt, ...) logInfo(__func__, fmt, ##__VA_ARGS__)

void logError(const char* file, const char* func, int line, const char* message) {
    FILE* logFile = fopen("logs.txt", "a");

    if (logFile == NULL) {
        perror("Не удалось открыть logs.txt");
        return;
    }

    time_t now = time(NULL);
    char* timeStr = ctime(&now);

    if (timeStr[strlen(timeStr) - 1] == '\n') {
        timeStr[strlen(timeStr) - 1] = '\0';
    }

    fprintf(logFile, "[%s] %s:%d (%s) | error: %s\n", timeStr, file, line, func, message);
    fclose(logFile);
}

void logInfo(const char* func, const char* fmt, ...) {
    FILE* logFile = fopen("logs.txt", "a");
    if (logFile == NULL) {
        perror("Не удалось открыть logs.txt");
        return;
    }

    time_t now = time(NULL);
    struct tm* t = localtime(&now);

    char timeStr[20];
    strftime(timeStr, sizeof(timeStr), "%Y.%m.%dT%H:%M:%S", t);

    if (timeStr[strlen(timeStr) - 1] == '\n') {
        timeStr[strlen(timeStr) - 1] = '\0';
    }

    fprintf(logFile, "{\"timestamp\":\"%s\", \"message\":\"", timeStr);

    va_list args;
    va_start(args, fmt);
    vfprintf(logFile, fmt, args);
    va_end(args);

    fprintf(logFile, "\"}\n");
    fclose(logFile);
}

#endif
