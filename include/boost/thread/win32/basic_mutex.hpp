#ifndef BOOST_BASIC_MUTEX_WIN32_HPP
#define BOOST_BASIC_MUTEX_WIN32_HPP

//  basic_mutex_win32.hpp
//
//  (C) Copyright 2006 Anthony Williams 
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/detail/interlocked.hpp>
#include <boost/thread/win32/thread_primitives.hpp>
#include <boost/thread/win32/interlocked_read.hpp>

namespace boost
{
    namespace detail
    {
        struct basic_mutex
        {
            long active_count;
            void* semaphore;

            void initialize()
            {
                active_count=0;
                semaphore=0;
            }

            void destroy()
            {
                void* const old_semaphore=BOOST_INTERLOCKED_EXCHANGE_POINTER(&semaphore,0);
                if(old_semaphore)
                {
                    BOOST_CLOSE_HANDLE(old_semaphore);
                }
            }
            
          
            bool try_lock()
            {
                return !BOOST_INTERLOCKED_COMPARE_EXCHANGE(&active_count,1,0);
            }
            
            void lock()
            {
                if(BOOST_INTERLOCKED_INCREMENT(&active_count)!=1)
                {
                    BOOST_WAIT_FOR_SINGLE_OBJECT(get_semaphore(),BOOST_INFINITE);
                }
            }

            long get_active_count()
            {
                return ::boost::detail::interlocked_read(&active_count);
            }

            void unlock()
            {
                if(BOOST_INTERLOCKED_DECREMENT(&active_count)>0)
                {
                    BOOST_RELEASE_SEMAPHORE(get_semaphore(),1,0);
                }
            }

            bool locked()
            {
                return get_active_count()>0;
            }
            
        private:
            void* get_semaphore()
            {
                void* current_semaphore=::boost::detail::interlocked_read(&semaphore);
                
                if(!current_semaphore)
                {
                    void* const new_semaphore=BOOST_CREATE_SEMAPHORE(0,0,1,0);
                    void* const old_semaphore=BOOST_INTERLOCKED_COMPARE_EXCHANGE_POINTER(&semaphore,new_semaphore,0);
                    if(old_semaphore!=0)
                    {
                        BOOST_CLOSE_HANDLE(new_semaphore);
                        return old_semaphore;
                    }
                    else
                    {
                        return new_semaphore;
                    }
                }
                return current_semaphore;
            }
            
        };
        
    }
}

#define BOOST_BASIC_MUTEX_INITIALIZER {0}

#endif
