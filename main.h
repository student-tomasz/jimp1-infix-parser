#ifndef _HELPERS_H
#define _HELPERS_H


#define max_msg_len 256
#define error(msg) do { fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, msg); } while(0)

#define is_operand(c) ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '.')
#define is_whitespace(c) (c == ' ' || c == '\t' || c == '\n')


#endif /* _HELPERS_H */