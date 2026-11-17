# Security audit: libexpat/libexpat

Date: 2026-11-17 | Auditor: [mutsuumii](https://github.com/mutsuumii)

## Summary

Found 91 issue(s): 10 critical, 81 high.

## Findings

### 1. [CRITICAL] Format string vulnerability

**CWE-134** | `expat/tests/common.c` line 192

User-controlled string passed as printf format argument. Attacker reads stack memory or overwrites return addresses via %n.

```
snprintf(buffer, sizeof(buffer),
```

**Fix:** Use a literal format string: printf("%s", user_input). Never pass user data as the format argument.
---

### 2. [HIGH] Integer overflow in size calculation

**CWE-190** | `expat/tests/common.c` line 426

Arithmetic in allocator argument can overflow to a small value, causing under-allocation and subsequent heap overflow.

```
XML_Char *const buf = calloc(len + /*terminator*/ 1, sizeof(XML_Char));
```

**Fix:** Validate sizes before arithmetic. Use calloc(n, size) for n*size. Check: if (n > SIZE_MAX / size) abort().
---

### 3. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/common.c` line 360

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(storage);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 4. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/common.c` line 349

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
CharData *const storage = malloc(sizeof(CharData));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 5. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/common.c` line 378

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
return tracking_malloc(size);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 6. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/common.c` line 388

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
return tracking_realloc(ptr, size);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 7. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/common.c` line 408

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
char *const buffer = malloc(n + 1);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 8. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/common.c` line 426

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
XML_Char *const buf = calloc(len + /*terminator*/ 1, sizeof(XML_Char));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 9. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/entities_tests.c` line 91

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(cdataOpen);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 10. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/entities_tests.c` line 92

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(commentOpen);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 11. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/entities_tests.c` line 93

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(piOpen);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 12. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/entities_tests.c` line 109

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(xcsText);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 13. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/entities_tests.c` line 163

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(entity);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 14. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/entities_tests.c` line 210

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(ten);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 15. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/entities_tests.c` line 216

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(entityReferencingTen);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 16. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/entities_tests.c` line 129

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
ENTITY *const entity = calloc(1, sizeof(ENTITY));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 17. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/runtests.c` line 123

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
srunner_free(sr);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 18. [HIGH] Use-after-free pattern

**CWE-416** | `expat/fuzz/xml_lpm_fuzzer.cpp` line 106

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(ptr);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 19. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/fuzz/xml_lpm_fuzzer.cpp` line 90

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
return malloc(size);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 20. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/fuzz/xml_lpm_fuzzer.cpp` line 101

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
return realloc(ptr, size);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 21. [HIGH] Integer overflow in size calculation

**CWE-190** | `expat/xmlwf/xmlfile.c` line 160

Arithmetic in allocator argument can overflow to a small value, causing under-allocation and subsequent heap overflow.

```
*toFree = malloc(charsRequired * sizeof(XML_Char));
```

**Fix:** Validate sizes before arithmetic. Use calloc(n, size) for n*size. Check: if (n > SIZE_MAX / size) abort().
---

### 22. [HIGH] Use-after-free pattern

**CWE-416** | `expat/xmlwf/xmlfile.c` line 203

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(s);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 23. [HIGH] Use-after-free pattern

**CWE-416** | `expat/xmlwf/xmlfile.c` line 265

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(s);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 24. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/xmlwf/xmlfile.c` line 160

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
*toFree = malloc(charsRequired * sizeof(XML_Char));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 25. [CRITICAL] Format string vulnerability

**CWE-134** | `expat/tests/handlers.c` line 201

User-controlled string passed as printf format argument. Attacker reads stack memory or overwrites return addresses via %n.

```
snprintf(buffer, sizeof(buffer),
```

**Fix:** Use a literal format string: printf("%s", user_input). Never pass user data as the format argument.
---

### 26. [CRITICAL] Format string vulnerability

**CWE-134** | `expat/tests/handlers.c` line 206

User-controlled string passed as printf format argument. Attacker reads stack memory or overwrites return addresses via %n.

```
snprintf(buffer, sizeof(buffer),
```

**Fix:** Use a literal format string: printf("%s", user_input). Never pass user data as the format argument.
---

### 27. [CRITICAL] Format string vulnerability

**CWE-134** | `expat/tests/handlers.c` line 222

User-controlled string passed as printf format argument. Attacker reads stack memory or overwrites return addresses via %n.

```
snprintf(buffer, sizeof(buffer),
```

**Fix:** Use a literal format string: printf("%s", user_input). Never pass user data as the format argument.
---

### 28. [CRITICAL] Format string vulnerability

**CWE-134** | `expat/tests/structdata.c` line 115

User-controlled string passed as printf format argument. Attacker reads stack memory or overwrites return addresses via %n.

```
snprintf(buffer, sizeof(buffer),
```

**Fix:** Use a literal format string: printf("%s", user_input). Never pass user data as the format argument.
---

### 29. [CRITICAL] Format string vulnerability

**CWE-134** | `expat/tests/structdata.c` line 134

User-controlled string passed as printf format argument. Attacker reads stack memory or overwrites return addresses via %n.

```
snprintf(buffer, sizeof(buffer),
```

**Fix:** Use a literal format string: printf("%s", user_input). Never pass user data as the format argument.
---

### 30. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/structdata.c` line 64

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
XML_Char *const dup = malloc(byte_count);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 31. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/structdata.c` line 97

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
entry->str = xmlstrdup(s);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 32. [HIGH] Integer overflow in size calculation

**CWE-190** | `expat/lib/internal.h` line 156

Arithmetic in allocator argument can overflow to a small value, causing under-allocation and subsequent heap overflow.

```
void *expat_realloc(XML_Parser parser, void *ptr, size_t size, int sourceLine);
```

**Fix:** Validate sizes before arithmetic. Use calloc(n, size) for n*size. Check: if (n > SIZE_MAX / size) abort().
---

### 33. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/lib/internal.h` line 154

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
void *expat_malloc(XML_Parser parser, size_t size, int sourceLine);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 34. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/lib/internal.h` line 156

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
void *expat_realloc(XML_Parser parser, void *ptr, size_t size, int sourceLine);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 35. [CRITICAL] Buffer overflow via unsafe string function

**CWE-120** | `expat/xmlwf/xmlmime.c` line 129

strcpy/strcat/sprintf/gets without bounds checking. Stack or heap overflow leads to code execution.

```
strcpy(charset, "us-ascii");
```

**Fix:** Use strncpy, strncat, snprintf with explicit size. Null-terminate manually. Prefer strlcpy/strlcat where available.
---

### 36. [HIGH] Integer overflow in size calculation

**CWE-190** | `expat/tests/memcheck.c` line 131

Arithmetic in allocator argument can overflow to a small value, causing under-allocation and subsequent heap overflow.

```
tracking_realloc(void *ptr, size_t size) {
```

**Fix:** Validate sizes before arithmetic. Use calloc(n, size) for n*size. Check: if (n > SIZE_MAX / size) abort().
---

### 37. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/memcheck.c` line 71

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(entry);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 38. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/memcheck.c` line 122

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(entry);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 39. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/memcheck.c` line 126

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(ptr);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 40. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/memcheck.c` line 139

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
/* By definition, this is equivalent to free(ptr) */
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 41. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/memcheck.c` line 140

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
tracking_free(ptr);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 42. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/memcheck.c` line 155

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(entry);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 43. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/memcheck.c` line 62

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
AllocationEntry *const entry = malloc(sizeof(AllocationEntry));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 44. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/memcheck.c` line 69

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
entry->allocation = malloc(size);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 45. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/memcheck.c` line 136

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
return tracking_malloc(size);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 46. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/memcheck.c` line 148

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
entry = malloc(sizeof(AllocationEntry));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 47. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/memcheck.c` line 153

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
entry->allocation = realloc(ptr, size);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 48. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/memcheck.c` line 170

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
void *const reallocated = realloc(ptr, size);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 49. [CRITICAL] Buffer overflow via unsafe string function

**CWE-120** | `expat/xmlwf/ct.c` line 124

strcpy/strcat/sprintf/gets without bounds checking. Stack or heap overflow leads to code execution.

```
strcpy(charset, "us-ascii");
```

**Fix:** Use strncpy, strncat, snprintf with explicit size. Null-terminate manually. Prefer strlcpy/strlcat where available.
---

### 50. [HIGH] Use-after-free pattern

**CWE-416** | `expat/examples/element_declarations.c` line 81

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(stackTop);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 51. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/examples/element_declarations.c` line 68

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
Stack *const newStackTop = malloc(sizeof(Stack));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 52. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/minicheck.c` line 116

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(tc);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 53. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/minicheck.c` line 130

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(suite);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 54. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/minicheck.c` line 276

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(runner);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 55. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/minicheck.c` line 60

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
Suite *suite = calloc(1, sizeof(Suite));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 56. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/minicheck.c` line 69

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
TCase *tc = calloc(1, sizeof(TCase));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 57. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/minicheck.c` line 100

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
tcase_test_function *const new_tests = realloc(tc->tests, new_size);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 58. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/minicheck.c` line 135

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
SRunner *const runner = calloc(1, sizeof(SRunner));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 59. [HIGH] Use-after-free pattern

**CWE-416** | `expat/xmlwf/readfilemap.c` line 136

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(p);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 60. [HIGH] Use-after-free pattern

**CWE-416** | `expat/xmlwf/readfilemap.c` line 142

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(p);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 61. [HIGH] Use-after-free pattern

**CWE-416** | `expat/xmlwf/readfilemap.c` line 147

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(p);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 62. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/xmlwf/readfilemap.c` line 127

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
p = malloc(nbytes);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 63. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/misc_tests.c` line 323

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(mydata);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 64. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/misc_tests.c` line 345

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(mydata);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 65. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/misc_tests.c` line 692

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(original_string);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 66. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/misc_tests.c` line 1015

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(expectedEncodingName);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 67. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/misc_tests.c` line 1050

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(encodingName);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 68. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/misc_tests.c` line 1222

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(literalTarget);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 69. [HIGH] Use-after-free pattern

**CWE-416** | `expat/tests/misc_tests.c` line 1223

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(literalData);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 70. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/misc_tests.c` line 315

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
mydata = malloc(sizeof(DataIssue240));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 71. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/misc_tests.c` line 337

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
mydata = malloc(sizeof(DataIssue240));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 72. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/misc_tests.c` line 600

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
void *const ptr = malloc(size);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 73. [HIGH] Integer overflow in size calculation

**CWE-190** | `expat/xmlwf/xmlwf.c` line 441

Arithmetic in allocator argument can overflow to a small value, causing under-allocation and subsequent heap overflow.

```
notations = malloc(notationCount * sizeof(NotationList *));
```

**Fix:** Validate sizes before arithmetic. Use calloc(n, size) for n*size. Check: if (n > SIZE_MAX / size) abort().
---

### 74. [HIGH] Integer overflow in size calculation

**CWE-190** | `expat/xmlwf/xmlwf.c` line 1304

Arithmetic in allocator argument can overflow to a small value, causing under-allocation and subsequent heap overflow.

```
outName = malloc(charsRequired * sizeof(XML_Char));
```

**Fix:** Validate sizes before arithmetic. Use calloc(n, size) for n*size. Check: if (n > SIZE_MAX / size) abort().
---

### 75. [HIGH] Use-after-free pattern

**CWE-416** | `expat/xmlwf/xmlwf.c` line 385

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(notationListHead);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 76. [HIGH] Use-after-free pattern

**CWE-416** | `expat/xmlwf/xmlwf.c` line 479

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(notations);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 77. [HIGH] Use-after-free pattern

**CWE-416** | `expat/xmlwf/xmlwf.c` line 502

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(entry);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 78. [HIGH] Use-after-free pattern

**CWE-416** | `expat/xmlwf/xmlwf.c` line 510

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(entry);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 79. [HIGH] Use-after-free pattern

**CWE-416** | `expat/xmlwf/xmlwf.c` line 522

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(entry);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 80. [HIGH] Use-after-free pattern

**CWE-416** | `expat/xmlwf/xmlwf.c` line 1329

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(outName);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 81. [HIGH] Use-after-free pattern

**CWE-416** | `expat/xmlwf/xmlwf.c` line 1397

Freed pointer not immediately set to NULL. Dangling pointer reuse corrupts heap and can lead to code execution.

```
free(outName);
```

**Fix:** Set pointer to NULL immediately after free(). Enable AddressSanitizer in CI: -fsanitize=address.
---

### 82. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/xmlwf/xmlwf.c` line 358

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
XML_Char *const result = malloc(numBytes);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 83. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/xmlwf/xmlwf.c` line 441

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
notations = malloc(notationCount * sizeof(NotationList *));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 84. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/xmlwf/xmlwf.c` line 491

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
NotationList *entry = malloc(sizeof(NotationList));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 85. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/xmlwf/xmlwf.c` line 880

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
info->data = malloc(sizeof(int));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 86. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/xmlwf/xmlwf.c` line 1304

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
outName = malloc(charsRequired * sizeof(XML_Char));
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 87. [HIGH] Integer overflow in size calculation

**CWE-190** | `expat/tests/memcheck.h` line 43

Arithmetic in allocator argument can overflow to a small value, causing under-allocation and subsequent heap overflow.

```
void *tracking_realloc(void *ptr, size_t size);
```

**Fix:** Validate sizes before arithmetic. Use calloc(n, size) for n*size. Check: if (n > SIZE_MAX / size) abort().
---

### 88. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/memcheck.h` line 41

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
void *tracking_malloc(size_t size);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 89. [HIGH] Missing NULL check after allocation

**CWE-476** | `expat/tests/memcheck.h` line 43

Return value of malloc/realloc not checked for NULL. On allocation failure the program dereferences NULL, causing a crash or exploitable condition.

```
void *tracking_realloc(void *ptr, size_t size);
```

**Fix:** Always check: ptr = malloc(n); if (!ptr) { handle_error(); return; }
---

### 90. [CRITICAL] Format string vulnerability

**CWE-134** | `expat/gennmtab/gennmtab.c` line 434

User-controlled string passed as printf format argument. Attacker reads stack memory or overwrites return addresses via %n.

```
printf("static const unsigned char nmstrtPages[] = {\n");
```

**Fix:** Use a literal format string: printf("%s", user_input). Never pass user data as the format argument.
---

### 91. [CRITICAL] Format string vulnerability

**CWE-134** | `expat/gennmtab/gennmtab.c` line 437

User-controlled string passed as printf format argument. Attacker reads stack memory or overwrites return addresses via %n.

```
printf("};\nstatic const unsigned char namePages[] = {\n");
```

**Fix:** Use a literal format string: printf("%s", user_input). Never pass user data as the format argument.
---
