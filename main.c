typedef struct {
    int tag;
    union {
        int data;
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

typedef ecs_Vec(ecs_Component) ecs_Components;
typedef ecs_Vec(int) ecs_Ids;

typedef struct {
    ecs_Components prototypes;
    ecs_Components components;
    ecs_Ids ids;
} ecs_Ecs;

//void ecs_define_component(ecs_Ecs * e, const char * name, I/
int * ecs_query(const ecs_Ecs *, const char *);

int game_do_physics(void) {
    int * iter = ecs_query(0, "physics");
    while(iter) {
        ecs_Component comp = ecs_get_component(&ecs, *iter, "physics");
    }
}

void ecs_component_prototype(ecs_Ecs * e, ecs_Component component) {

}

int main() {
    ecs_Component physics = {
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







