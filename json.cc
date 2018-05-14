#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <util.h>

#include "json.h"

// construct a json-object
json *json::loads(const char *json_contents)
{
    
}

// fd: file descriptor
json *json::load(int fd)
{
    char *buff;
    ssize_t nbytes;
    struct stat st;

    memset(&st, 0, sizeof(st));
    fstat(fd, &st);
    buff = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (buff == MAP_FAILED)
	err_sys("mmap error");

    json *jobj = new json();

    munmap(buff, st.st_size);

    return jobj;
}
