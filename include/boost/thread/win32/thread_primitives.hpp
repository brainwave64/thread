#ifndef BOOST_WIN32_THREAD_PRIMITIVES_HPP
#define BOOST_WIN32_THREAD_PRIMITIVES_HPP

//  win32_thread_primitives.hpp
//
//  (C) Copyright 2005 Anthony Williams 
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined( BOOST_USE_WINDOWS_H )
# include <windows.h>
# define BOOST_CLOSE_HANDLE ::CloseHandle
# define BOOST_RELEASE_MUTEX ::ReleaseMutex
# define BOOST_CREATE_MUTEX ::CreateMutexA
# define BOOST_GET_PROCESS_ID ::GetCurrentProcessId
# define BOOST_GET_CURRENT_THREAD_ID ::GetCurrentThreadId
# define BOOST_WAIT_FOR_SINGLE_OBJECT ::WaitForSingleObject
# define BOOST_CREATE_SEMAPHORE ::CreateSemaphoreA
# define BOOST_RELEASE_SEMAPHORE ::ReleaseSemaphore
# define BOOST_GET_CURRENT_THREAD ::GetCurrentThread
# define BOOST_GET_CURRENT_PROCESS ::GetCurrentProcess
# define BOOST_DUPLICATE_HANDLE ::DuplicateHandle
# define BOOST_SLEEP_EX ::SleepEx
# define BOOST_QUEUE_USER_APC ::QueueUserAPC
# define BOOST_INFINITE INFINITE
namespace boost
{
    namespace detail
    {
        typedef ULONG_PTR ulong_ptr;
    }
}
#elif defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ )
namespace boost
{
    namespace detail
    {
# ifdef _WIN64
        typedef unsigned __int64 ulong_ptr;
# else
        typedef unsigned long ulong_ptr;
# endif

        extern "C" __declspec(dllimport) int __stdcall CloseHandle(void*);
        extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void*);
        extern "C" struct _SECURITY_ATTRIBUTES;
        extern "C" __declspec(dllimport) void* __stdcall CreateMutexA(_SECURITY_ATTRIBUTES*,int,char const*);
        extern "C" __declspec(dllimport) unsigned long __stdcall GetCurrentProcessId();
        extern "C" __declspec(dllimport) unsigned long __stdcall GetCurrentThreadId();
        extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void*,unsigned long);
        extern "C" __declspec(dllimport) int __stdcall ReleaseSemaphore(void*,long,long*);
        extern "C" __declspec(dllimport) void* __stdcall CreateSemaphoreA(_SECURITY_ATTRIBUTES*,long,long,char const*);
        extern "C" __declspec(dllimport) void* __stdcall GetCurrentThread();
        extern "C" __declspec(dllimport) void* __stdcall GetCurrentProcess();
        extern "C" __declspec(dllimport) int __stdcall DuplicateHandle(void*,void*,void*,void**,unsigned long,int,unsigned long);
        extern "C" __declspec(dllimport) unsigned long __stdcall SleepEx(unsigned long,int);
        extern "C" __declspec(dllimport) unsigned long __stdcall QueueUserAPC(void __stdcall(ulong_ptr),void*,ulong_ptr);

    }
}
# define BOOST_CLOSE_HANDLE ::boost::detail::CloseHandle
# define BOOST_RELEASE_MUTEX ::boost::detail::ReleaseMutex
# define BOOST_CREATE_MUTEX ::boost::detail::CreateMutexA
# define BOOST_GET_PROCESS_ID ::boost::detail::GetCurrentProcessId
# define BOOST_GET_CURRENT_THREAD_ID ::boost::detail::GetCurrentThreadId
# define BOOST_WAIT_FOR_SINGLE_OBJECT ::boost::detail::WaitForSingleObject
# define BOOST_CREATE_SEMAPHORE ::boost::detail::CreateSemaphoreA
# define BOOST_RELEASE_SEMAPHORE ::boost::detail::ReleaseSemaphore
# define BOOST_GET_CURRENT_THREAD ::boost::detail::GetCurrentThread
# define BOOST_GET_CURRENT_PROCESS ::boost::detail::GetCurrentProcess
# define BOOST_DUPLICATE_HANDLE ::boost::detail::DuplicateHandle
# define BOOST_SLEEP_EX ::boost::detail::SleepEx
# define BOOST_QUEUE_USER_APC ::boost::detail::QueueUserAPC
# define BOOST_INFINITE 0xffffffff
#else
# error "Win32 functions not available"
#endif


#endif
