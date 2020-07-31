/*
 * Init order
 * Local 1
 */
class FileSystem
{
    public:
        std::size_t numDisks() const;

};

extern FileSystem tfs;

class Directory
{
    public:
        Directory(params);
};

Directory::Directory(params)
{
    std::size_t disks = tfs.numDisks();
}


/*
 * Local 2
 */
class FileSystem 
{
    public:
        ...
};

FileSystem & tfs()
{
    static FileSystem fs;
    return fs;
}

class Directory
{
    public: 
        ...
};

Directory::Directory(params)
{
    std::size_t disks = tfs().numDisks();
}

Directory & tempDir()
{
    static Directory td;
    return td;
}
