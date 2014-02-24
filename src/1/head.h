#pragma once

#ifndef HEAD_H
#define HEAD_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>

template<class T> class Arr2D final // Or use Locker friend
{
    public:
        friend class Meth2DPareto;
        friend class Meth2DSleyter;
        friend class Meth;

        Arr2D(){}

        ~Arr2D() //Or virtual if not final class
        {
            arrData.clear();
        }

        // Or template<class T> void Arr2D<T>::init
        // inline here is default
        auto init(const std::vector<T>& x, const std::vector<T>& y) -> void
        {
            arrData.clear();

            if(x.size() != y.size())
                return;
            if((x.empty() == true) || (y.empty() == true))
                return;

            sizeArr = x.size();
            for(size_t i = 0; i < sizeArr; ++i)
            {
                arrData.push_back(std::make_pair(x[i], y[i]));
            }
        }

        // Or use Private section
        Arr2D(Arr2D&& a) = delete;
        Arr2D& operator=(Arr2D&& a) = delete;
        Arr2D(const Arr2D& a) = delete;
        Arr2D& operator=(const Arr2D& a) = delete;

    private:
        std::vector<std::pair<T, T>> arrData;

        size_t sizeArr = 0;
};

class Meth
{
    public:
        void make(const Arr2D<int>& arr)
        {
            init(arr.sizeArr);
            int result = 0;
            for(size_t i = 0; i < arr.sizeArr - 1; ++i)
            {
                for(size_t j = i + 1; j < arr.sizeArr; ++j)
                {
                    result = comp(arr.arrData[i], arr.arrData[j]);
                    if(result == 1)
                    {
                        res[j] = i;
                    }
                    if(result == 2)
                    {
                        res[i] = j;
                    }
                }
            }

            write(arr);
        }

        virtual ~Meth()
        {
            res.clear();
        }

    protected:
        auto init(const size_t& k) -> void
        {
            res.clear();
            for(size_t i = 0; i < k; ++i)
            {
                res.push_back(NoN);
            }
        }

        auto write(const Arr2D<int>& arr) -> void
        {
            std::cout << std::endl << writeName();
            std::cout << std::endl << "Q1 = ";
            for(size_t i = 0; i < arr.sizeArr; ++i)
                std::cout << std::setw(3) << arr.arrData[i].first;
            std::cout << std::endl << "Q1 = ";
            for(size_t i = 0; i < arr.sizeArr; ++i)
                std::cout << std::setw(3) << arr.arrData[i].second;

            std::cout << std::endl << "R  = ";
            //std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, ""));
            std::vector<int>::iterator i;
            for(i = res.begin(); i < res.end(); ++i)
                if(*i == NoN)
                    std::cout << std::setw(3) << " ";
                else
                    std::cout << std::setw(3) << *i;

            std::cout << std::endl <<"Result:";
            //std::vector<int>::iterator i;
            for(size_t i = 0; i < res.size(); ++i)
                if(res[i] == NoN)
                    std::cout << " A[" << i << "](" <<arr.arrData[i].first
                        << "," <<arr.arrData[i].second << ")  ";
            std::cout << std::endl;
        }

        virtual std::string writeName() = 0;

        virtual int comp(const std::pair<int, int>& px, const std::pair<int, int>& py) = 0;

        const int NoN = -1;
        std::vector<int> res;
};

class Meth2DPareto : public Meth
{
    public:
        Meth2DPareto(){}

        Meth2DPareto(Meth2DPareto&& a) = delete;
        Meth2DPareto& operator=(Meth2DPareto&& a) = delete;
        Meth2DPareto(const Meth2DPareto& a) = delete;
        Meth2DPareto& operator=(const Meth2DPareto& a) = delete;

        ~Meth2DPareto()
        {
            // Only elements clear, not capacity
            res.clear();
        }

    private:
        std::string writeName() override
        {
            return "Pareto: ";
        }

        int comp(const std::pair<int, int>& px, const std::pair<int, int>& py) override
        {
            // && smart compare
            if((px.first == py.first) && (px.second == py.second))
               return 0;
            if((px.first >= py.first) && (px.second >= py.second))
               return 1;
            if((py.first >= px.first) && (py.second >= px.second))
               return 2;
            return 0;
        }
};

class Meth2DSleyter : public Meth
{
    public:
        Meth2DSleyter(){}

        Meth2DSleyter(Meth2DSleyter&& a) = delete;
        Meth2DSleyter& operator=(Meth2DSleyter&& a) = delete;
        Meth2DSleyter(const Meth2DSleyter& a) = delete;
        Meth2DSleyter& operator=(const Meth2DSleyter& a) = delete;

        ~Meth2DSleyter()
        {
            // Only elements clear, not capacity
            res.clear();
        }

    private:
        std::string writeName() override
        {
            return "Sleyter: ";
        }

        int comp(const std::pair<int, int>& px, const std::pair<int, int>& py) override
        {
            // && smart compare
            if((px.first > py.first) && (px.second > py.second))
               return 1;
            if((py.first > px.first) && (py.second > px.second))
               return 2;
            return 0;
        }
};


// Singleton
class Manage final
{
    public:
        static const Manage& Instance()
        {
                static Manage theSingleInstance;
                return theSingleInstance;
        }

        void operator() (const Arr2D<int>& arr, Meth* meth) const
        {
            meth->make(arr);
        }

    private:
        Manage(){};
        Manage(const Manage& root);
        Manage& operator=(const Manage&);
        Manage(Manage&& a);
        Manage& operator=(Manage&& a);
};

#endif // HEAD_H

