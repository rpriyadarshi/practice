//
//  factory.hpp
//  graphs
//
//  Created by Rohit Priyadarshi on 2/22/19.
//  Copyright © 2019 Rohit Priyadarshi. All rights reserved.
//

#ifndef factory_hpp
#define factory_hpp

////////////////////////////////////////////////////////////////////////////////
namespace adt {
    
    ////////////////////////////////////////////////////////////////////////////
    class factory {
    public: // Constructors/destructors
        factory();
        ~factory();
        
    public: // create
        template<typename T>
        T* create(T& t, std::allocator<T>& a);
        template<typename T>
        T* create(T& t);

    public: // destroy
        template<typename T>
        void destroy(T* ptr, std::allocator<T>& a);
        template<typename T>
        void destroy(T* ptr);
        
    public: // accessors
        template<typename T>
        static std::allocator<T>& alloc() { return m_alloc<T>; }

    private:
        template <typename T>
        static std::allocator<T> m_alloc;
    };

    ////////////////////////////////////////////////////////////////////////////
    template <typename T>
    std::allocator<T> factory::m_alloc;
    
    ////////////////////////////////////////////////////////////////////////////
    template<typename T>
    T* factory::create(T& t, std::allocator<T>& a) {
        T* ptr = a.allocate(1);
        a.construct(ptr, t);
        return ptr;
    }
    
    template<typename T>
    T* factory::create(T& t) {
        return create(t, alloc<T>());
    }
    
    template<typename T>
    void factory::destroy(T* ptr, std::allocator<T>& a) {
        a.deallocate(ptr, 1);
    }
    
    template<typename T>
    void factory::destroy(T* ptr) {
        destroy(ptr, alloc<T>());
    }

};

#endif /* factory_hpp */
