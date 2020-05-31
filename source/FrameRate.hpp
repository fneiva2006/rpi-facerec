/*
    File Name: FrameRate.hpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "FrameRate Calculator" on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/


#ifndef FRAMERATE_HPP
#define FRAMERATE_HPP

#include <iostream>
#include <time.h>
#include <thread>

using namespace std;

class FrameRate
{
    private:
        thread* m_fps_th = NULL;
        int m_fps, m_frame_counter;

        void fps_display(bool print)
        {
            time_t start = time(0), finish;

            while(1)
            {
                finish = time(0);

                if (m_frame_counter == -1) return;

                if( difftime(finish, start) >= 1)
                {
                    start = time(0);
                    m_fps = m_frame_counter;
                    if(print)
                    {
                        cout << format("\rAverage FPS = %3i\t\r",m_fps);
                        cout.flush();
                    }
                    m_frame_counter = 0;
                }
            }
        }

    public:
        FrameRate()
        {
            m_fps = 0; m_frame_counter = 0;
        }

        void start(bool disp = true)
        {
            m_fps = 0;
            m_frame_counter = 0;
            //if(m_fps_th == NULL)
            m_fps_th =  new thread(&FrameRate::fps_display,this,disp);
        }

        void stop()
        {
            m_frame_counter = -1;
            m_fps_th->join();
            delete m_fps_th;
        }

        void count_frame()
        {
            m_frame_counter++;
        }

        int getFps()
        {
            return m_fps;
        }
};

#endif
