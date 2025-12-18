#ifndef FILE_H
#define FILE_H

#include <stdbool.h>

bool saveStudioState(const char* filename);
bool loadStudioState(const char* filename);
bool fileExists(const char* filename);

#endif // FILE_H