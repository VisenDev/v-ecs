#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int tag;
    union {
        double data; //a double can store a normal 32 bit int without rounding!
        void * ptr;
    };
} ecs_Value;

typedef struct {
    const char * name;
    ecs_Value value;
} ecs_Field;

#define ECS_COMPONENT_MAX_FIELDS 16
typedef struct {
    const char * name;
    ecs_Field fields[ECS_COMPONENT_MAX_FIELDS];
} ecs_Component;

#define ecs_Vec(Type) struct { Type * items; int len; int cap; }
#define ecs_vec_append(vec, value) do { \
    if((vec)->cap <= 0) { \
        (vec)->cap = 8; \
        (vec)->len = 0; \
        (vec)->items = malloc(sizeof((vec)->items[0]) * (vec)->cap); \
        assert((vec)->items); \
    } else if((vec)->len + 1 >= (vec)->cap) { \
        (vec)->cap = (vec)->cap * 2; \
        (vec)->items = malloc(sizeof((vec)->items[0]) * (vec)->cap); \
        assert((vec)->items); \
    } \
    (vec)->items[(vec)->len++] = value; \
} while (0)

typedef struct { int i; } ecs_Id;
typedef ecs_Vec(ecs_Component) ecs_Components;
typedef ecs_Vec(ecs_Id) ecs_Ids;

typedef struct {
    ecs_Components prototypes;
    ecs_Components components;
    ecs_Id id_cap;
    ecs_Ids free_ids;
} ecs_Ecs;

//void ecs_define_component(ecs_Ecs * e, const char * name, I/
int * ecs_query(const ecs_Ecs *, const char *);

enum {
    physics_x,
    physics_y,
    physics_vel_x,
    physics_vel_y,
};

int game_do_physics(void) {
    int * iter = NULL;//ecs_query(0, "physics");
    while(iter) {
        ecs_Component c = {0}; /*get component "physics"*/
        c.fields[physics_x].value.data = 1;
        (void)c;
    }
    return 0;
}

void ecs_component_define_prototype(ecs_Ecs * e, ecs_Component prototype) {
    ecs_vec_append(&e->prototypes, prototype);
}

ecs_Id ecs_entity_new(ecs_Ecs * e) {
    if(e->free_ids.len <= 0) {
        ecs_Id stop = {e->id_cap.i + 128};
        for(; e->id_cap.i < stop.i; ++e->id_cap.i) {
            ecs_vec_append(&e->free_ids, e->id_cap);
        }
    }
    return e->free_ids.items[--e->free_ids.len];
}

int main() {
    int i[16] = {0};
    i[17] = 1;
    (void)i;

    ecs_Ecs  e = {0};
    ecs_component_define_prototype(&e, (ecs_Component){
        .name = "physics",
        .fields = {
            {.name = "x", .value = {0}},
            {.name = "y", .value = {0}},
            {.name = "x_vel", .value = {0}},
            {.name = "y_vel", .value = {0}},
            {.name = "x_acc", .value = {0}},
            {.name = "y_acc", .value = {0}},
        }
    });

    ecs_Id new = ecs_entity_new(&e);
    (void) new;

}







