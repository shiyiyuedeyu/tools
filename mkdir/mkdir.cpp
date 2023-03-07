#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#include <string>

void RecursiveMkdir(const char *dir) {
  char tmp[256];
  char *p = NULL;
  size_t len;

  snprintf(tmp, sizeof(tmp), "%s", dir);
  len = strlen(tmp);
  if (tmp[len - 1] == '/') tmp[len - 1] = 0;
  for (p = tmp + 1; *p; p++) {
    if (*p == '/') {
      *p = 0;
      mkdir(tmp, S_IRWXU);
      *p = '/';
    }
  }
  mkdir(tmp, S_IRWXU);
}

int main() {

  std::string root = "dump/json";
  RecursiveMkdir(root.c_str());

  return 0;
}
