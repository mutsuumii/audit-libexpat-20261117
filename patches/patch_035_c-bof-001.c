# Buffer overflow via unsafe string function
# CWE-120 | Severity: CRITICAL
# File: expat/xmlwf/xmlmime.c line 129

**Risk:** strcpy/strcat/sprintf/gets without bounds checking. Stack or heap overflow leads to code execution.

**Fix:** Use strncpy, strncat, snprintf with explicit size. Null-terminate manually. Prefer strlcpy/strlcat where available.
