#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

//typedef struct {
//    enum {
//        ECS_PARSER_TYPE_INT,
//        ECS_PARSER_TYPE_FLOAT,
//        ECS_PARSER_TYPE_CUSTOM,
//} ecs_parser_Type;

typedef enum {
    ECS_PARSER_TYPE_INT = 0,
    ECS_PARSER_TYPE_LONG,
    ECS_PARSER_TYPE_SHORT,
    ECS_PARSER_TYPE_CHAR,
    ECS_PARSER_TYPE_BOOL,
    ECS_PARSER_TYPE_FLOAT,
    ECS_PARSER_TYPE_DOUBLE = 255,

    //Any types greater than 255 are ids
} ecs_parser_Type;

typedef struct {
    const char name[32];
    ecs_parser_Type type;
} ecs_parser_StructField;

typedef struct {
    const char * name[32];
    ecs_parser_StructField fields[32];
} ecs_parser_Struct;

typedef struct {
    int count;
    ecs_parser_Struct structs[32];

    FILE * fp;
    FILE * out;
} ecs_Parser;

typedef struct {
    void * ctx;
    void (*get_name_for_serialize_function)(void * ctx, const char * type_name, char * outbuf, size_t len);
    void (*get_name_for_deserialize_function)(void * ctx, const char * type_name, char * outbuf, size_t len);
    //TODO figure out how to count pointers
} ecs_parser_Settings;

char ecs_parser_peek(ecs_Parser * p) {
    char ch = fgetc(p->fp);
    ungetc(ch, p->fp);
    return ch;
}

void ecs_parser_skip_whitespace(ecs_Parser * p) {
    while(isspace(ecs_parser_peek(p))) fgetc(p->fp);
}

bool ecs_parser_expect(ecs_Parser * p, const char * str) {
    for(;*str != 0; ++str) {
        if(fgetc(p->fp) != *str) {
            return false;
        }
    }
    return true;
}


bool ecs_parser_is_identifier_char(char ch) {
    return ch == '_' || isalpha(ch) || isdigit(ch);
}

bool ecs_parser_read_identifier(ecs_Parser * p, char * dst, size_t size) {
    ecs_parser_skip_whitespace(p);
    if(ecs_parser_peek(p) != '_' && !isalpha(ecs_parser_peek(p))) {
        return false;
    }
    int i = 0;
    while(ecs_parser_is_identifier_char(ecs_parser_peek(p))) {
       if(i + 2 > size) return false;
       dst[i++] = fgetc(p->fp);
       dst[i] = 0;
    }
    return true;
}

#define streql(a, b) (strcmp(a, b) == 0)

//bool ecs_parser_type_from_name(ecs_Parser * p, char * name, ecs_parser_Type * out) {
//    if(streql(name, "int")) {
//        *out = ECS_PARSER_TYPE_INT;
//    } else if(streql(name, "long")) {
//        *out = ECS_PARSER_TYPE_LONG;
//    } else {
//        //TODO lookup name in parser list of structs
//        return false;
//    }
//
//    return true;
//}

//bool ecs_parser_parse_type(ecs_Parser * p, ecs_parser_Type * out) {
//    char name[1024] = {0};
//    if(!ecs_parser_read_identifier(p, name, sizeof(name))) return false;
//
//    if(!ecs_parser_type_from_name(p, name, out)) return false;
//    return true;
//}


//void ecs_parser_parse_struct_field(ecs_Parser * p) {
//    char buf[1024] = {0};
//    ecs_parser_Type t = {0};
//    if(!ecs_parser_parse_type(p, &t)) assert(0);
//
//    //TODO parse name;
//    //
//}

void ecs_parser_out(ecs_Parser * p, const char * fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(p->out, fmt, args);
    va_end(args);
}

void ecs_parser_parse_struct(ecs_Parser * p) {
    ecs_parser_skip_whitespace(p); 
    //ecs_parser_expect(p, "typedef"); 
    //ecs_parser_skip_whitespace(p); 
    ecs_parser_expect(p, "struct"); 
    ecs_parser_skip_whitespace(p); 

    char buf[1024] = {0};
    ecs_parser_read_identifier(p, buf, sizeof(buf));
    ecs_parser_out(p, "void %s_serialize(struct %s input, FILE * out) {\n", buf, buf);

    ecs_parser_expect(p, "{"); 
    ecs_parser_skip_whitespace(p); 

    ecs_parser_out(p, "{\n");
}

void ecs_parse_header(FILE * fp) {
    ecs_Parser p = {0};
    p.fp = fp;
    ecs_parser_skip_whitespace(&p); 
    while(!feof(fp)) {
        ecs_parser_parse_struct(&p);
    }
}
