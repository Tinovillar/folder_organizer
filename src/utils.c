#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

struct ExtensionFolder {
    char *extension;
    char *folder_name;
};

struct ExtensionFolder extensionesMapping[] = {
    { ".mp3", "audio" },
    { ".wav", "audio" },
    { ".ogg", "audio" },
    { ".mp4", "video" },
    { ".avi", "video" },
    { ".webm", "video" },
    { ".jpg", "images" },
    { ".jpeg", "images" },
    { ".png", "images" },
    { ".ico", "images" },
    { ".svg", "images" },
    { ".log", "documents" },
    { ".doc", "documents" },
    { ".docx", "documents" },
    { ".pdf", "documents" },
    { ".xlsx", "documents" },
    { ".xls", "documents" },
    { ".pptx", "documents" },
    { ".xltx", "documents" },
    { ".txt", "documents" },
    { ".zip", "compressed" },
    { ".rar", "compressed" },
    { ".exe", "installers"},
    { ".msi", "installers"},
};

char *get_destination_folder(char *extension) {
    int numExtensiones = sizeof(extensionesMapping) / sizeof(struct ExtensionFolder);
    for (int i = 0; i < numExtensiones; i++) {
        if (strcmp(extension, extensionesMapping[i].extension) == 0) {
            return extensionesMapping[i].folder_name;
        }
    }
    return "others";  // Carpeta por defecto si no se encuentra la extensión
}

void move_file(char *path_folder, char *extension, char *file_name) {
    char *destination_folder = get_destination_folder(extension);
    // Destination Path, here i concat the path of the main folder with the folder where i want to send the file and create the destination path
    char destination[256] = "\0";
    strcat(destination, path_folder);
    strcat(destination, destination_folder);
    destination[strlen(destination)] = '/';
    destination[strlen(destination)] = '\0';
    strcat(destination, file_name);
    // Origin Path, here i save the original path of the file
    char origin[256] = "\0";
    strcat(origin, path_folder);
    strcat(origin, file_name);

    rename(origin, destination);
}

void start_organizer(char *path) {
    DIR *dir = opendir(path);
    struct dirent *file;

    while((file = readdir(dir)) != NULL) {
        char *extension = strrchr(file->d_name, '.');
        if(extension != NULL && strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0) {
            move_file(path, extension, file->d_name);
        }
    }

    closedir(dir);
};

void create_folder(char *path, char *folder_name) {
    char folder_path[100] = "\0";
    strcat(folder_path, path);
    strcat(folder_path, folder_name);
    struct stat st = {0};
    if(stat(folder_path, &st) == -1) {
        mkdir(folder_path);
    }
}

void add_slash_to_end(char *path) {
    int length = strlen(path);
    if(path[length - 1] != '/') {
        path[length] = '/';
        path[length + 1] = '\0';
    }
}

void show_help() {
    printf("\n\n============================================================\n\n");
    printf("HELLO, WELCOME TO FOLDER ORGANIZER\n\n");
    printf("How to use? Well, you only need to execute the .exe and following\n");
    printf("u gonna paste the path of the folder that u want to organize.\n");
    printf("\n============================================================\n\n");
}
