#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template <typename T>
class Singleton
{
public:
    static T& Instance() {
        static T staticInstance;

        return staticInstance;
    }
};

#define SINGLETON_CLASS(clas) friend class Singleton<clas>

#endif // SINGLETON_HPP
