#ifndef Debug_H
#define Debug_H

#define DEBUG 1

#if DEBUG
#define LOG(str) Log(str)
#else
#define LOG(str) 
#endif // DEBUG

#endif // Debug_H