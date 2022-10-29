#include "storage/common/limits.h"

void set_mem_null(void *dst, AttrType attr_type, size_t attr_len)
{
  if (attr_type == INTS) {
    int nullval = MINIOB_INT_NULL;
    memcpy(dst, &nullval, sizeof(int));
  } else if (attr_type == FLOATS) {
    float nullval = MINIOB_FLOAT_NULL;
    memcpy(dst, &nullval, sizeof(float));
  } else if (attr_type == DATES) {
    int32_t nullval = MINIOB_DATE_NULL;
    memcpy(dst, &nullval, sizeof(int32_t));
  } else if (attr_type == CHARS) {
    memset(dst, MINIOB_CHARS_NULL, attr_len);
  }
}

bool is_mem_null(void *dst, AttrType attr_type, size_t attr_len)
{
  if (attr_type == INTS) {
    int nullval = MINIOB_INT_NULL;
    return memcmp(dst, &nullval, sizeof(int)) == 0;
  } else if (attr_type == FLOATS) {
    float nullval = MINIOB_FLOAT_NULL;
    return memcmp(dst, &nullval, sizeof(float)) == 0;
  } else if (attr_type == DATES) {
    int32_t nullval = MINIOB_DATE_NULL;
    return memcmp(dst, &nullval, sizeof(int32_t)) == 0;
  } else if (attr_type == CHARS) {
    char *chars_null = (char *)malloc(attr_len);
    memset(chars_null, MINIOB_CHARS_NULL, attr_len);
    int ret = memcmp(dst, chars_null, attr_len);
    return ret == 0;
  } else {
    return false;
  }
}
