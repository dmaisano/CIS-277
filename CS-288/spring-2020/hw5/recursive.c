#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

struct File
{
  char *path;
  int size;
  struct File *next;
};

enum
{
  FALSE,
  TRUE
};

// function prototypes
void TraverseDirectories(char *, struct File **);
void AppendFileNode(struct File **, int, char *);
void SortList(struct File *);

int main(int argc, char const *argv[])
{
  if (argc < 1)
  {
    printf("Missing directory\n");
    return -1;
  }

  char *filePath = argv[1];

  // stat buffer
  struct stat buf;
  int statReturnCode = stat(filePath, &buf);

  if (statReturnCode == 0 && (S_ISREG(buf.st_mode) || S_ISDIR(buf.st_mode)))
  {
    struct File **filesList = malloc(sizeof(struct File)); // pointer to a 'File' pointer

    // recursively search for all files in the directory and sub-directories
    // add those files to the list of files Struct
    TraverseDirectories(filePath, filesList);
    SortList(*filesList);

    struct File *iter = *filesList;
    while (iter != NULL)
    {
      printf("%d\t%s\n", iter->size, iter->path);
      iter = iter->next;
    }
  }
  else
  {
    printf("Error checking directory '%s', please ensure directory exists\n", filePath);
  }

  return 0;
}

void TraverseDirectories(char *filePath, struct File **filesList)
{
  struct stat buf;
  lstat(filePath, &buf);

  if (S_ISREG(buf.st_mode))
  {
    AppendFileNode(filesList, buf.st_size, filePath);
  }
  else if (S_ISDIR(buf.st_mode))
  {
    struct DIR *dir;
    struct dirent *dirEntry;

    dir = opendir(filePath);
    while (((dirEntry = readdir(dir)) != NULL))
    {
      // ignore current and parent directories
      if (strcmp(dirEntry->d_name, "..") != 0 && strcmp(dirEntry->d_name, ".") != 0)
      {
        // append 2 extra bytes for "/" char and null-terminator
        char *newFilePath = malloc(sizeof(char) * (strlen(filePath) + strlen(dirEntry->d_name) + 2));

        // construct the complete file path of the sub-directory
        strcpy(newFilePath, filePath);
        strcat(newFilePath, "/");
        strcat(newFilePath, dirEntry->d_name);

        // recursively search for more files in the given sub-directory
        TraverseDirectories(newFilePath, filesList);
      }
    }

    closedir(dir);
  }
}

void AppendFileNode(struct File **filesList, int fileSizeBytes, char *filePath)
{
  struct File *new_node = malloc(sizeof(struct File));
  new_node->path = filePath;
  new_node->size = fileSizeBytes;
  new_node->next = NULL;

  // list is empty, set the first node to the new node
  if (*filesList == NULL)
  {
    *filesList = new_node;
  }
  else
  {
    struct File *current = *filesList;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = new_node;
  }
}

// reference: https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/
void SortList(struct File *filesList)
{
  struct File *iter;
  struct File *lptr = NULL;

  // list is empty, nothing to sort
  if (filesList == NULL)
  {
    return;
  }

  int isSwapped;
  do
  {
    isSwapped = 0;
    iter = filesList;

    while (iter->next != lptr)
    {
      if (iter->size > iter->next->size)
      {
        struct File *tmpFile = malloc(sizeof(iter));
        tmpFile->path = iter->path;
        tmpFile->size = iter->size;

        iter->path = iter->next->path;
        iter->size = iter->next->size;

        iter->next->path = tmpFile->path;
        iter->next->size = tmpFile->size;

        free(tmpFile);

        isSwapped = 1;
      }

      iter = iter->next;
    }

    lptr = iter;
  } while (isSwapped == 1);
}
