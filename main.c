typedef struct {
    int tag;
    union {
        int data;
        void * ptr;
    };
} ecs_Value;

typedef struct {
    const char * name;
    ecs_Value default_value;
} ecs_FieldDef;

#define ECS_COMPONENTDEF_MAX_FIELDS 16
typedef struct {
    const char * name;
    ecs_FieldDef fields[ECS_COMPONENTDEF_MAX_FIELDS];
} ecs_ComponentDef;

typedef struct {
    ecs_ComponentDef * component_defs;
    int component_defs_len;
    int component_defs_cap;
    
} ecs_Ecs;

//void ecs_define_component(ecs_Ecs * e, const char * name, I/
int * ecs_query(const ecs_Ecs *, const char *);

int game_do_physics(void) {
    int * iter = ecs_query(0, "physics");
    while(iter) {
        ecs_ComponentDef comp = ecs_get_component(&ecs, *iter, "physics");
    }
}

int main() {
    ecs_ComponentDef physics = {
        .name = "physics",
        .fields = {
            {.name = "x", .default_value = {0}},
            {.name = "y", .default_value = {0}},
            {.name = "x_vel", .default_value = {0}},
            {.name = "y_vel", .default_value = {0}},
            {.name = "x_acc", .default_value = {0}},
            {.name = "y_acc", .default_value = {0}},
        }
    };


}







