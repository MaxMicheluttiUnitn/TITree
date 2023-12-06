#ifndef _TURQUOISE_INDIGO_EXCEPTIONS_H__
#define _TURQUOISE_INDIGO_EXCEPTIONS_H__

#include <exception>
#include <string>

class ItemNotFoundException:public std::exception
{
    std::string what_message;
    
    public:
    ItemNotFoundException(std::string msg) noexcept: std::exception(){
        this->what_message = msg;
    }

    virtual ~ItemNotFoundException() noexcept = default;

    virtual const char* what() const throw(){
        return what_message.c_str();
    }
};

class KeyAlreadyPresentException:public std::exception
{
    std::string what_message;
    
    public:
    KeyAlreadyPresentException(std::string msg) noexcept: std::exception(){
        this->what_message = msg;
    }

    virtual ~KeyAlreadyPresentException() noexcept = default;

    virtual const char* what() const throw(){
        return what_message.c_str();
    }
};

class SetItemNotFoundException:public std::exception
{
    std::string what_message;
    
    public:
    SetItemNotFoundException(std::string msg) noexcept: std::exception(){
        this->what_message = msg;
    }

    virtual ~SetItemNotFoundException() noexcept = default;

    virtual const char* what() const throw(){
        return what_message.c_str();
    }
};

class ValueAlreadyPresentException:public std::exception{
    std::string what_message;
    
    public:
    ValueAlreadyPresentException(std::string msg) noexcept: std::exception(){what_message = msg;}

    virtual ~ValueAlreadyPresentException() noexcept =default;
    
    virtual const char* what() const throw(){
        return what_message.c_str();
    }
};

class MemoryException:public std::exception{
    std::string what_message;
    
    public:
    MemoryException(std::string msg) noexcept: std::exception(){what_message = msg;}

    virtual ~MemoryException() noexcept =default;
    
    virtual const char* what() const throw(){
        return what_message.c_str();
    }
};

#endif