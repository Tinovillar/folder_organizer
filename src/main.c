#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <sys/stat.h>
#include <dirent.h>
#include "utils.h"

int main(int argc, char **argv) {
    if(argc == 1 || (argc > 1 && strcmp(argv[1], "-h") == 0)) {
        show_help();
        return 0;
    }

    char *folder_path = argv[1];

    DIR *dir = opendir(folder_path);

    add_slash_to_end(folder_path);

    if(dir == NULL) {
        printf("Cant open folder");
        return 1;
    }

    create_folder(folder_path, "audio"); // .mp3 / .wav
    create_folder(folder_path, "video"); // .mp4 / .
    create_folder(folder_path, "documents"); // .docx / .xlsx / .pdf
    create_folder(folder_path, "images"); // .jpg / .png / .svg / .ico
    create_folder(folder_path, "compressed"); // .zip / .rar
    create_folder(folder_path, "installers"); // .exe / .msi
    create_folder(folder_path, "others");

    start_organizer(folder_path);

    // Quedarme con todos los nombres de archivos y su path correspondiente
    // Chequear si las carpetas ya existen de lo contrario crear las que falten
    // Empezar a recorrer los archivos e ir metiendolos en sus carpetas correspondientes
    // Si quedaron archivos sin mover, mandarlos todos a la carpeta Otros

    closedir(dir);
    return 0;
}
