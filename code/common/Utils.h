/*!
 * File Utils.h
 *
 * Some useful utilities for safe memory, I/O management etc...
 */

#pragma once

#include <cstring>
#include <string>
#include <sstream>
#include <cstdio>
#include <fstream>
#include <glm/ext.hpp>


#define LOG_ERROR(msg) hpms::ErrorHandler(__FILE__, __LINE__, msg)
#define LOG_WARN(msg) hpms::MsgHandler("WARN ", msg)
#define LOG_INFO(msg) hpms::MsgHandler("INFO ", msg)

#if !defined(_DEBUG) && !defined(NDEBUG)
#define LOG_DEBUG(msg) hpms::MsgHandler("DEBUG", msg)
#else
#define LOG_DEBUG(msg)
#endif


namespace hpms
{
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
        return obj;
    }

    template<typename T>
    inline T* SafeNewArray(size_t size)
    {
        T* obj = new T[size];
        return obj;
    }

    template<typename T>
    inline void SafeDelete(T*& ptr)
    {
        delete ptr;
        ptr = nullptr;
    }

    template<typename T>
    inline void SafeDeleteArray(T*& ptr)
    {
        delete[] ptr;
        ptr = nullptr;
    }

    inline std::string ReadFile(const std::string fileName)
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
}

