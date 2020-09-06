/*!
 * File Utils.h
 */

#pragma once

#include <cstring>
#include <string>
#include <regex>
#include <sstream>
#include <cstdio>
#include <fstream>
#include <glm/ext.hpp>
#include <unordered_map>
#include <functional>
#include "HPMSObject.h"


#define LOG_ERROR(msg) hpms::ErrorHandler(__FILE__, __LINE__, msg)
#define LOG_WARN(msg) hpms::MsgHandler("WARN ", msg)
#define LOG_INFO(msg) hpms::MsgHandler("INFO ", msg)

#define CONFIG_FILE "data/HPMS.ini"

#if !defined(_DEBUG) && !defined(NDEBUG)
#define LOG_DEBUG(msg) hpms::MsgHandler("DEBUG", msg)
#else
#define LOG_DEBUG(msg)
#endif


namespace hpms
{
    // Some useful utilities for safe memory, I/O management etc...

    struct AllocCounter
    {
        static std::unordered_map<std::string, int> gAllocationsMap;
    };

    inline static AllocCounter& AllocCounterInstance()
    {
        static AllocCounter inst;
        return inst;
    } 

    template<typename T>
    inline T GetConf(const std::string& key, T defaultValue)
    {
        return defaultValue;
    }

    inline void ErrorHandler(const char* file, int line, const char* message)
    {
        printf("[ERROR] - File %s, at line %d: %s", file, line, message);
        exit(-1);
    }

    inline void MsgHandler(const char* desc, const char* message)
    {
        printf("[%s] - %s\n", desc, message);
    }

    template<typename T, typename... ARGS>
    inline T* SafeNew(ARGS... args)
    {
        T* obj = new T(args...);
#if !defined(_DEBUG) && !defined(NDEBUG)

        std::string name = obj->Name();
        if (AllocCounterInstance().gAllocationsMap.find(name) == AllocCounterInstance().gAllocationsMap.end())
        {
            AllocCounterInstance().gAllocationsMap[name] = 0;
        }
        AllocCounterInstance().gAllocationsMap[name]++;

        std::stringstream ss;
        ss << "Malloc " << name << " to " << AllocCounterInstance().gAllocationsMap[name];
        LOG_DEBUG(ss.str().c_str());


#endif
        return obj;
    }

    template<typename T>
    inline T* SafeNewArray(size_t size)
    {
        T* obj = new T[size];
#if !defined(_DEBUG) && !defined(NDEBUG)
        std::string name = "ARRAY";
        if (AllocCounterInstance().gAllocationsMap.find(name) == AllocCounterInstance().gAllocationsMap.end())
        {
            AllocCounterInstance().gAllocationsMap[name] = 0;
        }
        AllocCounterInstance().gAllocationsMap[name]++;
#endif
        return obj;
    }

    template<typename T>
    inline void SafeDelete(T*& ptr)
    {


#if !defined(_DEBUG) && !defined(NDEBUG)

        std::string name = ptr->Name();
        AllocCounterInstance().gAllocationsMap[name]--;

        std::stringstream ss;
        ss << "Dealloc " << name << " to " << AllocCounterInstance().gAllocationsMap[name];
        LOG_DEBUG(ss.str().c_str());

#endif
        delete ptr;
        ptr = nullptr;

    }

    template<typename T>
    inline void SafeDeleteArray(T*& ptr)
    {

#if !defined(_DEBUG) && !defined(NDEBUG)
        std::string name = "ARRAY";
        AllocCounterInstance().gAllocationsMap[name]--;
#endif
        delete[] ptr;
        ptr = nullptr;

    }

    inline void ProcessFileLines(const std::string& fileName, std::function<void(const std::string&)> callback)
    {
        std::ifstream file(fileName);
        if (file)
        {
            for (std::string line; getline(file, line);)
            {
                callback(line);
            }
        } else
        {
            std::stringstream ss;
            ss << "Cannot open/read file with name " << fileName;
            LOG_ERROR(ss.str().c_str());
        }
    }

    inline std::string ReadFile(const std::string& fileName)
    {

        std::ifstream file(fileName);

        if (file)
        {
            std::stringstream buffer;
            buffer << file.rdbuf();
            file.close();
            return buffer.str();
        } else
        {
            std::stringstream ss;
            ss << "Cannot open/read file with name " << fileName;
            LOG_ERROR(ss.str().c_str());
        }
    }

    inline std::string PrintMatrix(const glm::mat4& m)
    {
        std::stringstream ss;
        ss << "[" << m[0][0] << "]" << "[" << m[0][1] << "]" << "[" << m[0][2] << "]" << "[" << m[0][3] << "]"
           << std::endl;
        ss << "[" << m[1][0] << "]" << "[" << m[1][1] << "]" << "[" << m[1][2] << "]" << "[" << m[1][3] << "]"
           << std::endl;
        ss << "[" << m[2][0] << "]" << "[" << m[2][1] << "]" << "[" << m[2][2] << "]" << "[" << m[2][3] << "]"
           << std::endl;
        ss << "[" << m[3][0] << "]" << "[" << m[3][1] << "]" << "[" << m[3][2] << "]" << "[" << m[3][3] << "]"
           << std::endl;
        return ss.str();
    }

    inline void RandomString(char* s, const int len)
    {
        static const char alphanum[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";

        for (int i = 0; i < len; ++i)
        {
            s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
        }

        s[len] = 0;
    }

    inline std::vector<std::string> Split(const std::string& stringToSplit, const std::string& reg)
    {
        std::vector<std::string> elems;

        std::regex rgx(reg);

        std::sregex_token_iterator iter(stringToSplit.begin(), stringToSplit.end(), rgx, -1);
        std::sregex_token_iterator end;

        while (iter != end)
        {
            elems.push_back(*iter);
            ++iter;
        }

        return elems;
    }

    inline std::string GetFileName(const std::string& s)
    {

        char sep = '/';
#ifdef _WIN32
        sep = '\\';
#endif
        size_t i = s.rfind(sep, s.length());
        if (i != std::string::npos)
        {
            std::string filename = s.substr(i + 1, s.length() - i);
            size_t lastindex = filename.find_last_of(".");
            std::string rawname = filename.substr(0, lastindex);
            return (rawname);
        }

        return ("");
    }

}

