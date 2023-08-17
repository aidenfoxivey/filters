#pragma once

// these hashes are from an online source
unsigned int RSHash(const char *str, unsigned int length);
unsigned int JSHash(const char *str, unsigned int length);
unsigned int PJWHash(const char *str, unsigned int length);
unsigned int ELFHash(const char *str, unsigned int length);
unsigned int BKDRHash(const char *str, unsigned int length);
unsigned int SDBMHash(const char *str, unsigned int length);
unsigned int DJBHash(const char *str, unsigned int length);
unsigned int DEKHash(const char *str, unsigned int length);
unsigned int APHash(const char *str, unsigned int length);

unsigned int AFIHash(const char *str, unsigned int length);

unsigned int oaat(const char* key, unsigned int length);
