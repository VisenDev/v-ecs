#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    const char * name;
    //*type information*/
} ecs_Type;

typedef struct {
    int len;
    int cap;
    ecs_Type * types; 

    FILE * fp;
} ecs_Parser;

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

ecs_Type ecs_parser_parse_type(ecs_Parser * p) {
    
}

void ecs_parser_parse_struct_field(ecs_Parser * p) {
    char buf[1024] = {0};


}

void ecs_parser_parse_struct(ecs_Parser * p) {
    ecs_parser_skip_whitespace(p); 
    ecs_parser_expect(p, "typedef"); 
    ecs_parser_skip_whitespace(p); 
    ecs_parser_expect(p, "struct"); 
    ecs_parser_skip_whitespace(p); 
    ecs_parser_expect(p, "{"); 
    ecs_parser_skip_whitespace(p); 
}

void ecs_parse_header(FILE * fp) {
    ecs_Parser p = {0};
    p.fp = fp;
    ecs_parser_skip_whitespace(&p); 
    while(!feof(fp)) {
        ecs_parser_parse_struct(&p);
    }
}
