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
struct File *PopFileNode(struct File **);
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

// Start at the base directory, and iteratively search for files and sub-dirs
void TraverseDirectories(char *filePath, struct File **filesList)
{
  struct File **filesQueue = malloc(sizeof(struct File));

  struct stat buf;
  lstat(filePath, &buf);

  AppendFileNode(filesQueue, 0, filePath);

  while (TRUE)
  {
    if (*filesQueue == NULL)
    {
      break;
    }

    struct File *iter = PopFileNode(filesQueue);

    lstat(iter->path, &buf);

    if (S_ISREG(buf.st_mode))
    {
      AppendFileNode(filesList, buf.st_size, iter->path);
    }
    else if (S_ISDIR(buf.st_mode))
    {
      struct DIR *dir = opendir(iter->path);
      if (dir != NULL)
      {
        struct dirent *dirEntry;
        while (((dirEntry = readdir(dir)) != NULL))
        {
          if (strcmp(dirEntry->d_name, "..") != 0 && strcmp(dirEntry->d_name, ".") != 0)
          {
            // append 2 extra bytes for "/" char and null-terminator
            char *newDirPath = malloc(sizeof(char) * (strlen(iter->path) + strlen(dirEntry->d_name) + 2));

            strcpy(newDirPath, iter->path);
            strcat(newDirPath, "/");
            strcat(newDirPath, dirEntry->d_name);

            AppendFileNode(filesQueue, 0, newDirPath);
          }
        }

        closedir(dir);
      }
    }
  }
}

void AppendFileNode(struct File **filesList, int fileSizeBytes, char *filePath)
{
  struct File *new_node = malloc(sizeof(struct File));
  new_node->size = fileSizeBytes;
  new_node->path = filePath;
  new_node->next = NULL;

  if (*filesList == NULL)
  {
    *filesList = new_node;
  }
  else
  {
    struct File *iter = *filesList;
    while (iter->next != NULL)
    {
      iter = iter->next;
    }
    iter->next = new_node;
  }
}

// Pop a node from the queue / list
struct File *PopFileNode(struct File **filesList)
{
  struct File *res;

  if (*filesList == NULL)
  {
    return NULL;
  }
  else if ((*filesList)->next == NULL)
  {
    res = *filesList;
    *filesList = NULL;
  }
  else
  {
    struct File *iter = *filesList;
    while (iter->next->next != NULL)
    {
      iter = iter->next;
    }

    res = iter->next;
    iter->next = NULL;
  }

  return res;
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
