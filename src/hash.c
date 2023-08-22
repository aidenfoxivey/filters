// retrieved from:
// http://www.partow.net/programming/hashfunctions/

unsigned int RSHash(const char *str, unsigned int length) {
  unsigned int b = 378551;
  unsigned int a = 63689;
  unsigned int hash = 0;
  unsigned int i = 0;

  for (i = 0; i < length; ++str, ++i) {
    hash = hash * a + (*str);
    a = a * b;
  }

  return hash;
}

unsigned int JSHash(const char *str, unsigned int length) {
  unsigned int hash = 1315423911;
  unsigned int i = 0;

  for (i = 0; i < length; ++str, ++i) {
    hash ^= ((hash << 5) + (*str) + (hash >> 2));
  }

  return hash;
}

unsigned int PJWHash(const char *str, unsigned int length) {
  const unsigned int BitsInUnsignedInt =
      (unsigned int)(sizeof(unsigned int) * 8);
  const unsigned int ThreeQuarters =
      (unsigned int)((BitsInUnsignedInt * 3) / 4);
  const unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
  const unsigned int HighBits = (unsigned int)(0xFFFFFFFF)
                                << (BitsInUnsignedInt - OneEighth);
  unsigned int hash = 0;
  unsigned int test = 0;
  unsigned int i = 0;

  for (i = 0; i < length; ++str, ++i) {
    hash = (hash << OneEighth) + (*str);

    if ((test = hash & HighBits) != 0) {
      hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
    }
  }

  return hash;
}

unsigned int ELFHash(const char *str, unsigned int length) {
  unsigned int hash = 0;
  unsigned int x = 0;
  unsigned int i = 0;

  for (i = 0; i < length; ++str, ++i) {
    hash = (hash << 4) + (*str);

    if ((x = hash & 0xF0000000L) != 0) {
      hash ^= (x >> 24);
    }

    hash &= ~x;
  }

  return hash;
}

unsigned int BKDRHash(const char *str, unsigned int length) {
  unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
  unsigned int hash = 0;
  unsigned int i = 0;

  for (i = 0; i < length; ++str, ++i) {
    hash = (hash * seed) + (*str);
  }

  return hash;
}

unsigned int SDBMHash(const char *str, unsigned int length) {
  unsigned int hash = 0;
  unsigned int i = 0;

  for (i = 0; i < length; ++str, ++i) {
    hash = (*str) + (hash << 6) + (hash << 16) - hash;
  }

  return hash;
}

unsigned int DJBHash(const char *str, unsigned int length) {
  unsigned int hash = 5381;
  unsigned int i = 0;

  for (i = 0; i < length; ++str, ++i) {
    hash = ((hash << 5) + hash) + (*str);
  }

  return hash;
}

// there was an issue here len instead of length
unsigned int DEKHash(const char *str, unsigned int length) {
  unsigned int hash = length;
  unsigned int i = 0;

  for (i = 0; i < length; ++str, ++i) {
    hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
  }

  return hash;
}

unsigned int APHash(const char *str, unsigned int length) {
  unsigned int hash = 0xAAAAAAAA;
  unsigned int i = 0;

  for (i = 0; i < length; ++str, ++i) {
    hash ^= ((i & 1) == 0) ? ((hash << 7) ^ (*str) * (hash >> 3))
                           : (~((hash << 11) + ((*str) ^ (hash >> 5))));
  }

  return hash;
}

unsigned int BadHash(const char *str, unsigned int length) {
  unsigned int hash = 0xFAF0FAF0;
  unsigned int seed = 454;
  unsigned int i = 0;

  for (i = 0; i < length; ++str, ++i) {
    hash &= (*str << 4) ^ (hash & seed);
  }

  return hash;
}

unsigned int BadHash2(const char *str, unsigned int length) {
  unsigned int hash = 0xFAF0FAF0;
  unsigned int i = 0;

  for (i = 0; i < length; ++str, ++i) {
    hash ^= (*str << 4) ^ (hash >> 2);
  }

  return hash;
}

// slightly rewritten version of Bob Jenkins "One at a time" hash function
unsigned int oaat(const char *str, unsigned int length) {
  unsigned int i = 0;
  unsigned int hash = 0;
  while (i != length) {
    hash += str[i++];
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash;
}

// unsigned int hash_test_harness(unsigned int (*f)(const char *str,
// unsigned int length),
// unsigned int table_space) {}
