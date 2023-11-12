#include <sys/stat.h>
#include <dirent.h> 
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static int count_files(const char *dirName){

    DIR* dir = opendir(dirName);
    if(dir == NULL){
        return -1;
    }

    struct dirent* entity;
    entity = readdir(dir);
    int count = 0;

    char *path = concat_paths(dirName, entity->d_name); 
    
    free(path);

    while(entity != NULL){
        
        if(is_dot_dir(entity->d_name) == 1){
            readdir(dir);
        }
        else{
            count = count + 1;
        }
        readdir(dir);
    }

    if(closedir(dir) == -1){
        return -1;
    }

}

static char* concat_paths(const char *first , const char *second) { 
    /* Aus Platzgründen weggelassen */
}

static int dir_entry_type(char *path) {
    /* Aus Platzgründen weggelassen */
}

static int is_dot_dir(char *entryName) {
    return !strncmp(entryName, ".", 1) || !strncmp(entryName, "..", 2);
}

int main(int argc, const char *argv[]){

    if(argc < 2){
        return 0;
    }

    int result = 0;

    for(int i = 1; i < argc; i++){
        result = result + count_files(argv[i]);
    }

    printf("Sum of all files: %d\n", result);

    return EXIT_SUCCESS;

}