#include    <stdio.h>
#include    "store.h"

int main(int argc, char *argv[]) {
    nadia::store s;
    s.insert(nadia::object::TYPE_STRING,
             "test", 4, 
             "1234567890", 10);

    nadia::object *obj = s.find("test", 4);
    if (obj) {
        printf("%s: %s\n", obj->get_key(), obj->get_data());
    } else {
        printf("error\n");
    }

    obj = s.find("abcd", 4);
    if (obj == NULL) {
        printf("obj is not in the store\n");
    } else {
        printf("find error\n");
    }

    return 0;
}
