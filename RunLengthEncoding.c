#include <stdio.h>
#include <dirent.h> 
#include <stdlib.h>
#include <string.h>

void runLengthEncode(const char *input) {
    int length = strlen(input);

    for (int i = 0; i < length; i++) {
        int count = 1;
        while (i < length - 1 && input[i] == input[i + 1]) {
            count++;
            i++;
        }

        printf("%c%d", input[i], count);
    }

    printf("\n");
}

char path[100];
char file_name[100];

int main() {
    struct dirent *de;

    printf("Enter the file directory path: ");
    fgets(path, sizeof(path), stdin);

    path[strcspn(path, "\n")] = '\0'; //Remove \n character so path is correct

    DIR *dr = opendir(path);

    if(dr == NULL){
        printf("\nCould not open directory: %s\n", path);
        printf("\nPress ENTER to exit program.");
        getchar();
        return 1;
    }

    while ((de = readdir(dr)) != NULL) 
            printf("\n%s", de->d_name); 
  
    closedir(dr);

    printf("\n\nEnter name of the file: ");
    fgets(file_name, sizeof(file_name), stdin);

    file_name[strcspn(file_name, "\n")] = '\0'; //Remove \n character so path is correct

    // Open the file in read mode
    FILE *file = fopen(file_name, "r");
    
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the content of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *file_content = (char *)malloc(file_size + 1);

    if (file_content == NULL) {
        fclose(file);
        perror("Memory allocation error");
        return 1;
    }

    fread(file_content, 1, file_size, file);
    fclose(file);

    file_content[file_size] = '\0';

    printf("Original string:\n%s\n\n", file_content);
    printf("Run-Length Encoded:\n");
    runLengthEncode(file_content);

    free(file_content);

    return 0;
}
