#include "filesystem.h"



std::string FileSystem::readFile(std::string path)
{
    std::ifstream ifile(path);
    std::string string((std::istreambuf_iterator<char>(ifile)), std::istreambuf_iterator<char>());
    ifile.close();
    return string;
}


std::vector<std::string> FileSystem::readDir(std::string path)
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != nullptr) {
        std::vector<std::string> result;
        while ((ent = readdir (dir)) != nullptr) {
            if(strcmp(ent->d_name, "..") && strcmp(ent->d_name, ".")) {
                result.push_back(ent->d_name);
                //std::cout << "ino: " << ent->d_ino << " name: " << ent->d_name << " off: " << ent->d_off << " reclen: " << ent->d_reclen << " type: " << ent->d_type << "\n";
            }
        }
        closedir (dir);
        return result;
    } else {
        return std::vector<std::string>();
    }
}


bool FileSystem::isDir(std::string path)
{
    struct stat st;
    if(stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
        return true;
    } else {
        return false;
    }
}
