#include <list>
#include <string>
#include <iostream>
#include <cstdlib>
extern "C" int last_mem_id = 0;
struct Minfo
{
    long id;
    long line;
    std::string file;
    size_t size;
    void *mptr;
    Minfo(long id, long ln, std::string f, size_t sz, void *p)
        : id(id), line(ln), size(sz), file(f), mptr(p){};
};

static std::list<Minfo> minfo_list;

extern "C" void *malloc_tracked(size_t size, long ln, const char *file)
{
    void *m = malloc(size);
    minfo_list.push_back(Minfo(last_mem_id + 1, ln, file, size, m));
    ++last_mem_id;
    return m;
}

extern "C" void free_tracked(void *p, long ln, const char *file)
{
    for (auto i = minfo_list.begin(); i != minfo_list.end(); ++i)
    {
        if (p == i->mptr)
        {
            free(p);
            minfo_list.erase(i);
            break;
        }
    }
}

extern "C" size_t DumpMemRecord()
{
    std::cout << "Resources unfreed:" << minfo_list.size() << std::endl;
    for (auto &&i : minfo_list)
    {
        std::cout << "[" << i.id << "] " << i.file << ":" << i.line << std::endl;
    }
    return minfo_list.size();
}
