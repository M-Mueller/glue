#ifndef GLUTILS_H
#define GLUTILS_H

class GlProgram;

namespace GlUtils
{
    /**
     * \brief The bind_guard class provides a convenvient RAII-style mechanism for binding and unbinding a OpenGL object.
     * The bind() method of the OpenGL object will be called when the bind_guard is constructed and
     * will be automatically unbind if the bind_guard object goes out of scope.
     */
    template<class T>
    class bind_guard
    {
    public:
        explicit bind_guard(T& object):
            _object(object)
        {
            _object.bind();
        }

        ~bind_guard()
        {
            _object.release();
        }

        bind_guard(const bind_guard&) =delete;
        bind_guard& operator=(const bind_guard&) =delete;

    private:
        T& _object;
    };
};

#endif // GLUTILS_H
